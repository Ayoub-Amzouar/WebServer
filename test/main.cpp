#include <iostream>
#include <dirent.h>
#include <sys/types.h>

#include <iostream>
#include <ctime>
#include <sys/types.h>
#include <sys/stat.h>
#include <cerrno>
#include <cstring>
#include <string>
#include <vector>
#include "../headers/webserv.hpp"

// using namespace std;
// std::vector<std::string> parse_line(std::string str, std::string delim)
// {
//     std::vector<std::string> strings;
//     size_t pos = 0;
//     std::string token;
//     while ((pos = str.find(delim)) != std::string::npos)
//     {
//         if (pos != 0)
//         {
//             token = str.substr(0, pos);
//             strings.push_back(token);
//         }
//         str.erase(0, pos + delim.length());
//     }
//     if(!str.empty())
//         strings.push_back(str);
//     return strings;
// }

// std::vector<std::string> list_dir(const char *path)
// {
//     struct dirent *entry;
//     DIR *dir = opendir(path);
//     std::vector<std::string> list;

//     if (dir == NULL)
//     {
//         return list;
//     }
//     while ((entry = readdir(dir)) != NULL)
//     {
//         list.push_back(entry->d_name);
//     }
//     closedir(dir);
//     return list;
// }
// int main(int argc, char **argv)
// {
//     std::string dir(argv[1]);
//     std::vector<std::string> files = list_dir(dir.c_str());
//     dir.append("/");
//     if (files.empty())
//         std::cout << "empty list" << std::endl;
//     struct stat fileInfo;

//     for (vector<string>::iterator it = files.begin(); files.end() != it; it++)
//     {
//         std::string tst = dir + *it;
//         if (stat(tst.c_str(), &fileInfo) != 0)
//             std::cerr << "Error: " << strerror(errno) << '\n';
//         // std::cout << ">>>>>>>>" << tst << std::endl;
//         // std::cout << "Size          : " << fileInfo.st_size << '\n';              // Size in bytes
//         std::string timeStr = std::ctime(&fileInfo.st_ctime);        // Creation time
//         // std::cout << timeStr << std::endl;
//         std::vector<std::string> vec = parse_line(timeStr, " ");
//         // for (std::vector<std::string>::iterator it = vec.begin(); vec.end() != it ; it++)
//         //     std::cout << *it << std::endl;
//         std::cout << tst << "     " << vec[2] << "-" << vec[1] << "-" << vec[4] << " " << vec[3] << " " << fileInfo.st_size << std::endl;
//         std::cout << vec[3]  << std::endl;;

//         // char str[100];
//         // strftime(str, 50, "Today is %B %d, %Y", (time_t)&fileInfo.st_ctimespec.tv_sec );
//         // std::cout << str << std::endl;
//     }
// }
// // #include <ctime>
// // #include <iostream>
// // using namespace std;

// // int main()
// // {
// // 	time_t curr_time;
// // 	tm * curr_tm;
// // 	char date_string[100];
// // 	char time_string[100];
	
// // 	time(&curr_time);
// // 	curr_tm = localtime(&curr_time);
	
// // 	strftime(time_string, 50, "Current time is %T", curr_tm);
	
// // 	cout << date_string << endl;
// // 	cout << time_string << endl;
	
// // 	return 0;
// // }

#include <iostream>
#include <string>
#include <sstream>
#include "../headers/webserv.hpp"
using namespace std;

// int main() {
//   string str = "/test/youssef/noam";

//   // replace "come" of "Welcome" with "abcd".
//   // starting position = 3, length = 4, 
//   // replacement string = "abcd"
//   int found = str.find("/test")
//   str.replace(3,4,"abcd");
//   cout << str << endl;

//   return 0;
// }
std::string get_msg(int cod)
{
    std::string status;
    status.append(std::to_string(cod));
    status.append(" ");
    status.append(std::to_string(cod));
    return status + "test";
}
int main(int ac, char **av)
{
    // std::ifstream t("file.txt");
    // std::stringstream buffer;
    // buffer << t.rdbuf();
    // std::cout << buffer.str() << std::endl;
    // std::cout << defaultErrPage(400) << std::endl;
    // std::cout << content_length(10) << std::endl;
    // ErrorPage err("/Users/ynoam/Desktop/WebServer/srcs/response//");

    // std::cout << err.get_page(404) << std::endl;
    Http http = parsing(av[1]);
    std::map<std::string, std::string> headers;
    headers["location"] = "/";
    headers["method"] = "GET";
    headers["method"] = "GET";
    std::string file("lkjlkjlk");
    Response res(http);
    std::cout << res.run(headers, file) << std::endl;
}