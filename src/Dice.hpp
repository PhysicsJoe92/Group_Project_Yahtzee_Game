/* 
 * File:   Dice.h
 * Author: Joseph Hernandez
 *
 * Created on November 1, 2022, 5:24 PM
 */

#ifndef DICE_H
#define DICE_H

#include <iostream>
#include <iomanip>
#include <list>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <sstream>
#include <map>
#include "Enums.hpp"

using namespace std;


class Dice{
    using DiceType = list<Face>::iterator;
    public:
        Dice();                     //Default constructor
        Dice(int);                  //Constructor with specified number of die
        void setSize(int);          //Set the number of dice
        void printDice();           //Print the dice
        void roll();                //Roll the dice
        void rollDice(int*,int);   //Roll non kept dice

        
        int getDiceVal(Face);       //Get value of dice (with selected face) 
        
        bool is3Kind();             //Check if 3 of a kind
        bool is4Kind();             //Check if 4 of a kind
        bool isFullHouse();         //Check if full house
        bool isSStraight();         //Check if small straight
        bool isLStraight();         //Check if large straight
        bool isYahtzee();           //Check if Yahtzee
        
        void mergeSort(int*,int,int);
        void merge(int*,int,int,int);
        
        void sort();
        void sort(int*,int);
        
        int* listToArray();
        void arrayToList(int*);
        
        void debugDice();               //Developer Debug
    private:
        list<Face> dice;            //List of die
        map<Face,string> picDie;    //ACSII art for each die
        int size;                   //Number of dice
};

#endif /* DICE_H */

