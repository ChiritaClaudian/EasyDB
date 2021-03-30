#ifndef ILOGICALSQLOBJECT_H
#define ILOGICALSQLOBJECT_H
#include <QString>

class ILogicalSqlObject
{
public:
    ILogicalSqlObject();
    virtual ~ILogicalSqlObject();
    virtual void setId(int) = 0;
    virtual int getId() = 0;
    virtual QString getType() = 0;
    virtual QString getNume() = 0;
    virtual int getParent() = 0;
    virtual void setParent(int) = 0;
    virtual void setCrypt(int isCrypt) = 0;
    virtual int isCrypt() = 0;
};

#endif // ILOGICALSQLOBJECT_H
