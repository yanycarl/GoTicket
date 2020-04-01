#include "mainwindow.h"
#include "login.h"
#include "context.h"
#include "signup.h"
#include "person.h"
#include "personal_info_window.h"
#include <QApplication>
#include <QTime>
#include "rail_map.h"
#include "station_node.h"
#include <buy_result.h>
#include "readfile.h"
#include "personal_info.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    readFile::resolve();

    Personal_info::new_dictionary("yanycarl","");

    MainWindow w;
    login window_login;
    signup window_signup;
    personal_info_window window_personal_info;
    person window_person;
    Buy_result window_buy_result;

//    window_person.setWindowFlags(Qt::FramelessWindowHint);//无边框
//    window_personal_info.setWindowFlags(Qt::FramelessWindowHint);
//    w.setWindowFlags(Qt::FramelessWindowHint);//无边框
//    window_login.setWindowFlags(Qt::FramelessWindowHint);//无边框
//    window_signup.setWindowFlags(Qt::FramelessWindowHint);//无边框

    w.show();
    QTime t;
    t.start();
    while(t.elapsed()<2000)
        QCoreApplication::processEvents();
    w.hide();
    window_login.show();

    return a.exec();
}
