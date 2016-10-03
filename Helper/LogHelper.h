#pragma once

#include "Helper_define.h"

class LogHelperImpl;
class LogHelper {
public :
	LogHelper();
	LogHelper(const std::tstring& path);
	~LogHelper();

	void AddMessage(const std::tstring& msg);
	LogHelper& operator()(const std::tstring& msg);
private :
	LogHelperImpl* impl;
};