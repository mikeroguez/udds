/** Modo de compilacion: gcc xxxPublisher.c -o pub -lrt **/
#include "stdlib.h"
#include "stdio.h"
#include "time.h"
#include "/home/partikle/user/uDDS/include/Data.h"
#include "/home/partikle/user/uDDS/include/uDDS.h"

static int publisher_main(int domainId, int sample_count)
{
    DomainParticipantFactory *TheParticipantFactory = NULL;
    DomainParticipant *participant = NULL; 
    Publisher *publisher = NULL;    
    Topic *topic = NULL;  
    DataWriter *writer = NULL;
    uDDS_MsgPackage xxxMsgPackage; //Estructura creada por el usuario 
    ReturnCode_t retcode;
    const char *type_name = NULL;
    int count = 0;  
    long handle = 0; //inicializando a NIL

    struct timespec t = {6, 0};

    /* Asignación de valores */ 
    struct Duration_t send_period = {4,0};
    struct DataWriterQos dwqos = DataWriterQos_INITIALIZER;
 
    participant = DomainParticipantFactory_create_participant(TheParticipantFactory, domainId, PARTICIPANT_QOS_DEFAULT, NULL /* listener */,  STATUS_MASK_NONE);
    if (participant == NULL) 
    {
        printf("Error en funcion create_participant\n");
        return -1;
    }

    publisher = DomainParticipant_create_publisher(participant, &PUBLISHER_QOS_DEFAULT, NULL /* listener */, STATUS_MASK_NONE);
    if (publisher == NULL) 
    {
        printf("Error en funcion create_publisher\n");
        return -1;
    }

    /* Register type before creating topic */
    type_name = TypeSupport_get_type_name();	
    retcode = TypeSupport_register_type(participant, type_name);//Falta acomodar esto - No hay nada - 161209 ************************************

    topic = DomainParticipant_create_topic(participant, "xxx", type_name, &TOPIC_QOS_DEFAULT, NULL /* listener */, STATUS_MASK_NONE);
    if (topic == NULL) 
    {
        printf("Error en funcion create_topic\n");
        return -1;
    }
    
    /*** Modificación de la calidad de servicios ***/
    Publisher_get_default_datawriter_qos(publisher, &dwqos); //Revisar esta funcion no tiene implementacion 161209 ******************************

    clock_gettime (CLOCK_REALTIME, &time1);
    dwqos.deadline.period.sec=8; //agregar mensaje si no se envia el dato
    dwqos.deadline.period.nanosec=12;

    writer = Publisher_create_datawriter(publisher, topic, &dwqos, NULL /* listener */, STATUS_MASK_NONE);
    if (writer == NULL) 
    {
        printf("Error en funcion create_datawriter\n");
        return -1;
    }

    /* Main loop */
    
    for (count=0; (sample_count == 0) || (count < sample_count); ++count) 
   {
       /* Modificación de los datos para ser escritos - el usuario hace esto */
       sprintf(xxxMsgPackage.String_Data,"Cadena%d",count);
       xxxMsgPackage.Int_Data=1234; 
       xxxMsgPackage.Float_Data=145.655896999;
       xxxMsgPackage.Double_Data=8.655896589651253585525;
       xxxMsgPackage.LongInt_Data=1234567891;
       
       /* Write data */
       DataWriter_write (writer, xxxMsgPackage, handle);
       //sleep (6);
       nanosleep (&t, 0);
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
    return publisher_main(domainId, sample_count);
}


