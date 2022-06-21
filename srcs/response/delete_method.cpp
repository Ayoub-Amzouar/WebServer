#include "../../headers/webserv.hpp"

// function to construct the response message to be sent

bool		is_slash_at_end( std::string uri )
{
	if (uri[uri.size() - 1] == "/")
		return (true);
	return (false);
}

bool		is_location_has_cgi( Location location )
{

}

std::string	resource_type_is_directory( std::string uri, Location location)
{
	if (is_slash_at_end(uri)) {
		if (is_location_has_cgi(location)) {

		}
	} else {
		// 409 Conflict
	}
}

std::string	delete_method( const Location &location, const std::map<std::string, std::string> &request )
{
	// std::string		uri	= find_header(location.attribute, "path");
	std::string		uri	= "/Users/aamzouar/wb_test";
	file_stats		stats = get_file_stats(uri);

	if (stats.exist == 0) {
		// 404 Not Found
	} else if (stats.type == FT_DIR) {
		resource_type_is_directory(uri, location);
	} else {
		// resource_type_is_file(uri);
	}

}