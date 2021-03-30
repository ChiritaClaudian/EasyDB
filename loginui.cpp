#include "loginui.h"
#include "ui_loginui.h"
#include "databasemanager.h"

LoginUI::LoginUI(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginUI)
{
    this->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    ui->setupUi(this);
    connect(ui->uiButtonLogin, &QPushButton::clicked,
            this, &LoginUI::checkCredentials);
    connect(ui->uiButtonRegister, &QPushButton::clicked,
            this, &LoginUI::openRegUI);

}

LoginUI::~LoginUI()
{
    delete ui;
}

void LoginUI::checkCredentials(){
    QString username(ui->uiLineUsername->text());
    QString password(ui->uiLinePassword->text());
    /*
    bool isGood = false;

    //To DO: sa verific baza de date cu aceste credentiale
    QFile fakeDB(QCoreApplication::applicationDirPath()
                 + "//fakeDataBase.db");
    if(!fakeDB.open(QIODevice::ReadOnly | QIODevice::Text)){
        qDebug()<<"Nu exista baza de date...";
        qDebug()<<QCoreApplication::applicationDirPath();
        return;
    }
    QTextStream in(&fakeDB);
    QString lineDB = in.readLine();
    //Qt voodoo string parser
    QRegExp rx("[, :\n");
    while(!lineDB.isNull()){
        QStringList list = lineDB.split(" ");
        if(list.at(0) == username && list.at(1) == password){
            User* logedUser = new Admin();
            emit LoginUI::successLogin(logedUser);
            qDebug()<<"Logare cu succes";
            isGood = true;
        }
        lineDB = in.readLine();
    }
    if(!isGood){

    }
    fakeDB.close();
    */
    User *logedUser = DatabaseManager::getInstance().userDao.loginUser(username, password);
    if(logedUser != nullptr){
        emit LoginUI::successLogin(logedUser);
    }
    else{
        QMessageBox::warning(this,
                             tr("Logarea a esuat!"),
                             tr("Credentialele folosite sunt gresite sau nu exista acest utilizator!"));
        qDebug()<<"nu exista";
    }


}

void LoginUI::openRegUI(){
    registrationUI = new RegistrationUI();
    registrationUI->show();
}
