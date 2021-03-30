#include "createtabelui.h"
#include "ui_createtabelui.h"
#include <QDebug>
#include "ilogicalsqlobject.h"
#include "logicalsqlobject.h"
#include "logicalcolumn.h"
#include "logicaltable.h"
#include "databasemanager.h"
#include "QSqlQuery"
#include "user.h"
#include <QMessageBox>
#define BASE_PERM 1
#define INTEGER_TYPE 0
#define TEXT_TYPE 1
#define BOOL_TYPE 2
#define PK_TYPE 3
CreateTabelUI::CreateTabelUI(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreateTabelUI),
    hasPK(0)
{

    ui->setupUi(this);
    connect(ui->uiButtonAddCol, &QPushButton::clicked, this, &CreateTabelUI::addColumn);
    connect(ui->uiButtonRem, &QPushButton::clicked, this, &CreateTabelUI::remColumn);
    connect(ui->uiButtonFinish, &QPushButton::clicked, this, &CreateTabelUI::finish);
    connect(ui->uiComboBoxTip,
            QOverload<int>::of(&QComboBox::activated),
            [this](int index){this->type = index;qDebug()<<this->type;});

}

CreateTabelUI::~CreateTabelUI()
{
    delete ui;
}

void CreateTabelUI::reset(){
    ui->uiComboBoxTip->repaint();
    hasPK = 0;
    ui->uiListCol->clear();
    ui->uiLineEditNumCol->setText("");
    ui->uiLineEditSize->setText("");
    ui->uiLineEditNumTab->setText("");
    listCol.clear();
}

void CreateTabelUI::addColumn(){
    numCol = ui->uiLineEditNumCol->text();
    size = ui->uiLineEditSize->text();
    switch (this->type) {
        case INTEGER_TYPE:
        stringType = "INTEGER";
        break;
    case TEXT_TYPE:
        stringType = "TEXT";
        break;
    case BOOL_TYPE:
        stringType = "BOOL";
        break;
    case PK_TYPE:
        stringType = "INTEGER PRIMARY KEY AUTOINCREMENT";
        hasPK = 1;
        size = "";
        break;

    }
    if(!listCol.size() && this->type != PK_TYPE){
        QMessageBox::warning(this,
                             tr("Executia a esuat!"),
                             tr("Tabela ta trebuie sa aibe prima coloana PK!"));

    }
    else{
        ui->uiListCol->addItem(numCol + " type: " + stringType + " size: " + size);
        ILogicalSqlObject* obj = new LogicalColumn(numCol,  ui->checkBox->isChecked());
        listCol.append({obj, stringType});
    }
}

void CreateTabelUI::remColumn(){
    QList<QListWidgetItem*> items = ui->uiListCol->selectedItems();
    if(!items.isEmpty()){
        QString numeItem = items.first()->text();
        QString numeColSel = numeItem.split(" ")[0];

        for(auto obj : listCol){
            if(obj.first->getNume() == numeColSel){
                if(obj.second.contains("PRIMARY")){
                    hasPK = false;
                }
                listCol.removeOne(obj);
                foreach(QListWidgetItem *item,items){
                    delete ui->uiListCol->takeItem(ui->uiListCol->row(item));
                }
                break;
            }
        }
    }
}

void CreateTabelUI::finish(){
    if(hasPK && listCol.at(0).second.contains("PRIMARY")){
        ILogicalSqlObject* table = new LogicalTable(ui->uiLineEditNumTab->text());
        if(table->getNume() != ""){
            QString query = "CREATE TABLE ";
            query = query + table->getNume() +" ( ";
            QString numeTab = table->getNume();
            QString typeTab = table->getType();
            DatabaseManager::getInstance().sqlObjectDao.addSqlObject(table);
           int parentId = DatabaseManager::getInstance().
                   sqlObjectDao.getSqlObject(numeTab, typeTab)->getId();
           DatabaseManager::getInstance().permDao.addPermission(mUser->getId(), parentId,BASE_PERM);
            for(auto col = listCol.begin(); col  != listCol.end(); col++){

                QString numCol = (*col).first->getNume();
                QString typeCol = (*col).first->getType();

                (*col).first->setParent(parentId);
                DatabaseManager::getInstance().sqlObjectDao.addSqlObject((*col).first);
                if(col + 1 != listCol.end()){
                    query = query + numCol + " ";
                    query = query + (*col).second + " , ";
                }
                else{
                    query = query + numCol + " ";
                    query = query + (*col).second + " ); ";
                }

                int idCol = DatabaseManager::getInstance().sqlObjectDao.getSqlObject(
                            numCol,typeCol)->getId();
                DatabaseManager::getInstance().permDao.addPermission(mUser->getId(), idCol, BASE_PERM);

            }
            qDebug()<<query;
            auto execution = DatabaseManager::getInstance().executeQuerry(query);
            reset();
            this->close();

        }
        else{
            QMessageBox::warning(this,
                                 tr("Executia a esuat!"),
                                 tr("Tabela ta trebuie sa aibe nume!"));

        }
    }
    else{
        QMessageBox::warning(this,
                             tr("Executia a esuat!"),
                             tr("Tabela ta trebuie sa aibe o coloana PK si sa fie prima!"));

    }
}

void CreateTabelUI::setUser(User user){
    mUser = new User(user);
}
