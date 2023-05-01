#ifndef USER_H_
#define USER_H_

#include "wet1util.h"

class User{
    private:
        int id;
        bool is_vip;
        //Tree* user_group
        int[4] movies_user_watched;

    public:
        User(int user_id, bool is_Vip, ... , int[4] movies_watched):id(user_id), is_vip(is_Vip), ...{
            for(int i = 0; i <= 4; i++){
                movies_user_watched[i] = movies_watched[i];
            }
        }

        virtual ~User(){
            free(movies_user_watched);
        }

        User(const User& user) = default;
        


}

    

