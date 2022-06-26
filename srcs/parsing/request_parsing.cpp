/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   request_parsing.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-hadj <mel-hadj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 10:54:28 by mel-hadj          #+#    #+#             */
/*   Updated: 2022/06/19 17:16:37 by mel-hadj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/webserv.hpp"

Request::Request(void)
{
}

void parse_request_line(std::map<std::string, std::string> &pair, std::string line)
{
    std::map<std::string, std::string> tmp;
    std::string value1;
    std::string value2;
    size_t pos;

    tmp = Utils::extract_key_value(line, " ");
    value1 = tmp.begin()->first;
    pos = tmp.begin()->second.find(" ");
    value2 = tmp.begin()->second.substr(0, pos);
    pair.insert(std::pair<std::string, std::string>("method", value1));
    pair.insert(std::pair<std::string, std::string>("location", value2));
}

int Request::check_req_validity(const std::map<std::string, std::string> &request)
{
    std::string content_length = Utils::find_in_map(request, "Content-Length");
    std::string content_type = Utils::find_in_map(request, "Content-Type");
    std::string transfer_encoding = Utils::find_in_map(request, "Transfer-Encoding");
    std::string method = Utils::find_in_map(request, "method");
    std::string uri = Utils::find_in_map(request, "location");
    std::string host = Utils::find_in_map(request, "Host");
    {                                                                       // URI
        if (uri.find_first_not_of(ALLOWED_CHARACTERS) != std::string::npos) // 400
            return 400;
        else if (uri.length() > 2048) // 414
            return 414;
    }
    { // POST
        if (method == "POST")
        {
            if (content_type.empty() || content_length.empty() || transfer_encoding.empty())
                return 400;
            else if (transfer_encoding != "chunked")
                return 501;
        }
    }
    { // Host request empty => error
        if (host.empty())
            return 400;
    }
    return 0;
}

void parse_request_body(Request_Data &request, std::string str)
{
    if (request.file_name.empty())
    {
        std::string file_name;
        file_name = Utils::get_file_name_by_time();
        std::ofstream myfile(file_name);
        if (!myfile.is_open())
        {
            std::cout << "Unable to open file!\n";
            exit(1);
        }
        request.file_name = file_name;
        request.file_size = std::stoi(Utils::find_in_map(request.attributes, "Content-Length"));
        request.reading_size = 0;
        request.chunk_size = -1;
        request.first_enter = true;
    }
    std::ofstream myfile;
    myfile.open(request.file_name, std::ios::app);
    if (!myfile.is_open())
    {
        std::cout << "Unable to open file!\n";
        exit(1);
    }
    if (!Utils::find_in_map(request.attributes, "Transfer-Encoding").compare("chunked"))
    {
        int pos;
        request.chunk_string += str;

        if (request.first_enter)
        {
            request.first_enter = false;
            pos = request.chunk_string.find("\r\n");
            if (pos != std::string::npos)
            {
                request.chunk_size = Utils::hexadecimalToDecimal(request.chunk_string.substr(0, pos));
                std::cout << "chunk1 = " << request.chunk_size << "\n";
                request.chunk_string.erase(0, pos + 2);
            }
        }
        if (request.chunk_string.length() >= request.chunk_size)
        {
            std::cout << "*********************************************=\n"
                      << request.chunk_string;
            std::cout << "****************************************************=-------------------------\n";
            myfile <<  request.chunk_string.substr(0, request.chunk_size);
            std::cout << "++++++++++++++++++++++++++++++++=\n"
                      << request.chunk_string.substr(0, request.chunk_size);
            std::cout << "++++++++++++++++++++++++++++++++=-------------------------\n";
            request.chunk_string.erase(0, request.chunk_size + 2);
            // std::cout << "chunk = " << request.chunk_size << "\n";
            // request.chunk_string = request.chunk_string.erase(0, request.chunk_size + 2);
            pos = request.chunk_string.find("\r\n");
            if (pos != std::string::npos)
            {
                request.chunk_size = Utils::hexadecimalToDecimal(request.chunk_string.substr(0, pos));
                if (request.chunk_size == 0)
                {
                    request.is_finished = true;
                    std::cout << "************finished***********\n\n";
                    return;
                }
                request.chunk_string.erase(0, pos + 2);
            }
            else{
                std::cout << "CHECK 000\n";
                request.first_enter = true;
            }
        }
    }
    else
    {
        myfile << str;
        request.reading_size += str.length();
        if (request.reading_size == request.file_size)
            request.is_finished = true;
    }
}

void Request::parse_request(std::string str, Request_Data &request)
{
    ErrorPage static const errorPage("");
    std::map<std::string, std::string> tmp;
    std::string line;
    std::string str1;
    int err_number;

    if (!request.attributes.size())
    {
        int pos = str.find("\n\r");
        str1 = str.substr(0, pos);
        // std::cout << str << std::endl;
        std::stringstream ss(str1);
        while (getline(ss, line))
        {
            line.erase(line.length() - 1);
            parse_request_line(request.attributes, line);
            while (getline(ss, line))
            {
                line.erase(line.length() - 1);
                tmp = Utils::extract_key_value(line, ": ");
                request.attributes.insert(std::pair<std::string, std::string>(tmp.begin()->first, tmp.begin()->second));
            }
        }
        err_number = check_req_validity(request.attributes);
        if (err_number)
        {
            std::cout << err_number << std::endl;
            request.response = errorPage.get_page(err_number);
            request.is_error = true;
        }
        str = str.substr(pos + 3, str.length());
    }
    if (str.length())
    {
        parse_request_body(request, str);
    }
}

void Request::get_request(int accept_fd, Response &response)
{
    Request_Data req;
    char buffer[1024];
    int ready_fd;

    if (accept_fd > 0)
    {
        struct pollfd ufd;

        ufd.fd = accept_fd;
        ufd.events = POLLIN;
        ufd.revents = 0;
        ufds.push_back(ufd);
    }

    if (!ufds.empty())
    {
        bzero(buffer, 1024);
        poll(&ufds[0], ufds.size(), -1);
        for (size_t i = 0; i < ufds.size(); i++)
        {
            if (ufds[i].revents == POLLIN)
            {
                ready_fd = ufds[i].fd;
                int ret = recv(ready_fd, buffer, 1024, 0);
                std::string str(buffer, ret);
                if (ret > 0)
                {

                    if (!request_table.count(ready_fd))
                    {
                        request_table.insert(std::make_pair(ready_fd, req));
                        parse_request(str, request_table[ready_fd]);
                        if (request_table[ready_fd].is_error)
                            std::cout << "------" << request_table[ready_fd].response << std::endl;
                    }
                    else if (!request_table[ready_fd].is_finished)
                    {
                        parse_request(str, request_table[ready_fd]);
                        // std::cout << "------" << request_table[ready_fd].attributes["location"] << std::endl;

                        // request_table[ready_fd].is_finished = true;
                    }
                    if (request_table[ready_fd].is_finished)
                    {
                        std::cout << request_table[ready_fd].file_name << "\n";
                        std::string str = response.run(request_table[ready_fd].attributes, request_table[ready_fd].file_name);
                        std::cout << str << std::endl;
                    }
                }
            }
        }
    }
}