#include "csvfile.h"
#include <QFile>
#include <QTextStream>

 QString CSVFile::defaultFilePath = QDir::currentPath() + QString::fromLocal8Bit("/csvfile.txt");

CSVFile::CSVFile(QString filepath, QObject *parent)
    : WinPrint{parent}, filepath{filepath}
{
    emit print("CSVFile. Default file path: " + filepath);
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

        emit print("CSVFile. Was writing " + QString::number(i) + " records to file: " + filepath);
    }
    else
    {
        emit print("Error writing file.");
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

       emit print("CSVFile. Was reading " + QString::number(i) + " records from file.");
    }
    else
    {
        QString text = "Error reading file.";
        emit print(text);
    }
}
