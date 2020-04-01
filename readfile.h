#ifndef READFILE_H
#define READFILE_H
#include <QString>


class readFile
{
public:
    readFile();
    void static resolve();
private:
    void static resolve_string(QString str);
};

#endif // READFILE_H
