#include "buy_result.h"
#include "ui_buy_result.h"
#include "context.h"
#include "rail_map.h"
#include <QListWidget>
#include <QListWidgetItem>
#include <iostream>
#include <QMap>
#include <string>
#include <QTime>
#include <math.h>
#include "orders.h"
#include <QMessageBox>

QString Buy_result::current_number_train = "";
QString Buy_result::current_start = "";
QString Buy_result::current_end = "";
int Buy_result::seg_num;

Buy_result::Buy_result(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Buy_result)
{
    ui->setupUi(this);
    ui->submit->hide();
    Context::windows->insert("buy_result", this);
    connect(this, SIGNAL(signal()),this, SLOT(initialization()));
}

Buy_result::~Buy_result()
{
    delete ui;
}

void Buy_result::initialization(){
    ui->select_train->show();
    ui->select_seat->hide();
    ui->listWidget->clear();
    ui->cabin_2->hide();
    ui->submit->hide();
    int p=1;
    QMap<QString, QMap<QString, QString>*>* temp_map;
    for(; p <= rail_map::get_sizeSearchResult(); p++){
        temp_map = rail_map::get_searchResultItem(p);
        int p2 = 1;
        for(; p2<temp_map->size()+1; p2++){
            QListWidgetItem *list_i1 = new QListWidgetItem();
            QString* str = new QString();
            str->append(temp_map->find(QString(p2)).value()->find("start").value());
            str->append("  ->  ");
            str->append(temp_map->find(QString(p2)).value()->find("end").value());
            str->append("\n" + temp_map->find(QString(p2)).value()->find("number").value());
            list_i1->setText(*str+"\n"+ rail_map::get_currentDate());
            list_i1->setSizeHint(QSize(1150, 100));
            ui->listWidget->addItem(list_i1);
        }
    }
}

int Buy_result::previous = -2;

void Buy_result::on_listWidget_itemClicked(QListWidgetItem *item)
{
    int pos = static_cast<Buy_result*>(Context::windows->find("but_result").value())->previous;
    if(previous == -2){
        pos = ui->listWidget->row(item);
        QListWidgetItem *list_i1 = new QListWidgetItem();
        QFont f;
        f.setPixelSize(20);
        list_i1->setFont(f);
        list_i1->setBackground(QBrush(QColor(255,255,255,200)));
        list_i1->setText("余票信息：\n 商务座：有票   一等座:有票   二等座：有票   无座：有票");
        list_i1->setSizeHint(QSize(1150, 80));
        ui->listWidget->insertItem(pos+1, list_i1);
        static_cast<Buy_result*>(Context::windows->find("but_result").value())->previous = pos+1;
    }
    else{
        int pos2 = ui->listWidget->row(item);
        if(pos2 == static_cast<Buy_result*>(Context::windows->find("but_result").value())->previous){
            return;
        }
        ui->listWidget->takeItem(pos);
        pos2 = ui->listWidget->row(item);
        QListWidgetItem *list_i1 = new QListWidgetItem();
        QFont f;
        f.setPixelSize(20);
        list_i1->setFont(f);
        list_i1->setBackground(QBrush(QColor(255,255,255,200)));
        list_i1->setText("余票信息：\n 商务座：有票   一等座:有票   二等座：有票   无座：有票");
        list_i1->setSizeHint(QSize(1150, 80));
        ui->listWidget->insertItem(pos2+1, list_i1);
        static_cast<Buy_result*>(Context::windows->find("but_result").value())->previous = pos2+1;
    }
}

