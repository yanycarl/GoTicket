#ifndef CONTEXT_H
#define CONTEXT_H
#include "QMainWindow"
#include "QMap"

class Context
{
public:
    static QMap<QString, QMainWindow*> *windows;
public:
    Context();
    static QString user_id;
};

#endif // CONTEXT_H
