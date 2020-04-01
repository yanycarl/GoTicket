#include "rail_map.h"
#include <QVector>
#include <iterator>
#include <iostream>

QMap <QString, rail_map::station_node*> *rail_map::data = new QMap <QString, station_node*>() ;

QVector<rail_map::search_node*> *rail_map::list_next = new QVector<rail_map::search_node*>();

QMap<QString, QMap<QString, QMap<QString, QString>*>*> *rail_map::search_result = new  QMap<QString, QMap<QString, QMap<QString, QString>*>*>();

QSet<QString>* rail_map::detect_duplex = new QSet<QString>();

QMap <QString, QVector<rail_map::station_node*>*> *rail_map::data2 = new QMap <QString, QVector<station_node*>*>;

QString rail_map::currentDate = "";

int rail_map::result_counter = 0;

rail_map::rail_map()
{

}

void rail_map::set_currentDate(QString s){
    currentDate = s;
}

QString rail_map::get_currentDate(){
    return currentDate;
}

int rail_map::get_sizeSearchResult(){
    return search_result->size();
}

int rail_map::get_sizeSubSearchResult(int i){
    return search_result->find(QString(i)).value()->size();
}

QMap<QString, QMap<QString, QString>*>* rail_map::get_searchResultItem(int i){
    return search_result->find(QString(i)).value();
}

void rail_map::reset_searchResult(){
    search_result->clear();
}

void rail_map:: add_node(QString s, QString s2){
    if(!rail_map::data->contains(s)){
        station_node *temp = new station_node();
        temp->name = s;
        rail_map::data->insert(s, temp);
    }
    if(!rail_map::data->contains(s2)){
        station_node *temp = new station_node();
        temp->name = s2;
        rail_map::data->insert(s2, temp);
    }
}

void rail_map::add_line(QString station, QString line){
    if(rail_map::data->contains(station)){
        rail_map::data->find(station).value()->lines->push_back(line);
    }
    else{
        add_node(station, station);
        rail_map::data->find(station).value()->lines->push_back(line);
    }
    if(rail_map::data2->contains(line)){
        rail_map::data2->find(line).value()->push_back(rail_map::data->find(station).value());
    }
    else{
        QVector<station_node*> *temp = new QVector<station_node*>();
        rail_map::data2->insert(line,temp);
        rail_map::data2->find(line).value()->push_back(rail_map::data->find(station).value());
    }
}

void rail_map::resolve(QString r){
    QString last="";
    QString last2="";
    QString current="";
    int count = 0;
    int left = 1;
    rail_map::result_counter++;
    QMap<QString, QMap<QString, QString>*> *temp_map = new QMap<QString, QMap<QString, QString>*>();
    for(int right = 1; right< r.length() ; right++){
        if(r.at(right) == ' ' || right == r.length()-1){
            if(right == r.length()-1){
                right++;
            }
            last2 = last;
            last = current;
            current = r.mid(left, right-left);
            left = right+1;
            count++;
            if(last2 != "" && count!=1 && count%2 == 1){
                QMap<QString, QString>* temp_map2 = new QMap<QString, QString>();
                temp_map2->insert("start", last2);
                temp_map2->insert("end", current);
                temp_map2->insert("number", last);
                temp_map->insert(QString(int(count/2)), temp_map2);
            }
        }
    }
    rail_map::search_result->insert(QString(rail_map::result_counter), temp_map);
}

QString rail_map::find_path(QString station1, QString station2){
    list_next->clear();
    detect_duplex->clear();
    rail_map::search_node *node = new rail_map::search_node();
    node->station = rail_map::data->find(station1).value();
    node->status = "";
    list_next->push_back(node);
    while(list_next->size() != 0){
        if(detect_duplex->contains(list_next->front()->station->name)){
            list_next->pop_front();
            continue;
        }
        QVector<QString> *temp = list_next->front()->station ->lines;
        detect_duplex->insert(list_next->front()->station->name);
        for (QVector<QString>::iterator itor = temp->begin(); itor != temp->end(); itor++) {
            if(detect_duplex->contains(QString(*itor))){
                continue;
            }
            detect_duplex->insert(QString(*itor));
            QVector<station_node*> *temp2 = rail_map::data2->find(*itor).value();
            QVector<station_node*>::iterator itor2 = temp2->begin();
            while((*(itor2))->name !=  list_next->front()->station->name){
                itor2++;
            }
            for (; itor2!=temp2->end();itor2++) {
                if((*itor2)->name == station2){
                    resolve(list_next->front()->status +" "+list_next->front()->station->name+" "+QString(*itor) + " "+ station2);
                    break;
                }
                rail_map::search_node *node = new rail_map::search_node();
                node->station = *itor2;
                node->status = list_next->front()->status + " " + list_next->front()->station->name +" "+QString(*itor);
                rail_map::list_next->push_back(node);
            }
        }
        list_next->pop_front();
    }
    return "";
}

rail_map::station_node::station_node()
{
    this->station_info = new QMap<QString, QMap<QString, QString>*>();
    this->lines = new QVector<QString>();
}

const QMap <QString, rail_map::station_node*>* rail_map::get_data(){
    return rail_map::data;
}

void rail_map::reset_counter(){
    result_counter = 0;
}
