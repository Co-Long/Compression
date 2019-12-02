#include"File.h"

void info(const boost::filesystem::path& relative_path)
{
	using namespace boost::filesystem;

	std::cout << "rel path: " << relative_path << '\n';
	std::cout << "cwd: " << current_path() << '\n'; // Thư mục đang làm việc

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