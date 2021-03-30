#ifndef MYMODEL_H
#define MYMODEL_H
#include <QSqlQueryModel>

class MyModel :
        QSqlQueryModel
{
public:
    MyModel();
    QVariant data(const QModelIndex &item, int role = Qt::DisplayRole) const override;

};

#endif // MYMODEL_H
