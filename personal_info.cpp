#include "personal_info.h"
#include <iostream>
#include "context.h"

QMap<QString, QMap<QString, QString>*> *Personal_info::data = new QMap<QString, QMap<QString, QString>*> ();

Personal_info::Personal_info()
{

}

void Personal_info::new_dictionary(QString user_id, QString pwd){
    QMap<QString, QString> *temp = new QMap<QString, QString>();
    temp->insert("password", pwd);
    temp->insert("phone", "");
    temp->insert("wechart", "");
    data->insert(user_id, temp);
    return;
}

bool Personal_info::check_have(QString user_id){
    return data->contains(user_id);
}

bool Personal_info::check_psw(QString user_i, QString psw){
    return data->find(user_i).value()->find("password").value() == psw;
}

QString Personal_info::get_info (QString str) const{
    return data->find(Context::user_id).value()->find(str).value();
}

void Personal_info::put_info(QString str, QString val){
    data->find(Context::user_id).value()->find(str).value() = val;
}
