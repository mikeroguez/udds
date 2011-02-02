#ifndef UDDSDATAREADER_C
#define UDDSDATAREADER_C

char* DataReader_read (){
   char* MsgtoReceiveP;
   MsgtoReceiveP=malloc(LENGHTMSGTOPACK); //Subscriber
   MsgtoReceiveP = received_data();
   return MsgtoReceiveP;
};

#endif


