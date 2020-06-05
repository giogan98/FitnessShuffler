#include "DBmanager.h"

#include <QVector>
#include <QFileDialog>
#include <QtSql/qsqlquery.h>
#include <QtSql/qsqlerror.h>


DBmanager dbManager = DBmanager::instance();
//------------------------------------------------------------------------------
DBmanager::DBmanager()
{
    //@todo check names and tables that repete themselves
    strl_tablesNames<<"EXERCISES"<<"BODY_PARTS"<<"EXE_TYPES"<<"FOODS";
}
//------------------------------------------------------------------------------
void DBmanager::createDB(void)
{
    //@todo change file path to something else
    dbMaster.createLoadDB("C:\\users\\giorg\\desktop\\test.db");
}
//------------------------------------------------------------------------------
bool DBmanager::openDB(void)
{
    return dbMaster.openDB();
}
//------------------------------------------------------------------------------
void DBmanager::closeDB(void)
{
    dbMaster.closeDB();
}
//------------------------------------------------------------------------------
void DBmanager::loadDBpath(QString strPath)
{
    if (strPath != "")
    {
        dbMaster.createLoadDB(strPath);
    }
}
//------------------------------------------------------------------------------
bool DBmanager::createTables(void)
{
    bool bSucc = openDB();
    if (bSucc)
    {
        QString strQuery = "";
        for (int ii = 0; ii < TB_NUMEL; ii++)
        {
            strQuery = "CREATE TABLE IF NOT EXISTS ";
            strQuery.append(strl_tablesNames[ii]);
            strQuery.append("(ID INTEGER UNIQUE PRIMARY KEY AUTOINCREMENT,");
            switch (ii)
            {
            case TB_EXERCISES                                    :
                strQuery.append(" 'Name'          VARCHAR(100),"
                                " 'Description'   VARCHAR(100),"
                                " 'Type'          VARCHAR(100),"
                                " 'Sets'          INTEGER,"
                                " 'Reps'          INTEGER,"
                                " 'Body Part'     VARCHAR(100),"
                                " 'Difficulty'    INTEGER)");
                break;
            case TB_BODYPARTS                                    :
                strQuery.append(" 'Description'   VARCHAR(100))");
                break;
            case TB_EXE_TYPES                                    :
                strQuery.append(" 'Description'   VARCHAR(100))");
                break;
            case TB_FOODS                                        :
                // @todo
                break;
            default:
                strQuery.clear();
                break;
            }

            if (strQuery != "")
            {
                dbMaster.executeCommandQuery(strQuery);
            }

        }
        closeDB();
    }

    return bSucc;
}
//------------------------------------------------------------------------------
//QStrinList containing the name of the columns
//QVector of QStringList containing the lines of values of the table
void DBmanager::insertInTable(QString strTableName, QStringList strlColumnNames,
                              QVector<QStringList> veclValues)
{
    bool bSucc = openDB();
    for ( int ii = 0; ii < veclValues.length(); ii++)
    {
        if (bSucc && strTableName != "" && strlColumnNames.length() > 0
                && veclValues[ii].length() == strlColumnNames.length() )
        {
            QString strQuery = "";
            strQuery = "INSERT INTO ";
            strQuery.append(strTableName);
            strQuery.append(" (");

            for (int kk = 0; kk < strlColumnNames.length(); kk++)
            {
                strQuery.append(strlColumnNames[kk]);
                strQuery.append(", ");
            }
            strQuery.chop(2);
            strQuery.append(") VALUES (");

            for (int jj = 0; jj < veclValues[ii].length(); jj++)
            {
                strQuery.append(veclValues[ii][jj]);
                strQuery.append(", ");
            }
            strQuery.chop(2);
            strQuery.append(")");

            if (strQuery != "")
            {
                dbMaster.executeCommandQuery(strQuery);
            }
        }
    }
    closeDB();
}
//------------------------------------------------------------------------------
void DBmanager::fillTables(void)
{
    // @todo execute this only if database is created new

    QVector<QStringList> vecTemp;

    //EXERCISES
    // @todo

    //BODY_PARTS
    vecTemp.append(QStringList("'Abs'"       ));
    vecTemp.append(QStringList("'Neck'"      ));
    vecTemp.append(QStringList("'Biceps'"    ));
    vecTemp.append(QStringList("'Triceps'"   ));
    vecTemp.append(QStringList("'Chest'"     ));
    vecTemp.append(QStringList("'Shoulders'" ));
    vecTemp.append(QStringList("'Traps'"     ));
    vecTemp.append(QStringList("'Quadriceps'"));
    vecTemp.append(QStringList("'Hamstrings'"));
    vecTemp.append(QStringList("'Calfs'"     ));
    vecTemp.append(QStringList("'Glutes'"    ));
    vecTemp.append(QStringList("'Lower Back'"));
    vecTemp.append(QStringList("'Lats'"      ));
    insertInTable("BODY_PARTS", QStringList("Description"), vecTemp);
    vecTemp.clear();

    //EXE_TYPES
    vecTemp.append(QStringList("'Cardio'"         ));
    vecTemp.append(QStringList("'Stretching'"     ));
    vecTemp.append(QStringList("'Muscle Building'"));
    insertInTable("EXE_TYPES", QStringList("Description"), vecTemp);
    vecTemp.clear();

    //FOODS
    // @todo
}
//------------------------------------------------------------------------------
//temporary function only to test queries
void DBmanager::fillTestTables(void)
{
    bool bSucc = openDB();
    if (bSucc)
    {
        QString strQuery = "";

        for (int ii = 0; ii < TB_NUMEL; ii++)
        {
            strQuery = "INSERT INTO ";
            strQuery.append(strl_tablesNames[ii]);

            switch (ii)
            {
            default:
                strQuery.clear();
                break;
            }

            if (strQuery != "")
            {
                dbMaster.executeCommandQuery(strQuery);
            }

        }
        closeDB();
    }

}
//------------------------------------------------------------------------------
uint DBmanager::findColumnsNumber(QString strQuery)
{
    uint uiColumns = 0;

    if (strQuery != "")
    {
        std::string firstWord = strQuery.split(" ").at(0).toStdString();

        switch (strdjb(firstWord.data()))
        {
        //        case EN_SELECT:
        //            uiColumns = processSelectColumns(strQuery);
        //            break;
        default:
            break;
        }

    }
    return uiColumns;
}
//------------------------------------------------------------------------------
uint DBmanager::processSelectColumns(QString strQuery)
{
    //SELECT ID, BODYPART FROM DICOM WHERE DESCRIPTION = 'dscrption'
    strQuery.remove("'");
    std::string firstWord = strQuery.split(" ").at(0).toStdString();
    int iFrstWhtSpc = strQuery.indexOf(" ");
    strQuery.remove(0, iFrstWhtSpc);
    int iFromIndex = strQuery.indexOf(" from ", 0, Qt::CaseInsensitive);
    strQuery.remove(iFromIndex, strQuery.length()-iFromIndex);
    strQuery.remove(" ");
    QStringList strl_columns = strQuery.split(",");
    uint iColumns = strl_columns.length();
    return iColumns;
}
//------------------------------------------------------------------------------
