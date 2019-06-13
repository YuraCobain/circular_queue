#include "circular_queue.h"

#include <limits>
#include <vector>

class CircularQueue::CircularQueueImpl
{
public:
    CircularQueueImpl( std::size_t size )
        : _is_full( 0 ), _head( 0 ), _tail( 0 ), _storage( size )
    {
    }

    ~CircularQueueImpl() = default;

    OpStatus push_in( int in_val )
    {
        if (_is_full)
        {
            return OpStatus::Q_IS_FULL;
        }
        _storage[_head] = in_val;
        _head = ( _head + 1 ) % _storage.size();

        _is_full = _head == _tail;

        return OpStatus::OP_OK;
    }

    std::pair<int, OpStatus> pop_out()
    {
        if ( !_is_full && _head == _tail )
        {
            return {std::numeric_limits<int>::min(), OpStatus::Q_IS_EMPTY};
        }

        int out_val = _storage[_tail];
        _tail = ( _tail + 1 ) % _storage.size();
        _is_full = 0;

        return {out_val, OpStatus::OP_OK};
    }

private:
    int _is_full;
    std::size_t _head;
    std::size_t _tail;
    std::vector<int> _storage;
};

CircularQueue::CircularQueue( std::size_t size )
    : _impl( new CircularQueue::CircularQueueImpl( size ) )
{
}

CircularQueue::~CircularQueue() = default;

OpStatus CircularQueue::push_in( int in_val ) { return _impl->push_in( in_val ); }
std::pair<int, OpStatus> CircularQueue::pop_out() { return _impl->pop_out(); }
