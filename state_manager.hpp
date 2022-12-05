#pragma once

enum control_signal_e {
    terminate
};

enum control_state_e {
    alive,
    dead
};

class blockpoint {
    public:
        void wait_while() {}
};