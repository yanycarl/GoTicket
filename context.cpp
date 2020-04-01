#include "context.h"
#include "QMainWindow"

Context::Context(){

}

QMap<QString, QMainWindow*> *Context::windows = new QMap<QString, QMainWindow*> ();

QString Context::user_id = "";

