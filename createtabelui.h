#ifndef CREATETABELUI_H
#define CREATETABELUI_H

#include <QDialog>
#include <QString>
class User;
class ILogicalSqlObject;
namespace Ui {
class CreateTabelUI;
}

class CreateTabelUI : public QDialog
{
    Q_OBJECT

public:
    explicit CreateTabelUI(QWidget *parent = nullptr);
    void setUser(User);
    ~CreateTabelUI();
signals:
    void end();

private:
    Ui::CreateTabelUI *ui;
    User *mUser;
    QString numTab;
    QString numCol;
    int type;
    QString stringType;
    QString size;
    QList<std::pair<ILogicalSqlObject *, QString>> listCol;
    bool hasPK;
    void reset();
private slots:
    void addColumn();
    void remColumn();
   // void changeType(QString);
    void finish();
};

#endif // CREATETABELUI_H
