#include "../../headers/webserv.hpp"
#include <sys/errno.h>

// function to construct the response message to be sent

bool		is_slash_at_end( std::string uri )
{
	if (uri[uri.size() - 1] == '/')
		return (true);
	return (false);
}

bool		is_location_has_cgi( Location location, std::string uri, bool type )
{
	if (type == FT_DIR)
	{
		if (!Utils::find_in_map(location.attributes, "cgi").empty())
		{
			if (!Utils::find_in_map(location.attributes, "cgi-ext").empty() && !Utils::find_in_map(location.attributes, "index").empty())
			{
				std::vector<std::string>	line_splitted = Utils::parse_line(Utils::find_in_map(location.attributes, "index"), ".");
				std::string 				index_ext = line_splitted[line_splitted.size() - 1];
				if (index_ext == Utils::find_in_map(location.attributes, "cgi-ext"))
					return (true);
			}
		}
	}
	else if (type == FT_FILE)
	{
		if (!Utils::find_in_map(location.attributes, "cgi").empty())
		{
			if (!Utils::find_in_map(location.attributes, "cgi-ext").empty())
			{
				std::vector<std::string>	line_splitted = Utils::parse_line(uri, "/");
				std::string 				file_ext = line_splitted[line_splitted.size() - 1];

				line_splitted = Utils::parse_line(uri, ".");
				file_ext = line_splitted[line_splitted.size() - 1];
				if (file_ext == Utils::find_in_map(location.attributes, "cgi-ext"))
					return (true);
			}
		}
	}
	return (false);
}

int		resource_type_is_directory( std::string uri, Location location, file_stats perms)
{
	if (is_slash_at_end(uri))
	{
		if (is_location_has_cgi(location, uri, FT_DIR))
		{
			std::string	path_2_index = uri + location.attributes["index"];
			file_stats	index_stats = Utils::get_file_stats(path_2_index);
			if (index_stats.exist == 0) {
				// 403 Forbidden
				return (403);
			}
			// call cgi for Delete 
		}
		else
		{
			if (perms.w_perm == false)
				// 403 Forbidden
				return (403);
			else if (system((std::string("rm -rf ") + uri).c_str()) != 0)
				// 500 internal Server Error
				return (500);
			else
				// 204 No Content
				return (204);
		}
	}
	// 409 Conflict
	return (409);
}

int		resource_type_is_file( const std::string &uri, const Location &location )
{
	if (is_location_has_cgi(location, uri, FT_FILE))
	{
		// call cgi for Delete 
	}
	remove(uri.c_str());
	// 204 No Content
	return (204);
}

std::string		delete_method(const ErrorPage&err_page, const Location &location, const std::map<std::string, std::string> &request, const std::string &body_file)
{
	std::string		uri	= Utils::give_me_uri(location, request);
	// std::string		uri	= "/Users/aamzouar/wb_test";
	file_stats		stats = Utils::get_file_stats(uri);
	int				status_code;

	if (stats.exist == 0)
		// 404 Not Found
		status_code = 404;
	else if (stats.type == FT_DIR)
		status_code = resource_type_is_directory(uri, location, stats);
	else
		status_code = resource_type_is_file(uri, location);


	if (status_code != 204)
		return (err_page.get_page(status_code));
	return (Utils::status_line(204) + "\n\n");
}