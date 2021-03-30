#include "permissiondao.h"
#include "permission.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QVariant>
#include <QSqlRecord>
#include <QStringList>
#define IDUSER_VALUE 0
#define IDSQLOBJECT_VALUE 1
#define PERMISSIONCODE_VALUE 2

PermissionDao::PermissionDao():
    mDatabase(*(new QSqlDatabase(QSqlDatabase::addDatabase("QSQLITE"))))
{
    mDatabase.close();
}

PermissionDao::PermissionDao(QSqlDatabase& database):
    mDatabase(database)
{

}

void PermissionDao::init() const{
    if(!mDatabase.tables().contains("Permissions")){
        QSqlQuery query(mDatabase);
        query.exec("CREATE TABLE Permissions (idUser INT, idSqlObject INT, permissionCode INT)");
    }
}

void PermissionDao::addPermission(int idUser, int idSqlObject, int permissionCode){
    QSqlQuery query(mDatabase);
    query.prepare("INSERT INTO Permissions(idUser, idSqlObject, permissionCode)"
                  "VALUES (:idUser, :idSqlObject, :permissionCode)");
    query.bindValue(":idUser", idUser);
    query.bindValue(":idSqlObject", idSqlObject);
    query.bindValue(":permissionCode", permissionCode);
    query.exec();
}

QVector<Permission> PermissionDao::getPermissions(int idUser){
    QVector<Permission> permissions;
    QSqlQuery query(mDatabase);
    QString stringIdUser(idUser);
    //query.prepare("SELECT * FROM Permissions WHERE idUser = ':idUser'");
   // query.bindValue(":idUser", stringIdUser);
    query.exec("SELECT * FROM Permissions");
    while(query.next()){
        Permission perm(query.value(IDUSER_VALUE).toInt(),
                        query.value(IDSQLOBJECT_VALUE).toInt(),
                        query.value(PERMISSIONCODE_VALUE).toInt());
        if(perm.getUserId() == idUser)
            permissions.append(perm);
    }
    return permissions;
}

void PermissionDao::setDatabase(QSqlDatabase &database){
    mDatabase = database;
}


