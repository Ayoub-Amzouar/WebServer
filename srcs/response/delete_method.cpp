#include "../../headers/webserv.hpp"

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
			// call cgi for Delete 
			return (-42);
		}
		else
		{
			if (perms.w_perm == false)
				// 403 Forbidden
				return (403);
			else if (system(("rm -rf " + uri + " 2>/dev/null").c_str()) != 0)
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

static int		resource_type_is_file( const std::string &uri, const Location &location )
{
	if (Utils::is_location_has_cgi(location, uri, FT_FILE))
		// call cgi for Delete 
		return (-42);
	if (remove(uri.c_str()) < 0)
		return (403);
	// 204 No Content
	return (204);
}

std::string		Response::delete_method(const ErrorPage&err_page, const Location &location, const std::map<std::string, std::string> &request, const std::string &body_file)
{
	std::string		uri	= Utils::give_me_uri(location, request);
	file_stats		stats = Utils::get_file_stats(uri);
	int				status_code;

	if (stats.exist == 0)
		// 404 Not Found
		return (err_page.get_page(404));
	else if (stats.type == FT_DIR)
		status_code = resource_type_is_directory(uri, location, stats);
	else
		status_code = resource_type_is_file(uri, location);

	if (status_code == -42)
		return Utils::run_cgi(location, request, body_file, uri);

	if (status_code != 204)
		return (err_page.get_page(status_code));
	return (Utils::status_line(204) + "\n\n");
}