#include "Sender.h"


#pragma warning(disable: 4996)


Sender::Sender(string file)
	: 
	wsa{ 0 },
	port{},
	send_socket{},
	recv_info{},
	file_path(file)
{
	assert(!(WSAStartup(MAKEWORD(2, 2), &wsa)) && "Couldn't init wsa");

	_create_socket();
}

Sender::~Sender()
{
	shutdown(send_socket, SD_BOTH);
	closesocket(send_socket);
	WSACleanup();
}

void Sender::set_file(string path)
{
	file_path = path;
}

void Sender::send_file()
{
	_send_file_name();
	_send_file_size();
	//_send_file_bin();

	cout << "Messages is sent" << endl;
}

void Sender::set_ip_port(string ip, int port)
{
	this->ip = ip;
	this->port = port;

	recv_info.sin_family = AF_INET;
	recv_info.sin_port = htons(port);
	recv_info.sin_addr.s_addr = inet_addr(ip.c_str());

	_connect();
}

void Sender::_serialise_file()
{
	/*_set_file_name();

	buffer.push_back('[');

	for (auto ch : file_name)
		buffer.push_back(ch);

	buffer.push_back(']');
	buffer.push_back('[');
	
	string file_size_str = std::to_string(_get_file_size());

	for (auto ch : file_size_str)
		buffer.push_back(ch);

	buffer.push_back(']');
	buffer.push_back('[');

	_read_file_in_bin();

	for (auto ch : file_bin)
		buffer.push_back(ch);

	buffer.push_back(']');*/
}

int Sender::_get_file_size()
{
	return std::filesystem::file_size(file_path);
}

void Sender::_set_file_name()
{
	for (int i = file_path.size() - 1; i >= 0; i--)
	{
		if (file_path[i] != '/')
		{
			file_name += file_path[i];
		}
		else
		{
			break;
		}
	}

	reverse(file_name.begin(), file_name.end());
}

void Sender::_connect()
{
	assert(!(connect(send_socket, (sockaddr*)&recv_info, sizeof(recv_info))));
}

void Sender::_read_file_in_bin()
{
	auto size = _get_file_size();

	ifstream file(file_path, std::ios::binary);

	if (!file.is_open())
		return;

	file_bin.resize(size);

	file.read(file_bin.data(), size);

	file.close();

	/*std::ofstream file_o("filename.png", std::ios::out | std::ios::binary);

	file_o.write(file_bin.data(), file_bin.size());

	file.close();*/
}

void Sender::_create_socket()
{
	assert(!((send_socket = socket(AF_INET, SOCK_STREAM, 0)) == SOCKET_ERROR) && ("Couldn't create socket"));
}

void Sender::_send_file_size()
{
	string file_size_str = std::to_string(_get_file_size());

	assert((send(send_socket, file_size_str.c_str(), file_size_str.size(), 0)) != -1);

	cout << "+ file size is sended" << endl;
}

void Sender::_send_file_name()
{
	_set_file_name();

	assert((send(send_socket, file_name.c_str(), file_name.size(), 0)) != -1);

	cout << "+ file name is sended" << endl;
}

void Sender::_send_file_bin()
{
	_read_file_in_bin();

	assert((send(send_socket, file_bin.data(), file_bin.size(), 0)) != -1);

	cout << "+ file bin is sended" << endl;
}

void Sender::show_buffer()
{
	for (auto ch : file_bin)
		cout << ch;

	cout << endl;
}


