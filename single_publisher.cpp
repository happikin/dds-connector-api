#include <dds_publisher.hpp>
#include <state_manager.hpp>
#include <csignal>
#include <thread>
#include <chrono>

#include <testdataTypeSupportC.h>
#include <testdataTypeSupportImpl.h>

using namespace sdv;

std::atomic<bool> thread_state{thread_state_e::alive};
void signal_handler(int _signal) {
    thread_state = thread_state_e::dead;
}

int main(int argc, char **argv) {
    signal(SIGINT,signal_handler);

    communication::dds::node dds_node(argc,argv);
    dds_node.create_topic<TestData::MediaPacketTypeSupport_ptr,TestData::MediaPacketTypeSupportImpl>("TOPIC_A");
    
    communication::dds::publisher publisher_one(dds_node);
    publisher_one.create_writer<TestData::MediaPacketDataWriter>(dds_node,std::string("TOPIC_A"));
    auto ret_code = publisher_one.wait_for_subscriber("TOPIC_A");
    
    std::cout << "wait_for_subscriber() returned status " << ret_code << "\n";
    
    TestData::MediaPacket packet;
    packet.message = "";
    packet.id = 0;
    
    publisher_one.write<TestData::MediaPacket,TestData::MediaPacketDataWriter>(packet,"TOPIC_A");
    ret_code = publisher_one.wait_for_acknowledgments("TOPIC_A");
    
    std::cout << "ack " << ret_code << " received\n";

    while(thread_state != thread_state_e::dead) {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
    
    return 0;
}
