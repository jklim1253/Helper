#include "LogHelper.h"
#include "AutoUnlocker.hpp"
#include "ThreadHelper.h"
#include "TimeHelper.h"
#include <deque>

class LogHelperImpl {
	struct LogWriteInstruction : public Instruction {
		LogHelperImpl* log_;
		LogWriteInstruction(LogHelperImpl* log) : log_(log) {
			logstream.open(log_->filename(), std::ios_base::app);
            logstream << TimeHelper.now() << " [START]" << std::endl;
		}
		~LogWriteInstruction() {
            logstream << TimeHelper.now() << " [END]" << std::endl;
			logstream.close();
		}
		virtual int execute() {
			while (true) {
				if (log_->is_empty()) {
					continue;
				}

				logstream << log_->pop() << std::endl;
			}

			return 0;
		}
		std::tfstream logstream;
	};
public :
	LogHelperImpl() {
        ::InitializeCriticalSection(&cs_);
    }
	~LogHelperImpl() {
		logThread.wait(1000);
        ::DeleteCriticalSection(&cs_);
	}
	bool is_empty() const {
		AutoUnlocker<CRITICAL_SECTION> au(cs_);
		return depot.empty();
	}
	void filename(const std::tstring& path) {
		filename_ = path;

		logThread.stop();
		logThread.run(new LogWriteInstruction(this));
	}
	std::tstring filename() const {
		return filename_;
	}
	void push(const std::tstring& msg) {
		AutoUnlocker<CRITICAL_SECTION> au(cs_);

		SYSTEMTIME now;
		::GetLocalTime(&now);

		depot.push_back(std::make_pair(now, msg));
	}
	std::tstring pop() {
		AutoUnlocker<CRITICAL_SECTION> au(cs_);

		auto data = depot.front();
		depot.pop_front();
		return TimeHelper.time(data.first) + _T(" ") + data.second;
	}
private :
	std::tstring filename_;
	std::deque<std::pair<SYSTEMTIME, std::tstring>> depot;
	mutable CRITICAL_SECTION cs_;

	ThreadHelper logThread;
};

LogHelper::LogHelper() 
: impl(new LogHelperImpl) {
}
LogHelper::LogHelper(const std::tstring& path) 
: LogHelper() {
	impl->filename(path);
}
LogHelper::~LogHelper() {
	if (impl) {
		delete impl;
		impl = 0;
	}
}
LogHelper& LogHelper::setLogFile(const std::tstring& path) {
	impl->filename(path);

	return *this;
}
void LogHelper::AddMessage(const std::tstring& msg) {
	(*this)(msg);
}
LogHelper& LogHelper::operator()(const std::tstring& msg) {
	impl->push(msg);

	return *this;
}
