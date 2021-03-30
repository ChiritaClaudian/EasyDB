#include "wizardqueryui.h"
#include "ui_wizardqueryui.h"

WizardQueryUI::WizardQueryUI(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WizardQueryUI)
{
    ui->setupUi(this);
}

WizardQueryUI::~WizardQueryUI()
{
    delete ui;
}
