#include "cryptmanager.h"

CryptManager* CryptManager::instance = NULL;

CryptManager::CryptManager():
    crypt{Q_UINT64_C(0xdeadbeefdeadbeef)}
{

}

CryptManager* CryptManager::getInstance(){
    if(CryptManager::instance == nullptr)
       CryptManager::instance = new CryptManager();
    return CryptManager::instance;
}

QString CryptManager::getDecrypt(QString& mesaj){
    return crypt.decryptToString(mesaj);
}

QString CryptManager::getEncrypt(QString& mesaj){
    return crypt.encryptToString(mesaj);
}
