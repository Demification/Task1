#include "csvrecords.h"
#include <QRandomGenerator>

CSVRecords::CSVRecords(QObject *parent)
    : WinPrint{parent}
{

}

const QStringList& CSVRecords::createRecordStrings()
{
    for(int i = 0; i < szRecordsInFile; i++)
        recordlist << createRecordString();

    QString text = "created list of records";
    emit print(text);

    return recordlist;
}

const QStringList &CSVRecords::getRecordlist() const
{
    return recordlist;
}

QStringList *CSVRecords::getPtrRecordlist()
{
    return &recordlist;
}

void CSVRecords::clearRecordlist()
{
    recordlist.clear();

    QString text = "clear list of records";
    emit print(text);
}

void CSVRecords::repleaceOddNumber2Sharp()
{
    for(auto& record: recordlist)
        for(int i = 0; i < record.length(); i++)
            if(record[i].isDigit())
                if(QString(record[i]).toInt() % 2)
                    record[i] = '#';

    QString text = "repleace odd number to sharp symbol";
    emit print(text);

}

void CSVRecords::delColumnIfFirstVowelChar()
{
    QStringList tempstrlst;
    for(auto& record: recordlist)
    {
        QString tmpstr;
        for(auto& column: record.splitRef(','))
            if(!isVowelChars(column[0]))
                tmpstr.append(column + ',');
        tempstrlst.push_back(tmpstr);
    }

    recordlist.clear();
    for(auto& record: tempstrlst)
    {
        record.chop(1);
        recordlist.push_back(record);
    }

    QString text = "delete column if first char is vowel";
    emit print(text);
}

QString CSVRecords::createRecordString()
{
    QString text;
    for(int i = 0; i < szColumnsInRecord; i++)
    {
        text += createRand8Chars();
        text.append(',');
    }
    text.chop(1);

    return text;
}

bool CSVRecords::isVowelChars(QChar a)
{
    for(auto record: vowelchars)
        if(a == record)
            return true;

    return false;
}

QString CSVRecords::createRand8Chars()
{
    QString text;
    int index;

    for(int i = 0; i < szCharsInColumn; i++)
    {
        index = QRandomGenerator::global()->generate() % latchars.length();
        text.append(latchars[index]);
    }

    return text;
}
