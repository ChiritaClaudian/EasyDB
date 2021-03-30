#include "permission.h"

Permission::Permission():
    mUserId(-1),
    mSqlObjectId(-1),
    mPermissionCode(0)
{

}

Permission::Permission(int idUser, int idSqlObject, int code):
    mUserId(idUser),
    mSqlObjectId(idSqlObject),
    mPermissionCode(code)
{

}

void Permission::setUserId(int id){
    this->mUserId = id;
}

void Permission::setSqlObjectId(int id){
    this->mSqlObjectId = id;
}

void Permission::setPermissionCode(int code){
    this->mPermissionCode = code;
}

int Permission::getPermissionCode(){
    return this->mPermissionCode;
}

int Permission::getUserId(){
    return this->mUserId;
}

int Permission::getSqlObjectId(){
    return this->mSqlObjectId;
}


