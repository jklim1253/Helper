#pragma once
#include "Helper_define.h"

struct HELPER_API Instruction {
	virtual int execute() = 0;
};

class ThreadHelperImpl;
class HELPER_API ThreadHelper {
public :
	ThreadHelper();
	ThreadHelper(Instruction* ins);

	void run();
	void run(Instruction* ins);

	void stop(DWORD exitcode = 1);

	void wait();
private :
	ThreadHelperImpl* impl;
};