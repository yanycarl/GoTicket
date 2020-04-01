#include "personal_info_window.h"
#include "ui_personal_info_window.h"
#include "context.h"
#include <QTime>

personal_info_window::personal_info_window(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::personal_info_window)
{
    ui->setupUi(this);
    Context::windows->insert("personal_info", this);
}

personal_info_window::~personal_info_window()
{
    delete ui;
}


void personal_info_window::on_return_2_pressed()
{
    this->ui->return_2->setStyleSheet("border-image: url(:/button/Resource/return_hover.jpg);");
}

void personal_info_window::on_return_2_released()
{
    this->ui->return_2->setStyleSheet("border-image: url(:/button/Resource/return.jpg);");
}


void personal_info_window::on_return_2_clicked()
{
    Context::windows->find("person").value()->show();
    QTime t;
    t.start();
    while(t.elapsed()<50)
        QCoreApplication::processEvents();
    Context::windows->find("personal_info").value()->hide();
}
