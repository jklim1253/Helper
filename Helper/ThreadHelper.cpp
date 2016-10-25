#include "ThreadHelper.h"
#include <Windows.h>

const DWORD FORCE_EXIT = -1;

Instruction::~Instruction() {}

class ThreadHelperImpl {
public :
    ThreadHelperImpl()
        : instruction(0)
        , handle(0)
        , exit_handler(0)
    {}
    ~ThreadHelperImpl() {
        stop_thread(FORCE_EXIT);
        releaseInstruction();
    }
	Instruction* getInstruction() const {
		return instruction;
	}
    Instruction* getExithandler() const {
        return exit_handler;
    }
	void setInstruction(Instruction* ins) {
        stop_thread(FORCE_EXIT);
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
        if (handle) {
            ::TerminateThread(handle, exitcode);
            ::CloseHandle(handle);
            handle = 0;
        }
	}
	void wait_thread(DWORD dwWaitMilliSecond = INFINITE) {
		::WaitForSingleObject(handle, dwWaitMilliSecond);
        stop_thread(0);
	}
    void releaseInstruction() {
        if (instruction) {
            delete instruction;
            instruction = 0;
        }
        if (exit_handler) {
            delete exit_handler;
            exit_handler = 0;
        }
    }
    void occur_thread_exit(Instruction* handler) {

    }
private :
	static int proc(ThreadHelperImpl* pThis) {
		if (pThis->getInstruction()) {
			pThis->getInstruction()->execute();
		}

        if (pThis->getExithandler()) {
            pThis->getExithandler()->execute();
        }

        pThis->releaseInstruction();
		return 0;
	}
private :
	Instruction* instruction;
    Instruction* exit_handler;
	HANDLE handle;
};

ThreadHelper::ThreadHelper() 
: impl(new ThreadHelperImpl) {
}
ThreadHelper::ThreadHelper(Instruction* ins)
: ThreadHelper() {
	impl->setInstruction(ins);
}
ThreadHelper::~ThreadHelper() {
    if (impl) {
        delete impl;
        impl = 0;
    }
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
ThreadHelper& ThreadHelper::wait(DWORD dwWait/*=INFINITE*/) {
	impl->wait_thread(dwWait);

    return *this;
}
ThreadHelper& ThreadHelper::setcompletionhandler(Instruction* handler) {
    impl->occur_thread_exit(handler);

    return *this;
}