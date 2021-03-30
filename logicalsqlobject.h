#ifndef LOGICALSQLOBJECT_H
#define LOGICALSQLOBJECT_H
#include "ilogicalsqlobject.h"
#include <QString>
class LogicalSqlObject :
        public ILogicalSqlObject
{
public:
    LogicalSqlObject();
    LogicalSqlObject(int id, QString &nume, const QString& type, int parentId, bool );
    LogicalSqlObject(const LogicalSqlObject&);
    void setId(int) override;
    int getId() override;
    void setType(QString &);
    QString getType() override;
    void setNume(QString&);
    QString getNume() override;
    int getParent() override;
    void setParent(int) override;
    void setCrypt(int) override;
    int isCrypt() override;
private:
    QString mNume;
    QString mType;
    int mId;
    int mParentId;
    bool mIsCrypt;
};

#endif // LOGICALSQLOBJECT_H
