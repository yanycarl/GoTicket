#ifndef BACK_TIMER_H
#define BACK_TIMER_H
#include <QThread>


class back_timer: public QThread
{
public:
    static back_timer* getInstance();
private:
    static back_timer* instance;
    void run();
    back_timer();
};

#endif // BACK_TIMER_H
