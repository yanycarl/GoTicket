#include "person.h"
#include "ui_person.h"
#include "QThread"
#include "QObject"
#include <QTime>
#include "context.h"
#include "back_timer.h"
#include <iostream>
#include <set>
#include <QMenu>
#include <rail_map.h>
#include <buy_result.h>
#include <QFile>
#include "orders.h"


QMap <int, int> *person::position = new QMap <int, int>();

person::person(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::person)
{
    ui->setupUi(this);
    ui->station_list->hide();
    ui->calendarWidget->hide();
    ui->searchLine->setPlaceholderText("输入汉字或字母查询");

    ui->calendarWidget->setDateRange(QDate::currentDate(), QDate::currentDate().addDays(60));

    ui->Button_personalInfo->setMask(QRegion(0,0,220,220,QRegion::Ellipse));
    ui->Button_money->setMask(QRegion(0,0,220,220,QRegion::Ellipse));
    ui->Button_privacy->setMask(QRegion(0,0,220,220,QRegion::Ellipse));
    ui->Button_setting->setMask(QRegion(0,0,220,220,QRegion::Ellipse));
    ui->Button_Author->setMask(QRegion(0,0,220,220,QRegion::Ellipse));
    ui->Button_logout->setMask(QRegion(0,0,220,220,QRegion::Ellipse));
    ui->Button_switch->setMask(QRegion(45,45,70,70,QRegion::Ellipse));
    connect(this, SIGNAL(my_signal()),this, SLOT(change_back()));
    Context::windows->insert("person", this);
    back_timer *ins = back_timer::getInstance();
    ins->start();

    position->insert(1, 1366);
    position->insert(2, 2732);
    position->insert(3, 4098);
    position->insert(-1, -1366);
    position->insert(-2, -2732);
    position->insert(-3, -4098);
    position->insert(0, 0);

    for(QString item:rail_map::get_data()->keys()){
        QListWidgetItem *list_i1 = new QListWidgetItem();
        list_i1->setText(item);
        ui->list_stations->addItem(list_i1);
    }
}

void person::initialization(){
    ui->listWidget->clear();
    QVector<orders::order_node*>* temp_map;
    if(!orders::data->contains(Context::user_id)){
        ui->label_none->show();
        return;
    }
    ui->label_none->hide();
    temp_map = orders::data->find(Context::user_id).value();
    for(int p=0; p < temp_map->size(); p++){
        QListWidgetItem *list_i1 = new QListWidgetItem();
        QString* str = new QString();
        str->append("订单号：" + temp_map->at(p)->order_number);
        str->append("\n 日期：" + temp_map->at(p)->date);
        str->append("                 车次：" + temp_map->at(p)->number_train+ "\n");
        str->append(temp_map->at(p)->start);
        str->append("  ->  ");
        str->append(temp_map->at(p)->end);
        str->append("\n 车厢号：" + temp_map->at(p)->cabin);
        str->append("                 座位：" + temp_map->at(p)->seat);
        str->append("\n---------------------------------");
        list_i1->setText(*str);
        ui->listWidget->addItem(list_i1);
    }
}

person::~person()
{
    delete ui;
}

void person::change_back(){
    if(this->pic == 0){
        this->ui->wall->setStyleSheet("border-image: url(:/pages/Resource/page2.jpg);");
        this->pic++;
    }
    else if(this->pic == 1){
        this->ui->wall->setStyleSheet("border-image: url(:/pages/Resource/page3.jpg);");
        this->pic++;
    }
    else if(this->pic == 2){
        this->ui->wall->setStyleSheet("border-image: url(:/pages/Resource/page4.jpg);");
        this->pic++;
    }
    else if(this->pic == 3){
        this->ui->wall->setStyleSheet("border-image: url(:/pages/Resource/page1.jpg);");
        this->pic = 0;
    }
}

void person::on_Button_personalInfo_clicked()
{
    Context::windows->find("person").value()->hide();
    QTime t;
    t.start();
    while(t.elapsed()<50)
        QCoreApplication::processEvents();
    Context::windows->find("personal_info").value()->show();
}


void person::on_Button_logout_pressed()
{
    this->ui->Button_logout->setStyleSheet("border-image: url(:/button/Resource/buttom_logout_hover.bmp);");
}

void person::on_Button_logout_released()
{
    this->ui->Button_logout->setStyleSheet("border-image: url(:/button/Resource/buttom_logout.bmp);");

}

void person::on_Button_personalInfo_pressed()
{
    this->ui->Button_personalInfo->setStyleSheet("border-image: url(:/button/Resource/button_person_hover.jpg);");
}

