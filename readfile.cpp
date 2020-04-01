#include "readfile.h"
#include <QFile>
#include "rail_map.h"

readFile::readFile()
{

}

void readFile::resolve(){
    QFile file(":/file/Resource/chineserail.csv");
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QByteArray t = file.readAll();
    readFile ::resolve_string(QString(t));
    file.close();
}

void readFile::resolve_string(QString str){
    QString left = "";
    QString right = "";
    int pointer = 0;
    for(int i = 0; i<str.length(); i++){
        if(str.at(i) == ','){
            left = str.mid(pointer, i-pointer);
            pointer = i+1;
        }
        else if(str.at(i) == '\n' || i == str.length()-1){
            if(i == str.length()-1){
                right = str.mid(pointer, i+1-pointer);
                rail_map::add_line(right, left);
                rail_map::add_node(right, right);
                return;
            }
            else{
                right = str.mid(pointer, i-pointer);
                pointer = i+1;
                rail_map::add_line(right, left);
                rail_map::add_node(right, right);
            }
        }
    }
}

