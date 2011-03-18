/***************************************************
* xxxNode.c
* By MikeRoguez
* 	genera Publisher y Subscribers en un solo
* 	proceso multihilo con pthreads.
* 7/marzo/2011
****************************************************/

#include <time.h>
#include <stdio.h>
#include <pthread.h> 
#include <errno.h>
#include <stdlib.h>
#include "/home/partikle/user/uDDS/include/Data.h"
#include "/home/partikle/user/uDDS/include/uDDS.h"

pthread_mutex_t rw_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t reader_mutex = PTHREAD_MUTEX_INITIALIZER;
int num_readers = 0;
/*Estructura de argumentos enviados a threads*/
struct thread_args
{
	int domain;
	int sample_count;
};
/*==========================================*/

int main(int argc, char *argv[])
{
	struct thread_args data;
	data.domain = 0; //por el momento solo hay un dominio
	data.sample_count = 0; //infinite loop
	if (argc >= 2) { //podemos cambiar este alterando la veces del ciclo for para pruebas i.e # ./publisher 100
		data.sample_count = atoi(argv[2]);
	}

	pthread_t subscriber_thread1; 
	pthread_t publisher_thread1; 
	void *publisher_main();
	void *subscriber_main();

	pthread_create(&subscriber_thread1,NULL,subscriber_main,&data);
	pthread_create(&publisher_thread1,NULL,publisher_main,&data);
	pthread_join(subscriber_thread1,NULL);
	pthread_join(publisher_thread1,NULL);

}

/*************
* SUBSCRIBER
**************/
void xxx_on_data_available (DataReader* reader) 
{ //arg: void* listener_data, DataReader* reader
	char* MsgtoReceive; //subscriber
	uDDS_MsgPackage xxxMsgPackageR;//Este no esta registrado en el Subscriber
	MsgtoReceive=malloc(LENGHTMSGTOPACK); //Subscriber

	clock_gettime (CLOCK_REALTIME, &time2);

	//printf("Nombre de Topico desde funcion on_data_available\n%s\n",reader->top->MsgHeader->name);

	MsgtoReceive = DataReader_read (); //se supone que este es responsable de deserializar el mensaje y almacenarlos en la cola de datawriter
	printf("Mensaje recibido antes de los IFs %s\n",MsgtoReceive);
if(strlen(MsgtoReceive) > 0){ //mike	
	printf ("\nEntro: \"%s\", %d\n",MsgtoReceive, strlen(MsgtoReceive));
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
} //mike
}

void *subscriber_main(void *args)
{
	struct thread_args *data = (struct thread_args *)args; //parseo de lo recibido a estructura args
	DomainParticipantFactory *TheParticipantFactory = NULL;
	DomainParticipant *participant = NULL;
	Subscriber *subscriber = NULL;
	Topic *topic = NULL;
	struct DataReaderListener reader_listener; // = DataReaderListener_INITIALIZER;
	DataReader *reader = NULL;
	ReturnCode_t retcode;
	//TopicDescription *topdes = NULL; // No va aqui
	
	struct timespec t = {0,0}; 

	const char *type_name = NULL;
	int count = 0;
	struct Duration_t poll_period = {4,0};
	struct DataReaderQos drqos = DataReaderQos_INITIALIZER;

	/* ********************************** */
	participant = DomainParticipantFactory_create_participant (TheParticipantFactory, data->domain, PARTICIPANT_QOS_DEFAULT, NULL, STATUS_MASK_NONE);
	if (participant == NULL) 
	{
		printf("Error en funcion create_participant\n");
		pthread_exit(NULL);
	}

	subscriber = DomainParticipant_create_subscriber ( participant, &SUBSCRIBER_QOS_DEFAULT, NULL /* listener */, STATUS_MASK_NONE);
	if (subscriber == NULL) 
	{
		printf("Error en funcion create_subscriber\n");
		pthread_exit(NULL);
	}

	/* Register type before creating topic */
	type_name = TypeSupport_get_type_name();	
	retcode = TypeSupport_register_type(participant, type_name); //no implementado

	topic = DomainParticipant_create_topic(participant, "xxx", type_name, &TOPIC_QOS_DEFAULT, NULL /* listener */, STATUS_MASK_NONE);
	if (topic == NULL) 
	{
		printf("Error en funcion create_topic\n");
		pthread_exit(NULL);
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
		pthread_exit(NULL);
	}

	for (count=0; (data->sample_count == 0) || (count < data->sample_count); ++count) 
	{

		pthread_mutex_lock(&reader_mutex);
		num_readers++;
		if (num_readers == 1) pthread_mutex_lock(&rw_mutex);
		pthread_mutex_unlock(&reader_mutex);

		printf("\nSubThread ...");
		xxx_on_data_available (reader);

		pthread_mutex_lock(&reader_mutex);
		num_readers--;
		if (num_readers == 0) pthread_mutex_unlock(&rw_mutex);
		pthread_mutex_unlock(&reader_mutex);
/*
		t.tv_sec = 0;
		t.tv_nsec = count%3;
*/

		t.tv_sec = 0;
		t.tv_nsec = 8000;

		nanosleep (&t, 0); 

	}
	pthread_exit(NULL);
}

