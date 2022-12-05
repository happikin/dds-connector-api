#include <dds_subscriber.hpp>
#include <state_manager.hpp>
#include <iostream>
#include <thread>

#include <listener.hpp>
#include <testdataTypeSupportC.h>
#include <testdataTypeSupportImpl.h>

std::atomic<bool> thread_state{control_state_e::alive};

int main(int argc, char *argv[]) {

    communication::dds::dds_node node(argc,argv);
    node.create_topic<TestData::MediaPacketTypeSupport_ptr,TestData::MediaPacketTypeSupportImpl>("TOPIC_A");
    
    communication::dds::dds_subscriber subscriber(node);
    DDS::DataReaderListener_ptr l = new listener;
    subscriber.create_reader<TestData::MediaPacketDataReader>(node,"TOPIC_A",l);
    subscriber.wait_for_publisher("TOPIC_A");
    
    while(thread_state != control_state_e::dead) {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
    return 0;
}
