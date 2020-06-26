#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <Drivers/DBmanager.h>

#include <QMainWindow>

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

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow(void);

private:
    bool checkDBfile(void);
};
#endif // MAINWINDOW_H
