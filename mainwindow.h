#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "csv_task/winprint.h"
#include "csv_task/csvfile.h"
#include "csv_task/csvrecords.h"
#include "sql_task/justsqlite.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

    CSVFile* csvfile = new CSVFile(CSVFile::defaultFilePath, this);
    CSVRecords* csvrecords = new CSVRecords(this);
    JustSQLite* justsqlite = new JustSQLite(this);

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;

    void partOfTaskAB();
    void partOfTaskC();

    QString getAnotherFilepath();

    void connectPrint(WinPrint *sender);
};
#endif // MAINWINDOW_H
