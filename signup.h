#ifndef SIGNUP_H
#define SIGNUP_H

#include <QMainWindow>

namespace Ui {
class signup;
}

class signup : public QMainWindow
{
    Q_OBJECT

public:
    explicit signup(QWidget *parent = nullptr);
    ~signup();

private slots:
    void on_commandLinkButton_clicked();

    void on_pushButton_2_clicked();

    void on_lineEdit_editingFinished();

private:
    Ui::signup *ui;

};

#endif // SIGNUP_H
