#include "joinui.h"
#include "ui_joinui.h"
#include <ilogicalsqlobject.h>
#include "permission.h"
#include "databasemanager.h"
#include "logicalsqlobject.h"
#include "permission.h"
#include <QMessageBox>

JoinUI::JoinUI(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::JoinUI),
    indexCurentTab(0)
{
    ui->setupUi(this);
    connect(ui->uiButtonSelect1, &QPushButton::clicked, this, &JoinUI::selectFromCurentTab);
    connect(ui->uiButtonSelect2, &QPushButton::clicked, this, &JoinUI::selectFromAvalCol);
    connect(ui->uiButton, &QPushButton::clicked, this, &JoinUI::nextIteration);
}

JoinUI::~JoinUI()
{
    delete ui;
}

void clearList(QListWidget* &list){
    int len = list->count();
    for(int i = 0 ; i < len; i++){
        QListWidgetItem* item = list->item(0);
        delete list->takeItem(list->row(item));
    }
}

void JoinUI::setParameters(QList<ILogicalSqlObject *>listTab,
                            QVector<Permission> permissions){
    mListTab = listTab;
   // mListColVal
    for(auto perm : permissions){
       ILogicalSqlObject* obj = new LogicalSqlObject(std::move(
                                                         DatabaseManager::getInstance()
                                                         .sqlObjectDao
                                                         .getSqlObject(
                                                             perm.getSqlObjectId())));
       for(auto parentTabel : mListTab)
           if(obj->getType() == "coloana" && parentTabel->getId() == obj->getParent())
           {
                mListColVal.append(obj);
           }
       }

    ILogicalSqlObject* tabBaza = listTab.at(indexCurentTab++);
    ILogicalSqlObject* tabCur = listTab.at(indexCurentTab++);
    for(auto obj : mListColVal){
        if(obj->getParent() == tabBaza->getId()){
            ui->uiListColTab->addItem(tabBaza->getNume() + "." + obj->getNume());
        }
        else if(obj->getParent() == tabCur->getId()){
            ui->uiListColAv->addItem(tabCur->getNume() + "." + obj->getNume());
        }
    }

}

void JoinUI::selectFromAvalCol(){
    QString numeColSel = ui->uiListColAv->selectedItems().first()->text();
    selCol2 = numeColSel;
    ui->uiLabelSecondCol->setText("Coloana selectata: " + numeColSel);
}

void JoinUI::selectFromCurentTab(){
    QString numeColSel = ui->uiListColTab->selectedItems().first()->text();
    selCol1 = numeColSel;
    ui->uiLabelFirstCol->setText("Coloana selectata: " + numeColSel);
}

void JoinUI::nextIteration(){
    if(selCol1 != "" && selCol2 != ""){
        std::pair<QString, QString> onClause({selCol1,selCol2});
        listOnClause.append(onClause);
        if(indexCurentTab <  mListTab.size()){
            clearList(ui->uiListColAv);
            clearList(ui->uiListColTab);

            ILogicalSqlObject* tabCur = mListTab.at(indexCurentTab);
            for(auto obj : mListColVal){
                for(int i = 0; i < indexCurentTab; i++){
                    ILogicalSqlObject* tab = mListTab.at(i);
                    if(tab->getId() == obj->getParent()){
                        ui->uiListColAv->addItem(tab->getNume() + "." + obj->getNume());
                    }
                }
                if(obj->getParent() == tabCur->getId()){
                    ui->uiListColTab->addItem(tabCur->getNume() + "." + obj->getNume());
                }
            }
             ui->uiLabelFirstCol->setText("Coloana selectata: ");
             ui->uiLabelSecondCol->setText("Coloana selectata: ");
             selCol1 = "";
             selCol2 = "";
             indexCurentTab++;

        }
        else{
            indexCurentTab = 0;
            emit(finish(listOnClause));

        }
    }
    else{
        QMessageBox::warning(this,
                             tr("Executia a esuat!"),
                             tr("Trebuie sa selectezi o coloana din ambele liste!"));
    }
}