void Buy_result::on_listWidget_itemDoubleClicked(QListWidgetItem *item)
{
    ui->horizontalSlider->setValue(0);
    int pos = ui->listWidget->row(item);
    int p=1;
    int q = -1;
    QMap<QString, QMap<QString, QString>*>* temp_map;
    for(; p <= rail_map::get_sizeSearchResult(); p++){
        temp_map = rail_map::get_searchResultItem(p);
        int p2 = 1;
        this->seg_num = 0;
        for(; p2<temp_map->size()+1; p2++){
            q++;
            if(q == pos){
                this->current_end = temp_map->find(QString(p2)).value()->find("end").value();
                this->current_start = temp_map->find(QString(p2)).value()->find("start").value();
                this->current_number_train = temp_map->find(QString(p2)).value()->find("number").value();
                if(temp_map->size()>1 && p2!=temp_map->size()){
                    this->seg_num = q+1;
                }
                ui->select_train->hide();
                ui->select_seat->show();
                return;
            }
        }
    }
}

void Buy_result::on_pushButton_clicked()
{
    this->seat = ui->pushButton->text();
    this->createOrder();
}

void Buy_result::on_pushButton_2_clicked()
{
    this->seat = ui->pushButton_2->text();
    this->createOrder();
}

void Buy_result::on_pushButton_3_clicked()
{
    this->seat = ui->pushButton_3->text();
    this->createOrder();
}

void Buy_result::on_pushButton_4_clicked()
{
    this->seat = ui->pushButton_4->text();
    this->createOrder();
}

void Buy_result::on_pushButton_5_clicked()
{
    this->seat = ui->pushButton_5->text();
    this->createOrder();
}


void Buy_result::on_pushButton_13_clicked()
{
    this->seat = ui->pushButton_13->text();
    this->createOrder();
}

void Buy_result::on_pushButton_14_clicked()
{
    this->seat = ui->pushButton_14->text();
    this->createOrder();
}

void Buy_result::on_pushButton_11_clicked()
{
    this->seat = ui->pushButton_11->text();
    this->createOrder();
}

void Buy_result::on_pushButton_12_clicked()
{
    this->seat = ui->pushButton_12->text();
    this->createOrder();
}

void Buy_result::on_pushButton_15_clicked()
{
    this->seat = ui->pushButton_15->text();
    this->createOrder();
}

void Buy_result::on_pushButton_22_clicked()
{
    this->seat = ui->pushButton_22->text();
    this->createOrder();
}

void Buy_result::on_pushButton_23_clicked()
{
    this->seat = ui->pushButton_23->text();
    this->createOrder();
}

void Buy_result::on_pushButton_17_clicked()
{
    this->seat = ui->pushButton_17->text();
    this->createOrder();
}

void Buy_result::on_pushButton_19_clicked()
{
    this->seat = ui->pushButton_19->text();
    this->createOrder();
}

void Buy_result::on_pushButton_24_clicked()
{
    this->seat = ui->pushButton_24->text();
    this->createOrder();
}

void Buy_result::on_pushButton_20_clicked()
{
    this->seat = ui->pushButton_20->text();
    this->createOrder();
}

void Buy_result::on_pushButton_16_clicked()
{
    this->seat = ui->pushButton_16->text();
    this->createOrder();
}

void Buy_result::on_pushButton_21_clicked()
{
    this->seat = ui->pushButton_21->text();
    this->createOrder();
}

void Buy_result::on_pushButton_18_clicked()
{
    this->seat = ui->pushButton_18->text();
    this->createOrder();
}

void Buy_result::on_pushButton_25_clicked()
{
    this->seat = ui->pushButton_25->text();
    this->createOrder();
}

void Buy_result::on_pushButton_32_clicked()
{
    this->seat = ui->pushButton_32->text();
    this->createOrder();
}

void Buy_result::on_pushButton_33_clicked()
{
    this->seat = ui->pushButton_33->text();
    this->createOrder();
}

void Buy_result::on_pushButton_27_clicked()
{
    this->seat = ui->pushButton_27->text();
    this->createOrder();
}

void Buy_result::on_pushButton_29_clicked()
{
    this->seat = ui->pushButton_29->text();
    this->createOrder();
}

