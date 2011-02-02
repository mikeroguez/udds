#ifndef UDDS_DOMAIN_H
#define UDDS_DOMAIN_H

struct Clase_DomainParticipant {
};

typedef struct Clase_DomainParticipant DomainParticipant;

struct Clase_DomainParticipantFactoryImpl {
};
typedef struct Clase_DomainParticipantFactoryImpl DomainParticipantFactory;

struct DomainParticipantListener {
};

struct DomainParticipantQos {
};

/******************************* METODOS DE LA CLASE DOMAINPARTICIPANTFACTORY ******************************/
DomainParticipant* DomainParticipantFactory_create_participant ( DomainParticipantFactory* self, DomainId_t domainId, const struct DomainParticipantQos* qos, const struct DomainParticipantListener* listener, StatusMask mask);

/********************************** METODOS DE LA CLASE DOMAINPARTICIPANT **********************************/
Publisher* DomainParticipant_create_publisher ( DomainParticipant* self, const struct PublisherQos* qos, const struct PublisherListener* a_listener, StatusMask mask);

Subscriber* DomainParticipant_create_subscriber ( DomainParticipant* self, const struct SubscriberQos* qos, const struct SubscriberListener* a_listener, StatusMask mask);

Topic* DomainParticipant_create_topic ( DomainParticipant* self, const char* topic_name, const char* type_name, const struct TopicQos* qos, const struct TopicListener* a_listener, StatusMask mask);

struct TopicQos TOPIC_QOS_DEFAULT;
struct PublisherQos PUBLISHER_QOS_DEFAULT;
struct SubscriberQos SUBSCRIBER_QOS_DEFAULT;

#endif /* dominio_h */
