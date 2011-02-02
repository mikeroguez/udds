#ifndef TYPESUPPORT_H
#define TYPESUPPORT_H

const char* TypeSupport_get_type_name();
ReturnCode_t TypeSupport_register_type(DomainParticipant* participant, const char* type_name);

#endif  

