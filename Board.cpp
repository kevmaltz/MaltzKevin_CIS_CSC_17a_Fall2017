#include "Board.h"
#include <iostream>

using namespace std;

//Private utility functions
bool Board::psgOpn(crdnl drctn, int plyrID)
{
    return rmGrid[plyrLoc[plyrID].row][plyrLoc[plyrID].col].chkPsg(drctn);
}

crdnl Board::flpD(crdnl dir)
{
    switch(dir)
    {
        case North:     dir = South; break;
        case East:      dir = West; break;
        case South:     dir = North; break;
        case West:      dir = East; break;
    }
    return dir;
}

void Board::brdConf()
{
    crdnl d;        //Wall to create passage in
    
    int numEPsg[ROW] = {9,7,6,10,4,6,10,6}; //# of East passages in each row
    int ePsgC[ROW][COL] = //Col # of rooms with East passage in each row
                          {{0,1,2,3,4,8,9,12,13},   
                          {0,1,5,10,11,12,13},
                          {1,2,4,9,13,14},
                          {0,3,4,6,7,9,10,11,12,13},
                          {1,3,4,10},
                          {5,7,8,10,11,14},
                          {0,1,2,3,5,9,10,11,12,13},
                          {4,5,6,11,12,13}};
    
    int numSPsg[ROW] = {7,7,7,5,5,8,7,0}; //# of South passages in each row
    int sPsgC[ROW][COL] = //Col # of rooms with South passage in each row
                          {{2,3,5,8,10,14,15},
                          {0,3,4,6,8,10,15},
                          {0,3,5,6,8,9,13},
                          {0,1,8,11,14},
                          {0,2,5,8,10,14},
                          {0,1,2,6,7,9,12,15},
                          {0,1,4,5,7,14,15},
                          {}};
    
    //Create all East passages and adjoining West passages
    d = East;
    for(int row=0; row < ROW; row++)
    {
        for(int psgN=0; psgN < numEPsg[row]; psgN++)
        {
            rmGrid[row][ePsgC[row][psgN]].mkePsg(d);
            rmGrid[row][ePsgC[row][psgN] + 1].mkePsg(flpD(d));
        }
    }
    
    //Create all South passages and adjoining North passages
    d = South;
    for(int row=0; row < ROW; row++)
    {
        for(int psgN=0; psgN < numSPsg[row]; psgN++)
        {
            rmGrid[row][sPsgC[row][psgN]].mkePsg(d);
            rmGrid[row + 1][sPsgC[row][psgN]].mkePsg(flpD(d));
        }
    }
    
    //Set exit location
    exit.row = 7;
    exit.col = 15;
}

//Default Constructor
Board::Board(int numPlyr)
{
    //Memory allocation
    rmExst = new bool* [ROW];
    for(int i=0; i < ROW; i++)
    {
        rmExst[i] = new bool[COL]();
    }
    //Testing rmExst
//    for(int row=0; row < ROW; row++)
//    {
//        rmExst[row][0] = true;
//    }
    
    plyrLoc = new Coords[numPlyr];
    
    rmGrid = new Room* [ROW];
    for(int i=0; i < ROW; i++)
    {
        rmGrid[i] = new Room[COL];
    }
    
    //Initialize Player coordinates to start point
    for(int i=0; i < numPlyr; i++)
    {
        plyrLoc[i] = {0,0};
    }
    
    //Create board configuration
    brdConf();
    
    //Testing if brdConf works properly, make all rooms visible
    for(int row=0; row < ROW; row++)
    {
        for(int col=0; col < COL; col++)
            rmExst[row][col] = true;
    }
}

//Destructor
Board::~Board()
{
    //Release rmExst array memory
    for(int i=0; i < ROW; i++)
        delete [] rmExst[i];
    delete [] rmExst;
    
    //Release plyrLoc array memory
    delete [] plyrLoc;
    
    //Release rmGrid array memory
    for(int i=0; i < ROW; i++)
        delete [] rmGrid[i];
    delete [] rmGrid;
}

//Public member functions
void Board::entrBrd(char token)
{
    rmGrid[0][0].addTok(token);
}

void Board::shwBrd()
{
    for(int row = 0; row < ROW; row++)
    {
        for(int lyr=0; lyr < RM_LYRS; lyr++)
        {
            for(int col=0; col < COL; col++)
            {
                if(rmExst[row][col])
                {
                    rmGrid[row][col].shwLyr(lyr);
                }
                else
                {
                    for(int i=0; i < RM_WDTH; i++)
                    {
                        cout << ' ';
                    }
                }
            }
            cout << endl;
        }
    }
    cout << "\n\n\n";
}

bool Board::mve2Rm(crdnl drctn, int plyrID, char token)
{
    bool moved;
    int curRow = plyrLoc[plyrID-1].row;
    int curCol = plyrLoc[plyrID-1].col;
    if(rmGrid[curRow][curCol].chkPsg(drctn))
    {
        //Remove player token from current room
        rmGrid[curRow][curCol].rmTok(token);

        //Update player location based on movement selected
        switch(drctn)
        {
            case North:
                curRow -= 1;
                break;
            case East:
                curCol += 1;
                break;
            case South:
                curRow += 1;
                break;
            case West:
                curCol -= 1;
                break;
        }
        plyrLoc[plyrID-1].row = curRow;
        plyrLoc[plyrID-1].col = curCol;
        
        //TODO
        //Activate entered room trap/monster spawner
        //rmGrid[curRow][curCol]
        
        //Add player token to room entered
        rmGrid[curRow][curCol].addTok(token);
        rmExst[curRow][curCol] = true;
        
        moved = true;
    }
    else
        moved = false;
}

void Board::mveOpts(int plyrID, bool mveOpt[])
{
    //Check North
    if(rmGrid[plyrLoc[plyrID-1].row][plyrLoc[plyrID-1].col].chkPsg(North))
        mveOpt[North] = true;
    else
        mveOpt[North] = false;
    
    //Check East
    if(rmGrid[plyrLoc[plyrID-1].row][plyrLoc[plyrID-1].col].chkPsg(East))
        mveOpt[East] = true;
    else
        mveOpt[East] = false;
    
    //Check South
    if(rmGrid[plyrLoc[plyrID-1].row][plyrLoc[plyrID-1].col].chkPsg(South))
        mveOpt[South] = true;
    else
        mveOpt[South] = false;
    
    //Check West
    if(rmGrid[plyrLoc[plyrID-1].row][plyrLoc[plyrID-1].col].chkPsg(West))
        mveOpt[West] = true;
    else
        mveOpt[West] = false;
    
}

bool Board::exitFnd()
{
    return rmExst[exit.row][exit.col];
}