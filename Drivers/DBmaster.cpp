#include "DBmaster.h"

#include <QDebug>
#include <QVariant>


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
void DBmaster::createLoadDB(const QString &strPath)
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
/**
 * @brief DBmaster::openDB
 * @brief function opens a connection to the database
 * @return
 */
bool DBmaster::openDB(void)
{
    bool bOpen = db.isOpen();
    if (!bOpen)
    {
        db.open();
        bOpen = db.isOpen();
    }
    return bOpen;
}
//------------------------------------------------------------------------------
/**
 * @brief DBmaster::closeDB
 * @brief function closes a connection to the database
 */
void DBmaster::closeDB(void)
{
    db.close();
}
//------------------------------------------------------------------------------
/**
 * @brief DBmaster::executeSingleCommandQuery
 * @warning differently from function 'executeMultipleCommandQuery', columns
 *          names and values must be between '' example : 'value'
 * @param strQuery
 * @brief given a valid query, executes it. Ideal to insert values or to create
 * tables in the database.
 * @return if the query is executed succesfully
*/
bool DBmaster::executeSingleCommandQuery(const QString &strQuery)
{
    bool bSucc = false;
    QSqlQuery query;
    openDB();
    if (db.isOpen() && strQuery != "")
    {
        bSucc = query.exec(strQuery);
    }
    return bSucc;
}
//------------------------------------------------------------------------------
/**
 * @brief DBmaster::executeMultipleCommandQuery
 * @brief insert all the n elements of the vector in the db. Each element is
 *        a row of the database, containing multiple columns.
 * @warning do NOT use '' while inserting in the db, contrary to what is done
 *          with the function for a single command query. Ex: 'value1' is wrong
 * @param iColumnsNumber numbers of columns that the query utilizes
 * @param strQueryToBind query with correct sintax that permit binding
 * @param veclValues vector of qstringlist, each element of the vector is a row
 *                   of the database wich will be inserted
 * @return if everyquery is executed successfully
 */
bool DBmaster::executeMultipleCommandQuery(const int &iColumnsNumber,
                                           const QString &strQueryToBind,
                                           const QVector<QStringList> &veclValues)
{
    //Example of strGenericQuery:
    //INSERT INTO table (column1 , column2) VALUES (:column1 , :column2)
    QSqlQuery query;
    bool bSucc = false;

    if (openDB() && strQueryToBind != "")
    {
        bSucc = true;
        query.exec("begin exclusive transaction;");
        query.prepare(strQueryToBind);

        for (int ii = 0; ii < veclValues.size(); ii++)
        {
            for (int jj = 0; jj < iColumnsNumber; jj++)
            {
                query.bindValue(jj, veclValues[ii][jj]);
            }
            bSucc = bSucc && query.exec();
            if (!bSucc)
                {
                    qDebug()<<"QUERY: "<<query.lastQuery();
                    qDebug()<<"ERROR: "<<query.lastError();
                }
        }
    }

    bSucc = bSucc && query.exec("commit;");
    return bSucc;
}
//------------------------------------------------------------------------------
/**
 * @brief DBmaster::executeRequestQuery
 * @brief executes a query and return its results
 * @warning does require explicit columns names, does NOT work with '*'
 * @param strQuery string containing query
 * @param iColumns number of columns requested by the query
 * @return
 */
QStringList DBmaster::executeRequestQuery(const QString &strQuery, const int &iColumns)
{
    //Example of strQuery:
    //SELECT column1, column2, column3 FROM table1
    QString strValue;
    QStringList strlResults;

    if (openDB() && strQuery != "")
    {
        QSqlQuery query(strQuery);
        query.exec();
        while (query.next())
        {
            for (int ii = 0; ii < iColumns; ii++)
            {
                strValue = query.value(ii).toString();
                if (strValue != "")
                {
                    strlResults.append(strValue);
                }
            }
        }
    }

    return strlResults;
}
//------------------------------------------------------------------------------
