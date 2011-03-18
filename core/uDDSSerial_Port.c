/*#include <termios.h> mike 04022011*/
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
# include "/home/partikle/user/uDDS/include/uDDSSerial.h"

#include <sys/io.h>

int serial_open(char *serial_name, double baud) /*mike 01022011 speed_t baud*/
{
	int port, ret;

	port = atoi(serial_name);
	if ((ret=iopl(3)) < 0){
		printf("iopl: ret %d errno %d %s\n", ret, errno, strerror(errno));
		//exit (-1);
	}

	return port;
}

void serial_send(int serial_fd, char *data, int size)
{
	outb(data, serial_fd);
}

int serial_read(int serial_fd, char *data, int size, int timeout_usec)
{
	struct timespec t = {0,timeout_usec}; 
	data = inb (serial_fd);
	nanosleep(&t,0);
	return strlen(data);
}

void serial_close(int fd)
{
/*
  close(fd);
*/
}




