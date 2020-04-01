#ifndef ORDERS_H
#define ORDERS_H
#include <QString>


class orders
{
public:
    orders();
    class order_node{
    public:
        order_node(){}
        QString order_number = "";
        QString date = "";
        QString number_train = "";
        QString seat;
        QString start = "";
        QString end;
        QString cabin;
    };
    static QString get_randomString(int length);
    static QMap<QString, QVector<order_node*>*>* data;
    static order_node* unsubmitted;
    static void submit();
};

#endif // ORDERS_H
