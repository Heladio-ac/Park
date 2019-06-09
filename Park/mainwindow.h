#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItem>
#include <QStandardItemModel>
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>
#include <iostream>

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
    void showSyntaxTree(void);
    void showError(void);

private slots:
    void on_LoadButton_clicked();

    void on_AnalyzeButton_clicked();

    void on_CodeText_textChanged();

    void on_SaveButton_clicked();

    void save();

private:
    Ui::MainWindow *ui;

    Parser *parser;

    QString fileName;
    std::string code;
};

#endif // MAINWINDOW_H
