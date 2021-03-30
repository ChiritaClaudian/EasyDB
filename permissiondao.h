#ifndef PERMISSIONDAO_H
#define PERMISSIONDAO_H

#include <QVector>

class QSqlDatabase;
class Permission;
class QString;


class PermissionDao
{
public:
    PermissionDao();
    PermissionDao(QSqlDatabase& database);
    void init() const;
    void addPermission(int idUser, int idSqlObject, int permissionCode);
    QVector<Permission> getPermissions(int idUser);
    void setDatabase(QSqlDatabase& database);
private:
    QSqlDatabase& mDatabase;
};

#endif // PERMISSIONDAO_H
