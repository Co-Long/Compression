#include"UnicodeFile.h"

using namespace std;

void FindFile(const wchar_t path[100]) {
	WIN32_FIND_DATA data;
	// Tìm tập tin đầu tiên
	HANDLE hFile = FindFirstFile(path, &data);
	wstring s;

	do {
		//in tên thư mục, tập tin ra màn hình
		wprintf(L"%s\n", data.cFileName);
		//Nếu là thư mục
		if (data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
			////Duyệt tiếp trong thư mục đó
			/*FindFile();*/
		}
		
		//Nếu là tập tin
		if (!(data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
			//Đọc file UTF-8
			/*wifstream in;
			in.open(data.cFileName);
			getline(in, s);
			wcout << s << endl;*/
		}

	} while (FindNextFile(hFile, &data)); // Cho đến khi không còn tập tin kế

	FindClose(hFile);
}
	