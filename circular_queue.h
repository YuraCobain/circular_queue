#pragma once

#include <memory>

class CircularQueue {
    CircularQueue(std::size_t size);
    void push_in( int in_val );
    int pop_out( );
    private: 
        class CircularQueueImpl;
        std::unique_ptr<CircularQueueImpl> _impl;
};
