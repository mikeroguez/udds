/*#include <termios.h> mike 04022011*/
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include "/home/partikle/user/uDDS/include/uDDSSerial.h"

#include <serial1.h>

int serial_open(char *serial_name, double baud) /*mike 01022011 speed_t baud*/
{
	return uartinit1 (baud);
}

void serial_send(int serial_fd, char *data, int size)
{
	putstring_serialn1 (data, size);
}

int serial_read(int serial_fd, char *data, int size, int timeout_usec)
{
	return getstring_serial1 (data, size);
}

void serial_close(int fd)
{
/*
  close(fd);
*/
}




