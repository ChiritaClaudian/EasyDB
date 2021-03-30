#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)

{
    ui->setupUi(this);
    loginUI = new LoginUI();
    insertUI = new InsertQueryUI();
    queryUI = new SelectQueryUI();

    loginUI->show();

    connect(loginUI, &LoginUI::successLogin, this, &MainWindow::connectUser);
    connect(ui->uiButtonCreate, &QPushButton::clicked, this, &MainWindow::openCreateQuery);
    connect(ui->uiButtonInsert, &QPushButton::clicked, this, &MainWindow::openInsertQuery);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::connectUser(User* user)
{
    this->show();
    loginUI->setParent(0);
    loginUI->close();
    this->user = user;

}

void MainWindow::on_uiButtonWizard_clicked()
{

    queryUI->setUser(user);
    queryUI->show();
}

void MainWindow::openCreateQuery(){
    createTableUI = new CreateTabelUI();
    createTableUI->setUser(*user);
    createTableUI->show();
}

void MainWindow::openInsertQuery(){

    insertUI->setUser(user);
    insertUI->show();

}

