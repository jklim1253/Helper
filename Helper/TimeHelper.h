#pragma once

#include "Helper_define.h"
#include "singleton.hpp"

class HELPER_API _TimeHelper : public singleton<_TimeHelper> {
	friend class singleton<_TimeHelper>;
private :
	_TimeHelper();
	~_TimeHelper();

public :
	std::tstring now() const;
	std::tstring time(SYSTEMTIME st) const;
};

#define TimeHelper (_TimeHelper::Reference())