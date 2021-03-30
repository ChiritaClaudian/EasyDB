#include "registrationui.h"
#include "ui_registrationui.h"
#include "databasemanager.h"
#include "user.h"
RegistrationUI::RegistrationUI(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RegistrationUI)
{
    ui->setupUi(this);
    connect(ui->uiButtonConfirm, &QPushButton::clicked,
            this, &RegistrationUI::confirmRegistration);
    connect(this, &RegistrationUI::registrationComplete,
            [this]{this->close();});
}

RegistrationUI::~RegistrationUI()
{
    delete ui;
}
//TO DO: trimiterea informatiilor catre baza de date
void RegistrationUI::confirmRegistration(){
    QString username = ui->uiLineUsername->text();
    QString password1 = ui->uiLinePassword1->text();
    QString password2 = ui->uiLinePassword2->text();
    if(password1 != password2){
        QMessageBox::warning(this,
                             tr("Inregistrarea a esuat!"),
                             tr("Trebuie sa introduci aceasi parola in ambele campuri!"));
        return;
    }
    User newUser(username, password1);
    DatabaseManager::getInstance().userDao.adduser(newUser);
    /*
    QFile fakeDB(QCoreApplication::applicationDirPath()
                 + "//fakeDataBase.db");
    if(!fakeDB.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append)){
        qDebug()<<"Nu exista baza de date...";
        return;
    }
    QTextStream stream(&fakeDB);
    stream<<username + " " + password1;
    */

    emit RegistrationUI::registrationComplete();
}


