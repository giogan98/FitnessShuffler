#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileInfo>

#define VERSION "1.0.0"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    strDBpath = "//database.db";
    this->setWindowTitle(strcat(strdup("Fitness Shuffler "), VERSION));
    checkDBfile();
}
//------------------------------------------------------------------------------
MainWindow::~MainWindow(void)
{
    delete ui;
}
//------------------------------------------------------------------------------
bool MainWindow::checkDBfile(void)
{
    bool bCheck = QFileInfo::exists(strDBpath) && QFileInfo(strDBpath).isFile();

    if (!bCheck)
    {
        dbManager.createDB(strDBpath);
        dbManager.createTables();
        dbManager.fillTables();
    }

    return  bCheck;
}
//------------------------------------------------------------------------------
