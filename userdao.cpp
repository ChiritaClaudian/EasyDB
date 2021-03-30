#include "userdao.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QStringList>
#include <QVariant>
#include <user.h>
#include <QSqlRecord>
#define ID_VALUE 0
#define USERNAME_VALUE 1
#define PASSWORD_VALUE 2

UserDao::UserDao():
    mDatabase(*(new QSqlDatabase(QSqlDatabase::addDatabase("QSQLITE")))){
    mDatabase.close();
}

UserDao::UserDao(QSqlDatabase& database):
    mDatabase(database)
{

}

void UserDao::init() const{
    if(!mDatabase.tables().contains("Users")){
        QSqlQuery query(mDatabase);
        query.exec("CREATE TABLE Users (id INTEGER PRIMARY KEY"
                    "AUTOINCREMENT, username TEXT, password TEXT)");
    }
}

void UserDao::adduser(User &user) const{
    QSqlQuery query(mDatabase);
    query.prepare("INSERT INTO Users (username, password)"
                  "VALUES (:username, :password)");
    query.bindValue(":username", user.mCredential.getUsername());
    query.bindValue(":password", user.mCredential.getPassword());
    query.exec();
    user.setId(query.lastInsertId().toInt());
}

User* UserDao::loginUser(QString username, QString password){
    QSqlQuery query(mDatabase);
    query.exec("SELECT * From Users WHERE username = '"+username+"' and password = '"+password+"'");
    if(query.next()){
        User *logedUser = new User();
        logedUser->setId(query.value(ID_VALUE).toInt());
        logedUser->mCredential.setUsername(username);
        logedUser->mCredential.setPassword(password);
        return logedUser;
    }
    return nullptr;

}

void UserDao::setDatabase(QSqlDatabase &database){
    this->mDatabase = database;
}
