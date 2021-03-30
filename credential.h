#ifndef CREDENTIAL_H
#define CREDENTIAL_H
#include <QString>

class Credential
{
public:
    Credential();
    ~Credential();
    QString getPassword();
    void setPassword(QString&);
    QString getUsername();
    void setUsername(QString&);
private:
    QString mPassword;
    QString mUsername;
};

#endif // CREDENTIAL_H
