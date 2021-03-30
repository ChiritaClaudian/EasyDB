#ifndef USER_H
#define USER_H
#include "iuser.h"
#include "credential.h"
#include <QString>
#include "permission.h"
class User :
        public IUser
{
public:
    User();
    User(QString username, QString password);
    void resetPassword(QString&) override;
    void resetUsername(QString&) override;
    void setId(int) override;
    int getId() override;
     Credential mCredential;
private:

    Permission mTabelList;
    Permission mColumnList;
    int mId;
};

#endif // USER_H
