#ifndef IUSER_H
#define IUSER_H
#include <QString>

class IUser
{
public:
    IUser();
    virtual ~IUser();
    virtual void resetPassword(QString&) = 0;
    virtual void resetUsername(QString&) = 0;
    virtual void setId(int ) = 0;
    virtual int getId() = 0;
};

#endif // IUSER_H
