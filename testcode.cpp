#include "dds_publisher.hpp"
#include <csignal>
bool flag{false};
void signal_handler(int _signal) {
    flag = true;
}

int main(int argc, char *argv[]) {
    signal(SIGINT,signal_handler);
    fev::dds::dds_node node1(argc,argv);
    while(flag == false);
    return 0;
}
