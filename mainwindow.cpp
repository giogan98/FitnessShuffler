#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileInfo>

#define VERSION "1.0.0"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    model = nullptr;
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
/**
 * @brief MainWindow::checkDBfile
 * @brief Checks if the database exists. If not, creates a new one.
 * @return
 */
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
/**
 * @brief MainWindow::initializeExercisesModel
 * @brief Initialize the QsqlRelationalTableModel to be able to show proper data
 */
void MainWindow::initializeExercisesModel(void)
{
    //EXERCISES
    //'Name'          ->   VARCHAR(100)   ->
    //'Description'   ->   VARCHAR(100)   ->
    //'Type'          ->   INTEGER        ->   link to EXE_TYPES
    //'Sets'          ->   INTEGER        ->
    //'Reps'          ->   INTEGER        ->
    //'Body_Part'     ->   INTEGER        ->   link to BODY_PARTS
    //'Difficulty'    ->   INTEGER        ->
    model = new QSqlRelationalTableModel(this);
    int miTypeIndex = 0;
    model->setTable("EXERCISES");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->setHeaderData(0,  Qt::Horizontal, QObject::tr("Id"         ));
    model->setHeaderData(1,  Qt::Horizontal, QObject::tr("Name"       ));
    model->setHeaderData(2,  Qt::Horizontal, QObject::tr("Description"));
    model->setHeaderData(3,  Qt::Horizontal, QObject::tr("Type"       ));
    model->setHeaderData(4,  Qt::Horizontal, QObject::tr("Sets"       ));
    model->setHeaderData(5,  Qt::Horizontal, QObject::tr("Reps"       ));
    model->setHeaderData(6,  Qt::Horizontal, QObject::tr("Body_Part"  ));
    model->setHeaderData(7,  Qt::Horizontal, QObject::tr("Difficulty" ));

    miTypeIndex= model->fieldIndex("Type");
    model->setRelation(miTypeIndex,
                       QSqlRelation("EXE_TYPES",
                                    "Id",
                                    "Description"
                                    ));

    miTypeIndex = model->fieldIndex("Body_Part");
    model->setRelation(miTypeIndex,
                       QSqlRelation("BODY_PARTS",
                                    "Id",
                                    "Description"
                                    ));

    model->setJoinMode(QSqlRelationalTableModel::LeftJoin);
    //    model->setFilter("");
    model->select();

}
//------------------------------------------------------------------------------
void MainWindow::setUpModel(QSqlRelationalTableModel * model, QTableView * tblView)
{
    tblView->setModel(model);
    tblView->resizeColumnsToContents();
    tblView->setItemDelegate(new QSqlRelationalDelegate(tblView));
    tblView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}
//------------------------------------------------------------------------------
