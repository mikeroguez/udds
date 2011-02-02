/** Compilacion:  gcc xxxSubscriber.c -o sub -lrt **/
#include "stdlib.h"
#include "stdio.h"
#include "time.h"
#include "/home/magaly/Escritorio/uDDS_161209/include/Data.h"
#include "/home/magaly/Escritorio/uDDS_161209/include/uDDS.h"

/*******************************************************************************/
void xxx_on_data_available (DataReader* reader) 
{ //arg: void* listener_data, DataReader* reader
   char* MsgtoReceive; //subscriber
   uDDS_MsgPackage xxxMsgPackageR;//Este no esta registrado en el Subscriber
   MsgtoReceive=malloc(LENGHTMSGTOPACK); //Subscriber
   
   clock_gettime (CLOCK_REALTIME, &time2);
   
   //printf("Nombre de Topico desde funcion on_data_available\n%s\n",reader->top->MsgHeader->name);

   MsgtoReceive = DataReader_read (); //se supone que este es responsable de deserializar el mensaje y almacenarlos en la cola de datawriter
   printf("Mensaje recibido antes de los IFs %s\n",MsgtoReceive);
   xxxMsgPackageR=deSerialize(MsgtoReceive);
   printf("Campos de la Estructura antes de los IFs %d\n",xxxMsgPackageR.uDDS_MsgHeader.MsgType);
   //printf("Campos de la Estructura antes de los IFs %s\n",xxxMsgPackageR.uDDS_MsgHeader.TopicTyped);
   printf("Campos de la Estructura antes de los IFs %s\n",xxxMsgPackageR.uDDS_MsgHeader.TopicName);

//lee los datos de la cola del datareader
   if((reader->rqos.time_based_filter.minimum_separation.sec != 0L || reader->rqos.time_based_filter.minimum_separation.nanosec != 0UL )&& (reader->rqos.deadline.period.sec == 0x7fffffffL || reader->rqos.deadline.period.nanosec == 0x7fffffffL))
   {
     if (first==0)
     {
       first=1;
       MsgtoReceive = DataReader_read ();  
       xxxMsgPackageR=deSerialize(MsgtoReceive);
       
       if(!strcmp(reader->top->MsgHeader->name,xxxMsgPackageR.uDDS_MsgHeader.TopicName))//comparacion del nombre de topico leido con el del subscriber
         showDataTopic(xxxMsgPackageR); //muestra el campo de la estructura topic con sus valores

     }

     if (SEC_TRANS() + (NSEC_TRANS()) *1E-9 > reader->rqos.time_based_filter.minimum_separation.sec + (reader->rqos.time_based_filter.minimum_separation.nanosec*1E-9))
     {
       time1=time2;
       MsgtoReceive = DataReader_read ();
       xxxMsgPackageR=deSerialize(MsgtoReceive);

       if(!strcmp(reader->top->MsgHeader->name,xxxMsgPackageR.uDDS_MsgHeader.TopicName))
         showDataTopic(xxxMsgPackageR); //muestra el campo de la estructura topic con sus valores

     }
   }
   else if((reader->rqos.time_based_filter.minimum_separation.sec != 0L || reader->rqos.time_based_filter.minimum_separation.nanosec != 0UL) && (reader->rqos.deadline.period.sec != 0x7fffffffL || reader->rqos.deadline.period.nanosec != 0x7fffffffL))
   {
     if (first==0)
     {
       first=1;
       MsgtoReceive = DataReader_read ();
       xxxMsgPackageR=deSerialize(MsgtoReceive);

       if(!strcmp(reader->top->MsgHeader->name,xxxMsgPackageR.uDDS_MsgHeader.TopicName))
         showDataTopic(xxxMsgPackageR); //muestra el campo de la estructura topic con sus valores

     }
     if ((SEC_TRANS() + (NSEC_TRANS() *1E-9) > reader->rqos.time_based_filter.minimum_separation.sec + (reader->rqos.time_based_filter.minimum_separation.nanosec*1E-9))&&(time2.tv_sec-time3.tv_sec))
     {
       time1=time2;
       time3=time2;
       MsgtoReceive = DataReader_read ();
       xxxMsgPackageR=deSerialize(MsgtoReceive);

       if(!strcmp(reader->top->MsgHeader->name,xxxMsgPackageR.uDDS_MsgHeader.TopicName)) 
         showDataTopic(xxxMsgPackageR); //muestra el campo de la estructura topic con sus valores

     }
   }
   else if((reader->rqos.time_based_filter.minimum_separation.sec == 0L || reader->rqos.time_based_filter.minimum_separation.nanosec == 0UL )&& (reader->rqos.deadline.period.sec != 0x7fffffffL || reader->rqos.deadline.period.nanosec != 0x7fffffffL))
   {
     if(SEC_TRANS() + (NSEC_TRANS()) *1E-9 <= reader->rqos.deadline.period.sec + (reader->rqos.deadline.period.nanosec*1E-9))
     {
       MsgtoReceive = DataReader_read ();
       xxxMsgPackageR=deSerialize(MsgtoReceive);

       if(!strcmp(reader->top->MsgHeader->name,xxxMsgPackageR.uDDS_MsgHeader.TopicName))
         showDataTopic(xxxMsgPackageR); //muestra el campo de la estructura topic con sus valores
       // clock_gettime (CLOCK_REALTIME, &time2);

     } else printf("FUERA DE DEADLINE");
     time1=time2;
   } 
   else // Con la calidad de Servicios por defecto - QoS_DEFAULT
   {
       MsgtoReceive = DataReader_read ();
       xxxMsgPackageR=deSerialize(MsgtoReceive);

       if(!strcmp(reader->top->MsgHeader->name,xxxMsgPackageR.uDDS_MsgHeader.TopicName))
         showDataTopic(xxxMsgPackageR); //muestra el campo de la estructura topic con sus valores

   }
}

