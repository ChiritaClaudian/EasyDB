#ifndef USERUILOGIC_H
#define USERUILOGIC_H
#include "iuseruilogic.h"

class UserUILogic :
        public IUserUILogic
{
public:
    UserUILogic();
    void changeCredentialUI() override;
};

#endif // USERUILOGIC_H
