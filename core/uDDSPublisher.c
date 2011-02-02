#ifndef UDDSPUBLISHER_C
#define UDDSPUBLISHER_C
#include "stdlib.h"

DataWriter* Publisher_create_datawriter ( Publisher* self, Topic* topic, const struct DataWriterQos* qos, const struct DataWriterListener* listener, StatusMask mask)
{
   DataWriter *dw;
   dw = malloc(sizeof(DataWriter));
   dw->top = topic; //Esta bien asignado el valor - el valor no se puede modificar desde aqui
   //dw->pub = self; //añadir
   dw->tqos.deadline.period.sec= qos->deadline.period.sec;
   dw->tqos.deadline.period.nanosec= qos->deadline.period.nanosec;
   return dw;
}

ReturnCode_t Publisher_get_default_datawriter_qos(Publisher* self, struct DataWriterQos* qos)
{
}
#endif

