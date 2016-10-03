#include "stdafx.h"
#include "TimeHelper.h"

_TimeHelper::_TimeHelper() {
}
_TimeHelper::~_TimeHelper() {
}

std::tstring _TimeHelper::now() const {
	SYSTEMTIME st;
	::GetLocalTime(&st);

	TCHAR buffer[20];
	::wsprintf(buffer, _T("%04d-%02d-%02d %02d:%02d:%02d"), 
		st.wYear, st.wMonth, st.wDay,
		st.wHour, st.wMinute, st.wDay);

	return std::tstring(buffer);
}
