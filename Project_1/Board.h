/****************************************************************************** 
 * File:   Board.h
 * Author: Kevin Maltz
 * Created on November 1, 2017, 6:28 PM
 ******************************************************************************/

#ifndef BOARD_H
#define BOARD_H

#include <fstream>
#include "Cardinal.h"
#include "Room.h"

struct Coords
{
    int row;
    int col;
};
class Board
{
    private:
        static const int ROW = 8;
        static const int COL = 16;
        static const int RM_LYRS = 5;
        static const int RM_WDTH = 9;
        bool **rmExst;
        Room **rmGrid;
        Coords *plyrLoc;
        void strctRm(crdnl);    //
        void cnctRms(crdnl);
        bool psgOpn(crdnl, int);     //Check if a move is allowable from the room
        void brdConf();           //Randomly select then build a board configuration
        crdnl flpD(crdnl);          //Returns the opposite direction
    public:
        Board(int players = 7);
        ~Board();
        void shwBrd();
        bool mve2Rm(crdnl dirctn, int plyrID, char token);
        void mveOpts(int plyrID);
};

#endif /* BOARD_H */

