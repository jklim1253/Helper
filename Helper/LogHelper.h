#pragma once

#include "Helper_define.h"

class LogHelperImpl;
class HELPER_API LogHelper {
public :
	LogHelper();
	LogHelper(const std::tstring& path);
	~LogHelper();

	LogHelper& setLogFile(const std::tstring& path);

	void AddMessage(const std::tstring& msg);
	LogHelper& operator()(const std::tstring& msg);
private :
	LogHelperImpl* impl;
};
