#ifndef RAIL_MAP_H
#define RAIL_MAP_H
#include <QMap>
#include <QVector>
#include "station_node.h"
#include <QSet>
#include <QDate>


class rail_map
{
public:
    rail_map();
    class station_node
    {
    public:
        station_node();
        QString name = "";
        QMap<QString, QMap<QString, QString>*> *station_info;
        QVector<QString> *lines;
    };
    class search_node{
    public:
        rail_map::station_node* station;
        QString status;
    };
    static const QMap <QString, station_node*>* get_data();
    static void add_node(QString s, QString s2);
    static void add_line(QString station, QString line);
    static void reset_counter();
    static int get_sizeSearchResult();
    static int get_sizeSubSearchResult(int i);
    static QMap<QString, QMap<QString, QString>*>* get_searchResultItem(int i);
    static void reset_searchResult();
    static QString find_path(QString station1, QString station2);
    static void set_currentDate(QString s);
    static QString get_currentDate();

private:
    static QMap <QString, station_node*> *data;
    static QMap <QString, QVector<station_node*>*> *data2;
    static int result_counter;
    static QMap<QString, QMap<QString, QMap<QString, QString>*>*> *search_result;
    static QSet<QString> *detect_duplex;
    static QVector<rail_map::search_node*> *list_next;
    static QString currentDate;
    static void resolve(QString r);
};

#endif // RAIL_MAP_H