void person::on_Button_personalInfo_released()
{
    this->ui->Button_personalInfo->setStyleSheet("border-image: url(:/button/Resource/button_person.jpg);");
}

void person::on_Button_Author_pressed()
{
    this->ui->Button_Author->setStyleSheet("border-image: url(:/button/Resource/button_about_hover.jpg);");
}

void person::on_Button_Author_released()
{
    this->ui->Button_Author->setStyleSheet("border-image: url(:/button/Resource/button_about.jpg);");
}

void person::on_Button_privacy_pressed()
{
    this->ui->Button_privacy->setStyleSheet("border-image: url(:/button/Resource/button_privacy_hover.jpg);");
}

void person::on_Button_privacy_released()
{
    this->ui->Button_privacy->setStyleSheet("border-image: url(:/button/Resource/button_privacy.jpg);");
}

void person::on_Button_money_pressed()
{
    this->ui->Button_money->setStyleSheet("border-image: url(:/button/Resource/button_money_hover.jpg);");
}

void person::on_Button_money_released()
{
    this->ui->Button_money->setStyleSheet("border-image: url(:/button/Resource/button_money.jpg);");
}


void person::on_Button_setting_pressed()
{
    this->ui->Button_setting->setStyleSheet("border-image: url(:/button/Resource/button_setting_hover.jpg);");
}

void person::on_Button_setting_released()
{
    this->ui->Button_setting->setStyleSheet("border-image: url(:/button/Resource/button_setting.jpg);");
}

void person::on_Button_Author_clicked()
{

}

void person::on_Person_clicked()
{
    ui->Buy->setEnabled(false);
    ui->Trip->setEnabled(false);
    ui->Order->setEnabled(false);
    ui->Person->setEnabled(false);

    int current_index = static_cast<person*>(Context::windows->find("person").value())->current;
    int distance_index = current_index - 3;
    int distance = static_cast<person*>(Context::windows->find("person").value())->position->find(distance_index).value();
    distance = (distance)/20;
    for (int i=0; i<20; i++) {
        QTime t;
        t.start();
        while(t.elapsed()<20)
            QCoreApplication::processEvents();
        this->ui->PersonalInfo_Widget->move(ui->PersonalInfo_Widget->x()+distance, 20);
        this->ui->Buy_widget->move(ui->Buy_widget->x()+distance, 20);
        this->ui->Order_widget->move(ui->Order_widget->x()+distance, 20);
        this->ui->Trip_widget->move(ui->Trip_widget->x()+distance, 20);
    }

    switch (current_index) {
    case 0:{
        ui->Buy->setStyleSheet("font: 14pt '黑体';background-color: rgba(255, 255, 255, 50);color: rgb(255, 255, 255);");
        ui->Trip->setStyleSheet("font: 14pt '黑体';background-color: rgba(255, 255, 255, 50);color: rgb(255, 255, 255);border-image: url(:/button/Resource/button_select.jpg);");
        QTime t;
        t.start();
        while(t.elapsed()<100)
            QCoreApplication::processEvents();
    }
    [[clang::fallthrough]]; case 1: {
        ui->Trip->setStyleSheet("font: 14pt '黑体';background-color: rgba(255, 255, 255, 50);color: rgb(255, 255, 255);");
        ui->Order->setStyleSheet("font: 14pt '黑体';background-color: rgba(255, 255, 255, 50);color: rgb(255, 255, 255);border-image: url(:/button/Resource/button_select.jpg);");
        QTime t;
        t.start();
        while(t.elapsed()<100)
            QCoreApplication::processEvents();
    }
    [[clang::fallthrough]]; case 2:{
        ui->Order->setStyleSheet("font: 14pt '黑体';background-color: rgba(255, 255, 255, 50);color: rgb(255, 255, 255);");
        ui->Person->setStyleSheet("font: 14pt '黑体';background-color: rgba(255, 255, 255, 50);color: rgb(255, 255, 255);border-image: url(:/button/Resource/button_select.jpg);");
        QTime t;
        t.start();
        while(t.elapsed()<100)
            QCoreApplication::processEvents();
    }
    }

    static_cast<person*>(Context::windows->find("person").value())->current = 3;

    ui->Buy->setEnabled(true);
    ui->Trip->setEnabled(true);
    ui->Order->setEnabled(true);
    ui->Person->setEnabled(true);
}