void Buy_result::on_pushButton_34_clicked()
{
    this->seat = ui->pushButton_34->text();
    this->createOrder();
}

void Buy_result::on_pushButton_30_clicked()
{
    this->seat = ui->pushButton_30->text();
    this->createOrder();
}

void Buy_result::on_pushButton_26_clicked()
{
    this->seat = ui->pushButton_26->text();
    this->createOrder();
}

void Buy_result::on_pushButton_31_clicked()
{
    this->seat = ui->pushButton_31->text();
    this->createOrder();
}

void Buy_result::on_pushButton_28_clicked()
{
    this->seat = ui->pushButton_28->text();
    this->createOrder();
}

void Buy_result::on_pushButton_35_clicked()
{
    this->seat = ui->pushButton_35->text();
    this->createOrder();
}

void Buy_result::on_horizontalSlider_sliderMoved(int position)
{
    ui->cabin_2->show();
    if(position >=0 && position<6){
        this->cabin = 1;
    }
    else if(position >=6 && position<17){
        this->cabin = 2;
    }
    else if(position >=17 && position<31){
        this->cabin = 3;
    }
    else if(position >=31 && position<44){
        this->cabin = 4;
    }
    else if(position >=44 && position<58){
        this->cabin = 5;
    }
    else if(position >=58 && position<71){
        this->cabin = 6;
    }
    else if(position >=71 && position<85){
        this->cabin = 7;
    }
    else{
        this->cabin = 8;
    }
    if(this->cabin!=this->past_cabin){
        int local_past_cabin = this->cabin;
        if(this->cabin < this->past_cabin){
            this->past_cabin = this->cabin;
            for(int i=-1100; i<=170; i+=50){
                if(local_past_cabin != this->cabin){
                    ui->cabin_2->move(110,170);
                    this->past_cabin = this->cabin;
                    return;
                }
                QTime t;
                t.start();
                while(t.elapsed()<1)
                    QCoreApplication::processEvents();
                ui->cabin_2->move(i,170);
            }
            ui->cabin_2->move(110,170);
        }
        else if(this->cabin > this->past_cabin){
            this->past_cabin = this->cabin;
            for(int i=1366; i>=110; i-=50){
                if(local_past_cabin != this->cabin){
                    ui->cabin_2->move(110,170);
                    this->past_cabin = this->cabin;
                    return;
                }
                QTime t;
                t.start();
                while(t.elapsed()<1)
                    QCoreApplication::processEvents();
                ui->cabin_2->move(i,170);
            }
            ui->cabin_2->move(110,170);
        }
    }
}

void Buy_result::on_horizontalSlider_valueChanged(int position)
{
    ui->cabin_2->show();
    if(position >=0 && position<6){
        this->cabin = 1;
    }
    else if(position >=6 && position<17){
        this->cabin = 2;
    }
    else if(position >=17 && position<31){
        this->cabin = 3;
    }
    else if(position >=31 && position<44){
        this->cabin = 4;
    }
    else if(position >=44 && position<58){
        this->cabin = 5;
    }
    else if(position >=58 && position<71){
        this->cabin = 6;
    }
    else if(position >=71 && position<85){
        this->cabin = 7;
    }
    else{
        this->cabin = 8;
    }
    if(this->cabin!=this->past_cabin){
        int local_past_cabin = this->cabin;
        if(this->cabin < this->past_cabin){
            this->past_cabin = this->cabin;
            for(int i=-1100; i<=170; i+=50){
                if(local_past_cabin != this->cabin){
                    ui->cabin_2->move(110,170);
                    this->past_cabin = this->cabin;
                    return;
                }
                QTime t;
                t.start();
                while(t.elapsed()<1)
                    QCoreApplication::processEvents();
                ui->cabin_2->move(i,170);
            }
            ui->cabin_2->move(110,170);
        }
        else if(this->cabin > this->past_cabin){
            this->past_cabin = this->cabin;
            for(int i=1366; i>=110; i-=50){
                if(local_past_cabin != this->cabin){
                    ui->cabin_2->move(110,170);
                    this->past_cabin = this->cabin;
                    return;
                }
                QTime t;
                t.start();
                while(t.elapsed()<1)
                    QCoreApplication::processEvents();
                ui->cabin_2->move(i,170);
            }
            ui->cabin_2->move(110,170);
        }
    }
}

