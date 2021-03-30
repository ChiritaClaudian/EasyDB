#include "credential.h"

Credential::Credential()
{

}

Credential::~Credential()
{

}


QString Credential::getPassword(){
    return this->mPassword;
}

QString Credential::getUsername(){
    return this->mUsername;
}

void Credential::setUsername(QString &d){
    this->mUsername = d;
}

void Credential::setPassword(QString &d){
    this->mPassword = d;
}

