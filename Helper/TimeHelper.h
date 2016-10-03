#pragma once

#include "Helper_define.h"
#include "singleton.hpp"

class _TimeHelper : public singleton<_TimeHelper> {
	friend class singleton<_TimeHelper>;
private :
	_TimeHelper();
	~_TimeHelper();

public :
	std::tstring now() const;
};

#define TimeHelper (_TimeHelper::Reference())