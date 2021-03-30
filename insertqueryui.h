#ifndef INSERTQUERYUI_H
#define INSERTQUERYUI_H

#include <QDialog>
#include <QString>
class Permission;
class ILogicalSqlObject;
class User;
namespace Ui {
class InsertQueryUI;
}

class InsertQueryUI : public QDialog
{
    Q_OBJECT

public:
    explicit InsertQueryUI(QWidget *parent = nullptr);
    ~InsertQueryUI();
    void setUser(User*);
private:
    QString query;
    Ui::InsertQueryUI *ui;
    int index;
    User *user;
    QVector<Permission> permissions;
    QList<ILogicalSqlObject*> tabele;
    QList<ILogicalSqlObject*> coloane;
    int tabelIndex;
    void reset();
    bool hasUser;
private slots:
    void nextIteration();
};

#endif // INSERTQUERYUI_H
