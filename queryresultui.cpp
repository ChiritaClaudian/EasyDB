#include "queryresultui.h"
#include "ui_queryresultui.h"
#include <QSqlQuery>
#include <QAbstractTableModel>
#include <QSqlQueryModel>
#include "ilogicalsqlobject.h"
#include <QDebug>
#include "cryptmanager.h"



QueryResultUI::QueryResultUI(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QueryResultUI)
{
    ui->setupUi(this);

}

QueryResultUI::~QueryResultUI()
{
    delete ui;
}

void QueryResultUI::setQuery(QSqlQuery query, QList<ILogicalSqlObject*> colSel){
    QSqlQuery testQuery = query;
    int maxRow = 0;
    int row = 0;

    while(testQuery.next()){
        maxRow++;
    }
    ui->tableWidget->setRowCount(maxRow);
    ui->tableWidget->setColumnCount(colSel.size());
    QTableWidgetItem *item[10][10];
    QStringList tableHeader;
    for(auto obj : colSel){
        tableHeader<<obj->getNume();
    }
    ui->tableWidget->setHorizontalHeaderLabels(tableHeader);
    while(query.previous()){

    }
    while(query.next()){
        for(int col = 0; col < colSel.size(); col++){
            QString result = query.value(col).toString();
            item[row][col] = new QTableWidgetItem();
            if(colSel.at(col)->isCrypt()){
                result = CryptManager::getInstance()->getDecrypt(result);
            }
            item[row][col]->setText(result);
           // ui->tableWidget->ins
        }
        row++;
    }
    for(int row = 0; row < maxRow; row++){
        for(int col = 0; col < colSel.size(); col++){
            qDebug()<<item[row][col]->text();
            ui->tableWidget->setItem(row, col, item[row][col]);

        }
    }
}
