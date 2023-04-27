/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/class.cc to edit this template
 */

/* 
 * File:   AdminPlayer.cpp
 * Author: aawri
 * Edited by: Joseph Hernandez
 * 
 * Created on April 27, 2023, 1:18 AM
 * Edited on April 27, 2023, 12:49PM
 */

#include "AdminPlayer.hpp"

AdminPlayer::AdminPlayer() {
     readDataIntoMap();
}
void AdminPlayer::adminSession(Menu& menu){
    Scanner sc;
    //Start admin loop
    int choice;
    
    do{
        menu.printAdminMenu();
        choice=sc.nextInt();
        switch(choice){
            case 1:showUsers();break;//View Users
            case 2:break;//Remove User
        }
        
    }while(choice!=3);
}
void AdminPlayer::readDataIntoMap(){
    fstream file("home/user_info.dat", std::ios::in | std::ios::binary);
    if (!file) {
        std::cout << "Error opening file!" << std::endl;
        return;
    }
    
    long cursor=0L;
    file.seekg(0, std::ios::end);
    long end_pos = file.tellg();
    file.seekg(0, std::ios::beg);
    while(cursor<end_pos){
        UserInfo info;
        file.seekg(cursor,ios::beg);
        file.read(reinterpret_cast<char*>(&info.id),sizeof(unsigned int));
        file.read(reinterpret_cast<char*>(&info.size),sizeof(int));
        info.name=new char[info.size];
        file.read(info.name,sizeof(char)*info.size);
        cursor+=(sizeof(int)+sizeof(int)+info.size);
        //Map users
        users[info.id]=info.name;
    }
    file.close();
}

void AdminPlayer::showUsers(){
    std::map<unsigned int,std::string>::iterator it;
    cout<<setw(21)<<""<<"User ID:";
    cout<<setw(5)<<""<<"User Name: "<<endl;
    
    for(it = users.begin(); it != users.end(); it++){
        cout<<setw(28)<<""<< it->first << setw(5)<<""<<it->second << std::endl;
    }
}

void AdminPlayer::removeUser(unsigned int id){
    //Remove user from passwd.bin
    fstream file,tmp;
    string fileName="etc/passwd.bin",
           tmpName="etc/temp.bin";
    file.open(fileName,ios::in|ios::binary);
    tmp.open(tmpName,ios::out|ios::binary);
    long cursor=0L;
    file.seekg(0,ios::end);
    long size=file.tellg();
    while(cursor<size){
        LoginInfo info;
        file.read(reinterpret_cast<char*>(&info),sizeof(LoginInfo));
        if(info.id!=id){
            //Only write to tmp file if not id
            tmp.write(reinterpret_cast<char*>(&info),sizeof(LoginInfo));
        }
        cursor+=sizeof(LoginInfo);
    }
    file.close();
    tmp.close();
    
    //Remove old file
    remove(fileName.c_str());
    //Rename tmp file
    rename(tmpName.c_str(),fileName.c_str());
    
    //Remove user info from userInfo.dat
    fileName="home/user_info.dat";
    tmpName="home/tmp.bin";
    file.open(fileName,ios::in|ios::binary);
    tmp.open(tmpName,ios::out|ios::binary);
    cursor=0L;
    size=file.tellg();
    while(cursor<size){
        UserInfo info;
        file.seekg(cursor,ios::beg);
        file.read(reinterpret_cast<char*>(&info.id),sizeof(unsigned int));
        file.read(reinterpret_cast<char*>(&info.size),sizeof(int));
        file.read(info.name,info.size);
        if(id!=info.id){
            tmp.write(reinterpret_cast<char*>(&info),sizeof(info));
        }
        cursor+=sizeof(info);
    }

    //Remove old file
    remove(fileName.c_str());
    //Rename tmp file
    rename(tmpName.c_str(),fileName.c_str());
    
    //Delete user's scorecard
    string userCard = "saves/" + users[id] + "_" + to_string(id) + ".sav";
    remove(userCard.c_str());
    
    //Remove from map
    users.erase(id);
    
}