#ifndef UDDSDATAWRITER_C
#define UDDSDATAWRITER_C

void DataWriter_write(DataWriter *self, uDDS_MsgPackage instance_data, long handle)
{
   char* MsgtoSend;
   MsgtoSend=malloc(LENGHTMSGTOPACK);//Publisher
   clock_gettime (CLOCK_REALTIME, &time2);

   /*********************************     Normalización tiempo  ************************************************************/
//   if(SEC_TRANS() + (NSEC_TRANS()) *1E-9 <= self->tqos.deadline.period.sec + (self->tqos.deadline.period.nanosec*1E-9))
 //  {
     MsgtoSend=Serialize(self, instance_data);
     //printf("\nMensaje a enviar - Datawriter.c:\n%s\n\n",MsgtoSend);
     send_data (MsgtoSend);
  // }
  // else printf("Fuera de deadline");

  // time1=time2;
} 

#endif