void Buy_result::on_Button_cabin1_clicked()
{
    ui->horizontalSlider->setValue(0);
}

void Buy_result::on_Button_cabin2_clicked()
{
    ui->horizontalSlider->setValue(13);
}

void Buy_result::on_Button_cabin3_clicked()
{
    ui->horizontalSlider->setValue(26);
}

void Buy_result::on_Button_cabin4_clicked()
{
    ui->horizontalSlider->setValue(39);
}

void Buy_result::on_Button_cabin5_clicked()
{
    ui->horizontalSlider->setValue(52);
}

void Buy_result::on_Button_cabin6_clicked()
{
    ui->horizontalSlider->setValue(65);
}

void Buy_result::on_Button_cabin7_clicked()
{
    ui->horizontalSlider->setValue(78);
}

void Buy_result::on_Button_cabin8_clicked()
{
    ui->horizontalSlider->setValue(90);
}

void Buy_result::on_pushButton_42_clicked()
{
    this->seat = ui->pushButton_42->text();
    this->createOrder();
}

void Buy_result::on_pushButton_43_clicked()
{
    this->seat = ui->pushButton_43->text();
    this->createOrder();
}


void Buy_result::on_pushButton_37_clicked()
{
    this->seat = ui->pushButton_37->text();
    this->createOrder();
}

void Buy_result::on_pushButton_39_clicked()
{
    this->seat = ui->pushButton_39->text();
    this->createOrder();
}

void Buy_result::on_pushButton_44_clicked()
{
    this->seat = ui->pushButton_44->text();
    this->createOrder();
}

void Buy_result::on_pushButton_40_clicked()
{
    this->seat = ui->pushButton_40->text();
    this->createOrder();
}

void Buy_result::on_pushButton_36_clicked()
{
    this->seat = ui->pushButton_36->text();
    this->createOrder();
}

void Buy_result::on_pushButton_41_clicked()
{
    this->seat = ui->pushButton_41->text();
    this->createOrder();
}

void Buy_result::on_pushButton_38_clicked()
{
    this->seat = ui->pushButton_38->text();
    this->createOrder();
}

void Buy_result::on_pushButton_45_clicked()
{
    this->seat = ui->pushButton_45->text();
    this->createOrder();
}

void Buy_result::on_pushButton_52_clicked()
{
    this->seat = ui->pushButton_52->text();
    this->createOrder();
}

void Buy_result::on_pushButton_53_clicked()
{
    this->seat = ui->pushButton_53->text();
    this->createOrder();
}

void Buy_result::on_pushButton_47_clicked()
{
    this->seat = ui->pushButton_47->text();
    this->createOrder();
}

void Buy_result::on_pushButton_49_clicked()
{
    this->seat = ui->pushButton_49->text();
    this->createOrder();
}

void Buy_result::on_pushButton_54_clicked()
{
    this->seat = ui->pushButton_54->text();
    this->createOrder();
}

void Buy_result::on_pushButton_50_clicked()
{
    this->seat = ui->pushButton_50->text();
    this->createOrder();
}

void Buy_result::on_pushButton_46_clicked()
{
    this->seat = ui->pushButton_46->text();
    this->createOrder();
}

void Buy_result::on_pushButton_51_clicked()
{
    this->seat = ui->pushButton_51->text();
    this->createOrder();
}

void Buy_result::on_pushButton_48_clicked()
{
    this->seat = ui->pushButton_48->text();
    this->createOrder();
}

