#ifndef CSVRECORDS_H
#define CSVRECORDS_H

#include "winprint.h"
#include <QString>
#include <QStringList>

class CSVRecords : public WinPrint
{
    Q_OBJECT

    mutable QStringList recordlist;

    const QString vowelchars = "eyuioaEYUIOA";
    const QString latchars = "qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM1234567890";

    bool isVowelChars(QChar a);

    QString createRand8Chars();

    QString createRecordString();

public:
    static int szCharsInColumn;
    static int szColumnsInRecord;
    static int szRecordsInFile;

    explicit CSVRecords(QObject *parent = nullptr);

    const QStringList& createRecordStrings();

    const QStringList& getRecordlist() const;

    QStringList* getPtrRecordlist();

    void clearRecordlist();

    void repleaceOddNumber2Sharp();

    void delColumnIfFirstVowelChar();

};

#endif // CSVRECORDS_H