void person::on_Buy_clicked()
{
    ui->Buy->setEnabled(false);
    ui->Trip->setEnabled(false);
    ui->Order->setEnabled(false);
    ui->Person->setEnabled(false);

    int current_index = static_cast<person*>(Context::windows->find("person").value())->current;
    int distance_index = current_index;
    int distance = static_cast<person*>(Context::windows->find("person").value())->position->find(distance_index).value();
    distance = (distance)/20;
    for (int i=0; i<20; i++) {
        QTime t;
        t.start();
        while(t.elapsed()<20)
            QCoreApplication::processEvents();
        this->ui->PersonalInfo_Widget->move(ui->PersonalInfo_Widget->x()+distance, 20);
        this->ui->Buy_widget->move(ui->Buy_widget->x()+distance, 20);
        this->ui->Order_widget->move(ui->Order_widget->x()+distance, 20);
        this->ui->Trip_widget->move(ui->Trip_widget->x()+distance, 20);
    }

    switch (current_index) {
    case 3:{
        ui->Person->setStyleSheet("font: 14pt '黑体';background-color: rgba(255, 255, 255, 50);color: rgb(255, 255, 255);");
        ui->Order->setStyleSheet("font: 14pt '黑体';background-color: rgba(255, 255, 255, 50);color: rgb(255, 255, 255);border-image: url(:/button/Resource/button_select.jpg);");
        QTime t;
        t.start();
        while(t.elapsed()<100)
            QCoreApplication::processEvents();
    }
    [[clang::fallthrough]]; case 2: {
        ui->Order->setStyleSheet("font: 14pt '黑体';background-color: rgba(255, 255, 255, 50);color: rgb(255, 255, 255);");
        ui->Trip->setStyleSheet("font: 14pt '黑体';background-color: rgba(255, 255, 255, 50);color: rgb(255, 255, 255);border-image: url(:/button/Resource/button_select.jpg);");
        QTime t;
        t.start();
        while(t.elapsed()<100)
            QCoreApplication::processEvents();
    }
    [[clang::fallthrough]]; case 1:{
        ui->Trip->setStyleSheet("font: 14pt '黑体';background-color: rgba(255, 255, 255, 50);color: rgb(255, 255, 255);");
        ui->Buy->setStyleSheet("font: 14pt '黑体';background-color: rgba(255, 255, 255, 50);color: rgb(255, 255, 255);border-image: url(:/button/Resource/button_select.jpg);");
        QTime t;
        t.start();
        while(t.elapsed()<100)
            QCoreApplication::processEvents();
    }
    }

    static_cast<person*>(Context::windows->find("person").value())->current = 0;
    ui->Buy->setEnabled(true);
    ui->Trip->setEnabled(true);
    ui->Order->setEnabled(true);
    ui->Person->setEnabled(true);
}

void person::on_Trip_clicked()
{
    ui->Buy->setEnabled(false);
    ui->Trip->setEnabled(false);
    ui->Order->setEnabled(false);
    ui->Person->setEnabled(false);

    int current_index = static_cast<person*>(Context::windows->find("person").value())->current;
    int distance_index = current_index-1;
    int distance = static_cast<person*>(Context::windows->find("person").value())->position->find(distance_index).value();
    distance = (distance)/20;
    for (int i=0; i<20; i++) {
        QTime t;
        t.start();
        while(t.elapsed()<20)
            QCoreApplication::processEvents();
        this->ui->PersonalInfo_Widget->move(ui->PersonalInfo_Widget->x()+distance, 20);
        this->ui->Buy_widget->move(ui->Buy_widget->x()+distance, 20);
        this->ui->Order_widget->move(ui->Order_widget->x()+distance, 20);
        this->ui->Trip_widget->move(ui->Trip_widget->x()+distance, 20);
    }

    switch (current_index) {
    case 3:{
        ui->Person->setStyleSheet("font: 14pt '黑体';background-color: rgba(255, 255, 255, 50);color: rgb(255, 255, 255);");
        ui->Order->setStyleSheet("font: 14pt '黑体';background-color: rgba(255, 255, 255, 50);color: rgb(255, 255, 255);border-image: url(:/button/Resource/button_select.jpg);");
        QTime t;
        t.start();
        while(t.elapsed()<100)
            QCoreApplication::processEvents();
    }
    [[clang::fallthrough]]; case 2: {
        ui->Order->setStyleSheet("font: 14pt '黑体';background-color: rgba(255, 255, 255, 50);color: rgb(255, 255, 255);");
        ui->Trip->setStyleSheet("font: 14pt '黑体';background-color: rgba(255, 255, 255, 50);color: rgb(255, 255, 255);border-image: url(:/button/Resource/button_select.jpg);");
        QTime t;
        t.start();
        while(t.elapsed()<100)
            QCoreApplication::processEvents();
        break;
    }
    case 0:{
        ui->Buy->setStyleSheet("font: 14pt '黑体';background-color: rgba(255, 255, 255, 50);color: rgb(255, 255, 255);");
        ui->Trip->setStyleSheet("font: 14pt '黑体';background-color: rgba(255, 255, 255, 50);color: rgb(255, 255, 255);border-image: url(:/button/Resource/button_select.jpg);");
        QTime t;
        t.start();
        while(t.elapsed()<100)
            QCoreApplication::processEvents();
    }
    }

    static_cast<person*>(Context::windows->find("person").value())->current = 1;
    ui->Buy->setEnabled(true);
    ui->Trip->setEnabled(true);
    ui->Order->setEnabled(true);
    ui->Person->setEnabled(true);
}

