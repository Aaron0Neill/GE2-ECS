#ifndef OBSERVER_INCLUDE
#define OBSERVER_INCLUDE

class Observer
{
public:
    Observer() = default;
    virtual ~Observer() = default;

    virtual void onNotify(Event t_event) = 0;
};

#endif