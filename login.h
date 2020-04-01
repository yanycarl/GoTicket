#ifndef LOGIN_H
#define LOGIN_H

#include <QMainWindow>

namespace Ui {
class login;
}

class login : public QMainWindow
{
    Q_OBJECT

public:
    explicit login(QWidget *parent = nullptr);
    ~login();

private slots:
    void on_Button_signup_clicked();

    void on_Button_login_clicked();

private:
    Ui::login *ui;
};

#endif // LOGIN_H
