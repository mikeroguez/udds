#ifndef UDDSDOMAIN_C
#define UDDSDOMAIN_C

DomainParticipant* DomainParticipantFactory_create_participant ( DomainParticipantFactory* self, DomainId_t domainId, const struct DomainParticipantQos* qos, const struct DomainParticipantListener* listener, StatusMask mask)
{
    DomainParticipant* dom;
    dom = malloc(sizeof(DomainParticipant));
    return dom;
}

Publisher* DomainParticipant_create_publisher (DomainParticipant* self, const struct PublisherQos* qos, const struct PublisherListener* a_listener, StatusMask mask)
{
    Publisher* pub;
    pub = malloc(sizeof(Publisher));
    return pub;
};

Topic* DomainParticipant_create_topic ( DomainParticipant* self, const char* topic_name, const char* type_name, const struct TopicQos* qos, const struct TopicListener* a_listener, StatusMask mask)
{
    Topic* top;
    top = malloc(sizeof(Topic));
    top->MsgHeader = malloc(sizeof(TopicDescription));

    top->MsgHeader->MsgType=GENERAL; 
    top->MsgHeader->type_name = type_name;
    top->MsgHeader->name = topic_name;//Por el momento se esta manejando como el topic_id en si se puede agregar otra estructura para el id que sea distito del topic name y que sea un id interno que será enviando en el mensaje para identificar un mensaje(sample de otro). **************** 161209 **************
    return top;
}

Subscriber* DomainParticipant_create_subscriber ( DomainParticipant* self, const struct SubscriberQos* qos, const struct SubscriberListener* a_listener, StatusMask mask)
{
    Subscriber* sub;
    sub = malloc(sizeof(Subscriber));
    return sub;
}
#endif
