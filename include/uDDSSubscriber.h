#ifndef UDDSSUBSCRIBE_H
#define UDDSSUBSCRIBE_H

struct SubscriberQos 
{                                                   
};

struct DataReaderQos 
{
  struct DeadlineQosPolicy            deadline;
  struct TimeBasedFilterQosPolicy 	time_based_filter;
};

#define DataReaderQos_INITIALIZER   {    \
    DEADLINE_QOS_POLICY_DEFAULT,         \
    TIME_BASED_FILTER_QOS_POLICY_DEFAULT \
}

struct DataReaderQos DATAREADER_QOS_DEFAULT;

struct Clase_Subscriber 
{
  Entity as_entity;
};

struct Clase_DataReader 
{
  Topic *top;
  Publisher *pub;
  struct DataWriterQos tqos;
  struct DataReaderQos rqos;
};

typedef struct Clase_DataReader DataReader; 
typedef struct Clase_Subscriber Subscriber; 

typedef void (*DataReaderListener_DataAvailableCallback)(void* listener_data, DataReader* the_reader); //SOLO FALTA SABER DONDE ESTA LA FUNCION
typedef void (*SubscriberListener_DataOnReadersCallback)( void* listener_data, Subscriber* the_subscriber);
//Definida: void on_data_on_readers (Subscriber the_subscriber);

struct DataReaderListener 
{
  struct Listener as_listener; //La estructura esta definida en "qospolicy"
};

struct SubscriberListener 
{
  /* SubscriberListener_as_datareaderlistener */
  struct DataReaderListener as_datareaderlistener; //Hereda de datareaderlistener
  /* SubscriberListener_on_data_on_readers */                                                     
  SubscriberListener_DataOnReadersCallback on_data_on_readers; //DESCRIPTOR: FALTA DETERMINAR ESTA FUNCION
};

/********************************** METODOS DE LA CLASE SUBSCRIBER ***********************************/
//DataReader* Subscriber_create_datareader ( Subscriber* self, TopicDescription* a_topic, const struct DataReaderQos* qos, const struct DataReaderListener* listener, StatusMask mask); //de la especificacion
DataReader* Subscriber_create_datareader ( Subscriber* self, Topic* a_topic, const struct DataReaderQos* qos, const struct DataReaderListener* listener, StatusMask mask);


ReturnCode_t Subscriber_get_default_datareader_qos ( Subscriber* self, struct DataReaderQos* qos);
#endif /* subscriber_h */
