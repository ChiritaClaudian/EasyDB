#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QString>
#include "userdao.h"
#include "logicalsqlobjectdao.h"
#include "permissiondao.h"
class QSqlQuery;
class QSqlDatabase;

const QString DATABASE_FILENAME = "database.db";

class DatabaseManager
{
public:
    static DatabaseManager& getInstance();
    ~DatabaseManager();
     UserDao userDao;
     LogicalSqlObjectDao sqlObjectDao;
     PermissionDao permDao;
     QSqlQuery executeQuerry(QString );
protected:
    DatabaseManager(const QString &path = DATABASE_FILENAME);
    DatabaseManager& operator=(const DatabaseManager& rhs);
    DatabaseManager(const DatabaseManager&);
private:
    QSqlDatabase *mDatabase;

};

#endif // DATABASEMANAGER_H
