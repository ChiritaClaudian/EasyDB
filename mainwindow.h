#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "loginui.h"
#include "selectqueryui.h"
#include "createtabelui.h"
#include "insertqueryui.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    LoginUI *loginUI;
    SelectQueryUI *queryUI;
    User* user;
    CreateTabelUI *createTableUI;
    InsertQueryUI *insertUI;
signals:
    void sendUser(User*);
public slots:
    void connectUser(User*);
private slots:
    void on_uiButtonWizard_clicked();
    void openCreateQuery();
    void openInsertQuery();

};
#endif // MAINWINDOW_H
