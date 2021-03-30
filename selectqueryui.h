#ifndef SELECTQUERYUI_H
#define SELECTQUERYUI_H

#include <QWidget>
#include <user.h>
#include <QVector>
#include <QListWidgetItem>
#include "queryresultui.h"
#include "joinui.h"
class ILogicalSqlObject;
namespace Ui {
class SelectQueryUI;
}

class SelectQueryUI : public QWidget
{
    Q_OBJECT

public:
    explicit SelectQueryUI(QWidget *parent = nullptr);
    ~SelectQueryUI();
    void setUser(User*);
private:
    Ui::SelectQueryUI *ui;
    User* mUser;
    QList<ILogicalSqlObject *> tabeleSel;
    QList<ILogicalSqlObject *> tabeleVal;
    QList<ILogicalSqlObject *> colVal;
    QList<ILogicalSqlObject *> colSel;
    QVector<Permission> permissions;
    QString querryComand;
    JoinUI *joinUI;
    QueryResultUI *queryResultUI;
private slots:
    void addTabel();
    void removeTabel();
    void addColoana();
    void removeColoana();
    void executeSelect();
    void sendQuery(QList<std::pair<QString, QString>>);
};

#endif // SELECTQUERYUI_H
