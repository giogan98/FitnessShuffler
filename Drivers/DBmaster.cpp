#include "DBmaster.h"

#include <QDebug>
#include <QVariant>

//class that consent to create db, open and close db,
//execute single query
//------------------------------------------------------------------------------
DBmaster::DBmaster()
{

}
//------------------------------------------------------------------------------
/**
 * @brief DBmaster::createDB
 * @param strPath path of the database to create
 * @brief create a database or if the database exist set the database
 * name to be able to use it later
 */
void DBmaster::createLoadDB(QString strPath)
{
    if (strPath != "")
    {
        strDBpath.clear();
        strDBpath.append(strPath);
        db = QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName(strPath);
    }
}
//------------------------------------------------------------------------------
bool DBmaster::openDB(void)
{
    db.open();
    bool bOpen = db.isOpen();
    return bOpen;
}
//------------------------------------------------------------------------------
void DBmaster::closeDB(void)
{
    db.close();
}
//------------------------------------------------------------------------------
/**
 * @brief DBmaster::executeQuery
 * @param strQuery
 * @brief given a valid query, executes it. Ideal to insert values or to create
 * tables in the database.
*/
void DBmaster::executeCommandQuery(QString strQuery)
{
    QSqlQuery query;
    openDB();
    if (db.isOpen() && strQuery != "")
    {
        QSqlQuery query;
        query.exec(strQuery);
    }
    closeDB();
}
//------------------------------------------------------------------------------
QStringList DBmaster::executeRequestQuery(QString strQuery, uint uiColumns)
{
    //SELECT bla1, bla2, bla3 FROM table...
    QString strValue;
    QSqlQuery query;
    QStringList strlResults;
    openDB();
    if (db.isOpen() && strQuery != "")
    {
        QSqlQuery query(strQuery);
        query.exec();
        while (query.next())
        {
            for (uint ii = 0; ii < uiColumns; ii++)
            {
                strValue = query.value(ii).toString();
                if (strValue != "")
                {
                    strlResults.append(strValue);
                }
            }
        }
    }
    closeDB();
    return strlResults;
}
//------------------------------------------------------------------------------
