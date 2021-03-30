#include "databasemanager.h"
#include <QDebug>
#include <QSqlDatabase>
#include <QCoreApplication>
#include <QSqlQuery>

DatabaseManager& DatabaseManager::getInstance(){
    static DatabaseManager singleton;
    return singleton;
}

DatabaseManager::DatabaseManager(const QString &path):
    mDatabase((new QSqlDatabase(QSqlDatabase::addDatabase("QSQLITE"))))
{
    userDao.setDatabase(*mDatabase);
    sqlObjectDao.setDatabase(*mDatabase);
    permDao.setDatabase(*mDatabase);
    mDatabase->setDatabaseName("C:\\Users\\chiri\\Documents\\qt_Project\\build-EasyDB-Desktop_Qt_5_14_1_MSVC2017_64bit-Debug\\database.db");
    if(!mDatabase->open()){
        qDebug()<<"nu merge baza de date";
    }

    userDao.init();
    sqlObjectDao.init();
    permDao.init();
}

DatabaseManager::~DatabaseManager(){
    mDatabase->close();
    delete mDatabase;
}

QSqlQuery DatabaseManager::executeQuerry(QString command){
    QSqlQuery query(*mDatabase);
    query.exec(command);
    return query;
}
