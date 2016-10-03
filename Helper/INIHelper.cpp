#include "INIHelper.hpp"

class INIHelperImpl {
public :
	std::tstring filename() const {
		return _filename;
	}
	void filename(const std::tstring& name) {
		// check name contain drive letter.
		std::tstring::size_type pos = name.find(_T(":\\"));
		if (pos == std::tstring::npos) {
			// set filename to current working directory and name.
			_filename = GetExecutablePath() + _T("\\") + name;
		}
	}
	std::tstring GetExecutablePath() const {
		DWORD allocSize = 16;
		TCHAR* buffer = new TCHAR[allocSize];
		DWORD dwSize;
		do {
			if (buffer) {
				delete[] buffer;
			}
			allocSize *= 2;
			buffer = new TCHAR[allocSize];

			dwSize = ::GetModuleFileName(NULL, buffer, allocSize);
		} while (dwSize >= allocSize);

		std::tstring exepath(buffer);
		delete[] buffer;

		std::tstring::size_type pos = exepath.find_last_of(_T("\\"));
		exepath = exepath.substr(0, pos);

		return exepath;
	}
	std::tstring section() const {
		return _section;
	}
	void section(const std::tstring& sect) {
		_section = sect;
	}
private :
	std::tstring _filename;
	std::tstring _section;
};
INIHelper::INIHelper()
	: impl(new INIHelperImpl)
{
}

INIHelper::INIHelper(const TCHAR* _filename)
	: impl(new INIHelperImpl)
{
	useFile(_filename);
}

INIHelper::~INIHelper()
{
	if (impl) {
		delete impl;
		impl = 0;
	}
}
INIHelper::INIHelper(const INIHelper& o) {
}
INIHelper& INIHelper::operator=(const INIHelper& o) {
	return *this;
}

INIHelper & INIHelper::useFile(const TCHAR * _filename)
{
	impl->filename(_filename);
	return *this;
}

INIHelper & INIHelper::useSection(const TCHAR * _section)
{
	impl->section(_section);
	return *this;
}
void INIHelper::Write(const TCHAR* szKey, const TCHAR* szValue) throw(...) {
	if (impl->filename().empty()) {
		throw std::exception("file did not set.");
	}
	if (impl->section().empty()) {
		throw std::exception("section did not set.");
	}
	BOOL ret = ::WritePrivateProfileString(impl->section().c_str(), szKey, szValue, impl->filename().c_str());
	if (ret == 0) {
		DWORD dwError = ::GetLastError();
		::MessageBox(NULL, _T("Error"), _T("Error"), MB_OK);
	}
}

std::tstring INIHelper::Read(const TCHAR* szKey, const TCHAR* szDefault) throw(...)
{
	DWORD allocSize = 16;
	DWORD dwSize;
	TCHAR* szReturn = 0;
	do {
		if (szReturn) {
			delete[] szReturn;
		}
		allocSize *= 2;
		szReturn = new TCHAR[allocSize];

		dwSize = ::GetPrivateProfileString(impl->section().c_str(), szKey, szDefault, szReturn, allocSize, impl->filename().c_str());
		if (dwSize == 0) {
			// not found key.
			return std::tstring(_T(""));
		}
	} while (dwSize == (allocSize - 1));

	std::tstring ret(szReturn);
	delete[] szReturn;

	return ret;
}