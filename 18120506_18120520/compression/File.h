#pragma once
#include<iostream>
#include<fstream>
#include<windows.h>
#include<string>
#include <direct.h>
#include <boost/filesystem.hpp>
#include"Compress.h"

//Chế độ nhập và xuất UTF8
//_setmode(_fileno(stdin), _O_U8TEXT);
//_setmode(_fileno(stdout), _O_U8TEXT);

using namespace std;

void info(const boost::filesystem::path& relative_path);