#pragma once
#include "Helper_define.h"

struct HELPER_API Instruction {
    virtual ~Instruction();
	virtual int execute() = 0;
};

class ThreadHelperImpl;
class HELPER_API ThreadHelper {
public :
	ThreadHelper();
	ThreadHelper(Instruction* ins);
    ~ThreadHelper();

	ThreadHelper& run();
	ThreadHelper& run(Instruction* ins);

	ThreadHelper& stop(DWORD exitcode = 1);

	ThreadHelper& wait(DWORD dwWait = INFINITE);

    ThreadHelper& setcompletionhandler(Instruction* handler);
private :
	ThreadHelperImpl* impl;
};