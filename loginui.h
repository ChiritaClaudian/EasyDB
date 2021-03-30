#ifndef LOGINUI_H
#define LOGINUI_H

#include <QDialog>
#include "user.h"
#include <QString>
#include <QFile>
#include <QDebug>
#include "admin.h"
#include "baseuser.h"
#include <QMessageBox>
#include <QDir>
#include "registrationui.h"
namespace Ui {
class LoginUI;
}

class LoginUI : public QDialog
{
    Q_OBJECT

public:
    explicit LoginUI(QWidget *parent = nullptr);
    ~LoginUI();

private:
    Ui::LoginUI *ui;
    RegistrationUI* registrationUI;

signals:
   void successLogin(User*);
public slots:
   void checkCredentials();
   void openRegUI();
};

#endif // LOGINUI_H
