#include "user.h"

User::User(QString username, QString password){
    mCredential.setUsername(username);
    mCredential.setPassword(password);
}

User::User():
    mId(-1)

{

}

void User::resetPassword(QString &){

}

void User::resetUsername(QString &){

}

void User::setId(int id){
    this->mId = id;
}

int User::getId(){
    return mId;
}
