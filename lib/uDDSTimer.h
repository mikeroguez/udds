#ifndef UDDSTimer_H
#define UDDSTimer_H

#define SEC_TRANS()                      (time2.tv_sec - time1.tv_sec)
#define NSEC_TRANS()                     (time2.tv_nsec - time1.tv_nsec)

short int first;
struct timespec       time1, time2, time3; //Mide el tiempo en nanosegundos

#endif