void Buy_result::on_pushButton_55_clicked()
{
    this->seat = ui->pushButton_55->text();
    this->createOrder();
}

void Buy_result::on_pushButton_62_clicked()
{
    this->seat = ui->pushButton_62->text();
    this->createOrder();
}

void Buy_result::on_pushButton_63_clicked()
{
    this->seat = ui->pushButton_63->text();
    this->createOrder();
}

void Buy_result::on_pushButton_57_clicked()
{
    this->seat = ui->pushButton_57->text();
    this->createOrder();
}

void Buy_result::on_pushButton_59_clicked()
{
    this->seat = ui->pushButton_59->text();
    this->createOrder();
}

void Buy_result::on_pushButton_64_clicked()
{
    this->seat = ui->pushButton_64->text();
    this->createOrder();
}

void Buy_result::on_pushButton_60_clicked()
{
    this->seat = ui->pushButton_60->text();
    this->createOrder();
}

void Buy_result::on_pushButton_56_clicked()
{
    this->seat = ui->pushButton_56->text();
    this->createOrder();
}

void Buy_result::on_pushButton_61_clicked()
{
    this->seat = ui->pushButton_61->text();
    this->createOrder();
}

void Buy_result::on_pushButton_58_clicked()
{
    this->seat = ui->pushButton_58->text();
    this->createOrder();
}

void Buy_result::on_pushButton_65_clicked()
{
    this->seat = ui->pushButton_65->text();
    this->createOrder();
}

void Buy_result::on_pushButton_72_clicked()
{
    this->seat = ui->pushButton_72->text();
    this->createOrder();
}

void Buy_result::on_pushButton_73_clicked()
{
    this->seat = ui->pushButton_73->text();
    this->createOrder();
}

void Buy_result::on_pushButton_67_clicked()
{
    this->seat = ui->pushButton_67->text();
    this->createOrder();
}

void Buy_result::on_pushButton_69_clicked()
{
    this->seat = ui->pushButton_69->text();
    this->createOrder();
}

void Buy_result::on_pushButton_74_clicked()
{
    this->seat = ui->pushButton_74->text();
    this->createOrder();
}

void Buy_result::on_pushButton_70_clicked()
{
    this->seat = ui->pushButton_70->text();
    this->createOrder();
}

void Buy_result::on_pushButton_66_clicked()
{
    this->seat = ui->pushButton_66->text();
    this->createOrder();
}

void Buy_result::on_pushButton_71_clicked()
{
    this->seat = ui->pushButton_71->text();
    this->createOrder();
}

void Buy_result::on_pushButton_68_clicked()
{
    this->seat = ui->pushButton_68->text();
    this->createOrder();
}

void Buy_result::on_pushButton_75_clicked()
{
    this->seat = ui->pushButton_75->text();
    this->createOrder();
}

void Buy_result::on_pushButton_82_clicked()
{
    this->seat = ui->pushButton_82->text();
    this->createOrder();
}

void Buy_result::on_pushButton_83_clicked()
{
    this->seat = ui->pushButton_83->text();
    this->createOrder();
}

void Buy_result::on_pushButton_77_clicked()
{
    this->seat = ui->pushButton_77->text();
    this->createOrder();
}

void Buy_result::on_pushButton_79_clicked()
{
    this->seat = ui->pushButton_79->text();
    this->createOrder();
}

void Buy_result::on_pushButton_84_clicked()
{
    this->seat = ui->pushButton_84->text();
    this->createOrder();
}

void Buy_result::on_pushButton_80_clicked()
{
    this->seat = ui->pushButton_80->text();
    this->createOrder();
}

void Buy_result::on_pushButton_76_clicked()
{
    this->seat = ui->pushButton_76->text();
    this->createOrder();
}

void Buy_result::on_pushButton_81_clicked()
{
    this->seat = ui->pushButton_81->text();
    this->createOrder();
}

