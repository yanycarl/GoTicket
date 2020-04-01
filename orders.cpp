#include "orders.h"
#include <QMap>
#include <QDateTime>
#include "context.h"

QMap<QString, QVector<orders::order_node*>*>* orders::data = new QMap<QString, QVector<orders::order_node*>*>();

orders::order_node* orders::unsubmitted;

orders::orders()
{

}

QString orders::get_randomString(int length)
{
    qsrand(QDateTime::currentMSecsSinceEpoch());//为随机值设定一个seed

    const char chrs[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    int chrs_size = sizeof(chrs);

    char* ch = new char[length + 1];
    memset(ch, 0, length+1);
    int randomx = 0;
    for (int i = 0; i < length; ++i)
    {
        randomx= rand() % (chrs_size - 1);
        ch[i] = chrs[randomx];
    }

    QString ret(ch);
    delete[] ch;
    return ret;
}

void orders::submit(){
    if(data->contains(Context::user_id)){
        data->find(Context::user_id).value()->push_front(unsubmitted);
    }
    else {
        QVector<orders::order_node*>* temp = new QVector<orders::order_node*>();
        temp->push_front(unsubmitted);
        data->insert(Context::user_id, temp);
    }
}
