/****************************************************************************** 
 * File:   Player.h
 * Author: Kevin Maltz
 * Created on November 1, 2017, 8:53 PM
 ******************************************************************************/

#ifndef PLAYER_H
#define PLAYER_H

#include <string>

class Player
{
    private:
        std::string name;
        char token;
        int hp;
        int atk;
        int plyNum;
        bool alive;

    public:
        Player();
        Player(std::string n, char tok, int pNum);
        ~Player();
        void setName(std::string);
        void getName();
        void setTkn(char);
        char getTkn();
        void dmgHp(int);
        void healHp(int);
        bool isAlive();
        int getAtk();
        void loseAtk(int);
        void gainAtk(int);
        
        
};

#endif /* PLAYER_H */

