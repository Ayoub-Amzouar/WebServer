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

```json
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

| Directive		 | Value			| Description |
| -------------- | ---------------- | ----------- |
| listen		 | ex. 9002			|				|
| host			 | ex. 127.0.0.1	|				|
| server-name 	 | ex. example.com  |				|
| error-pages 	 | Absolute Path    |				|
| max-body-size	 | ex. 1024			|				|
| path			 | ex. /en/docs		|				|
| index			 | ex. index.html	|				|
| root 			 | Absolute Path	|				|
| autoindex 	 |		|				|
| return 		 |		|				|
| methods 		 |		|				|
| cgi 			 |		|				|
| cgi-ext 		 |		|				|
| upload 		 |		|				|


## Collaborators

## Resources