void person::on_Order_clicked()
{

    this->initialization();

    ui->Buy->setEnabled(false);
    ui->Trip->setEnabled(false);
    ui->Order->setEnabled(false);
    ui->Person->setEnabled(false);

    int current_index = static_cast<person*>(Context::windows->find("person").value())->current;
    int distance_index = current_index-2;
    int distance = static_cast<person*>(Context::windows->find("person").value())->position->find(distance_index).value();
    distance = (distance)/20;
    for (int i=0; i<20; i++) {
        QTime t;
        t.start();
        while(t.elapsed()<20)
            QCoreApplication::processEvents();
        this->ui->PersonalInfo_Widget->move(ui->PersonalInfo_Widget->x()+distance, 20);
        this->ui->Buy_widget->move(ui->Buy_widget->x()+distance, 20);
        this->ui->Order_widget->move(ui->Order_widget->x()+distance, 20);
        this->ui->Trip_widget->move(ui->Trip_widget->x()+distance, 20);
    }

    switch (current_index) {
        case 3:{
            ui->Person->setStyleSheet("font: 14pt '黑体';background-color: rgba(255, 255, 255, 50);color: rgb(255, 255, 255);");
            ui->Order->setStyleSheet("font: 14pt '黑体';background-color: rgba(255, 255, 255, 50);color: rgb(255, 255, 255);border-image: url(:/button/Resource/button_select.jpg);");
            QTime t;
            t.start();
            while(t.elapsed()<100)
                QCoreApplication::processEvents();
            break;
        }
        case 0:{
            ui->Buy->setStyleSheet("font: 14pt '黑体';background-color: rgba(255, 255, 255, 50);color: rgb(255, 255, 255);");
            ui->Trip->setStyleSheet("font: 14pt '黑体';background-color: rgba(255, 255, 255, 50);color: rgb(255, 255, 255);border-image: url(:/button/Resource/button_select.jpg);");
            QTime t;
            t.start();
            while(t.elapsed()<100)
                QCoreApplication::processEvents();
        }
        [[clang::fallthrough]]; case 1: {
            ui->Trip->setStyleSheet("font: 14pt '黑体';background-color: rgba(255, 255, 255, 50);color: rgb(255, 255, 255);");
            ui->Order->setStyleSheet("font: 14pt '黑体';background-color: rgba(255, 255, 255, 50);color: rgb(255, 255, 255);border-image: url(:/button/Resource/button_select.jpg);");
            QTime t;
            t.start();
            while(t.elapsed()<100)
                QCoreApplication::processEvents();
            break;
        }
    }

    static_cast<person*>(Context::windows->find("person").value())->current = 2;

    ui->Buy->setEnabled(true);
    ui->Trip->setEnabled(true);
    ui->Order->setEnabled(true);
    ui->Person->setEnabled(true);
}

void person::on_pushButton_7_pressed()
{
    ui->pushButton_7->setStyleSheet("font: 24pt '楷体';border-image: url(:/button/Resource/button_search_hover.jpg); color: rgb(255, 255, 255);");
}

void person::on_pushButton_7_released()
{
    ui->pushButton_7->setStyleSheet("font: 24pt '楷体';border-image: url(:/button/Resource/button_search.jpg); color: rgb(255, 255, 255);");
}

void person::on_Button_start_clicked()
{
    if(ui->Button_end->isEnabled()){
        ui->Button_end->setEnabled(false);
        static_cast<person*>(Context::windows->find("person").value())->direct = 1;
        ui->searchLine->clear();
        ui->station_list->show();
        ui->Button_start->setStyleSheet("background-color: rgba(255, 255, 255, 220);font: 16pt '楷体';");
    }
    else{
        ui->Button_end->setEnabled(true);
        ui->station_list->hide();
        ui->Button_start->setStyleSheet("background-color: rgba(255, 255, 255, 120);font: 16pt '楷体';");
    }
}

