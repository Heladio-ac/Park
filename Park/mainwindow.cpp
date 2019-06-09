#include "mainwindow.h"
#include "ui_mainwindow.h"


void addSubTree(tree<std::string>, tree<std::string>::sibling_iterator, QStandardItem*);

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
    delete parser;
}

void MainWindow::on_LoadButton_clicked()
{
    fileName = QFileDialog::getOpenFileName(this,tr("Open eyement file"),
                                            "", tr("eye Files (*.eye)"));
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
    ui->ErrorText->clear();
    ui->treeView->setModel(new QStandardItemModel());
    code = code + " ";
    if (parser->transduce(code)) {
        showSyntaxTree();
    } else {
        showError();
    }
}

void MainWindow::on_CodeText_textChanged()
{
    code = ui->CodeText->toPlainText().toStdString();
}

void MainWindow::showSyntaxTree()
{
    QStandardItem* root = new QStandardItem("Syntax Tree");
    tree<std::string> t = parser->syntaxTree;
    for(tree<std::string>::sibling_iterator iRoots = ++t.begin(); iRoots != t.end(); ++iRoots) {
        addSubTree(t,iRoots, root);
    }
    QStandardItemModel* model = new QStandardItemModel();
    model->appendRow(root);
    ui->treeView->setModel(model);
}

void MainWindow::showError()
{
    ui->ErrorText->setPlainText(QString::fromStdString(parser->error));
}

void addSubTree(tree<std::string> t, tree<std::string>::sibling_iterator iRoot, QStandardItem* item) {
    if(t.empty()) return;
    QStandardItem* child = new QStandardItem(QString::fromStdString(*iRoot));
    item->appendRow(child);
    if (t.number_of_children(iRoot) > 0) {
        tree<std::string>::sibling_iterator iChildren;
        for (iChildren = t.begin(iRoot); iChildren != t.end(iRoot); ++iChildren) {
            // recursively add child
            addSubTree(t, iChildren, child);
        }
    }
}