void Buy_result::on_pushButton_78_clicked()
{
    this->seat = ui->pushButton_78->text();
    this->createOrder();
}

void Buy_result::on_pushButton_85_clicked()
{
    this->seat = ui->pushButton_85->text();
    this->createOrder();
}

void Buy_result::on_pushButton_92_clicked()
{
    this->seat = ui->pushButton_92->text();
    this->createOrder();
}

void Buy_result::on_pushButton_93_clicked()
{
    this->seat = ui->pushButton_93->text();
    this->createOrder();
}

void Buy_result::on_pushButton_87_clicked()
{
    this->seat = ui->pushButton_87->text();
    this->createOrder();
}

void Buy_result::on_pushButton_89_clicked()
{
    this->seat = ui->pushButton_89->text();
    this->createOrder();
}

void Buy_result::on_pushButton_94_clicked()
{
    this->seat = ui->pushButton_94->text();
    this->createOrder();
}

void Buy_result::createOrder(){
    int position = ui->horizontalSlider->value();
    QString cabin = "";
    if(position >=0 && position<6){
        cabin = "1";
    }
    else if(position >=6 && position<17){
        cabin = "2";
    }
    else if(position >=17 && position<31){
        cabin = "3";
    }
    else if(position >=31 && position<44){
        cabin = "4";
    }
    else if(position >=44 && position<58){
        cabin = "5";
    }
    else if(position >=58 && position<71){
        cabin = "6";
    }
    else if(position >=71 && position<85){
        cabin = "7";
    }
    else{
        cabin = "8";
    }
    if(!orders::data->contains(Context::user_id)){
        orders::order_node* node = new orders::order_node();
        node->order_number = orders::get_randomString(10);
        node->seat = this->seat;
        node->date = rail_map::get_currentDate();
        node->cabin = cabin;
        node->number_train = this->current_number_train;
        node->start = this->current_start;
        node->end = this->current_end;
        orders::unsubmitted = node;
    }
    else{
        orders::order_node* node = new orders::order_node();
        node->order_number = orders::get_randomString(10);
        node->seat = this->seat;
        node->cabin = cabin;
        node->number_train = this->current_number_train;
        node->start = this->current_start;
        node->end = this->current_end;
        node->date = rail_map::get_currentDate();
        orders::unsubmitted = node;
    }
    QString str = "您的订单信息如下：\n";
    str.append("\n 日期：" + orders::unsubmitted->date);
    str.append("\n 车次：" + orders::unsubmitted->number_train);
    str.append(orders::unsubmitted->start);
    str.append("  ->  ");
    str.append(orders::unsubmitted->end);
    str.append("\n 车厢号：" + orders::unsubmitted->cabin);
    str.append("\n 座位：" + orders::unsubmitted->seat);
    ui->content->setText(str);
    ui->select_seat->hide();
    ui->submit->show();
}

void Buy_result::on_submit_2_clicked()
{
    orders::submit();
    QMessageBox::question(this, tr("订单状态"),QString(tr("成功购买车票")),QMessageBox::Yes);
    if(this->seg_num != 0){
        int choose;
        choose= QMessageBox::question(this, tr("发现问题"),
                                       QString(tr("您购买了中转票中的部分，是否继续购买?")),
                                       QMessageBox::Yes | QMessageBox::No);

        if (choose== QMessageBox::No){
            Context::windows->find("buy_result").value()->hide();
            Context::windows->find("person").value()->show();
        }
        else if (choose== QMessageBox::Yes)
        {
            ui->submit->hide();
            ui->select_train->show();
        }
    }
    else{
        Context::windows->find("buy_result").value()->hide();
        Context::windows->find("person").value()->show();
    }
}

void Buy_result::on_cancel_clicked()
{
    QMessageBox::question(this, tr("订单状态"),QString(tr("成功放弃购买")),QMessageBox::Yes);
    Context::windows->find("buy_result").value()->hide();
    Context::windows->find("person").value()->show();
}
