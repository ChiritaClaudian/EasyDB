#ifndef ADMIN_H
#define ADMIN_H
#include "user.h"
#include <QString>
class Admin:
        public User
{
public:
    Admin();
   void addUser(User*);
   void removeUser(User*);
   void addInsertPermission(User*, QString&);
   void removeInsertPermission(User*, QString&);
   void addSelectPermission(User*, QString&);
   void removeSelectPermission(User*, QString&);
};

#endif // ADMIN_H
