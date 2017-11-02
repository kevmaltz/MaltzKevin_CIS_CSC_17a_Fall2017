#include "Player.h"

Player::Player()
{
    alive = true;
    name = "N/A";
    token = " ";
    plyNum = 8;
    hp = 20;
    atk = 2;
}
Player::Player(std::string n, char tok, int pNum)
{
    alive = true;
    name = n;
    token = tok;
    plyNum = pNum;
    hp = 20;
    atk = 2;
    
}
void Player::setName(std::string n)
{
    name = n;
}
void Player::getName()
{
    return name;
}
void Player::setTkn(char t)
{
    token = t;
}
char Player::getTkn()
{
    return token;
}
void Player::dmgHp(int dmg)
{
    hp = hp - dmg;
}
void Player::healHp(int heal)
{
    hp = hp + heal;
}
bool Player::isAlive()
{
    if(hp <= 0)
        alive = false;
    return alive;
}
int Player::getAtk()
{
    return atk;
}
void Player::gainAtk(int bonus)
{
    atk = atk + bonus;
}
void Player::loseAtk(int pnlty)
{
    atk = atk - pnlty;
}
