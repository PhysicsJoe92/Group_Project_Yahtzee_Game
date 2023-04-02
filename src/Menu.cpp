/*
 * File: Menu.cpp
 * Author: Joseph Hernandez
 * Created on November 4, 2022, 10:48 PM
 * 
 */

#include "Menu.hpp"

Menu::Menu(){
    getline(fstream("res/Menu/MainMenu.txt"), menuSys[0], '\0');
    getline(fstream("res/Menu/Rules.txt"), menuSys[1], '\0');
    getline(fstream("res/Menu/End.txt"), menuSys[2], '\0');
}

void Menu::printMainMenu(){
    cout << menuSys[0] << endl;
}

void Menu::printRules(){
    cout << endl << menuSys[1] << endl;
}

void Menu::printExit(){
    cout << endl << menuSys[2] << endl;
}
