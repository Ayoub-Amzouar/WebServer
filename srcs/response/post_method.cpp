#include "../../headers/webserv.hpp"

bool			is_location_support_upload(const Location &location)
{
	if (Utils::find_in_map(location.attributes, "upload").empty() != true)
		return (true);
	return (false);
}

int				upload_the_file(const Location &location, const std::string &body_file)
{
	std::string		root		= Utils::find_in_map(location.attributes, "root");
	std::string		upload_path = root + '/' + Utils::find_in_map(location.attributes, "upload");
	file_stats		stats		= Utils::get_file_stats(upload_path);

	if (stats.exist == false)
	{
		if (mkdir(upload_path.c_str(), 0755) < 0)
			return (403);
	}
	else if (stats.w_perm == false)
		return (403);
	// upload the file to this path (upload_path variable)
	return (201);
}

static int		resource_type_is_directory( std::string uri, Location location, file_stats perms)
{
	if (Utils::is_slash_at_end(uri))
	{
		if (Utils::is_location_has_cgi(location, uri, FT_DIR))
		{
			std::string	path_2_index = uri + location.attributes["index"];
			file_stats	index_stats = Utils::get_file_stats(path_2_index);
			if (index_stats.exist == false) {
				// 403 Forbidden
				return (403);
			}
			// call cgi for Post 
		}
		else
			// 403 forbidden
			return (403);
	}
	// 301 moved permanently
	// return(redirection(""));
}

static int		resource_type_is_file( const std::string &uri, const Location &location )
{
	if (Utils::is_location_has_cgi(location, uri, FT_FILE))
	{
		// call cgi for Delete 
	}
	// 403 Forbidden
	return (403);
}

std::string		post_method(const ErrorPage&err_page, const Location &location, const std::map<std::string, std::string> &request, const std::string &body_file)
{
	std::string		uri		= Utils::give_me_uri(location, request);
	file_stats		stats	= Utils::get_file_stats(uri);
	int				status_code;

	if (is_location_support_upload(location))
	{
		status_code = upload_the_file(location, body_file);
	}
	else if (stats.exist == 0)
		// 404 Not Found
		return (err_page.get_page(404));
	else if (stats.type == FT_DIR)
		status_code = resource_type_is_directory(uri, location, stats);
	else
		status_code = resource_type_is_file(uri, location);

	if (status_code != 201)
		return (err_page.get_page(status_code));
	return (Utils::status_line(201) + "\n\n");
}