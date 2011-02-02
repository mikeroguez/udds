#ifndef UDDSSERIAL_H
#define UDDSSERIAL_H

#include <termios.h>
/* ---------- Prototipos de Funciones ----------- */
int  serial_open(char *serial_name, speed_t baud);
void serial_send(int serial_fd, char *data, int size);
int  serial_read(int serial_fd, char *data, int size, int timeout_usec);
void serial_close(int fd);

#endif  
