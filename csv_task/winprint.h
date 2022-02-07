#ifndef WINPRINT_H
#define WINPRINT_H

#include <QObject>

class WinPrint : public QObject
{
    Q_OBJECT
public:
    explicit WinPrint(QObject *parent = nullptr);

signals:
    void print(const QString& text);
};

#endif // WINPRINT_H
