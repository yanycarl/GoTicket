#include "login.h"
#include "ui_login.h"
#include "context.h"
#include <QTime>
#include "personal_info.h"

login::login(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::login)
{
    ui->setupUi(this);
    ui->warning->hide();
    Context::windows->insert("login", this);
}

login::~login()
{
    delete ui;
}

void login::on_Button_signup_clicked()
{
    ui->warning->hide();
    Context::windows->find("login").value()->hide();
    QTime t;
    t.start();
    while(t.elapsed()<20)
        QCoreApplication::processEvents();
    Context::windows->find("signup").value()->show();
}

void login::on_Button_login_clicked()
{
//    if(Personal_info::check_have(ui->user_id->text()) && Personal_info::check_psw(ui->user_id->text(), ui->psw->text())){
//        Context::windows->find("login").value()->hide();
//        QTime t;
//        t.start();
//        while(t.elapsed()<20)
//            QCoreApplication::processEvents();
//        Context::windows->find("person").value()->show();
//        ui->warning->hide();
//    }
//    else{
//        ui->warning->show();
//    }

    Context::windows->find("login").value()->hide();
    QTime t;
    t.start();
    while(t.elapsed()<20)
        QCoreApplication::processEvents();
    Context::windows->find("person").value()->show();
    Context::user_id = "yanycarl";
}
