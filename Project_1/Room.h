/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/****************************************************************************** 
 * File:   Room.h
 * Author: Kevin Maltz
 * Created on October 30, 2017, 9:08 PM
 ******************************************************************************/

#ifndef ROOM_H
#define ROOM_H

//TODO replace Trap & Monster with Trap.h & Monster.h
//#include "Monster.h"
//#include "Trap.h"
#include "Cardinal.h"

class Room
{
    private:
        //TODO update layers and rWidth in all files to appropriate const names
        static const int layers = 5;    //number of layers in a room
        static const int rmWdth = 9;    //Character width of a room
        static const int MX_CRWD = 7;   //Max Players that can fit inside a room
        bool pssgs[4];               //Does wall posses a passage
        char **rmView;          //Create dynamic char array to hold the room in
        int crowd;              //How many players are in the room
        //Trap trap;
        //Monster mnstr;
    public:
        Room();
        ~Room();
        void randPsg();
        void mkePsg(crdnl);
        bool chkPsg(crdnl);
        void dstryPsg(crdnl);
        void shwRm();
        void shwLyr0();
        void shwLyr1();
        void shwLyr2();
        void shwLyr3();
        void shwLyr4();
        //TODO create add/remove token functions. pass the token to remove from room to function
        void addTok(char);
        void rmTok(char);
};

#endif /* ROOM_H */

