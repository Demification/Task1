#include "justsqlite.h"
#include <QDebug>
#include "csv_task/csvrecords.h"

QString JustSQLite::defaultDBPath = QDir::currentPath() + QString::fromLocal8Bit("/justsqlite.db");

JustSQLite::JustSQLite(QObject *parent)
    : QObject{parent}
{

}

bool JustSQLite::exec(QSqlQuery &query, const QString &execstr)
{
    if (!query.exec(execstr))
    {
        qWarning() << "error exec query: " + query.lastError().text();
        return false;
    }
    return true;
}

bool JustSQLite::create()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(defaultDBPath);

    if(db.open())
    {
        QSqlQuery query(db);

        QString substr;
        for(int i = 0; i < CSVRecords::szColumnsInRecord; i++)
            substr += "column_" + QString::number(i) + ", ";
        substr.chop(2);

        exec(query, "DROP TABLE IF EXISTS " + tbname);
        exec(query, "CREATE TABLE " + tbname + " (" + substr + ");");

        model = new QSqlTableModel(this, db);
        model->setTable(tbname);
        model->select();

    }
    else
    {
        qCritical() << "error open db: " + db.lastError().text();
        return false;

    }
    return true;
}

QString JustSQLite::normExecDataStr(const QString& record)
{
    auto splited_rec = record.split(',');
    QString text;
    for(auto& column: splited_rec)
        text += "'" + column + "',";
    text.chop(1);
    return text;
}

bool JustSQLite::loadCSVRecords(const QStringList &records)
{
    QSqlQuery query(db);

    for(auto& record: records)
        if(!exec(query, "INSERT INTO " + tbname + " VALUES(" + normExecDataStr(record) + ");"))
            return false;

    model->select();

    return true;
}

bool JustSQLite::execAndRefresh(const QString &execstr)
{
    if(db.isOpen())
    {
        QSqlQuery query(db);
        if(exec(query, execstr))
        {
            model->select();
            return true;
        }
    }
    return false;
}





