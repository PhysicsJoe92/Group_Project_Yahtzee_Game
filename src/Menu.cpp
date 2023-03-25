/*
 * File: Menu.cpp
 * Author: Joseph Hernandez
 * Created on November 4, 2022, 10:48 PM
 * 
 */

#include "Menu.hpp"

Menu::Menu(){
    string mainMenu, rules, ending;
    getline(fstream("res/Menu/MainMenu.txt"),mainMenu,'\0');
    menuSys.insert(mainMenu);
    getline(fstream("res/Menu/Rules.txt"),rules,'\0');
    menuSys.insert(rules);
    getline(fstream("res/Menu/End.txt"),ending,'\0');
    menuSys.insert(ending);
}

void Menu::printMainMenu(){
    menuSys.print(0);
    cout<<endl;
}

void Menu::printRules(){
    menuSys.print(1);
    cout<<endl;
}

void Menu::printExit(){
    cout<<endl<<endl;
    menuSys.print(2);
    cout<<endl;
}