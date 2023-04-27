
#ifndef GAME_H
#define GAME_H
#include <thread>
#include <bitset>

#include "Player.hpp"
#include "Dice.hpp"
#include "Menu.hpp"
#include "Scanner.hpp"
#include "SHA.hpp"

enum Privilege{Admin,Standard};

class Game{
    public:
        Game();
        bool gameMenu(bool&);
        int loginMenu();
        bool playAgain();
        void start();                   //Start the game, init players and dice
        void play();                    //Game loop/logic
        void printCard(Player);         //Print player card
        void pause();                   //Pause for user input
        void end();                  //Get final scores and display winner
        void debugGame();
    private:
        int numP;
        Dice dice;
        Menu menu;
        vector<Player> players;
        
        //Check if each player is done
        bool gameOver();
        
        //Log-in function
        void addPlayer();
        void createPlayer();
        void checkFile();
        void createFile();
        unsigned int setID();
        unsigned int getID(fstream&);
        bool usernameCheck(fstream&,char*);
        bool validPassword(fstream&,char*);
        bool passwordFormat(char*);
        Privilege getPrivilege(fstream&);
        void playerRecords(char * , int );
};

#endif /* GAME_H */

