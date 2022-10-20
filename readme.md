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