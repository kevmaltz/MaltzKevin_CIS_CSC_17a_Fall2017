/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/****************************************************************************** 
 * File:   main.cpp
 * Author: Kevin Maltz
 * Created on October 30, 2017, 7:41 PM
 * Purpose: 
 ******************************************************************************/

#include <iostream>
#include <vector>
#include <string>

using namespace std;
#include "Cardinal.h"
#include "Room.h"
#include "Board.h"
#include "Player.h"

void dispMves(const bool[]);
crdnl ctod(char);
void vldChar(char &mve);

int main() 
{
    const char PATHFINDER = 'P';
    const char LONE_SURVIVOR = 'L';
    
    int nPlyrs;             //Number of players
    vector<Player> plyrs;   //Vector to hold Player objects
    string name;            //Temp storage for a player name
    char tokens[7] = {'1','2','3','4','5','6','7'}; //Array of tokens to be used
    bool mveOpts[4] = {false};  //North=0,...,West=3. True if movement available
    bool gmDne = false;     //Is the game done?
    char mve;               //Holds movement command from player
    int nAlive;             //Number of players alive. Start = nPlyrs
    int winPId = 0;         //Player ID of winner
    char winCond;           //Stores 1 letter code for which win condition met
    
    //Output Game Title
    cout << "  ____    _   _   _   _    ____   _____    ___    _   _    "
            "     ____   ____       _     __        __  _     " << endl;
    cout << " |  _ \\  | | | | | \\ | |  / ___| | ____|  / _ \\  | \\ | |   "
            "    / ___| |  _ \\     / \\    \\ \\      / / | |    " << endl;
    cout << " | | | | | | | | |  \\| | | |  _  |  _|   | | | | |  \\| |   "
            "   | |     | |_) |   / _ \\    \\ \\ /\\ / /  | |    " << endl;
    cout << " | |_| | | |_| | | |\\  | | |_| | | |___  | |_| | | |\\  |   "
            "   | |___  |  _ <   / ___ \\    \\ V  V /   | |___ " << endl;
    cout << " |____/   \\___/  |_| \\_|  \\____| |_____|  \\___/  |_| \\_|   "
            "    \\____| |_| \\_\\ /_/   \\_\\    \\_/\\_/    |_____|" << endl;
    cout << endl << endl;
    
    //Option to output detailed game instructions
    //TODO Make function with detailed game instructions
    
    //Get number of players
    cout << "Enter number of players(2 min, 7 max): ";
    cin >> nPlyrs;
    while(nPlyrs > 7 || nPlyrs < 2)
    {
        cout << "Invalid number of players(2 min, 7 max), Re-enter: ";
        cin >> nPlyrs;
    }
    
    //Set number of living players
    nAlive = nPlyrs;
    
    //Setup the game
    Board board(nPlyrs);
    
    cin.ignore(1000,'\n');
    for(int plyrID=1; plyrID <= nPlyrs; plyrID++)
    {
        cout << "Enter player " << plyrID << "'s name: ";
        getline(cin,name);
        plyrs.push_back(Player(name, tokens[plyrID-1], plyrID));
        board.entrBrd(tokens[plyrID-1]);
    }
    board.shwBrd();
    
    //Start game. Loop till game won.
    while(!gmDne)
    {
        //Loops through turn of every player
        for(int pTrn=1; pTrn <= nPlyrs && !gmDne; pTrn++)
        {
            //If player is alive, take their turn. If not, skip them.
            if(plyrs[pTrn-1].isAlive())
            {
                cout << plyrs[pTrn-1].getName() << "'s turn.\n";

                //Show movement options
                board.mveOpts(pTrn, mveOpts);
                dispMves(mveOpts);

                //Get player movement
                cout << "Enter movement: ";
                cin >> mve;
                mve = toupper(mve);
                vldChar(mve);

                //If moved allowed, commit. If not, re-enter and try again.
                while(!board.mve2Rm(ctod(mve), pTrn, plyrs[pTrn-1].getTkn()))
                {
                    cout << "Move not allowed. Enter movement: ";
                    cin >> mve;
                    mve = toupper(mve);
                    vldChar(mve);
                }
                
                //Show board updated with character movement
                board.shwBrd();

                //TODO Implement combat/death mechanics.
                //If player is dead, decrease living counter.
                if(!plyrs[pTrn-1].isAlive())
                    nAlive--; 
                
                //Check win conditions. Pathfinder or Lone Survivor
                if(board.exitFnd())
                {
                    gmDne = true;
                    winPId = pTrn;
                    winCond = PATHFINDER;
                }
                if(nAlive == 1)
                {
                    gmDne = true;
                    for(int p=1; p <= nPlyrs; p++)
                    {
                        if(plyrs[p-1].isAlive())
                            winPId = p;
                    }
                    winCond = LONE_SURVIVOR;
                }
                
            }                       
        }
        
    }
    
    cout << "Congratulations " << plyrs[winPId-1].getName() << "!\n";
    if(winCond == PATHFINDER)
    {
        cout << "Mind over Matter, only the truly cunning escape the dungeon. "
             << "Enjoy your freedom!";
    }
    if(winCond == LONE_SURVIVOR)
    {
        cout << "You challenged the horrors of the dungeon depths and "
             << "triumphed! Claim your riches!";
    }

    return 0;
}

void dispMves(const bool opnMves[])
{
    cout << "Can move ";
    if(opnMves[North])
        cout << "(N)orth ";
    if(opnMves[East])
        cout << "(E)ast ";
    if(opnMves[South])
        cout << "(S)outh ";
    if(opnMves[West])
        cout << "(W)est ";
        
}

crdnl ctod(char c)
{
    crdnl d;
    if(c=='N')
        d = North;
    else if(c=='E')
        d = East;
    else if(c=='S')
        d = South;
    else if(c=='W')
        d = West;
}
void vldChar(char &mve)
{
    while(mve != 'N' && mve != 'E' && mve != 'S' && mve != 'W')
            {
                cout << "Unrecognized movement. Only N, E, S, W are valid.\n";
                cout << "Enter movement: ";
                cin >> mve;
                mve = toupper(mve);
            }
}