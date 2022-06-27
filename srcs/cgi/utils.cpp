#include "../../headers/webserv.hpp"


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

std::string ReverseContentType::get_mime(std::string extension) const
{
    std::map<std::string, std::string>::const_iterator end = _code.end();
    std::map<std::string, std::string>::const_iterator exist;
    exist = _code.find(extension);
    if (exist != end)
        return exist->second;
    else
        return std::string();
}

ReverseContentType::ReverseContentType()
{
    _code["text/plain"]  = "txt";
    _code["text/html"]  = "htm";
    _code["text/html"] = "html";
    // _code["text/html"]  = "php";
    _code["text/css"]  = "css";
    _code["application/javascript"]   = "js";
    _code["application/json"] = "json";
    _code["application/xml"]  = "xml";
    _code["application/x-shockwave-flash"]  = "swf";
    _code["video/x-flv"]  = "flv";
    _code["image/png"]  = "png";
    _code["image/jpeg"]  = "jpe";
    _code["image/jpeg"] = "jpeg";
    _code["image/jpeg"]  = "jpg";
    _code["image/gif"]  = "gif";
    _code["image/bmp"]  = "bmp";
    _code["image/vnd.microsoft.icon"]  = "ico";
    _code["image/tiff"] = "tiff";
    _code["image/tiff"]  = "tif";
    _code["image/svg+xml"]  = "svg";
    _code["image/svg+xml"] = "svgz";
    _code["application/zip"]  = "zip";
    _code["application/x-rar-compressed"]  = "rar";
    _code["application/x-msdownload"]  = "exe";
    _code["application/x-msdownload"]  = "msi";
    _code["application/vnd.ms-cab-compressed"]  = "cab";
    _code["audio/mpeg"]  = "mp3";
    _code["video/quicktime"]   = "qt";
    _code["video/quicktime"]  = "mov";
    _code["application/pdf"]  = "pdf";
    _code["image/vnd.adobe.photoshop"]  = "psd";
    _code["application/postscript"]   = "ai";
    _code["application/postscript"]  = "eps";
    _code["application/postscript"]   = "ps";
    _code["application/msword"]  = "doc";
    _code["application/rtf"]  = "rtf";
    _code["application/vnd.ms-excel"]  = "xls";
    _code["application/vnd.ms-powerpoint"]  = "ppt";
    _code["application/vnd.oasis.opendocument.text"]  = "odt";
    _code["application/vnd.oasis.opendocument.spreadsheet"]  = "ods";
}

ErrorPage::ErrorPage(std::string error_page_path)
{
    file_stats dir =  Utils::get_file_stats(error_page_path);
    const static int errors[] = {400, 403, 404, 405, 409, 413, 414, 500};
    const static std::vector<int> err(errors, errors + sizeof(errors) / sizeof(int));
    for(std::vector<int>::const_iterator it = err.begin(); it != err.end(); it++)
    {
        std::string file_str(error_page_path + "/" + std::to_string(*it) + ".html");
        file_stats file =  Utils::get_file_stats(file_str);
        std::string response;
        std::string body;
        response.append( Utils::status_line(*it));
        response.append("\n");
        response.append(content_type("html"));
        response.append("\n");
        body = (dir.exist && file.exist && file.r_perm == true) ?  Utils::fileToStr(file_str) :  Utils::defaultErrPage(*it);
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

