/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/file.h to edit this template
 */

/* 
 * File:   BSTMenu.hpp
 * Author: Joseph Hernandez
 *
 * Created on December 11, 2022, 2:38 PM
 */

#ifndef BSTMENU_HPP
#define BSTMENU_HPP

#include "BSTNode.hpp"

#include <iostream>

using namespace std;

class BSTMenu{
public:
    BSTMenu();
    
    BSTNode* newNode(string);
    
    void insert(string);
    void print(int);
private:
    BSTNode *root;
};

#endif /* BSTMENU_HPP */

