#pragma once
#include<iostream>
#include<fstream>
#include<windows.h>
#include<string>
#include <io.h>
#include <fcntl.h>
#include <locale>
#include <codecvt>
#include"Compress.h"

using namespace std;

//Chế độ nhập và xuất UTF8
//_setmode(_fileno(stdin), _O_U8TEXT);
//_setmode(_fileno(stdout), _O_U8TEXT);

wstring StringToWideString(string str);
string WidestringToString(wstring wstr);