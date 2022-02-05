#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    partOfTaskAB();
    partOfTaskC();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QString appendtext;
    for(auto& line: csvrecords->getRecordlist())
        appendtext.append(line + '\n');
    ui->textEdit->setText(appendtext);
}

void MainWindow::partOfTaskAB()
{
    connectPrint(csvfile);
    connectPrint(csvrecords);

    csvrecords->createRecordStrings();
    csvfile->writeRecordsToFile(csvrecords->getRecordlist());
    csvrecords->clearRecordlist();
    csvfile->writeRecordsFromFile(csvrecords->getPtrRecordlist());
    csvrecords->repleaceOddNumber2Sharp();
    csvrecords->delColumnIfFirstVowelChar();
    csvfile->writeRecordsToAnotherFile(getAnotherFilepath(), csvrecords->getRecordlist());
}

void MainWindow::partOfTaskC()
{
    if(justsqlite->create())
    {
        QStringList records;
        csvfile->writeRecordsFromFile(&records);
        justsqlite->loadCSVRecords(records);
        ui->tableView->setModel(justsqlite->model);
    }
}

QString MainWindow::getAnotherFilepath()
{
    QString changed_filepath = CSVFile::defaultFilePath;
    changed_filepath.chop(4);
    changed_filepath += "_changed.txt";

    return changed_filepath;
}

void MainWindow::connectPrint(WinPrint *sender)
{
    connect(sender, &WinPrint::print, this, [&](QString& text){ui->textEdit->setText(ui->textEdit->toPlainText() + text + '\n');});
}

void MainWindow::on_pushButton_2_clicked()
{
    justsqlite->execAndRefresh("DELETE FROM " + justsqlite->tbname + " WHERE SUBSTR(column_1, 1, 1) IN ('0','1','2','3','4','5','6','7','8','9');");
}

