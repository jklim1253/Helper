#pragma once

#include "Helper_define.h"
#include "singleton.hpp"
#include <list>

class HELPER_API _DLLHelper : public singleton<_DLLHelper> {
	friend class singleton<_DLLHelper>;
private :
	_DLLHelper();
	~_DLLHelper();
public :
	std::list<std::tstring> EnumDll();
};

#define DLLHelper (_DLLHelper::Reference())