#ifndef QUERYRESULTUI_H
#define QUERYRESULTUI_H

#include <QDialog>
#include <QList>

class QSqlQuery;
class ILogicalSqlObject;
namespace Ui {
class QueryResultUI;
}

class QueryResultUI : public QDialog
{
    Q_OBJECT

public:
    explicit QueryResultUI(QWidget *parent = nullptr);
    void setQuery(QSqlQuery, QList<ILogicalSqlObject*>);
    ~QueryResultUI();

private:
    Ui::QueryResultUI *ui;



};

#endif // QUERYRESULTUI_H
