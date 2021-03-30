#ifndef JOINUI_H
#define JOINUI_H

#include <QDialog>
#include <QList>
#include <utility>
#include <QString>
class ILogicalSqlObject;
class Permission;
namespace Ui {
class JoinUI;
}

class JoinUI : public QDialog
{
    Q_OBJECT

public:
    explicit JoinUI(QWidget *parent = nullptr);
    void setParameters(QList<ILogicalSqlObject*>, QVector<Permission>);
    ~JoinUI();
signals:
   void finish(  QList<std::pair<QString, QString>>);
private:
    Ui::JoinUI *ui;
    QList<ILogicalSqlObject *> mListTab;
    QList<ILogicalSqlObject *> mListColVal;
    QList<std::pair<QString, QString>> listOnClause;
    int indexCurentTab;
    QString selCol1;
    QString selCol2;
private slots:
    void selectFromCurentTab();
    void selectFromAvalCol();
    void nextIteration();
};

#endif // JOINUI_H
