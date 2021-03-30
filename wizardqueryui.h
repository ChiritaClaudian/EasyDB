#ifndef WIZARDQUERYUI_H
#define WIZARDQUERYUI_H

#include <QDialog>

namespace Ui {
class WizardQueryUI;
}

class WizardQueryUI : public QDialog
{
    Q_OBJECT

public:
    explicit WizardQueryUI(QWidget *parent = nullptr);
    ~WizardQueryUI();

private:
    Ui::WizardQueryUI *ui;
};

#endif // WIZARDQUERYUI_H
