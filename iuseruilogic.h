#ifndef IUSERUILOGIC_H
#define IUSERUILOGIC_H

#include <QMainWindow>

class IUserUILogic : public QMainWindow
{
    Q_OBJECT
public:
    explicit IUserUILogic(QWidget *parent = nullptr);
    virtual ~IUserUILogic();
    virtual void changeCredentialUI() = 0;
};

#endif // IUSERUILOGIC_H
