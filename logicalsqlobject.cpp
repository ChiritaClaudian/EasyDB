#include "logicalsqlobject.h"

LogicalSqlObject::LogicalSqlObject()
{

}

LogicalSqlObject::LogicalSqlObject(const LogicalSqlObject & object){
    this->mId = object.mId;
    this->mNume = object.mNume;
    this->mType = object.mType;
    this->mParentId = object.mParentId;
    this->mIsCrypt = object.mIsCrypt;
}

LogicalSqlObject::LogicalSqlObject(int id, QString& nume,
                                   const QString& type,
                                   int parentId,
                                   bool isCrypt):
    mId{id},
    mNume{nume},
    mType{type},
    mParentId{parentId},
    mIsCrypt{isCrypt}
{

}

void LogicalSqlObject::setId(int id){
    this->mId = id;
}

int LogicalSqlObject::getId(){
    return mId;
}

void LogicalSqlObject::setType(QString & t){
    this->mType = t;
}

QString LogicalSqlObject::getType(){
    return mType;
}

void LogicalSqlObject::setNume(QString &n){
    this->mNume = n;
}

QString LogicalSqlObject::getNume(){
    return this->mNume;
}

int LogicalSqlObject::getParent(){
    return mParentId;
}

void LogicalSqlObject::setParent(int parentId){
    this->mParentId = parentId;
}

void LogicalSqlObject::setCrypt(int isCrypt){
    mIsCrypt = isCrypt;
}

int LogicalSqlObject::isCrypt(){
    return mIsCrypt;
}
