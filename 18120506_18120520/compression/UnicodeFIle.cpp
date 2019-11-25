#include"UnicodeFile.h"

using namespace std;

std::wstring StringToWideString(std::string str)
{
	/*if (str.empty())
	{
		return std::wstring();
	}
	size_t len = str.length() + 1;
	std::wstring ret = std::wstring(len, 0);
#if defined WIN32
	int size = MultiByteToWideChar(CP_UTF8, MB_ERR_INVALID_CHARS, &str[0], str.size(), &ret[0], len);
	ret.resize(size);
#else
	size_t size = 0;
	_locale_t lc = _create_locale(LC_ALL, "en_US.UTF-8");
	errno_t retval = _mbstowcs_s_l(&size, &ret[0], len, &str[0], _TRUNCATE, lc);
	_free_locale(lc);
	ret.resize(size - 1);
#endif
	return ret;*/

	using convert_typeX = std::codecvt_utf8<wchar_t>;
	std::wstring_convert<convert_typeX, wchar_t> converterX;

	return converterX.from_bytes(str);
}

std::string WidestringToString(std::wstring wstr)
{
	/*if (wstr.empty())
	{
		return std::string();
	}
#if defined WIN32
	int size = WideCharToMultiByte(CP_UTF8, WC_ERR_INVALID_CHARS, &wstr[0], wstr.size(), NULL, 0, NULL, NULL);
	std::string ret = std::string(size, 0);
	WideCharToMultiByte(CP_UTF8, WC_ERR_INVALID_CHARS, &wstr[0], wstr.size(), &ret[0], size, NULL, NULL);
#else
	size_t size = 0;
	_locale_t lc = _create_locale(LC_ALL, "en_US.UTF-8");
	errno_t err = _wcstombs_s_l(&size, NULL, 0, &wstr[0], _TRUNCATE, lc);
	std::string ret = std::string(size, 0);
	err = _wcstombs_s_l(&size, &ret[0], size, &wstr[0], _TRUNCATE, lc);
	_free_locale(lc);
	ret.resize(size - 1);
#endif
	return ret;*/

	using convert_typeX = std::codecvt_utf8<wchar_t>;
	std::wstring_convert<convert_typeX, wchar_t> converterX;

	return converterX.to_bytes(wstr);
}
	