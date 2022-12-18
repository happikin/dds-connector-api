#include <dds_subscriber.hpp>
#include <state_manager.hpp>
#include <iostream>
#include <thread>

#include <listener.hpp>
#include <testdataTypeSupportC.h>
#include <testdataTypeSupportImpl.h>

using namespace sdv;

std::atomic<bool> thread_state{thread_state_e::alive};
void signal_handler(int _signalid) {
    thread_state = thread_state_e::dead;
}

int main(int argc, char *argv[]) {
    signal(SIGINT,signal_handler);

    communication::dds::node dds_node(argc,argv);
    dds_node.create_topic<TestData::MediaPacketTypeSupport_ptr,TestData::MediaPacketTypeSupportImpl>("TOPIC_A");
    
    communication::dds::subscriber subscriber_one(dds_node);
    DDS::DataReaderListener_ptr listener_ptr = new listener;
    subscriber_one.create_reader<TestData::MediaPacketDataReader>(dds_node,"TOPIC_A",listener_ptr);
    subscriber_one.wait_for_publisher("TOPIC_A");

    while(thread_state != thread_state_e::dead) {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
    return 0;
}
