#include "back_timer.h"
#include <QTime>
#include <QApplication>
#include "context.h"
#include "person.h"

back_timer::back_timer()
{

}

back_timer* back_timer::instance = new back_timer();

back_timer* back_timer::getInstance(){
    return instance;
}

void back_timer::run(){
    while (true) {
        QTime t;
        t.start();
        while(t.elapsed()<10000)
            QCoreApplication::processEvents();
        emit static_cast<person*>(Context::windows->find("person").value())->my_signal();
    }
}
