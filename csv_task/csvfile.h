#ifndef CSVFILE_H
#define CSVFILE_H

#include "winprint.h"
#include <QString>
#include <QDir>

class CSVFile : public WinPrint
{
    Q_OBJECT

    QString filepath;

public:
    static QString defaultFilePath;

    explicit CSVFile(QString filepath, QObject *parent = nullptr);

    void writeRecordsToFile(const QStringList& recordlist);

     void writeRecordsToAnotherFile(QString filepath, const QStringList& recordlist);

    void writeRecordsFromFile(QStringList* recordlist);

};

#endif // CSVFILE_H
