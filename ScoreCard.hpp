
/* 
 * File:   ScoreCard.h
 * Author: Joseph Hernandez
 *
 * Created on November 3, 2022, 12:42 AM
 */

#ifndef SCORECARD_H
#define SCORECARD_H

#include <string>
#include <stack>
#include <functional>
#include <fstream>
#include "Dice.hpp"


class ScoreCard{
    public:
        ScoreCard();//Default Constructor
        void printScoreCard();
        void printCategories();
        void loadCard(string);
        void saveCard(string);
        void replaceCard(string);
        int getScore();
        
        bool setScoreCell(string,Dice);
        bool isCardFull();
        
        static string format(string);
        
        inline int getCurrGame(){return currGame;}
        
        void debugCard();
        
    private:
        int currGame = 0;
        static const int numGames = 5;
        static const int upRows   = 9;
        static const int lwRows   = 11;
        static const int bSize    = 13;
        
        //Bit vector to hold if section is filled
        bool bit_vector[bSize];
        //Stack to hold YAHTZEE BONUS
        stack<int> bonus;
        // container to hold upper section values (up to 5 games)
        int upperSec[numGames][upRows];
        // container to hold lower section values (up to 5 games)
        int lowerSec[numGames][lwRows];
        // container to hold upper section names
        string upperName[upRows];
        // container to hold lower section names
        string lowerName[lwRows];
        //Hash Function
        unsigned int hashFunction(string&);
        
};

#endif /* SCORECARD_H */

