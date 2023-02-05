# WebServ

## Project Overview

Webserv is a school project made by group of school mates, the purpose of it was to implement a simple HTTP server inspired by **Nginx** that runs **HTTP 1.1** version, it can server a fully static website, upload files through it and can also handle multiple clients at the same time as well as listen to multiple ports. You can provide the server with a configuration file to direct its behavior.

> :memo: **Note:** The project was fully written in **C++ 98** programming language.

## What I Learned

I was responsible for socket programming and some HTTP response duties.

- Learned to setup sockets of type Stream Sockets, which enables reliable two-way communication streams of two connected programs.
- Learned to do Synchronous I/O Multiplexing using `poll()` function, which basically let us handle mutiple clients and requests at the same time.
- Learned how to implement `POST` & `DELETE` HTTP methods.

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

> :memo: **Note:** Try to play with already existing config files in `./tests/configfiles/` or script files in `./tests/scripts/`.

### Configuration File

As I said before our web server was inspired by nginx so our configuration file, we used so called [Directives](https://docs.nginx.com/nginx/admin-guide/basic-functionality/managing-configuration-files/) to specify server options.

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

| Server Directives		| Required	| Value										| Description													 		|
| --------------------- | --------- | ----------------------------------------- | --------------------------------------------------------------------- |
| listen				| true		| ex. 9002									| The port you want the server to accept requests from.			 		|
| host					| true		| ex. 127.0.0.1						 		| The host IP address you want the server to accept requests from. 		|
| server-name 			| true		| ex. example.com  					 		| Sets names of a virtual server.								 		|
| error-pages 			| false		| ex. /../../../../tests/scripts			| The absolute path to a directory containing custom HTML error pages.	|
| max-body-size			| false		| ex. 1024									| Sets the maximum allowed size of the client request body.				|


| Location Directives	| Required	| Value										| Description													 		|
| --------------------- | --------- | ----------------------------------------- | --------------------------------------------------------------------- |
| path					| true		| ex. /en/docs							 	| Sets the routes for example http://domain-name/en/docs				|
| index					| true		| ex. index.html						 	| Defines the file that will be used as an index.						|
| root 					| true		| Absolute Path						 		| Sets the root directory for requests.									|
| autoindex 			| true		| `on` or `off`								| Enables or disables the directory listing output.						|
| return 				| false		| `307` or `301` \| https://www.facebook.com| Stops processing and returns the specified code to a client.			|
| methods 				| false		| ex. DELETE, POST, GET						| Sets allowed HTTP methods for a specific route.						|
| cgi 					| false		| ex. php-cgi								| Sets CGI name.														|
| cgi-ext 				| false		| ex. php									| Sets file extension that a specific CGI can accept as an input.		|
| upload 				| false		| `upload`									| Sets the route for uploading.											|

Here's an example of a valid configuration file.

```html
<HTTP>
	<server>
		error-pages=/home/USERNAME/Desktop/webserv/tests/scripts
		max-body-size=4000000
		listen=9002
		host=127.0.0.1
		server-name=example.com
		<location>
			path=/
			index=index.html
			root=/home/USERNAME/Desktop/webserv/tests/scripts/site/Graphic
			return=307 | https://www.facebook.com
			methods=DELETE, POST, GET
			autoindex=on
			cgi=php-cgi
			cgi-ext=php
		<location>
		<location>
			path=/upload
			index=index.html
			root=/home/USERNAME/Desktop/webserv/tests/scripts/site/Graphic
			upload=upload
		<location>
	<server>
<HTTP>
```

> :memo: **Note:** The project has been tested both in 🍏 **macOS** and 🐧 **Linux** machines.

## Collaborators

- [Youssef Noam](https://github.com/yssefnoam)
- [El Hadjaoui Mohamed](https://github.com/elhadjaoui)

## Resources

#### HTTP Theory Stuff:
- [Transport Layer | OSI Model](https://www.techopedia.com/definition/9760/transport-layer)
- [The HTTP Server Explained](https://medium.com/@gabriellamedas/the-http-server-explained-c41380307917)
- [HTTP Messages](https://developer.mozilla.org/en-US/docs/Web/HTTP/Messages)
- [List of RFCs](https://en.wikipedia.org/wiki/List_of_RFCs)

#### Socket Programming:
- [Beej's Guide to Network Programming](https://beej.us/guide/bgnet/html/)
- [SOCKETS - SERVER & CLIENT](https://bogotobogo.com/cplusplus/sockets_server_client.php)
- [Socket Programming in C/C++](https://www.geeksforgeeks.org/socket-programming-cc/)

#### HTTP Server Components:
- [HTTP Server: Everything you need to know to Build a simple HTTP server from scratch](https://medium.com/from-the-scratch/http-server-what-do-you-need-to-know-to-build-a-simple-http-server-from-scratch-d1ef8945e4fa)
- [Simple Http Web Server in Linux using C/C++ from Scratch](https://github.com/Dungyichao/http_server)
- [HTTP request parser in C](https://codereview.stackexchange.com/questions/188384/http-request-parser-in-c)
- [How does HTTP Deliver a Large File?](https://cabulous.medium.com/how-http-delivers-a-large-file-78af8840aad5)

#### Other:
- [Understanding the Nginx Configuration File Structure and Configuration Contexts](https://www.digitalocean.com/community/tutorials/understanding-the-nginx-configuration-file-structure-and-configuration-contexts)
- [Chapter 3: CGI Environment Variables](http://www.cgi101.com/book/ch3/text.html)
- [Load Testing Web Servers with Siege](https://www.linode.com/docs/guides/load-testing-with-siege/)
