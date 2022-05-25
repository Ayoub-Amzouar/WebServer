#include "../../headers/webserv.hpp"
using namespace std;

int main(int argc, char **argv)
{
    if (argc > 1)
    { 
    string line;
    ifstream fin;
 
    fin.open(argv[1]);
 
    // Execute a loop until EOF (End of File)
    while (fin) {
 
        // Read a Line from File
        getline(fin, line);
 
        // Print line in Console
        cout << line << endl;
    }
 
    // Close the file
    fin.close();
 
    return 0;
    }
}