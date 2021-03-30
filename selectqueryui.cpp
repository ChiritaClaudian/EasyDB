#include "selectqueryui.h"
#include "ui_selectqueryui.h"
#include "mainwindow.h"
#include "databasemanager.h"
#include "permission.h"
#include "logicalsqlobject.h"
#include "ilogicalsqlobject.h"
#include "databasemanager.h"
#include <QVector>
#include <QDebug>
#include <QSqlQuery>
#include <QWidgetItem>
#include <algorithm>
#define TABEL_POS 0
#define COL_POS 1
SelectQueryUI::SelectQueryUI(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SelectQueryUI)
{
    ui->setupUi(this);
    joinUI = new JoinUI();
    queryResultUI = new QueryResultUI();
    connect(ui->uiButtonAddTab, &QPushButton::clicked, this, &SelectQueryUI::addTabel);
    connect(ui->uiButtonRemTab, &QPushButton::clicked, this, &SelectQueryUI::removeTabel);
    connect(ui->uiButtonAddCol, &QPushButton::clicked, this, &SelectQueryUI::addColoana);
    connect(ui->uiButtonRemCol, &QPushButton::clicked, this, &SelectQueryUI::removeColoana);
    connect(ui->uiButtonExe, &QPushButton::clicked, this, &SelectQueryUI::executeSelect);
    connect(joinUI, &JoinUI::finish, this, &SelectQueryUI::sendQuery);

}

SelectQueryUI::~SelectQueryUI()
{
    delete ui;
}

void deleteItemsFromWidgetList(QListWidget*& listWidget,
                               QList<ILogicalSqlObject*> &list,
                               QString numeTabelSelectat){
    QList<QListWidgetItem*> delList;

        for(auto item : listWidget->findItems("*", Qt::MatchWildcard)){
            QString numeTabelAlColSel = item->text().split(".")[TABEL_POS];
            QString numeColSel = item->text().split(".")[COL_POS];
            if(numeTabelAlColSel == numeTabelSelectat){

                delList.append(listWidget->takeItem(listWidget->row(item)));
                QList<ILogicalSqlObject*>::iterator delObj;
                delObj = std::find_if(list.begin(),
                                      list.end(),
                                      [numeColSel](ILogicalSqlObject* o){
                                            return numeColSel == o->getNume();
                                      });
                if(delObj != list.end()){
                    list.erase(delObj);
                }
            }
        }
        for(auto item : delList){
            delete listWidget->takeItem(listWidget->row(item));
        }

}

void SelectQueryUI::setUser(User *user){
    this->mUser = user;
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
            ui->uiListTabVal->addItem(obj->getNume());
            tabeleVal.append(obj);
       }
    }

}

void SelectQueryUI::addTabel(){
    ILogicalSqlObject* parentTabel;
    QList<QListWidgetItem*> items = ui->uiListTabVal->selectedItems();
    if(!items.isEmpty()){
        QString numeTabelSelectat = items.first()->text();
        for(auto obj : tabeleVal){
            if(obj->getNume() == numeTabelSelectat){
                parentTabel = obj;
                tabeleSel.append(obj);
                tabeleVal.removeOne(obj);
                ui->uiListTabSel->addItem(obj->getNume());
                foreach(QListWidgetItem *item,items){
                    delete ui->uiListTabVal->takeItem(ui->uiListTabVal->row(item));
                }
                break;
            }
        }

        for(auto perm : permissions){
           ILogicalSqlObject* obj = new LogicalSqlObject(std::move(
                                                             DatabaseManager::getInstance()
                                                             .sqlObjectDao
                                                             .getSqlObject(
                                                                 perm.getSqlObjectId())));
           if(obj->getType() == "coloana" && parentTabel->getId() == obj->getParent())
           {
                qDebug()<<obj->isCrypt();
                ui->uiListColVal->addItem(parentTabel->getNume()+"."+obj->getNume());
                colVal.append(obj);
           }
        }
    }

}

