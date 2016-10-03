#pragma once
#include <Windows.h>

struct Instruction {
	virtual int execute() = 0;
};

class ThreadHelperImpl;
class ThreadHelper {
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