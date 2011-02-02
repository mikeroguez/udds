#ifndef UDDS_QOSPOLICY_H
#define UDDS_QOSPOLICY_H

typedef long DomainId_t;
typedef unsigned long StatusMask; // bit-mask StatusKind
#define STATUS_MASK_NONE   ((StatusMask) 0) //checket that I DONT REMEMBER
#define STATUS_MASK_ALL 0 //no esta bien
#define HANDLE_TYPE_NATIVE long

#define PARTICIPANT_QOS_DEFAULT 0 //se queda por mientras asi pero es una ESTRUCTURA

/************************      LA CLASE ENTIDAD      **********************************/
typedef struct EntityImpl{
} Entity;

typedef HANDLE_TYPE_NATIVE InstanceHandle_t;

struct Listener {
};

/************************* ENUM, ESTRUCTURAS ... QOSPOLICY *********************************/
struct Duration_t {
   long sec;
   unsigned long nanosec;
};

typedef enum {
    RETCODE_OK                   = 0,
    RETCODE_ERROR                = 1,
} ReturnCode_t;

struct DeadlineQosPolicy {
    struct Duration_t period;
};

#define DEADLINE_QOS_POLICY_DEFAULT {{ 0x7fffffffL, 0x7fffffffUL }}

struct TimeBasedFilterQosPolicy {
    struct Duration_t minimum_separation;
};

#define TIME_BASED_FILTER_QOS_POLICY_DEFAULT { {0L, 0UL} }

struct Time_t {
   long sec;
   unsigned long nanosec;
};

#endif /* qosPolicy_udds_h */
