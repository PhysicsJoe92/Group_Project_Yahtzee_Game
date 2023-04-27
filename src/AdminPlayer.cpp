/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/class.cc to edit this template
 */

/* 
 * File:   AdminPlayer.cpp
 * Author: aawri
 * 
 * Created on April 27, 2023, 1:18 AM
 */

#include "AdminPlayer.hpp"

AdminPlayer::AdminPlayer() {
     readDataIntoMap();
}

AdminPlayer::~AdminPlayer() {
}

void AdminPlayer::readDataIntoMap()
{
     std::ifstream infile("userInfo.dat", std::ios::in | std::ios::binary);
    if (!infile) {
        std::cout << "Error opening file!" << std::endl;
        return;
    }
    infile.seekg(0, std::ios::end);
    std::streampos end_pos = infile.tellg();
    infile.seekg(0, std::ios::beg);
    while (true) {
        std::streampos cur_pos = infile.tellg();
        if (end_pos == cur_pos) {
            break; 
        }
        int size = 0;
        int id = 0;
        infile.read(reinterpret_cast<char*>(&size), sizeof(int));
        char* buffer = new char[size];
        infile.read(buffer, size);
        infile.read(reinterpret_cast<char*>(&id), sizeof(int));
        users.emplace(id, buffer);
        delete[] buffer;
    }

    infile.close();
}

void AdminPlayer::showUsers(){
    std::map<int,std::string>::iterator it;
    for(it = users.begin(); it != users.end(); it++){
        std::cout << "ID: " << it->first << " Username: " << it->second << std::endl;
    }
}