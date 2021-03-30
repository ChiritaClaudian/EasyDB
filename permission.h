#ifndef PERMISSION_H
#define PERMISSION_H
#include "ilogicalsqlobject.h"
#include <QVector>
#include <QString>
class Permission
{
public:
    Permission();
    Permission(int idUser, int idSqlObject, int code);
    void addObject(int , int, int);
    void removeObject(int, int);
    void setUserId(int);
    void setSqlObjectId(int);
    void setPermissionCode(int);
    int getUserId();
    int getSqlObjectId();
    int getPermissionCode();
private:
    int mUserId;
    int mSqlObjectId;
    int mPermissionCode;


};

#endif // PERMISSION_H
