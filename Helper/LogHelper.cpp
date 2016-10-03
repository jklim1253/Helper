#include "LogHelper.h"
#include "AutoUnlocker.hpp"
#include "ThreadHelper.h"
#include "TimeHelper.h"
#include <deque>

class LogHelperImpl {
	struct LogWriteInstruction : public Instruction {
		LogHelperImpl* log_;
		LogWriteInstruction(LogHelperImpl* log) : log_(log) {

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
	bool is_empty() const {
		AutoUnlocker<CRITICAL_SECTION> au(cs);
		return depot.empty();
	}
	void filename(const std::tstring& path) {
		filename_ = path;
	}
	void push(const std::tstring& msg) {
		AutoUnlocker<CRITICAL_SECTION> au(cs);

		SYSTEMTIME now;
		::GetLocalTime(&now);

		depot.push_back(std::make_pair(now, msg));
	}
	std::tstring pop() {
		AutoUnlocker<CRITICAL_SECTION> au(cs);

		auto data = depot.front();
		depot.pop_front();
		return TimeHelper.time(data.first) + _T(" ") + data.second;
	}
private :
	std::tstring filename_;
	std::deque<std::pair<SYSTEMTIME, std::tstring>> depot;
	mutable CRITICAL_SECTION cs;
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
void LogHelper::AddMessage(const std::tstring& msg) {
	(*this)(msg);
}
LogHelper& LogHelper::operator()(const std::tstring& msg) {
	impl->push(msg);

	return *this;
}