static int subscriber_main(int domainId, int sample_count)
{
    DomainParticipantFactory *TheParticipantFactory = NULL;
    DomainParticipant *participant = NULL;
    Subscriber *subscriber = NULL;
    Topic *topic = NULL;
    struct DataReaderListener reader_listener; // = DataReaderListener_INITIALIZER;
    DataReader *reader = NULL;
    ReturnCode_t retcode;
    //TopicDescription *topdes = NULL; // No va aqui

    const char *type_name = NULL;
    int count = 0;
    struct Duration_t poll_period = {4,0};
    struct DataReaderQos drqos = DataReaderQos_INITIALIZER;

    /* ********************************** */
    participant = DomainParticipantFactory_create_participant (TheParticipantFactory, domainId, PARTICIPANT_QOS_DEFAULT, NULL, STATUS_MASK_NONE);
    if (participant == NULL) 
    {
        printf("Error en funcion create_participant\n");
        return -1;
    }

    subscriber = DomainParticipant_create_subscriber ( participant, &SUBSCRIBER_QOS_DEFAULT, NULL /* listener */, STATUS_MASK_NONE);
    if (subscriber == NULL) 
    {
        printf("Error en funcion create_subscriber\n");
        return -1;
    }

    /* Register type before creating topic */
    type_name = TypeSupport_get_type_name();	
    retcode = TypeSupport_register_type(participant, type_name); //no implementado

    topic = DomainParticipant_create_topic(participant, "xxx", type_name, &TOPIC_QOS_DEFAULT, NULL /* listener */, STATUS_MASK_NONE);
    if (topic == NULL) 
    {
        printf("Error en funcion create_topic\n");
        return -1;
    }

    /*** Modificación de la calidad de servicios ***/
    /* To personalizar el data read QoS, use Publisher_get_default_dataread_qos() */
    Subscriber_get_default_datareader_qos (subscriber, &drqos); //no esta implementada

    /*** Modificar la calidad de servicio ***/
    clock_gettime (CLOCK_REALTIME, &time1);
    time3=time1;

    drqos.time_based_filter.minimum_separation.sec=4;
    drqos.time_based_filter.minimum_separation.nanosec=8;

    drqos.deadline.period.sec = 5;
    drqos.deadline.period.nanosec = 10;
    
    //Topic_as_topicdescription(topic);
    //reader = Subscriber_create_datareader(subscriber, Topic_as_topicdescription(topic), &drqos, &reader_listener, STATUS_MASK_ALL);
    reader = Subscriber_create_datareader(subscriber, topic, &drqos, &reader_listener, STATUS_MASK_ALL); //revisar topic enviar funcion
    if (reader == NULL) 
    {
        printf("Error en funcion create_datareader\n");
        return -1;
    }

    for (count=0; (sample_count == 0) || (count < sample_count); ++count) 
    {
        //printf("\nEsperando dato para leer ...");
        xxx_on_data_available (reader);
    }
return 0;
}

/*************************************          MAIN         *************************************************************/
int main(int argc, char *argv[])
{
    int domainId = 0; //por el momento solo hay un dominio
    int sample_count = 0; /* infinite loop */
    if (argc >= 2) { //podemos cambiar este alterando la veces del ciclo for para pruebas i.e # ./publisher 100
        sample_count = atoi(argv[2]);
    }
    return subscriber_main(domainId, sample_count);
}


