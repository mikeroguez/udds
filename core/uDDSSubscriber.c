#ifndef UDDSSUBSCRIBER_C
#define UDDSSUBSCRIBER_C

DataReader* Subscriber_create_datareader ( Subscriber* self, Topic* a_topic, const struct DataReaderQos* qos, const struct DataReaderListener* listener, StatusMask mask)
{
   DataReader *dr;
   dr = malloc(sizeof(DataReader));
   dr->top = a_topic;
   //dr->sub = self; //añadir, tambien enlace con calidad de servicios
   dr->rqos.deadline.period.sec= qos->deadline.period.sec;
   dr->rqos.deadline.period.nanosec= qos->deadline.period.nanosec;
   dr->rqos.time_based_filter.minimum_separation.sec = qos->time_based_filter.minimum_separation.sec;
   dr->rqos.time_based_filter.minimum_separation.nanosec = qos->time_based_filter.minimum_separation.nanosec;
   return dr;
}

ReturnCode_t Subscriber_get_default_datareader_qos ( Subscriber* self, struct DataReaderQos* qos)
{
  //qos = default_datareader_qos;
}
#endif


