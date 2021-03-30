#include "logicalsqlobjectdao.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QStringList>
#include <QVariant>
#include <QVariant>
#include <QSqlRecord>
#include "logicalsqlobject.h"
#include "logicalcolumn.h"
#include "logicaltable.h"
#include "ilogicalsqlobject.h"
#include <QSqlError>
#define ID_VALUE 0
#define NUME_VALUE 1
#define TYPE_VALUE 2
#define PARENTID_VALUE 3
#define CRYPT_VALUE 4
LogicalSqlObjectDao::LogicalSqlObjectDao():
    mDatabase(*(new QSqlDatabase(QSqlDatabase::addDatabase("QSQLITE"))))
{
    mDatabase.close();
}

LogicalSqlObjectDao::LogicalSqlObjectDao(QSqlDatabase& database):
    mDatabase(database)
{

}

void LogicalSqlObjectDao::init() const{
    if(!mDatabase.tables().contains("LogicalSqlObjects")){
        QSqlQuery query(mDatabase);
        query.exec("CREATE TABLE LogicalSqlObjects (id INTEGER PRIMARY KEY"
                   "AUTOINCREMENT, nume TEXT(50), type TEXT(50), parentId int)");
    }
}

LogicalSqlObject LogicalSqlObjectDao::getSqlObject(int id){
    QSqlQuery query(mDatabase);
    query.prepare("SELECT * FROM LogicalSqlObjects WHERE id = :id");
    query.bindValue(":id", id);
    LogicalSqlObject object;
    query.exec();
    if(query.next()){
        QString nume(query.value(NUME_VALUE).toString());
        QString type(query.value(TYPE_VALUE).toString());
        int parentId(query.value(PARENTID_VALUE).toInt());
        int isCrypt{query.value(CRYPT_VALUE).toInt()};
        object.setId(id);
        object.setNume(nume);
        object.setType(type);
        object.setParent(parentId);
        object.setCrypt(isCrypt);
    }
    return object;
}

void LogicalSqlObjectDao::addSqlObject(QString &nume,
                                       QString &type,
                                       int parentId,
                                       bool isCrypt){

    QSqlQuery query(mDatabase);
    query.prepare("INSERT INTO LogicalSqlObjects (nume, type, parentId, isCrypt)"
                  "VALUES (:nume, :type, :parentId, :isCrypt)");
    query.bindValue(":nume", nume);
    query.bindValue(":type", type);
    query.bindValue(":parentId",parentId);
    query.bindValue(":isCrypt", isCrypt);
    query.exec();

}



LogicalSqlObject* LogicalSqlObjectDao::getSqlObject( QString &nume, QString &type){
    QSqlQuery query(mDatabase);
    query.exec("SELECT * FROM LogicalSqlObjects ");
    try {
        while(query.next()){
                if(nume == query.value(NUME_VALUE).toString() &&
                        type == query.value(TYPE_VALUE).toString()){
                int objectId = query.value(ID_VALUE).toInt();
                int parentId = query.value(PARENTID_VALUE).toInt();
                bool isCrypt = query.value(CRYPT_VALUE).toBool();
                LogicalSqlObject *newSqlObject = new LogicalSqlObject(objectId,
                                                                      nume,
                                                                      type,
                                                                      parentId,
                                                                      isCrypt);
                return newSqlObject;
            }
        }
    } catch (std::exception e) {

    }
    return nullptr;
}



void LogicalSqlObjectDao::setDatabase(QSqlDatabase &database){
    mDatabase = database;
}

void LogicalSqlObjectDao::addSqlObject(ILogicalSqlObject* obj){
    QSqlQuery query(mDatabase);
    query.prepare("INSERT INTO LogicalSqlObjects (nume, type, parentId, isCrypt)"
                  "VALUES (:nume, :type, :parentId, :isCrypt)");
    query.bindValue(":nume", obj->getNume());
    query.bindValue(":type", obj->getType());
    query.bindValue(":parentId", obj->getParent());
    query.bindValue(":isCrypt", obj->isCrypt());
    query.exec();
}




