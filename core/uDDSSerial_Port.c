/*#include <termios.h> mike 04022011*/
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
# include "/home/partikle/user/uDDS/include/uDDSSerial.h"

int serial_open(char *serial_name, double baud) /*mike 01022011 speed_t baud*/
{
/*
  struct termios newtermios;
  int fd;

  // Abrir el puerto serial
  fd = open(serial_name,O_RDWR | O_NOCTTY | O_NDELAY); 

  // Configure the serial port attributes: -- No parity -- 8 data bits -- other things...
  newtermios.c_cflag= CBAUD | CS8 | CLOCAL | CREAD;
  newtermios.c_iflag=IGNPAR;
  newtermios.c_oflag=0;
  newtermios.c_lflag=0;
  newtermios.c_cc[VMIN]=1;
  newtermios.c_cc[VTIME]=0;

  // Set the speed
  cfsetospeed(&newtermios,baud);
  cfsetispeed(&newtermios,baud);
  
  // flush the input buffer
  if (tcflush(fd,TCIFLUSH)==-1) {
    return -1;
  }

  // flush the output buffer
  if (tcflush(fd,TCOFLUSH)==-1) {
    return -1;
  }

  //-- Configure the serial port now!!
  if (tcsetattr(fd,TCSANOW,&newtermios)==-1) {
    return -1;
  }  

  //-- Return the file descriptor
  return fd;
*/
return 0;
}

void serial_send(int serial_fd, char *data, int size)
{
/*
  write(serial_fd, data, size);
*/
}

int serial_read(int serial_fd, char *data, int size, int timeout_usec)
{
/*
  fd_set fds;
  struct timeval timeout;
  int count=0;
  int ret;
  int n;
  
  do {
      //-- Set the fds variable to wait for the serial descriptor
      FD_ZERO(&fds);
      FD_SET (serial_fd, &fds);
    
      //-- Set the timeout in usec.
      timeout.tv_sec = 0;  
      timeout.tv_usec = timeout_usec;

      //-- Wait for the data
      ret=select (FD_SETSIZE,&fds, NULL, NULL,&timeout);
    
      //-- If there are data waiting: read it
      if (ret==1) {
        
        //-- Read the data (n bytes)
        n=read (serial_fd, &data[count], size-count); 
        
        //-- The number of bytes receives is increased in n
        count+=n;
        
        //-- The last byte is always a 0 (for printing the string data)
        data[count]=0;
      }

    //-- Repeat the loop until a data block of size bytes is received or
    //-- a timeout occurs
  } while (count<size && ret==1);

  //-- Return the number of bytes reads. 0 If a timeout has occurred.
  return count;
*/
return 0;
}

void serial_close(int fd)
{
/*
  close(fd);
*/
}




