#ifndef REGISTRATIONUI_H
#define REGISTRATIONUI_H

#include <QDialog>
#include <QString>
#include <QMessageBox>
#include <QFile>
#include <QDebug>

namespace Ui {
class RegistrationUI;
}

class RegistrationUI : public QDialog
{
    Q_OBJECT

public:
    explicit RegistrationUI(QWidget *parent = nullptr);
    ~RegistrationUI();

private:
    Ui::RegistrationUI *ui;
public slots:
    void confirmRegistration();
signals:
    void registrationComplete();
};

#endif // REGISTRATIONUI_H
