#ifndef PERSON_H
#define PERSON_H

#include <QMainWindow>
#include <QThread>
#include<QEvent>
#include <QListWidgetItem>

namespace Ui {
class person;
}

class person : public QMainWindow
{
    Q_OBJECT

public:
    explicit person(QWidget *parent = nullptr);
    ~person();


private slots:
    void on_Button_personalInfo_clicked();
    void change_back();

    void on_Button_logout_pressed();

    void on_Button_logout_released();

    void on_Button_personalInfo_pressed();

    void on_Button_personalInfo_released();

    void on_Button_Author_pressed();

    void on_Button_Author_released();

    void on_Button_privacy_pressed();

    void on_Button_privacy_released();

    void on_Button_money_pressed();

    void on_Button_money_released();

    void on_Button_setting_pressed();

    void on_Button_setting_released();

    void on_Button_Author_clicked();

    void on_Person_clicked();

    void on_Buy_clicked();

    void on_Trip_clicked();

    void on_Order_clicked();

    void on_pushButton_7_pressed();

    void on_pushButton_7_released();

    void on_Button_start_clicked();

    void on_list_stations_itemClicked(QListWidgetItem *item);

    void on_searchLine_textChanged(const QString &arg1);

    void on_Button_end_clicked();

    void on_Button_switch_clicked();

    void on_calendarWidget_clicked(const QDate &date);

    void on_pushButton_13_clicked();

    void on_pushButton_7_clicked();

private:
    Ui::person *ui;
    int pic = 0;
    int current = 0;
    int direct = 0;
    static QMap <int, int> *position;
    void initialization();

public: signals:
    void my_signal();
};


#endif // PERSON_H
