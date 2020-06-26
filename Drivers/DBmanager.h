#ifndef DBMANAGER_H
#define DBMANAGER_H

#include "DBmaster.h"

#include <QVector>
#include <QVariant>

class DBmanager
{
public:
    static DBmanager& instance()
    {
        static DBmanager dbManager;
        return dbManager     ;
    }

private:
    DBmaster dbMaster;
    QStringList strl_tablesNames;

//    enum enQueryStart
//    {
//        EN_SELECT = strdjb("SELECT"),
//    };

    enum enTables
    {
        TB_EXERCISES,
        TB_BODYPARTS,
        TB_EXE_TYPES,
        TB_FOODS    ,
        TB_NUMEL
    };

    enum enSelect
    {
        SE_NUMEL,
    };

public:
    bool openDB(void);
    void closeDB(void);
    void fillTables(void);
    bool createTables(void);
    void createDB(QString strDBpath);
    void loadDBpath(QString strDBpath);

private:
    DBmanager();
    QStringList fillCBdistricts(void);
    uint findColumnsNumber(QString strQuery);
    uint processSelectColumns(QString strQuery);
    QStringList selectData(enSelect enSlct, int iCode);
    QStringList fillCBdistrictsDescription(QString strDistrict);
    void insertInTable(QString strTableName, QStringList strlColumnNames,
                       QVector<QStringList> veclValues);

};

extern DBmanager dbManager;

#endif // DBMANAGER_H
