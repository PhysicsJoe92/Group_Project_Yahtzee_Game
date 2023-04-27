/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/class.h to edit this template
 */

/* 
 * File:   AdminPlayer.hpp
 * Author: aawri
 *
 * Created on April 27, 2023, 1:18 AM
 */

#ifndef ADMINPLAYER_HPP
#define ADMINPLAYER_HPP
#include <map>
#include <string>
#include <iostream>
#include <fstream>
class AdminPlayer {
public:
    AdminPlayer();
    virtual ~AdminPlayer();
  void readDataIntoMap();
    void showUsers();
    
private:
    std::map<int, std::string> users;
};

#endif /* ADMINPLAYER_HPP */

