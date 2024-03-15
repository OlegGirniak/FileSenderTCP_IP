#include "Sender.h"
#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING


int main()
{
	Sender sender("example.docx");

	sender.set_ip_port("127.0.0.1", 2222);

	sender.send_file();

	sender.show_buffer();

	return 0;
}