#include "../../headers/webserv.hpp"

// std::string erasePathFromUri(std::string &uri, std::string &location_path)
// {
//     uri.erase(0, location_path.length());
//     return uri;
// }

// std::pair<std::string, std::string> parse_uri(std::string uri)
// {
//     int pos;
//     pos = uri.find("?");
//     if (pos == -1)
//         return make_pair(uri, std::string(""));
//     return make_pair(uri.substr(0, pos), uri.substr(pos + 1));
// }

// std::string content_length(size_t size)
// {
//     std::string c("Content-Length: ");
//     return c + std::to_string(size);
// }
//     std::string cut_uri(std::string uri)
// {
//     if (uri.empty())
//         return std::string("");
//     size_t found = uri.find_last_of("/");
//     if (found == std::string::npos)
//         return std::string("");
//     if (uri[found] == *(uri.end() - 1))
//         uri.erase(found, 1);
//     else
//         uri.erase(found + 1, uri.length() - 1);
//     return uri;
// }

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

// bool doesFileExist(const std::string &name)
// {
//     std::ifstream f(name.c_str());
//     return f.good();
// }

// std::string status_line(int code)
// {
//     static const StatusCode s;
//     std::string exist = s.get_message(code);
//     if (!exist.empty())
//     {
//         std::string status("HTTP1.1 ");
//         status.append(std::to_string(code));
//         status.append(" ");
//         status.append(exist);
//         return status;
//     }
//     else
//         return std::string();
// }

StatusCode::StatusCode()
{
    _code[100] = "Continue";
    _code[101] = "Switching Protocols";
    _code[200] = "OK";
    _code[201] = "Created";
    _code[202] = "Accepted";
    _code[203] = "Non-Authoritative Information";
    _code[204] = "No Content";
    _code[205] = "Reset Content";
    _code[206] = "Partial Content";
    _code[300] = "Multiple Choices";
    _code[301] = "Moved Permanently";
    _code[302] = "Found";
    _code[303] = "See Other";
    _code[304] = "Not Modified";
    _code[305] = "Use Proxy";
    _code[307] = "Temporary Redirect";
    _code[400] = "Bad Request";
    _code[401] = "Unauthorized";
    _code[402] = "Payment Required";
    _code[403] = "Forbidden";
    _code[404] = "Not Found";
    _code[405] = "Method Not Allowed";
    _code[406] = "Not Acceptable";
    _code[407] = "Proxy Authentication Required";
    _code[408] = "Request Time-out";
    _code[409] = "Conflict";
    _code[410] = "Gone";
    _code[411] = "Length Required";
    _code[412] = "Precondition Failed";
    _code[413] = "Request Entity Too Large";
    _code[414] = "Request-URI Too Large";
    _code[415] = "Unsupported Media Type";
    _code[416] = "Requested range not satisfiable";
    _code[417] = "Expectation Failed";
    _code[500] = "Internal Server Error";
    _code[501] = "Not Implemented";
    _code[502] = "Bad Gateway";
    _code[503] = "Service Unavailable";
    _code[504] = "Gateway Time-out";
    _code[505] = "HTTP Version not supported";
}

std::string StatusCode::get_message(int code) const
{
    std::map<int, std::string>::const_iterator end = _code.end();
    std::map<int, std::string>::const_iterator exist;
    exist = _code.find(code);
    if (exist != end)
        return exist->second;
    else
        return std::string();
}

std::string content_type(std::string exten)
{
    static const ContentType s;
    std::string exist = s.get_mime(exten);
    if (!exist.empty())
    {
        std::string cntnt_type("Content-Type: ");
        cntnt_type.append(exist);
        return cntnt_type;
    }
    else
        return std::string();
}

std::string ContentType::get_mime(std::string extension) const
{
    std::map<std::string, std::string>::const_iterator end = _code.end();
    std::map<std::string, std::string>::const_iterator exist;
    exist = _code.find(extension);
    if (exist != end)
        return exist->second;
    else
        return std::string();
}

