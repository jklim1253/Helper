#include "stdafx.h"
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
	LPTSTR strFilePath = NULL;
	DWORD dwRet = 0;

	try {
		do {
			if (strFilePath) {
				delete[] strFilePath;
				strFilePath = NULL;
			}
			dwBufferSize *= 2;
			strFilePath = new TCHAR[dwBufferSize];
			dwRet = ::GetModuleFileName(NULL, strFilePath, dwBufferSize);
			if (dwRet == 0) {
				DWORD dwError = ::GetLastError();
				throw std::exception("GetModuleFileName failed.", dwError);
			}
		} while (dwRet == dwBufferSize);

		strExePath = strFilePath;
		delete[] strFilePath;

		strExePath = strExePath.substr(0, strExePath.find_last_of(_T("\\")));
	}
	catch (std::exception& e) {
		Log.Format(_T("%s %s"), TimeHelper.now(), e.what());
	}

	std::tstring strDll(strExePath + _T("\\*.dll"));

	CFileFind finder;
	if (!finder.FindFile(strDll.c_str())) {
		DWORD dwError = ::GetLastError();
		Log.Format(_T("%s CFileFind::FindFile [%d]"), TimeHelper.now(), dwError);
		finder.Close();
		return dlllist;
	}

	BOOL NoMore = FALSE;
	do {
		NoMore = finder.FindNextFile();
		dlllist.push_back((LPCTSTR)finder.GetFilePath());
	} while (NoMore);

	finder.Close();

	return dlllist;
}
