#pragma once
#include <jklim.h>
#include <list>

class _DLLHelper : public singleton<_DLLHelper> {
	friend class singleton<_DLLHelper>;
private :
	_DLLHelper();
	~_DLLHelper();
public :
	std::list<std::tstring> EnumDll();
};

#define DLLHelper (_DLLHelper::Reference())