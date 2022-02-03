#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connectPrint(csvfile);
    connectPrint(csvrecords);

    csvrecords->createRecordStrings();
    csvfile->writeRecordsToFile(csvrecords->getRecordlist());
    csvrecords->clearRecordlist();
    csvfile->writeRecordsFromFile(csvrecords->getPtrRecordlist());
    csvrecords->repleaceOddNumber2Sharp();
    csvrecords->delColumnIfFirstVowelChar();
    QString changed_filepath = CSVFile::defaultFilePath;
    changed_filepath.chop(4);
    changed_filepath += "_changed.txt";
    csvfile->writeRecordsToAnotherFile(changed_filepath, csvrecords->getRecordlist());
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

void MainWindow::connectPrint(WinPrint *sender)
{
    connect(sender, &WinPrint::print, this, [&](QString& text){ui->textEdit->setText(ui->textEdit->toPlainText() + text + '\n');});
}

