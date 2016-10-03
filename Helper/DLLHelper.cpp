#include "DLLHelper.h"
#include "TimeHelper.h"

struct _LogHelper : public singleton<_LogHelper> {
	friend class singleton<_LogHelper>;
private :
	_LogHelper(){}
	~_LogHelper(){}
public :
	int Format(LPCTSTR strFormat, ...) {
		return 0;
	}
};

#define Log (_LogHelper::Reference())

_DLLHelper::_DLLHelper() {
}
_DLLHelper::~_DLLHelper() {
}
std::list<std::tstring> _DLLHelper::EnumDll() {
	std::list<std::tstring> dlllist;
	std::tstring strExePath;

	DWORD dwBufferSize = 16;
	LPTSTR strFilePath = 0;
	DWORD dwRet = 0;

	try {
		do {
			if (strFilePath) {
				delete[] strFilePath;
				strFilePath = 0;
			}
			dwBufferSize *= 2;
			strFilePath = new TCHAR[dwBufferSize];
			dwRet = ::GetModuleFileName(0, strFilePath, dwBufferSize);
			if (dwRet == 0) {
				DWORD dwError = ::GetLastError();
				throw std::exception("GetModuleFileName failed.", dwError);
			}
		} while (dwRet == dwBufferSize);

		strExePath = strFilePath;
		delete[] strFilePath;
		strFilePath = 0;

		strExePath = strExePath.substr(0, strExePath.find_last_of(_T("\\")));
	}
	catch (std::exception& e) {
		if (strFilePath) {
			delete[] strFilePath;
			strFilePath = 0;
		}
		Log.Format(_T("%s %s"), TimeHelper.now(), e.what());
	}

	std::tstring strDll(strExePath + _T("\\*.dll"));

	WIN32_FIND_DATA ffd;
	HANDLE handle = ::FindFirstFile(strDll.c_str(), &ffd);
	if (handle == INVALID_HANDLE_VALUE) {
		DWORD dwError = ::GetLastError();
		return dlllist;
	}

	while (::FindNextFile(handle, &ffd)) {
		dlllist.push_back(ffd.cFileName);
	}
	::FindClose(handle);

	return dlllist;
}
