#ifndef UDDSCORE_C
#define UDDSCORE_C

#define TIMEOUT 1000000  //--TIMEOUT in micro-sec
#define LENGHTMAX 256

/*#include <termios.h> mike 04022011*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "/home/partikle/user/uDDS/lib/uDDSLibrary.c"
#include "/home/partikle/user/uDDS/include/uDDSSerial.h" 
#include "/home/partikle/user/uDDS/core/uDDSSerial_Port.c"

char* IntMsgtoPack(int int_subMsgtoPack)
{
  char* MsgtoSend;
  MsgtoSend=malloc(LENGHTMSGTOPACK);
  itoa(int_subMsgtoPack,MsgtoSend,10);
  return MsgtoSend;
}

char* StrMsgtoPack(char* char_subMsgtoPack)
{
  char* MsgtoSend;

  MsgtoSend=malloc(LENGHTMSGTOPACK);
  strcat(MsgtoSend,char_subMsgtoPack);
  return MsgtoSend;
}

char * FloatMsgtoPack(float float_subMsgtoPack, int ndigits)
{
  char *MsgtoSend;

  MsgtoSend=malloc(LENGHTMSGTOPACK);
  ftoa(float_subMsgtoPack, ndigits);
}

char * DoubleMsgtoPack(double double_subMsgtoPack, int ndigits)
{
  char *MsgtoSend, *buffer;

  MsgtoSend=malloc(LENGHTMSGTOPACK);
  buffer = malloc(LENGHTMSGTOPACK);
  dtoa(double_subMsgtoPack, ndigits, buffer);
}

char * LongIntMsgtoPack(long int longint_subMsgtoPack)
{
    return ltoa(longint_subMsgtoPack, 10);
}

char* Serialize(DataWriter *sdw, uDDS_MsgPackage xxxPackMsg)
{
   char* MsgtoSend, *MsgtoPack;

   MsgtoSend = malloc(LENGHTMSGTOPACK);
   MsgtoPack = malloc(LENGHTMSGTOPACK);
   strcat(MsgtoSend,"#"); //inicio del mensaje

   //Agregando Tipo de mensaje por default general = 1
   MsgtoPack = IntMsgtoPack(sdw->top->MsgHeader->MsgType);
   strcat(MsgtoSend,MsgtoPack);
   strcat(MsgtoSend,"$");

   //Agregando el Id del topic
   MsgtoPack = StrMsgtoPack((char *)sdw->top->MsgHeader->name); //cast a (char *), para que no haya wornings por desconocer el tipo de puntero - 161209
   strcat(MsgtoSend,MsgtoPack);
   strcat(MsgtoSend,"$");

   //Agregando el tipo de dato
   MsgtoPack = StrMsgtoPack((char *)sdw->top->MsgHeader->type_name); //cast a (char *), para que no haya wornings por desconocer el tipo de puntero-161209
   strcat(MsgtoSend,MsgtoPack);
   strcat(MsgtoSend,"$");

   //Agregando la informacion de la estructura
   MsgtoPack = StrMsgtoPack(xxxPackMsg.String_Data);
   strcat(MsgtoSend,MsgtoPack);
   strcat(MsgtoSend,"$");
   MsgtoPack = IntMsgtoPack(xxxPackMsg.Int_Data);
   strcat(MsgtoSend,MsgtoPack);
   strcat(MsgtoSend,"$");
   MsgtoPack = FloatMsgtoPack(xxxPackMsg.Float_Data, 10); //cantidad de digitos a considerar
   strcat(MsgtoSend,MsgtoPack);
   strcat(MsgtoSend,"$");
   MsgtoPack = DoubleMsgtoPack(xxxPackMsg.Double_Data, 15); //cantidad de digitos a considerar
   strcat(MsgtoSend,MsgtoPack);
   strcat(MsgtoSend,"$");
   MsgtoPack = LongIntMsgtoPack(xxxPackMsg.LongInt_Data); //cantidad de digitos a considerar
   strcat(MsgtoSend,MsgtoPack);
   strcat(MsgtoSend,"#"); //fin del mensaje

   return MsgtoSend;
}


uDDS_MsgPackage deSerialize(char *MsgtoReceive)
{

  uDDS_MsgPackage xxxMsgPackaged;
  char *array[MAXNUMSUBMSG],*MsgtoTopic;
  int index;

  if((MsgtoReceive[0]=='#') && (MsgtoReceive[strlen(MsgtoReceive-1)]=='#')) 
  {
     MsgtoTopic=substring(MsgtoReceive, 2, strlen(MsgtoReceive)-2);
  }
  else
  {
     printf("Topic Error Received\n");
  }
  
  array[0]=strtok(MsgtoTopic,"$");
  
  if(array[0]==NULL)
  {
    printf("No test to search.\n");
    return ;
  }

  for(index=1;index<MAXNUMSUBMSG;index++)
  {
    array[index]=strtok(NULL,"$");
    if(array[index]==NULL)  break;
  }
  char **endstr;
  endstr=malloc(30);

  //Asignacion de los campos de la estructura del topico ********** 161209 ***********************************************************************
  xxxMsgPackaged.uDDS_MsgHeader.MsgType=atoi(array[0]);
  //strcpy(xxxMsgPackaged.uDDS_MsgHeader.TopicTyped,array[2]);
  strcpy(xxxMsgPackaged.uDDS_MsgHeader.TopicName,array[1]);
  strcpy(xxxMsgPackaged.String_Data,array[3]);
  xxxMsgPackaged.Int_Data=atoi(array[4]);
  xxxMsgPackaged.Float_Data=atof(array[5]);
  xxxMsgPackaged.Double_Data=atod(array[6],endstr);
  xxxMsgPackaged.LongInt_Data=atol(array[7]);
  return xxxMsgPackaged;
}

static int serial_fd = 0; //-- Descriptor de puerto serial
char data[LENGHTMAX];    //-- The received command

/***********************  ENVIAR  ********************************/
void *send_data (char *sCmd)
{
  //serial_fd=serial_open("/dev/ttyUSB0",B115200);   
  char* serial_name = "/dev/ttyUSB0";

  //open the serial port: The speed is configure at 9600 baud
  serial_fd=serial_open(serial_name,115200); //mike 04022011 B115200   

  //-- Error checking
  if (serial_fd==-1) 
  {
    printf ("Error opening the serial device: %s\n",serial_name);
    perror("OPEN");
    exit(0);
  }
  
  int iSpot;  //-- variable de longitud de cadena
  iSpot = strlen(sCmd);
  //-- Send the command to the serial port
  serial_send(serial_fd, sCmd, strlen(sCmd));
  printf("\nCadena enviada: uDDSCore.c\n %s %d\n",sCmd,strlen(sCmd));
  serial_close(serial_fd);
  return 0;
}

/*********************** RECIBIR ********************************/
char *received_data ()
{
  char* serial_name = "/dev/ttyUSB1";

  //open the serial port: The speed is configure at 9600 baud
  serial_fd=serial_open(serial_name,115200); //mike 04022011  B115200

  //-- Error checking
  if (serial_fd==-1) 
  {
    printf ("Error opening the serial device: %s\n",serial_name);
    perror("OPEN");
    exit(0);
  }

  int n;
  int ban = 1;
  while (ban)
  { 
    //-- Wait for the received data con un tiempo de espera TIMEOUT
    n=serial_read(serial_fd,data,LENGHTMAX,TIMEOUT);
    //printf("%s",data);
    //-- Show the received data
    //fflush(stdout); mike14022011
    
    if (n>0) 
    {
      printf ("\nDato Recibido: \"%s\", %d\n",data, strlen(data));
      ban = 0;
    }
    else 
    {
      printf ("\nEsperando leer dato ... Timeout!\n");
	  ban=0;
	  //data='$';
	 data[0] = '$';
     data[1] = '\0';
    }
  }; //fin del while
  
  //-- Close the serial port
  serial_close(serial_fd);
  return data;
}

#endif
