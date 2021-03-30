#ifndef USERDAO_H
#define USERDAO_H
#include <QString>

class QSqlDatabase;
class User;
class UserDao
{
public:
    UserDao(QSqlDatabase& database);
    UserDao();
    void init() const;
    void adduser(User& user) const;
    User* loginUser(QString username, QString password);
    void setDatabase(QSqlDatabase& database);
private:
    QSqlDatabase& mDatabase;
};

#endif // USERDAO_H