/*=======SUBSCRIBER=========*/

/*************
* PUBLISHER
**************/
void *publisher_main(void *args)
{ 
	struct thread_args *data = (struct thread_args *)args; //parseo de lo recibido a estructura args
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

	struct timespec t = {0, 0};

	/* Asignación de valores */ 
	struct Duration_t send_period = {4,0};
	struct DataWriterQos dwqos = DataWriterQos_INITIALIZER;

	participant = DomainParticipantFactory_create_participant(TheParticipantFactory, data->domain, PARTICIPANT_QOS_DEFAULT, NULL /* listener */,  STATUS_MASK_NONE);
	if (participant == NULL) 
	{
		printf("Error en funcion create_participant\n");
		pthread_exit(NULL);
	}

	publisher = DomainParticipant_create_publisher(participant, &PUBLISHER_QOS_DEFAULT, NULL /* listener */, STATUS_MASK_NONE);
	if (publisher == NULL) 
	{
		printf("Error en funcion create_publisher\n");
		pthread_exit(NULL);
	}

	/* Register type before creating topic */
	type_name = TypeSupport_get_type_name();
	retcode = TypeSupport_register_type(participant, type_name);//Falta acomodar esto - No hay nada - 161209 
	/**************************************/

	topic = DomainParticipant_create_topic(participant, "xxx", type_name, &TOPIC_QOS_DEFAULT, NULL /* listener */, STATUS_MASK_NONE);
	if (topic == NULL) 
	{
		printf("Error en funcion create_topic\n");
		pthread_exit(NULL);
	}

	/*** Modificación de la calidad de servicios ***/
	Publisher_get_default_datawriter_qos(publisher, &dwqos); //Revisar esta funcion no tiene implementacion 161209 
	/***********************************************/

	clock_gettime (CLOCK_REALTIME, &time1);
	dwqos.deadline.period.sec=8; //agregar mensaje si no se envia el dato
	dwqos.deadline.period.nanosec=12;

	writer = Publisher_create_datawriter(publisher, topic, &dwqos, NULL /* listener */, STATUS_MASK_NONE);
	if (writer == NULL) 
	{
		printf("Error en funcion create_datawriter\n");
		pthread_exit(NULL);
	}

	/* Main loop */

	for (count=0; (data->sample_count == 0) || (count < data->sample_count); ++count) 
	{
		pthread_mutex_lock(&rw_mutex);

		/* Modificación de los datos para ser escritos - el usuario hace esto */
		sprintf(xxxMsgPackage.String_Data,"Cadena%d",count);
		xxxMsgPackage.Int_Data=1234; 
		xxxMsgPackage.Float_Data=145.655896999;
		xxxMsgPackage.Double_Data=8.655896589651253585525;
		xxxMsgPackage.LongInt_Data=1234567891;
	   
		/* Write data */
		printf("\nWriThread ...");
		DataWriter_write (writer, xxxMsgPackage, handle);
		t.tv_sec = 0;
		t.tv_nsec = 100000000;
		nanosleep (&t, 0);
		pthread_mutex_unlock(&rw_mutex);


		t.tv_sec = 0;
		t.tv_nsec = (count%2)*500000;
		nanosleep (&t, 0);

	}
	pthread_exit(NULL);
}
/*=======PUBLISHER=========*/
