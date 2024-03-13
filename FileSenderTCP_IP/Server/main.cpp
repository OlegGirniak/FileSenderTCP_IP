#include <iostream>
#include <assert.h>
#include <vector>
#include <WinSock2.h>
#include <string>
#include <fstream>  
#include <thread>
#include <mutex>

#pragma comment(lib, "ws2_32.lib")
#pragma warning(disable: 4996)

using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::pair;
using std::move;
using std::ofstream;
using std::thread;
using std::mutex;

using bite_t = char;

#define PORT (2222)

string ip_addr("127.0.0.1");

WSADATA wsa{};

SOCKET server_socket{};

SOCKET client_socket{};

sockaddr_in socket_info{};

int file_size{};

vector<bite_t> file_bin;

mutex recv_mutex;


void wsa_start()
{
    assert(!(WSAStartup(MAKEWORD(2, 2), &wsa)) && "Couldn't init wsa");
    cout << "WSA startup +" << endl;
}


void socket_listen()
{
    assert(!((server_socket = socket(AF_INET, SOCK_STREAM, 0)) == SOCKET_ERROR) && ("Couldn't create socket"));

    socket_info.sin_family = AF_INET;
    socket_info.sin_addr.s_addr = inet_addr(ip_addr.c_str());;
    socket_info.sin_port = htons(PORT);

    assert(!(bind(server_socket, (struct sockaddr*)&socket_info, sizeof(socket_info))) && "Couldn't bind socket");
    cout << "Server socket binded +" << endl;

    assert(!(listen(server_socket, 10)) && "Couldn't listen socket");
    cout << "Server socket listen + " << endl;
}


void recv_file_name()
{
    char file_name[100]{};

    recv(client_socket, file_name, sizeof(file_name), 0);

    cout << "file_name: " << file_name << endl;
}

void recv_file_size()
{

    char file_size_buffer[8]{};

    recv(client_socket, file_size_buffer, 8, 0);

    string file_size_str(file_size_buffer);

    file_size = std::stoi(file_size_str);

    cout << "file size: " << file_size << endl;
}

void recv_file_bin()
{

}

void recv_file()
{
    sockaddr_in client_addr{};
    int size_client_addr = sizeof(client_addr);

    client_socket = accept(server_socket, (struct sockaddr*)&client_addr, &size_client_addr);

    recv_file_name();
    recv_file_size();
}


int main()
{
    wsa_start();

    socket_listen();

    recv_file();

    return 0;
}