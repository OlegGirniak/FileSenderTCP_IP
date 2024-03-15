#pragma once
#include <iostream>
#include <assert.h>
#include <vector>
#include <WinSock2.h>
#include <string>
#include <fstream>  

#pragma comment(lib, "ws2_32.lib")
#pragma warning(disable: 4996)

using bite_t = char;

using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::pair;
using std::move;
using std::ofstream;


class Server
{
private:
	WSADATA wsa;

	//server
	int PORT;
	string server_ip;
	SOCKET server_socket;

	//client
	sockaddr_in client_info;
	SOCKET client_socket;

	//file
	
	size_t file_size;
	vector<bite_t> file_bin;
	char file_name[20];

public:
	Server(string ip, int port);
	~Server();

	void start_receving();

private:
	void _wsa_start();
	void _socket_listen();
	void _accept_client();
	void _recv_file_name();
	void _recv_file_size();
	void _recv_file_bin();
	void _save_file();
};

