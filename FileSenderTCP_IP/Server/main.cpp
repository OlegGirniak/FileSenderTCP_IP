#include <iostream>
#include "Server.h"

int main()
{
    Server server("127.0.0.1", 2222);

    server.start_receving();

    return 0;
}