ContentType::ContentType()
{
    _code["txt"]  = "text/plain";
    _code["htm"]  = "text/html";
    _code["html"] = "text/html";
    _code["php"]  = "text/html";
    _code["css"]  = "text/css";
    _code["js"]   = "application/javascript";
    _code["json"] = "application/json";
    _code["xml"]  = "application/xml";
    _code["swf"]  = "application/x-shockwave-flash";
    _code["flv"]  = "video/x-flv";
    _code["png"]  = "image/png";
    _code["jpe"]  = "image/jpeg";
    _code["jpeg"] = "image/jpeg";
    _code["jpg"]  = "image/jpeg";
    _code["gif"]  = "image/gif";
    _code["bmp"]  = "image/bmp";
    _code["ico"]  = "image/vnd.microsoft.icon";
    _code["tiff"] = "image/tiff";
    _code["tif"]  = "image/tiff";
    _code["svg"]  = "image/svg+xml";
    _code["svgz"] = "image/svg+xml";
    _code["zip"]  = "application/zip";
    _code["rar"]  = "application/x-rar-compressed";
    _code["exe"]  = "application/x-msdownload";
    _code["msi"]  = "application/x-msdownload";
    _code["cab"]  = "application/vnd.ms-cab-compressed";
    _code["mp3"]  = "audio/mpeg";
    _code["qt"]   = "video/quicktime";
    _code["mov"]  = "video/quicktime";
    _code["pdf"]  = "application/pdf";
    _code["psd"]  = "image/vnd.adobe.photoshop";
    _code["ai"]   = "application/postscript";
    _code["eps"]  = "application/postscript";
    _code["ps"]   = "application/postscript";
    _code["doc"]  = "application/msword";
    _code["rtf"]  = "application/rtf";
    _code["xls"]  = "application/vnd.ms-excel";
    _code["ppt"]  = "application/vnd.ms-powerpoint";
    _code["odt"]  = "application/vnd.oasis.opendocument.text";
    _code["ods"]  = "application/vnd.oasis.opendocument.spreadsheet";
}

// @@@ ERROR PAGES
// std::string defaultErrPage(int code)
// {
//     static const StatusCode s;
//     std::string exist = s.get_message(code);
//     if (!exist.empty())
//     {
//         std::string status;
//         status.append(std::to_string(code));
//         status.append(" ");
//         status.append(exist);
//         return "<html><head><title>" + status + "</title></head><body><center><h1>" + status + "</h1></center><hr><center>WebServ</center></body></html>";
//     }
//     else
//         return std::string();
// }

// std::string error_page(int code)
// {
//     static const ErrorPage s;
//     std::string exist = s.get_page(code);
//     if (!exist.empty())
//         return exist;
//     else
//         return std::string();
// }
// std::string fileToStr(std::string &fileName)
// {
//     std::ifstream   in;

//     in.open(fileName);
//     std::ostringstream sstr;
//     sstr << in.rdbuf();
//     return sstr.str();
// }
ErrorPage::ErrorPage(std::string error_page_path)
{
    file_stats dir =  Utils::get_file_stats(error_page_path);
    int errors[] = {400, 403, 404, 405, 409, 413, 414, 500};
    std::vector<int> err(errors, errors + sizeof(errors) / sizeof(int));
    for(std::vector<int>::iterator it = err.begin(); it != err.end(); it++)
    {
        std::string file_str(error_page_path + "/" + std::to_string(*it) + ".html");
        file_stats file =  Utils::get_file_stats(file_str);
        std::string response;
        std::string body;
        response.append( Utils::status_line(*it));
        response.append("\n");
        response.append(content_type("html"));
        response.append("\n");
        body = (dir.exist && file.exist && file.perm >= 4) ?  Utils::fileToStr(file_str) :  Utils::defaultErrPage(*it);
        response.append( Utils::content_length(body.size()));
        response.append("\n");
        response.append("\n");
        response.append(body);
        _code[*it] = response;
    }
}

std::string ErrorPage::get_page(int code) const
{
    std::map<int, std::string>::const_iterator end = _code.end();
    std::map<int, std::string>::const_iterator exist;
    exist = _code.find(code);
    if (exist != end)
        return exist->second;
    else
        return std::string();
}

// @@@@ FILE PERMISSION

// file_stats    get_file_stats ( std::string filename )
// {
//     struct stat        fs;
//     int                r;
//     file_stats        res;

//     if (stat(filename.c_str(), &fs) < 0)
//         return (res);

//     res.exist = 1;

//     res.perm = (fs.st_mode & S_IRUSR) ? 4 : 0;
//     res.perm += (fs.st_mode & S_IWUSR) ? 2 : 0;
//     res.perm += (fs.st_mode & S_IXUSR) ? 1 : 0;

//     if (S_ISDIR(fs.st_mode))
//         res.type = FT_DIR;
//     else if (S_ISREG(fs.st_mode))
//         res.type = FT_FILE;

//     return (res);
// }
