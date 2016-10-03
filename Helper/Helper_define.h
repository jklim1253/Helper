#pragma once

#ifdef HELPER_EXPORTS
#define HELPER_API    __declspec(dllexport)
#else
#define HELPER_API    __declspec(dllimport)
#endif // HELPER_EXPORTS

#include <Windows.h>
#include <tchar.h>
#include <string>
#include <sstream>
#include <fstream>

#if defined(UNICODE) || defined(_UNICODE)
#define tstring wstring
#define tostringstream wostringstream
#define tistringstream wistringstream
#define tfstream wfstream
#else
#define tstring string
#define tostringstream ostringstream
#define tistringstream istringstream
#define tfstream fstream
#endif