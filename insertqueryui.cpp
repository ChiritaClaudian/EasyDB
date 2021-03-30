#include "insertqueryui.h"
#include "ui_insertqueryui.h"
#include <user.h>
#include "permission.h"
#include "ilogicalsqlobject.h"
#include "databasemanager.h"
#include "logicalsqlobject.h"
#include <QDebug>
#include "databasemanager.h"
#include <QSqlQuery>
#include "cryptmanager.h"

InsertQueryUI::InsertQueryUI(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InsertQueryUI),
    index(0),
    tabelIndex(0),
    hasUser(false)
{
    ui->setupUi(this);
    connect(ui->comboBox,
            QOverload<int>::of(&QComboBox::activated),
            [this](int index){this->tabelIndex = index;});
    connect(ui->uiButtonNext, &QPushButton::clicked, this, &InsertQueryUI::nextIteration);
    ui->uiLabelVal->setVisible(false);
    ui->uiLabelNumCol->setVisible(false);
    ui->lineEdit->setVisible(false);
}

InsertQueryUI::~InsertQueryUI()
{
    delete ui;
}

void InsertQueryUI::reset(){
    ui->uiLabelVal->setVisible(false);
    ui->uiLabelNumCol->setVisible(false);
    ui->lineEdit->setVisible(false);
     ui->comboBox->setVisible(true);
     ui->uiLabelTab->setText("Tabel: ");
     ui->lineEdit->setText("");
     index = -1;
     tabelIndex = 0;
     coloane.clear();
     ui->comboBox->clear();
     tabele.clear();
}

void InsertQueryUI::nextIteration(){

    if(!index){
        ui->uiLabelVal->setVisible(true);
        ui->uiLabelNumCol->setVisible(true);
        ui->lineEdit->setVisible(true);
        ui->comboBox->setVisible(false);
        ILogicalSqlObject* tabel = tabele.at(tabelIndex);
        QString numeTab = tabel->getNume();
        ui->uiLabelTab->setText("Tabel: " + numeTab);
        query = "INSERT INTO " + numeTab + " ( ";
        for(auto perm : permissions){
           ILogicalSqlObject* obj = new LogicalSqlObject(std::move(
                                                             DatabaseManager::getInstance()
                                                             .sqlObjectDao
                                                             .getSqlObject(
                                                                 perm.getSqlObjectId())));
           if(obj->getType() == "coloana" && tabel->getId() == obj->getParent())
           {

                coloane.append(obj);
           }

        }
        for(auto col = coloane.begin() + 1; col != coloane.end(); col++){
            if(col + 1 != coloane.end()){
                query = query + (*col)->getNume() + ",  ";
            }
            else{
                query = query + (*col)->getNume() +") VALUES ( ";
            }
        }
        ui->uiLabelNumCol->setText("Coloana: " + coloane.at(index + 1)->getNume());

    }
    else{
        if(index < coloane.size() - 1){
            ui->uiLabelNumCol->setText("Coloana: " + coloane.at(index + 1)->getNume());
            if(coloane.at(index - 1)->isCrypt()){
                QString val = ui->lineEdit->text();
                query = query + "'" + CryptManager::getInstance()->getEncrypt(val) + "'" + ", ";
            }
            else{
                query = query + "'" + ui->lineEdit->text() + "'" + ", ";
            }
            ui->lineEdit->setText("");
        }
        else{
            if(coloane.at(index)->isCrypt()){
                QString val = ui->lineEdit->text();
                query = query + "'" + CryptManager::getInstance()->getEncrypt(val) + "'" + ") ";
            }
            else{
               query = query + "'" + ui->lineEdit->text() + "'" + + ")";
            }

            auto execute = DatabaseManager::getInstance().executeQuerry(query);
            qDebug()<<query;
            reset();
            this->close();
        }
    }
    index++;
}

void InsertQueryUI::setUser(User *user){
        this->user = user;
        permissions = DatabaseManager::getInstance()
                .permDao.getPermissions(user->getId());
        for(auto perm : permissions){
           ILogicalSqlObject* obj = new LogicalSqlObject(std::move(
                                                             DatabaseManager::getInstance()
                                                             .sqlObjectDao
                                                             .getSqlObject(
                                                                 perm.getSqlObjectId())));
           if(obj->getType() == "tabel")
           {
                tabele.append(obj);
                ui->comboBox->addItem(obj->getNume());
           }
        }



}
