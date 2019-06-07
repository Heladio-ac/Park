#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    parser = new Parser();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_LoadButton_clicked()
{
    fileName = QFileDialog::getOpenFileName(this,tr("Open eyement file"),
                                            "/home", tr("eye Files (*.eye)"));
    if (fileName.isEmpty()) {
        QMessageBox::warning(this, "Warning", "Non existant file");
    } else {
        QFile file(fileName);
        if (file.open(QFile::ReadOnly)){
            code = file.readAll().toStdString();
            ui->CodeText->setPlainText(QString::fromStdString(code));
        }
    }
}

void MainWindow::on_AnalyzeButton_clicked()
{
    code = code + " ";
    parser->transduce(code);

}

void MainWindow::on_CodeText_textChanged()
{
    code = ui->CodeText->toPlainText().toStdString();
}
