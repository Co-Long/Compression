#pragma once
#include<iostream>
#include<fstream>
#include<windows.h>
#include<string>
#include <io.h>
#include <fcntl.h>
#include <locale>
#include <codecvt>
#include <conio.h>
#include <stdlib.h>
#include <direct.h>
#include <boost/filesystem.hpp>

#include"Compress.h"

using namespace std;

//Chế độ nhập và xuất UTF8
//_setmode(_fileno(stdin), _O_U8TEXT);
//_setmode(_fileno(stdout), _O_U8TEXT);

struct path_leaf_string
{
	std::string operator()(const boost::filesystem::directory_entry& entry) const
	{
		
		return entry.path().leaf().string();
	}
};

wstring StringToWideString(string str);
string WidestringToString(wstring wstr);
void PrintFullPath(wchar_t partialPath[100]);
void info(const boost::filesystem::path& relative_path); 