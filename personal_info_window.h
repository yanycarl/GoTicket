#ifndef PERSONAL_INFO_WINDOW_H
#define PERSONAL_INFO_WINDOW_H

#include <QMainWindow>

namespace Ui {
class personal_info_window;
}

class personal_info_window : public QMainWindow
{
    Q_OBJECT

public:
    explicit personal_info_window(QWidget *parent = nullptr);
    ~personal_info_window();

private slots:
    void on_return_2_pressed();

    void on_return_2_released();

    void on_return_2_clicked();

private:
    Ui::personal_info_window *ui;
};

#endif // PERSONAL_INFO_WINDOW_H
