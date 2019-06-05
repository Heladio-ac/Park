#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
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
            code = file.readAll();
            ui->CodeText->setPlainText(code);
        }
    }
}

void MainWindow::on_AnalyzeButton_clicked()
{
//    parser->transduce(code.toStdString() + " ");
}

void MainWindow::on_CodeText_textChanged()
{
    code = ui->CodeText->toPlainText();
}
