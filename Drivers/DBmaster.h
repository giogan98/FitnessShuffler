#ifndef DBMASTER_H
#define DBMASTER_H

#include <QStringList>
#include <QtSql/QSqlDatabase>
#include <QtSql/qsqlquery.h>
#include <QtSql/qsqlerror.h>


class DBmaster
{
public:

private:
    QSqlDatabase db;
    QString strDBpath;

public:
    DBmaster();
    bool openDB(void);
    void closeDB(void);
    void createLoadDB(const QString &strPath);
    bool executeSingleCommandQuery(const QString &strQuery);
    QStringList executeRequestQuery(const QString &strQuery, const int &iColumns);
    bool executeMultipleCommandQuery(const int &iColumnsNumber, const QString &strQueryToBind,
                                     const QVector<QStringList> &veclValues);
private:

};

constexpr unsigned int strdjb(const char* str, int h = 0)
{
    return !str[h] ? 5381 : (strdjb(str, h+1) * 33) ^ static_cast<uint32_t>(str[h]);
}

#endif // DBMASTER_H
