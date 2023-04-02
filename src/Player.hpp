/* 
 * File:   Player.h
 * Author: Joseph Hernandez
 * Created on November 3, 2022, 9:48 PM
 */

#ifndef PLAYER_H
#define PLAYER_H

#include <algorithm>
#include <set>
#include "ScoreCard.hpp"

class Player{
    public:
        Player();
        Player(string);
        void resetDKeep(int*,int);
        void setName(string);
        void selCat(Dice);
        void printCard();
        void throwDice(Dice&,int);
        void takeTurn(Dice&);
        void saveCard();
        void setScore();
        
        bool isEmpty(fstream&);
        bool isPlayerDone();
        
        inline int getScore(){return score;}
        inline string getName(){return userName;}
        
        void debugPlayer(Dice&);
    private:
        int score=0;
        int numWins=0;
        string userName;
        ScoreCard card;
};

#endif /* PLAYER_H */

