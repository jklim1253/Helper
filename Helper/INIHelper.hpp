#pragma once

#include "Helper_define.h"

class INIHelperImpl;
class HELPER_API INIHelper {
public :
	INIHelper();
	INIHelper(const TCHAR* _filename);
	~INIHelper();

	INIHelper& useFile(const TCHAR* _filename);
	INIHelper& useSection(const TCHAR* _section);

	template<typename T>
	void SetValue(const TCHAR* szKey, const T& value) throw(...) {
		std::tostringstream oss;
		oss << value;

		Write(szKey, oss.str().c_str());
	}
	template<typename T>
	void SetValue(const TCHAR* szSection, const TCHAR* szKey, T value) throw(...) {
		useSection(szSection).SetValue(szKey, value);
	}
	template<typename T>
	void SetValue(const TCHAR* szFileName, const TCHAR* szSection, const TCHAR* szKey, T value) throw(...) {
		useFile(szFileName).SetValue(szSection, szKey, value);
	}
	template<typename T>
	T GetValue(const TCHAR* szKey, const T& default_value = T()) throw(...) {
		std::tostringstream oss;
		oss << default_value;
		std::tstring buffer = Read(szKey, oss.str().c_str());

		T ret;
		std::tistringstream iss(buffer);
		iss >> ret;

		return ret;
	}
	template<>
	std::tstring GetValue(const TCHAR* szKey, const std::tstring& default_value) throw(...) {
		std::tostringstream oss;
		oss << default_value;
		std::tstring buffer = Read(szKey, oss.str().c_str());

		return buffer;
	}
	template<typename T>
	T GetValue(const TCHAR* szSection, const TCHAR* szKey, T default_value = T()) throw(...) {
		return useSection(szSection).GetValue(szKey, default_value);
	}
	template<typename T>
	T GetValue(const TCHAR* szFileName, const TCHAR* szSection, const TCHAR* szKey, T default_value = T()) throw(...) {
		return useFile(szFileName).GetValue(szSection, szKey, default_value);
	}
private :
	void Write(const TCHAR* szKey, const TCHAR* szValue) throw(...);
	std::tstring Read(const TCHAR* szKey, const TCHAR* szDefault) throw(...);

private :
	INIHelper(const INIHelper& o); // prevent using copy constructor.
	INIHelper& operator=(const INIHelper& o); // prevent using assign operator.

private :
	INIHelperImpl* impl;
};