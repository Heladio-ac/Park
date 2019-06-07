#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>
#include "parser.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_LoadButton_clicked();

    void on_AnalyzeButton_clicked();

    void on_CodeText_textChanged();

private:
    Ui::MainWindow *ui;

    Parser *parser;

    QString fileName;
    std::string code;
};

#endif // MAINWINDOW_H