void SelectQueryUI::removeTabel(){
    QList<QListWidgetItem*> items = ui->uiListTabSel->selectedItems();
    if(!items.isEmpty()){
        QString numeTabelSelectat = items.first()->text();
        for(auto obj : tabeleSel){
            if(obj->getNume() == numeTabelSelectat){
                tabeleVal.append(obj);
                tabeleSel.removeOne(obj);
                ui->uiListTabVal->addItem(obj->getNume());
                foreach(QListWidgetItem *item,items){
                    delete ui->uiListTabSel->takeItem(ui->uiListTabSel->row(item));
                }
                break;
            }
        }
        deleteItemsFromWidgetList(ui->uiListColVal,colVal, numeTabelSelectat);
        deleteItemsFromWidgetList(ui->uiListColSel, colSel, numeTabelSelectat);
    }



}

void SelectQueryUI::addColoana(){
    QList<QListWidgetItem*> items = ui->uiListColVal->selectedItems();
    if(!items.isEmpty()){
        QString itemSel = items.first()->text();
        QString numColSel = itemSel.split(".")[COL_POS];
        for(auto obj : colVal){
            if(obj->getNume() == numColSel){
                colSel.append(obj);
                colVal.removeOne(obj);
                ui->uiListColSel->addItem(itemSel);
                foreach(QListWidgetItem *item,items){
                    delete ui->uiListColVal->takeItem(ui->uiListColVal->row(item));
                }
                break;
            }
        }
    }
}

void SelectQueryUI::removeColoana(){
    QList<QListWidgetItem*> items = ui->uiListColSel->selectedItems();
    if(!items.isEmpty()){
        QString numeItem = items.first()->text();
        QString numeColSel = numeItem.split(".")[COL_POS];

        for(auto obj : colSel){
            if(obj->getNume() == numeColSel){
                colVal.append(obj);
                colSel.removeOne(obj);
                ui->uiListColVal->addItem(numeItem);
                foreach(QListWidgetItem *item,items){
                    delete ui->uiListColSel->takeItem(ui->uiListColSel->row(item));
                }
                break;
            }
        }
    }
}

void SelectQueryUI::executeSelect(){
    bool atLeastOne;
    bool canExecute = false;
    for(auto tab : tabeleSel){
        atLeastOne = false;
        for(auto col : colSel){
            if(col->getParent() == tab->getId()){
                atLeastOne = true;
                break;
            }
        }
        if(atLeastOne)
            canExecute = true;
        else{
            canExecute = false;
            break;
            QMessageBox::warning(this,
                                 tr("Executia a esuat!"),
                                 tr("Trebuie sa selectezi cel putin o coloana din fiecare tabel "));

        }
    }
    if(canExecute){
        querryComand = "SELECT ";
        for(auto objTab : tabeleSel){
            qDebug()<<objTab->getNume();
            for(auto objCol = colSel.begin(); objCol != colSel.end(); objCol++){
                if((*objCol)->getParent() == objTab->getId()){
                    querryComand += objTab->getNume() + "." + (*objCol)->getNume();
                    if(objCol + 1 != colSel.end()){
                        querryComand += ", ";
                    }
                }
            }
        }
        querryComand += " From " + tabeleSel.first()->getNume() + " ";
        if(tabeleSel.count() <= 1){
            //execute querry
            QSqlQuery query ;
            queryResultUI->setQuery(DatabaseManager::getInstance().executeQuerry(querryComand), colSel);
            queryResultUI->show();
            qDebug()<<"execute";
        }
        else{
            joinUI->setParameters(tabeleSel, permissions);
            joinUI->show();
        }
   }
}

void SelectQueryUI::sendQuery(QList<std::pair<QString, QString>> listOnClause){
    joinUI->close();
    for(auto clause : listOnClause){
        querryComand += "Inner Join "
                + clause.second.split(".")[TABEL_POS]
                + " on " + clause.first
                + " = " + clause.second + " ";
    }
    //execute querry
    QSqlQuery query ;
    queryResultUI->setQuery(DatabaseManager::getInstance().executeQuerry(querryComand), colSel);
    queryResultUI->show();
    qDebug() << querryComand;
}
