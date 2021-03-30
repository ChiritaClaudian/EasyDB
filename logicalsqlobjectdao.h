#ifndef LOGICASQLOBJECTDAO_H
#define LOGICASQLOBJECTDAO_H

class QSqlDatabase;
class QString;
class LogicalSqlObject;
class LogicalTable;
class LogicalColumn;
class ILogicalSqlObject;
class LogicalSqlObjectDao
{
public:
    LogicalSqlObjectDao();
    LogicalSqlObjectDao(QSqlDatabase& database);
    void init() const;
    void addSqlObject(QString& nume, QString& type, int parentId, bool isCrypt);
    LogicalSqlObject getSqlObject(int id);
    LogicalSqlObject* getSqlObject(QString& nume, QString& type);
    void addSqlObject(ILogicalSqlObject*);
    void setDatabase(QSqlDatabase&);

private:
    QSqlDatabase& mDatabase;
};

#endif // LOGICASQLOBJECTDAO_H
