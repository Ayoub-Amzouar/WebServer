#include <string>
#include <iostream>
#include <map>
using namespace std;
// #include <utility>
// int main()
// {
//     std::map<int, std::string> Employees;
//     Employees.insert(std::pair<int, std::string>(101,"john"));
//     Employees.insert(std::pair<int, std::string>(102,"simo"));
//     Employees.insert(std::pair<int, std::string>(103,"lorus"));

//     Employees[105] = "luffy";
//     Employees[107] = "zoro";
//     std::cout << "size of the map is : " << Employees.size() << std::endl;
//     std::cout << "Default Order of value in map:" << std::endl;
//     for (std::map<int, std::string>::iterator iter = Employees.begin(); iter!=Employees.end(); ++iter)
//     {
//         std::cout << (*iter).first << ": " << (*iter).second << std::endl;
//     }

//     std::map<int, std::string>::iterator it = Employees.find(104);
//     if (it != Employees.end())
//         std::cout << std::endl<< "vlaue of key 102 = " << Employees.find(104)->second;
//         std::cout << std::endl<< "map max size is : " << Employees.max_size();

// }

 int main()
{
  multimap<const char*, int> m;

  m.insert(pair<const char* const, int>("a", 1));
  m.insert(pair<const char* const, int>("c", 2));
  m.insert(pair<const char* const, int>("b", 3));
  m.insert(pair<const char* const, int>("b", 4));
  m.insert(pair<const char* const, int>("a", 5));
  m.insert(pair<const char* const, int>("b", 6));

  cout << "Number of elements with key a: " << m.count("a") << endl;
  cout << "Number of elements with key b: " << m.count("b") << endl;
  cout << "Number of elements with key c: " << m.count("c") << endl;

  cout << "Elements in m: " << endl;
  for (multimap<const char*, int>::iterator it = m.begin();
       it != m.end();
       ++it)
   cout << "  [" << (*it).first << ", " << (*it).second << "]" << endl;
   pair<multimap<const char*, int>::iterator, multimap<const char*, int>::iterator> tst = m.equal_range("a");
  for (multimap<const char*, int>::iterator it = tst.first;
       it !=tst.second;
       ++it)
   cout << "  [" << (*it).first << ", " << (*it).second << "]" << endl;

}
