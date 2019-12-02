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
	
void PrintFullPath(wchar_t partialPath[100])
{
	wchar_t full[_MAX_PATH];
	if (_wfullpath(full, partialPath, _MAX_PATH) != NULL)
		wprintf(L"Full path is: %s\n", full);
	else
		printf("Invalid path\n"); 
}

void info(const boost::filesystem::path& relative_path)
{
	using namespace boost::filesystem;

	std::cout << "rel path: " << relative_path << '\n';
	std::cout << "cwd: " << current_path() << '\n'; // current working directory
	
	

	const path absolute_path = absolute(relative_path);
	//Thay đổi thư mục làm việc
	//_chdir(const char)
	_chdir("\.."); 
	std::cout << "New cwd: " << current_path() << '\n';
	std::cout << "absolute: " << absolute_path << '\n'
		<< "root dir: " << absolute_path.root_directory() << '\n'
		<< "root path: " << absolute_path.root_path() << '\n'
		<< "parent dir: " << absolute_path.parent_path() << '\n'
		<< "file name: " << absolute_path.filename() << '\n'
		<< "-----------------------------------------------\n";
}