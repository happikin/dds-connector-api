#### points to be noted:-
-   there are three classes in this dds-connector api, namely dds_node, dds_publisher, dds_subscriber
-   all three classes fall under the `dds namespace`
-   and the `dds namespace` falls under the parent `fev namespace`
-   example use of a dds_node class is `fev::dds::dds_node node1(argc, argv);`
1. class name:- **dds_node**
   - details:- this class encapsulates the DDS::Participant and a std::map of DDS::Topic registered with that participant
   - in one cpp file there should be at least one instance of dds_node created first and it's constructor takes the argc and argv while construction.
   - member variables:- dds_node has following private member variables
     - DomainParticipantFactory_var
     - DomainParticipant_var
     - map<string, Topic_ptr>
     - std::mutex
   - member functions:- following public member functions exist
     - dds_node(int, char **)
     - create_topic(const std::string)
     - get_participant()
     - get_topic(const std::string)
     - ~dds_node()

2.  class name:- **dds_publisher**
       - details:- this class serves the purpose of encapsulating the publisher with a collection of all data writers associated with it
       - it's not possible to construct a dds_publisher using it's default constructor because it needs a by reference instance of a dds_node class
       - member variables:- dds_publisher has the following variables
         - std::mutex
         - DDS::Publisher_var
         - std::map<std::string, DDS::DataWriter_ptr>
       - member functions:- following member functions are available for users to use
          - dds_publisher(dds_node&)
          - create_writer(dds_node&, const std::string&)
          - wait_for_subscriber(const std::string)
          - write(payload_type, const std::string)
          - wait_for_acknowledgements(const std::string, DDS::Duration_t)
          - ~dds_publisher()

3.  class name:- **dds_subscriber**
    -  details:- this class serves the purpose of encapsulating a dds subscriber with a collection of all associated data readers
    -  just like dds_publisher we need a dds_node instance by reference to construct a dds_subscriber as it's default constructor is marked deleted
    -  member variables:- following are it's member variables
       -  DDS::Subscriber_var
       -  std::map<std::string, DDS::DataReader_ptr>
    -  member functions:- following are the user accessible functions
       -  dds_subscriber(dds_node&)
       -  create_reader(dds_node& const std::string, DDS::DaraReaderListener_ptr)
       -  wait_for_publisher(const std::string)
       -  ~dds_subscriber()

#### How to create a simple publisher:-
1. create an instance of dds::node to initiate a domain participant in dds domain like this `communication::dds::node dds_node(argc,argv);`
2. create a topic in the above created dds_node like this `dds_node.create_topic<TestData::MediaPacketTypeSupport_ptr,TestData::MediaPacketTypeSupportImpl>("TOPIC_A");`
   - create_topic() is a template based function which takes in two template paramenters namely `type_support` and `type_support_impl`
   - these types are auto generated by the TAO and IDL compilers from your .idl file
   - eg. for an idl struct `MediaPacket`, `type_support` will be `MediaPacketTypeSupport_ptr` and `type_support_impl` will be `MediaPacketTypeSupportImpl`
   - and the actual argument to this function is a topic name, which can be in std::string format
3. now we can start creating the actual publisher using the following syntax `communication::dds::publisher publisher_one(dds_node);`, the dds_node is passed by reference in the constructor to show that publisher_one wants to specifically exist in the dds_node because there could be more than one dds::node and dds::publisher
4. next task is to create a data writer and link it with the above created publisher, use the following syntax `publisher_one.create_writer<TestData::MediaPacketDataWriter>(dds_node,std::string("TOPIC_A"));`.
   - as you can see create_writer() is also a template function which takes in a template paramenter namely `writer_t`, which is the type of the data writer corresponding to your idl struct.
   In this case the idl struct is `MediaPacket` thus the data writer type will be `TestData::MediaPacketDataWriter`
   - then we need to pass two actual function arguments namely `dds::node` and `topic name`, which here are dds_node and TOPIC_A
5. now if we want to wait for a subscriber on TOPIC_A we can use the wait_for_acknowledgements() function which simply takes in the topic name to wait on and gives a return code
6. now we are ready to transmit some data in the form of `MediaPacket`, so lets create an object `packet` and the use the write() function on the publisher_one to send the data packet over dds.
To do so use the following syntax `publisher_one.write<TestData::MediaPacket,TestData::MediaPacketDataWriter>(packet,"TOPIC_A");`
   - write() is again a template based function which takes in two template arguments namely `payload_type` and `writer_t`, in our case these are `MediaPacket` and `MediaPacketDataWriter` respectively.
   - then pass in the `packet` and topic name as actual arguments to this call
7. finally we can wait for some ack from subscriber using the following syntax `publisher_one.wait_for_acknowledgments("TOPIC_A");`
*NOTE:- [click here](./single_publisher.cpp) to open the file with full publisher code*