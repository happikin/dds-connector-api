#include <dds_publisher.hpp>
#include <state_manager.hpp>
#include <csignal>
#include <thread>
#include <chrono>

#include <testdataTypeSupportC.h>
#include <testdataTypeSupportImpl.h>

std::atomic<bool> thread_state{control_state_e::alive};
void signal_handler(int _signal) {
    thread_state = control_state_e::dead;
}

int main(int argc, char *argv[]) {
    signal(SIGINT,signal_handler);
    
    communication::dds::dds_node node(argc,argv);
    node.create_topic<TestData::MediaPacketTypeSupport_ptr,TestData::MediaPacketTypeSupportImpl>("TOPIC_A");
    
    communication::dds::dds_publisher publisher(node);
    publisher.create_writer<TestData::MediaPacketDataWriter>(node,std::string("TOPIC_A"));
    auto ret_code = publisher.wait_for_subscriber("TOPIC_A");
    
    std::cout << "wait_for_subscriber() returned status " << ret_code << "\n";
    
    TestData::MediaPacket packet;
    packet.message = "";
    packet.id = 0;
    
    publisher.write<TestData::MediaPacket,TestData::MediaPacketDataWriter>(packet,"TOPIC_A");
    ret_code = publisher.wait_for_acknowledgments("TOPIC_A");
    
    std::cout << "ack " << ret_code << " received\n";

    while(thread_state != control_state_e::dead) {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
    
    return 0;
}
