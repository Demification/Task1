#include "csvrecords.h"
#include <QRandomGenerator>

int CSVRecords::szCharsInColumn = 8;
int CSVRecords::szColumnsInRecord = 6;
int CSVRecords::szRecordsInFile = 1024;

CSVRecords::CSVRecords(QObject *parent)
    : WinPrint{parent}
{

}

const QStringList& CSVRecords::createRecordStrings()
{
    for(int i = 0; i < szRecordsInFile; i++)
        recordlist << createRecordString();

    emit print("CSVRecords. Created list of records.");

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

    emit print("CSVRecords. Clear list of records.");
}

void CSVRecords::repleaceOddNumber2Sharp()
{
    for(auto& record: recordlist)
        for(int i = 0; i < record.length(); i++)
            if(record[i].isDigit())
                if(isOddNumber(oneCharSumbolToInt(record[i])))
                    record[i] = '#';

    emit print("CSVRecords. Repleace odd number to sharp symbol.");
}

void CSVRecords::delColumnIfFirstVowelChar()
{
    QStringList strlst;
    for(auto& record: recordlist)
    {
        QString tmpstr;
        for(auto& column: record.splitRef(','))
            if(!isVowelChars(column[0]))
                tmpstr.append(column + ',');
        strlst.push_back(tmpstr);
    }

    recordlist.clear();
    for(auto& record: strlst)
    {
        record.chop(1);
        recordlist.push_back(record);
    }

    emit print("CSVRecords. Delete column if first char is vowel.");
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
