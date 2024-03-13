#include <iostream>
#include <string>
#include <filesystem>
#include <WinSock2.h>
#include <cassert>
#include <vector>
#include <algorithm>
#include <fstream>

#pragma comment(lib, "Ws2_32.lib")


using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::vector;
using std::reverse;
using std::ifstream;

using bite_t = char;

#pragma once
class Sender
{
private:
	WSADATA wsa;

	// to socket
	string ip;
	int port;
	sockaddr_in recv_info;

	// from socket
	int send_socket;

	// file info
	string file_name;
	string file_path;
	vector<bite_t> file_bin;



public:

	Sender(string file);

	~Sender();

	void set_file(string file_path);

	void send_file();

	void set_ip_port(string ip, int port);

private:

	void _connect();

	int _get_file_size();

	void _set_file_name();

	void _read_file_in_bin();

	void _create_socket();

	void _send_file_size();

	void _send_file_name();

	void _send_file_bin();

	// tmp

public:

	void show_buffer();

};