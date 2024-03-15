#include "Server.h"

Server::Server(string ip, int port)
	: wsa{0},
	PORT(port),
	server_ip(ip), 
	server_socket(0),
	client_socket(0),
	client_info{},
	file_size(0),
	file_name{}
{
	_wsa_start();
}

Server::~Server()
{
	memset(&client_info, 0, sizeof(client_info));

	file_bin.clear();

	closesocket(client_socket);

	closesocket(server_socket);
	
	WSACleanup();
}

void Server::start_receving()
{
	_socket_listen();
	_accept_client();
	_recv_file_name();
	_recv_file_size();
	_recv_file_bin();

	cout << "File received" << endl;

	_save_file();
}

void Server::_wsa_start()
{
	assert(!(WSAStartup(MAKEWORD(2, 2), &wsa)) && "Couldn't init wsa");
	cout << "WSA startup +" << endl;
}

void Server::_socket_listen()
{
	assert(!((server_socket = socket(AF_INET, SOCK_STREAM, 0)) == SOCKET_ERROR) && ("Couldn't create socket"));

	client_info.sin_family = AF_INET;
	client_info.sin_addr.s_addr = inet_addr(server_ip.c_str());;
	client_info.sin_port = htons(PORT);

	assert(!(bind(server_socket, (struct sockaddr*)&client_info, sizeof(client_info))) && "Couldn't bind socket");
	cout << "Server socket binded +" << endl;

	assert(!(listen(server_socket, 10)) && "Couldn't listen socket");
	cout << "Server socket listen + " << endl;
}

void Server::_accept_client()
{
	int size_client_info = sizeof(client_info);
	client_socket = accept(server_socket, (struct sockaddr*)&client_info, &size_client_info);
}

void Server::_recv_file_name()
{
	recv(client_socket, file_name, sizeof(file_name), 0);
	cout << "+ file name" << endl;
}

void Server::_recv_file_size()
{
	char file_size_buffer[8]{};

	recv(client_socket, file_size_buffer, sizeof(file_size_buffer), 0);

	file_size = std::stoi(string(file_size_buffer));

	cout << "+ file size" << endl;
}

void Server::_recv_file_bin()
{
	file_bin.resize(file_size);

	recv(client_socket, file_bin.data(), file_size, 0);

	cout << "+ file bin:" << endl;

	for (auto ch : file_bin)
	{
		cout << ch;
	}
	cout << endl;
}

void Server::_save_file()
{
	ofstream file(file_name, std::ios::binary);

	if (file.is_open())
	{
		file.write(file_bin.data(), file_bin.size());
		file.close();
	}
}
