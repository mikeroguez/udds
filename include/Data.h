#ifndef DATA_H
#define DATA_H

#define MAXLENGHTMSG 20
#define LENGHTMSGTOPACK 50
#define MAXNUMSUBMSG 30

const char *xxxTYPENAME = "uDDS_MsgPackage"; //Nombre de la estructura de datos

//Message Header que es el TOPICDESCRIPTION esta en topic.h *********** 161209 *******************************************

/**
typedef enum {
               GENERAL=1,CONTROL,MSGOK
             } uDDS_MsgType; //GENERAL=1, CONTROL=2, MSGOK=3
**/
typedef struct 
{
    int MsgType;

//    char *TopicTyped;
    char *TopicName;
} uDDS_MsgHeader;

//Message package
typedef struct {
  uDDS_MsgHeader uDDS_MsgHeader;

  char String_Data[MAXLENGHTMSG];
  int Int_Data;
  float Float_Data;
  double Double_Data;
  long int LongInt_Data;
} uDDS_MsgPackage;

#endif  


