#include "csvfile.h"
#include <QFile>
#include <QTextStream>

 QString CSVFile::defaultFilePath = QDir::currentPath() + QString::fromLocal8Bit("/csvfile.txt");

CSVFile::CSVFile(QString filepath, QObject *parent)
    : WinPrint{parent}, filepath{filepath}
{
    QString text = "file path:" + filepath;
    emit print(text);
}

void CSVFile::writeRecordsToFile(const QStringList& recordlist)
{
  writeRecordsToAnotherFile(filepath, recordlist);
}

void CSVFile::writeRecordsToAnotherFile(QString filepath, const QStringList &recordlist)
{
    QFile file(filepath);
    if(file.open(QIODevice::Text | QIODevice::WriteOnly))
    {
        int i = 0;
        QTextStream stream(&file);
        for(auto& str: recordlist)
        {
             stream << str + "\n";
             ++i;
        }

        QString text = "was writing " + QString::number(i) + " records to file: " + filepath;
        emit print(text);
    }
    else
    {
        QString text = "error writing file";
        emit print(text);
    }
}

void CSVFile::writeRecordsFromFile(QStringList *recordlist)
{
    QFile file(filepath);
    if(file.open(QIODevice::Text | QIODevice::ReadOnly))
    {
       int i = 0;
       QTextStream stream(&file);
       while(!stream.atEnd())
       {
            *recordlist << stream.readLine();
            i++;
       }

       QString text = "was reading " + QString::number(i) + "records from file";
       emit print(text);
    }
    else
    {
        QString text = "error reading file";
        emit print(text);
    }
}
