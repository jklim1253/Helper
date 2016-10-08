#include "ThreadHelper.h"
#include <Windows.h>

class ThreadHelperImpl {
public :
	Instruction* getInstruction() const {
		return instruction;
	}
	void setInstruction(Instruction* ins) {
		instruction = ins;
	}
	HANDLE& Handle() {
		return handle;
	}
	void run_thread() {
		DWORD addr;
		handle = ::CreateThread(0, 0, (LPTHREAD_START_ROUTINE)&ThreadHelperImpl::proc, this, 0, &addr);
	}
	void stop_thread(DWORD exitcode) {
		::TerminateThread(handle, exitcode);
	}
	void wait_thread() {
		::WaitForSingleObject(handle, INFINITE);
	}
private :
	static int proc(ThreadHelperImpl* pThis) {
		if (pThis->getInstruction()) {
			return pThis->getInstruction()->execute();
		}

		return 0;
	}
private :
	Instruction* instruction;
	HANDLE handle;
};

ThreadHelper::ThreadHelper() 
: impl(new ThreadHelperImpl) {
}
ThreadHelper::ThreadHelper(Instruction* ins)
: ThreadHelper() {
	impl->setInstruction(ins);
}

void ThreadHelper::run() {
	impl->run_thread();
}
void ThreadHelper::run(Instruction* ins) {
	impl->setInstruction(ins);

	run();
}
void ThreadHelper::stop(DWORD exitcode/*=1*/) {
	impl->stop_thread(exitcode);
}
void ThreadHelper::wait() {
	impl->wait_thread();
}
