#pragma once

#include <memory>
#include <utility>

enum class OpStatus
{
    OP_OK = 0,
    Q_IS_EMPTY,
    Q_IS_FULL
};

/* Simple circular queue/ring buffer without overwriting policy when max size is exceeded */
class CircularQueue
{
public:
    CircularQueue( std::size_t size );
    ~CircularQueue();
    OpStatus push_in( int in_val );
    std::pair<int, OpStatus> pop_out();

private:
    class CircularQueueImpl;
    std::unique_ptr<CircularQueueImpl> _impl;
};
