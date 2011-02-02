#ifndef UDDS_PUBLISHER_H
#define UDDS_PUBLISHER_H

typedef struct Clase_Publisher
{
} Publisher;

struct DataWriterQos 
{  
    struct DeadlineQosPolicy            deadline;
};
#define DataWriterQos_INITIALIZER   {  DEADLINE_QOS_POLICY_DEFAULT  }

// Modificada Clase_DataWriter el 161209 **************************************************************************************************************
typedef struct Clase_DataWriter
{
  Topic *top;
  Publisher *pub;
  struct DataWriterQos tqos;
} DataWriter; 

struct DataWriterQos DATAWRITER_QOS_DEFAULT;

struct PublisherQos 
{
};

struct DataWriterListener 
{
  struct Listener as_listener; //Hereda de Listener: Buscar en qospolicy
};

struct PublisherListener 
{
};

/********************************** METODOS DE LA CLASE PUBLISHER ***********************************/
DataWriter* Publisher_create_datawriter(Publisher* self, Topic* a_topic, const struct DataWriterQos* qos, const struct DataWriterListener* a_listener, StatusMask mask);

ReturnCode_t Publisher_get_default_datawriter_qos ( Publisher* self, struct DataWriterQos* qos);

#endif /* publisher_udds_h */
