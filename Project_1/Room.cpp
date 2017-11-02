#include "Room.h"

#include <cstdlib>
#include <ctime>
#include <iostream>

using namespace std;

Room::Room()    //Constructor. Creates empty room with no passages
{
    //Allocate memory
    rmView = new char* [layers];
    for(int i=0; i<layers; i++)
    {
        rmView[i] = new char[rmWdth];
    }
    
    //Place rmView, no passages
    for(int i=0; i<layers; i++)
    {
        if(i==0 || i==4)
        {
            for(int j=0; j<rmWdth; j++)
            {
                rmView[i][j] = '-';
            }
        }
        if(i>0 && i<4)
        {
            rmView[i][0] = '|';
            rmView[i][8] = '|';
            for(int j=1; j<rmWdth-1; j++)
                rmView[i][j] = ' ';
        }
    }
    
    //No passages exist
    pssgs[North] = false;
    pssgs[East] = false;
    pssgs[South] = false;
    pssgs[West] = false;
}

Room::~Room()   //Destructor
{
    for(int i=0; i<layers; i++)
    {
        delete [] rmView[i];
    }
    delete [] rmView;
}

void Room::randPsg()
{
    unsigned int pssLoc;         //Position to place a passage in the room
    
    //Doors in layer 0 & 4 are rmWdth = 3,4,5
    //Doors in layer 2 are rmWdth = 0 or 8
    srand(time(0));
    pssLoc = static_cast<unsigned int>(rand())%4;
    switch(pssLoc)
    {
        case 0:
            rmView[0][3] = ' ';
            rmView[0][4] = ' ';
            rmView[0][5] = ' ';
            pssgs[North] = true;
            break;
        case 1:
            rmView[2][8] = ' ';
            pssgs[East] = true;
            break;
        case 2:
            rmView[4][3] = ' ';
            rmView[4][4] = ' ';
            rmView[4][5] = ' ';
            pssgs[South] = true;
            break;
        case 3:
            rmView[2][0] = ' ';
            pssgs[West] = true;
    }
}

void Room::mkePsg(crdnl pssg)
{
    switch(pssg)
    {
        case North:
            rmView[0][3] = ' ';
            rmView[0][4] = ' ';
            rmView[0][5] = ' ';
            pssgs[North] = true;
            break;
        case East:
            rmView[2][8] = ' ';
            pssgs[East] = true;
            break;
        case South:
            rmView[4][3] = ' ';
            rmView[4][4] = ' ';
            rmView[4][5] = ' ';
            pssgs[South] = true;
            break;
        case West:
            rmView[2][0] = ' ';
            pssgs[West] = true;
            break;
    }
}

bool Room::chkPsg(crdnl pssg)
{
    return pssgs[pssg];
}

void Room::dstryPsg(crdnl pssg)
{
    switch(pssg)
    {
        case North:
            rmView[0][3] = '-';
            rmView[0][4] = '-';
            rmView[0][5] = '-';
            pssgs[North] = false;
            break;
        case East:
            rmView[2][8] = '|';
            pssgs[East] = false;
            break;
        case South:
            rmView[4][3] = '-';
            rmView[4][4] = '-';
            rmView[4][5] = '-';
            pssgs[South] = false;
            break;
        case West:
            rmView[2][0] = '|';
            pssgs[West] = false;
            break;
    }
}

void Room::shwRm()
{
    for(int i=0;i<layers;i++)
        {
            for(int j=0; j<rmWdth; j++)
                cout << rmView[i][j];
            cout << endl;
        }
}

//TODO create shwLyr functions
void Room::shwLyr0()
{
    for(int i=0; i < rmWdth; i++)
        cout << rmView[0][i];
    cout << endl;
}

void Room::shwLyr1()
{
    for(int i=0; i < rmWdth; i++)
        cout << rmView[1][i];
    cout << endl;
}

void Room::shwLyr2()
{
    for(int i=0; i < rmWdth; i++)
        cout << rmView[2][i];
    cout << endl;
}

void Room::shwLyr3()
{
    for(int i=0; i < rmWdth; i++)
        cout << rmView[3][i];
    cout << endl;
}

void Room::shwLyr4()
{
    for(int i=0; i < rmWdth; i++)
        cout << rmView[4][i];
    cout << endl;
}

void Room::addTok(char pTok)
{
    if(crowd < MX_CRWD)
    {
        crowd++;
        rmView[3][crowd] = pTok;
    }
}
void Room::rmTok(char pTok)
{
    bool tokFnd = false;
    for(int i=1; i <= crowd && !tokFnd; i++)
    {
        if(rmView[3][i] == pTok)
        {
            tokFnd = true;
            rmView[3][i] = rmView[3][crowd];
            rmView[3][crowd] = ' ';
            crowd--;
        }
    }
}