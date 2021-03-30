#ifndef LOGICALCOLUMN_H
#define LOGICALCOLUMN_H
#include "logicalsqlobject.h"

class LogicalColumn:
        public LogicalSqlObject
{
public:
    LogicalColumn(QString nume, bool isCrypt);

};

#endif // LOGICALCOLUMN_H
