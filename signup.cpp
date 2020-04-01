#include "signup.h"
#include "ui_signup.h"
#include "context.h"
#include "QMouseEvent"
#include <QTime>
#include "personal_info.h"

signup::signup(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::signup)
{
    ui->setupUi(this);
    ui->warning->hide();
    Context::windows->insert("signup", this);
}

signup::~signup()
{
    delete ui;
}

void signup::on_commandLinkButton_clicked()
{
    Context::windows->find("signup").value()->hide();
    QTime t;
    t.start();
    while(t.elapsed()<20)
        QCoreApplication::processEvents();
    Context::windows->find("login").value()->show();
}

void signup::on_pushButton_2_clicked()
{
    if(Personal_info::check_have(ui->lineEdit->text())){
        ui->warning->show();
    }
    else {
        ui->warning->hide();
        Personal_info::new_dictionary(ui->lineEdit->text(), ui->lineEdit_2->text());
        Context::windows->find("signup").value()->hide();
        QTime t;
        t.start();
        while(t.elapsed()<20)
            QCoreApplication::processEvents();
        Context::windows->find("login").value()->show();
    }
}

void signup::on_lineEdit_editingFinished()
{
    if(Personal_info::check_have(ui->lineEdit->text())){
        ui->warning->show();
    }
    else {
        ui->warning->hide();
    }
}
