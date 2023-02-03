# WebServ

## Project Overview

Webserv is a school project made by group of school mates, the purpose of it was to implement a simple HTTP server inspired by **Nginx** that runs **HTTP 1.1** version, it can server a fully static website, upload files through it and can also handle multiple clients at the same time as well as listen to multiple ports. You can provide the server with a configuration file to direct its behavior.

> The project was fully written in C++ 98 programming language.

## What I've Learned

I was responsible for socket programming and some HTTP response duties.

- Learned to setup sockets of type Stream Sockets, which enables reliable two-way communication streams of two connected programs.
- Learned to do Synchronous I/O Multiplexing using `poll()` function, which basically let us handle mutiple clients and requests at the same time.
- Learned how to implement POST & DELETE HTTP methods.

## How to Use

Run make to compile all necessary files.

```console
make
```

Then run the executable `webserv` with a configuration file.

```console
./webserv [configfile]
```

And that's it you have a running Web Server.

> Try to play with already existing config files in `./tests/configfiles/`.

### Configuration File

As I said before our web server was inspired from nginx so our configuration file, we used so called [Directives](https://docs.nginx.com/nginx/admin-guide/basic-functionality/managing-configuration-files/) to specify server options.

First and foremost the mandatory directives which are of type group directives.

```html
<HTTP>
	// HTTP holds all virtual servers
	<server>
		// configuration of HTTP virtual server 1  
		<location>
			path=/one
			// configuration for processing URIs starting with '/one'
		<location>
	<server>
	<server>
		// configuration of HTTP virtual server 2  
		<location>
			path=/two
			// configuration for processing URIs starting with '/two'
		<location>
	<server>
<HTTP>
```

| Server Directive	| Required	| Value									| Description													 		|
| ----------------- | --------- | ------------------------------------- | --------------------------------------------------------------------- |
| listen			| true		| ex. 9002								| The port you want the server to accept request from.			 		|
| host				| true		| ex. 127.0.0.1						 	| The host IP address you want the servert to accept requst from. 		|
| server-name 		| true		| ex. example.com  					 	| Sets names of a virtual server.								 		|
| error-pages 		| false		| ex. /../../../../tests/scripts		| The absolute path to a directory containing custom HTML error pages.	|
| max-body-size		| false		| ex. 1024								| Sets the maximum allowed size of the client request body.				|


| Location Directive	| Required	| Value										| Description													 		|
| --------------------- | --------- | ----------------------------------------- | --------------------------------------------------------------------- |
| path					| true		| ex. /en/docs							 	| Sets the routes for example http://domain-name/**en/docs**			|
| index					| true		| ex. index.html						 	| Defines the file that will be used as an index.						|
| root 					| true		| Absolute Path						 		| Sets the root directory for requests.									|
| autoindex 			| true		| ex. on/off							 	| Enables or disables the directory listing output.						|
| return 				| false		| ex. 307/301 \| https://www.facebook.com	| Stops processing and returns the specified code to a client.			|
| methods 				| false		| ex. DELETE, POST, GET						| Sets allowed HTTP methods for a specific route.						|
| cgi 					| false		| ex. php-cgi								| Sets CGI name.														|
| cgi-ext 				| false		| ex. php									| Sets file extension that a specific CGI can accept.					|
| upload 				| false		| ex. upload								| Sets the route for uploading.											|


## Collaborators

## Resources