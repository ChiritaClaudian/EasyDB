#ifndef CRYPTMANAGER_H
#define CRYPTMANAGER_H

#include "simplecrypt.h"

class CryptManager
{
public:

    static CryptManager* getInstance();
    QString getEncrypt(QString&);
    QString getDecrypt(QString&);
private:
    static CryptManager* instance;
    CryptManager();
    SimpleCrypt crypt;
};



#endif // CRYPTMANAGER_H
