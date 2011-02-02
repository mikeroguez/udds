#ifndef UDDS_TOPIC_H
#define UDDS_TOPIC_H

// Agregado el 161209 *******************************************************************************************************************
typedef enum {
               GENERAL=1,CONTROL,MSGOK
             } uDDS_MsgType; //GENERAL=1, CONTROL=2, MSGOK=3


/************************ ESTRUCTURA TOPICQOS **********************************/
struct TopicQos {
    struct DeadlineQosPolicy            deadline;
};

#define TopicQos_INITIALIZER   { DEADLINE_QOS_POLICY_DEFAULT }

/********************** ESTRUCTURA TOPICLISTENER *******************************/
struct TopicListener {
    struct Listener as_listener;
};

//struct Clase_TopicDescription modificado el 161209 **********************************************************************************
typedef struct Clase_TopicDescription{
    uDDS_MsgType MsgType;
    const char *type_name;
    const char *name;  
} TopicDescription;

//struct Clase_topic modificado el 161209 ***********************************************************************************************
struct Clase_Topic {
    //Entity*            _as_Entity;
    TopicDescription*  MsgHeader;
    //agregar id_domain;
    //struct TopicImpl* _impl;
};

typedef struct Clase_Topic Topic;

/*** FUNCIONES DEL TOPICDESCRIPTION ***/
const char* TopicDescription_get_type_name();
const char* TopicDescription_get_name();
//DomainParticipant* TopicDescription_get_participant(TopicDescription* self);

#endif /* topic_udds_h */
