#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <Drivers/DBmanager.h>

#include <QTableView>
#include <QMainWindow>
#include <QSqlRelationalDelegate>
#include <QSqlRelationalTableModel>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    Ui::MainWindow *ui;

private:
    QString strDBpath;
    QSqlRelationalTableModel * model;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow(void);

private:
    bool checkDBfile(void);
    void initializeExercisesModel(void);
    void setUpModel(QSqlRelationalTableModel *model, QTableView *tblView);
};
#endif // MAINWINDOW_H
