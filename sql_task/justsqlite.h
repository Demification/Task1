#ifndef JUSTSQLITE_H
#define JUSTSQLITE_H

#include <QObject>
#include <QtSql>
#include <QSqlTableModel>
#include "csv_task/csvrecords.h"

class JustSQLite : public QObject
{
    Q_OBJECT

    QSqlDatabase db;
    static QString defaultDBPath;

    bool exec(QSqlQuery &query, const QString& execstr);

    QString normExecDataStr(const QString& record);

public:
    QString tbname = "records";

    QSqlTableModel *model;

    explicit JustSQLite(QObject *parent = nullptr);

    bool create();

    bool loadCSVRecords(const QStringList& records);

    bool execAndRefresh(const QString& execstr);

};

#endif // JUSTSQLITE_H
