#include "../../headers/webserv.hpp"

bool			is_location_support_upload(const Location &location)
{
	if (Utils::find_in_map(location.attributes, "upload").empty() != true)
		return (true);
	return (false);
}

int upload_the_file(const Location &location, std::map<std::string, std::string> request, const std::string &body_file)
{
	std::string		root		= Utils::find_in_map(location.attributes, "root");
	std::string		upload_path = root + '/' + Utils::find_in_map(location.attributes, "upload");
	std::string		content_type = Utils::find_in_map(request, "Content-Type");
	file_stats		stats		= Utils::get_file_stats(upload_path);

	if (stats.exist == false)
	{
		if (mkdir(upload_path.c_str(), 0755) < 0)
			return (500);
	}
	else if (stats.w_perm == false)
		return (403);
	const static ReverseContentType mimes;
	std::vector<std::string> pars = Utils::parse_line(content_type, ";");
	std::string mime = mimes.get_mime(pars[0]);
	std::string file_name = Utils::parse_line(body_file, "/").back();
	file_name += mime.empty() ? "" : ("." + mime);
	if (system(("mv " + body_file + " " + upload_path + "/" + file_name + " 2>/dev/null").c_str()) != 0)
		return (500);
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
			return (-42);
			// call cgi for Post 
		}
		else
			// 403 forbidden
			return (403);
	}
	return (404);
	// 301 moved permanently
	return(301);
}

static int		resource_type_is_file( const std::string &uri, const Location &location )
{
	if (Utils::is_location_has_cgi(location, uri, FT_FILE))
	{
		return (-42);
		// call cgi for Delete 
	}
	// 403 Forbidden
	return (403);
}

std::string		Response::post_method(const ErrorPage&err_page, const Location &location, const std::map<std::string, std::string> &request, const std::string &body_file)
{
	std::string		uri		= Utils::give_me_uri(location, request);
	file_stats		stats	= Utils::get_file_stats(uri);
	int				status_code;

	if (is_location_support_upload(location))
	{
		status_code = upload_the_file(location, request,body_file);
	}
	else if (stats.exist == 0)
		// 404 Not Found
		return (err_page.get_page(404));
	else if (stats.type == FT_DIR)
		status_code = resource_type_is_directory(uri, location, stats);
	else
		status_code = resource_type_is_file(uri, location);

	if (status_code == 301)
	{
		std::string red = "301|" + Utils::parse_uri(Utils::find_in_map(request, "location")).first + "/";
		return redirection(red);
	}
	if (status_code == -42)
		return Utils::run_cgi(location, request, body_file, "POST", uri);

	if (status_code != 201)
		return (err_page.get_page(status_code));
	return (Utils::status_line(201) + "\n\n");
}