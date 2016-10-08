#include "ThreadHelper.h"
#include <Windows.h>

Instruction::~Instruction() {}

class ThreadHelperImpl {
public :
    ThreadHelperImpl() : instruction(0), handle(0) {}
    ~ThreadHelperImpl() {
        releaseInstruction();
    }
	Instruction* getInstruction() const {
		return instruction;
	}
	void setInstruction(Instruction* ins) {
        releaseInstruction();

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
    void releaseInstruction() {
        if (instruction) {
            delete instruction;
            instruction = 0;
        }
    }
private :
	static int proc(ThreadHelperImpl* pThis) {
		if (pThis->getInstruction()) {
			return pThis->getInstruction()->execute();
		}

        pThis->releaseInstruction();
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

ThreadHelper& ThreadHelper::run() {
	impl->run_thread();

    return *this;
}
ThreadHelper& ThreadHelper::run(Instruction* ins) {
	impl->setInstruction(ins);

	return run();
}
ThreadHelper& ThreadHelper::stop(DWORD exitcode/*=1*/) {
	impl->stop_thread(exitcode);

    return *this;
}
ThreadHelper& ThreadHelper::wait() {
	impl->wait_thread();

    return *this;
}
