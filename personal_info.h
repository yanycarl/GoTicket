#ifndef PERSONAL_INFO_H
#define PERSONAL_INFO_H
#include <QMap>
#include <QString>

class Personal_info
{
private:
    static QMap<QString, QMap<QString, QString>* > *data;
public:
    Personal_info();
    void static new_dictionary(QString user_i, QString pwdd);
    bool static check_have(QString user_i);
    bool static check_psw(QString user_i, QString psw);
    QString get_info (QString str) const;
    void put_info(QString str, QString val);
};

#endif // PERSONAL_INFO_H
