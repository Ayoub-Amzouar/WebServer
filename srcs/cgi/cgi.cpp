#include "../../headers/webserv.hpp"

static std::string random_file_name()
{
    char buf[] = "/tmp/temp.XXXXXXXXXXX";
    return mktemp(buf);
}

Cgi::Cgi(std::string &cgi_name)
: _cgi_out_file(random_file_name())
, _response_file(random_file_name())
{
    std::string s(getenv("PATH"));
    if (!s.empty()) // ERROR
    {
        std::string del(":");
        std::vector<std::string> paths =  Utils::parse_line(s, del);
        for (std::vector<std::string>::iterator it= paths.begin(); it != paths.end(); it++)
            if (Utils::doesFileExist(*it + "/" + cgi_name))
            {
                _path = *it + "/" + cgi_name;
                break;
            }
    }
    // ERROR:  PATH var empty;
    // ERROR:  _path private var empty;
}

void Cgi::error(std::string e)
{
    std::cerr << "CGI: " << e << std::endl;
}

void Cgi::fileInOut(std::string in_file , std::string out_file)
{
    std::ifstream   in;
    std::ofstream   out;
    std::string     line;

    in.open(in_file);
    out.open(out_file, std::ios::app);
    while (in)
    {
        getline(in, line);
        out << line << std::endl;
    }
    in.close();
    out.close();
}

std::map<std::string, std::string> Cgi::parse_cgi_output(void)
{
    std::fstream f;
    f.open(_cgi_out_file);
    if (!f.is_open())
        error("can't open random file.");
    std::string line;
    std::map<std::string, std::string> data;
    while(f)
    {
        getline(f, line);
        if (line.empty())
            break;
        int pos = line.find(":");
        if (pos != -1)
            data[line.substr(0, pos)] = line.substr(pos + 2);
    }
    f.close();
    return data;
}

int Cgi::execute(std::string body_file)
{
    if (fork() == 0)
    {
        int output_fd, fd;
        if ((output_fd = open(_cgi_out_file.c_str(), O_RDWR | O_TRUNC | O_CREAT, 0666)) == -1)
            error("can't open output_file for cgi.");

        if (!body_file.empty())
        {
            if ((fd = open(body_file.c_str(), O_RDWR)) == -1)
                error("can't open body file for cgi.");
            dup2(fd, STDIN_FILENO);
        }
        dup2(output_fd, STDOUT_FILENO);
        char *args[3];
        args[0] = (char *)_path.c_str();
        args[1] = (char *)_file.c_str();
        args[2] = NULL;
        execv(_path.c_str(), args);
        error("path to cgi executable not correct.");
        exit(1);
    }
    wait(NULL);
    return 0;
}

int Cgi::cgi_status_code(void)
{
    std::map<std::string, std::string> out = parse_cgi_output();
    std::map<std::string, std::string>::iterator it = out.find("Status");
    if (it != out.end())
    {
        const std::string &line = it->second;
        return std::atol(line.substr(0, line.find(" ")).c_str());
    }
    else // default
        return 0;
}

void Cgi::generate_response(int code)
{
    std::ofstream out;
    out.open(_response_file, std::ios::trunc);
    out << Utils::status_line(code) << std::endl;
    std::string file = Utils::fileToStr(_cgi_out_file);
    int found = file.find("\r\n\r\n");
    if (found < 0)
        out << Utils::content_length(0) << std::endl;
    else
        out << Utils::content_length(file.length() - found - 4) << std::endl;
    out.close();
    fileInOut(_cgi_out_file, _response_file);
}
void Cgi::send_response(int fd)
{
    std::ifstream in;
    in.open(_response_file);
    std::string line;
    while (in)
    {
        getline(in, line);
        line.push_back('\n');
        write(fd, line.c_str(), line.length());
    }
    in.close();
}

std::string Cgi::run(const std::map<std::string, std::string> &map)
{
    if (_path.empty())
        return std::string();
    std::string method = Utils::find_in_map(map, "METHOD");
    std::string file = Utils::find_in_map(map, "FILE");
    std::string content_type = Utils::find_in_map(map, "Content-Type");
    std::string content_length = Utils::find_in_map(map, "Content-Length");
    std::string body_file = Utils::find_in_map(map, "BODY_FILE");
    std::string query = Utils::find_in_map(map, "QUERY_STRING");
    std::string cookie = Utils::find_in_map(map, "Cookie");
    std::string host = Utils::find_in_map(map, "Host");
    setenv("QUERY_STRING", query.c_str(), true);
    setenv("REQUEST_METHOD", method.c_str(), true);
    setenv("SCRIPT_FILENAME", file.c_str(), true);
    setenv("REDIRECT_STATUS", "CGI", true);
    setenv("CONTENT_LENGTH", content_length.c_str(), true);
    setenv("CONTENT_TYPE", content_type.c_str(), true);
    setenv("HTTP_COOKIE", cookie.c_str(), true);
    setenv("HTTP_HOST", host.c_str(), true);
    _file = file;
    execute(body_file);
    int cgi_code = cgi_status_code();
    if (cgi_code == 0 && method == "POST") // no status by cgi.
        generate_response((cgi_code == 0) ? 201: cgi_code);
    else if (method == "DELETE")
        generate_response((cgi_code == 0) ? 204: cgi_code);
    else
        generate_response((cgi_code == 0) ? 200: cgi_code);
    return  Utils::fileToStr(_response_file);
}

