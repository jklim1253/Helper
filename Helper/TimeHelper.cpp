#include "TimeHelper.h"

_TimeHelper::_TimeHelper() {
}
_TimeHelper::~_TimeHelper() {
}

std::tstring _TimeHelper::now() const {
	SYSTEMTIME st;
	::GetLocalTime(&st);

	return this->time(st);
}
std::tstring _TimeHelper::time(SYSTEMTIME st) const {
	TCHAR buffer[50];
	::wsprintf(buffer, _T("%04d-%02d-%02d %02d:%02d:%02d:%03d"), 
		st.wYear, st.wMonth, st.wDay,
		st.wHour, st.wMinute, st.wSecond, st.wMilliseconds);

	return std::tstring(buffer);
}