void person::on_list_stations_itemClicked(QListWidgetItem *item)
{
    if(static_cast<person*>(Context::windows->find("person").value())->direct == 1){
        ui->Button_start->setText("始发站\n\n"+item->text());
        ui->Button_start->setStyleSheet("background-color: rgba(255, 255, 255, 120);font: 16pt '楷体';");
    }
    else{
        ui->Button_end->setText("终到站\n\n"+item->text());
        ui->Button_end->setStyleSheet("background-color: rgba(255, 255, 255, 120);font: 16pt '楷体';");
    }
    ui->station_list->hide();
    ui->Button_start->setEnabled(true);
    ui->Button_end->setEnabled(true);
}

void person::on_searchLine_textChanged(const QString &arg1)
{
    for(QListWidgetItem* item:ui->list_stations->findItems(arg1, Qt::MatchContains)){
        ui->list_stations->insertItem(0, ui->list_stations->takeItem(ui->list_stations->row(item)));
    }
    ui->list_stations->scrollToItem(ui->list_stations->item(0));
}

void person::on_Button_end_clicked()
{
    if(ui->Button_start->isEnabled()){
        ui->Button_start->setEnabled(false);
        static_cast<person*>(Context::windows->find("person").value())->direct = 2;
        ui->searchLine->clear();
        ui->station_list->show();
        ui->Button_end->setStyleSheet("background-color: rgba(255, 255, 255, 220);font: 16pt '楷体';");
    }
    else{
        ui->Button_start->setEnabled(true);
        ui->station_list->hide();
        ui->Button_end->setStyleSheet("background-color: rgba(255, 255, 255, 120);font: 16pt '楷体';");
    }
}

void person::on_Button_switch_clicked()
{
    QString s = ui->Button_end->text();
    QString s2 = ui->Button_start->text();
    ui->Button_start->setText("始发站\n\n"+s.right(s.length()-5));
    ui->Button_end->setText("终到站\n\n"+s2.right(s2.length()-5));
}

void person::on_calendarWidget_clicked(const QDate &date)
{
    std::string string;
    char* ch = new char[16];
    itoa(date.month(), ch ,10);
    string = std::string(ch)+ std::string("月");
    itoa(date.day(), ch ,10);
    string += std::string(ch)+ std::string("日  星期");
    switch(date.dayOfWeek()){
        case 1: string += "一"; break;
        case 2: string += "二"; break;
        case 3: string += "三"; break;
        case 4: string += "四"; break;
        case 5: string += "五"; break;
        case 6: string += "六"; break;
        case 7: string += "日"; break;
    }
    string += std::string("  （");
    if(date != QDate::currentDate()){
        itoa(static_cast<int>(-1 * date.daysTo(QDate::currentDate())), ch ,10);
        string += std::string(ch)+ std::string("天后）");
    }
    else{
        string += std::string("今天）");
    }
    ui->pushButton_13->setText(QString(string.c_str()));
    ui->pushButton_13->setStyleSheet("font: 16pt '微软雅黑';background-color: rgba(255, 255, 255, 120);");
    ui->calendarWidget->hide();
}

void person::on_pushButton_13_clicked()
{
    ui->calendarWidget->show();
    ui->pushButton_13->setStyleSheet("font: 16pt '微软雅黑';background-color: rgba(255, 255, 255, 220);");
}

void person::on_pushButton_7_clicked()
{
    rail_map::reset_searchResult();
    rail_map::reset_counter();
    rail_map::set_currentDate(ui->pushButton_13->text());
    ui->calendarWidget->hide();
    ui->station_list->hide();
    ui->Button_start->setEnabled(true);
    ui->Button_end->setEnabled(true);
    ui->pushButton_13->setStyleSheet("font: 16pt '微软雅黑';background-color: rgba(255, 255, 255, 120);");
    ui->Button_start->setStyleSheet("background-color: rgba(255, 255, 255, 120);font: 16pt '楷体';");
    ui->Button_end->setStyleSheet("background-color: rgba(255, 255, 255, 120);font: 16pt '楷体';");
    rail_map::find_path(ui->Button_start->text().right(ui->Button_start->text().length()-5), ui->Button_end->text().right(ui->Button_end->text().length()-5));
    emit static_cast<Buy_result*>(Context::windows->find("buy_result").value())->signal();
    Context::windows->find("person").value()->hide();
    Context::windows->find("buy_result").value()->show();
}
