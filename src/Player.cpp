/*
 * File: Player.cpp
 * Author: Joseph Hernandez
 * Created on November 3, 2022, 9:50PM
 */

#include "Player.hpp"

Player::Player(){
    userName="";
}

Player::Player(string name){
    userName=name;
    //Open player save file, if no save file exist, create a new file
    fstream file;
    
    file.open("saves/" + userName + ".sav", ios::in | ios::out);

    if(!isEmpty(file)){card.replaceCard(userName);}
    
    file.close();
}

void Player::resetDKeep(int *dieKeep,int keep){
    for(int i=0;i<keep;i++){
        dieKeep[i]=-1;
    }
}

void Player::setName(string name){
    userName=name;
    //Open player save file, if no save file exist, create a new file
    fstream file;
    
    file.open("saves/" + userName + ".sav", ios::in | ios::out);

    if(isEmpty(file)){}//do nothing
    else card.replaceCard(userName);
    
    file.close();
}

void Player::throwDice(Dice& dice,int keep){
    if(keep==0) dice.rollDice();
    else{
        char hold=0;
        
        while(!holdDice(hold,keep));
        int* diceKept=holdCheck(hold,keep);
        
        cout<<setw(21)<<""<<"Dice Kept: ";
        for(int i=0;i<keep;i++){
            cout<<diceKept[i]+1<<" ";
        }
        cout<<endl;
        dice.rollDice(diceKept,keep);
        
        
        delete []diceKept;
    }
}

void Player::takeTurn(Dice& dice){
    int turns=0;
    int keep=0;
    cout<<"\n \n";
    cout<<setw(21)<<""<<userName<<"'s Turn:"<<endl;
    
    while(keep!=5 && turns<3){
        throwDice(dice,keep);
        turns++;
        dice.printDice();
        if(turns < 3)keep = keepDice();
    }
    
    selCat(dice);
    saveCard();
}

bool Player::holdDice(char &hold,int numHold){
    char *buffer;
    buffer=new char[numHold];
    hold=0;
    cout<<setw(21)<<""<<"Enter dice to keep: ";
    for(int i=0;i<numHold;i++){
        cin>>buffer[i];
    }
    buffer[numHold]='\0';
    
    // 000|_ _ _ _ _ last 5 bits represent dice to hold
    int size=strlen((char*)buffer);
    for(int i=0;i<numHold;i++){
        switch(buffer[i]){
            case '1':
                //Test if already marked
                {
                    char tmp = hold;
                    tmp&=1;
                    tmp^=1;
                    if(tmp==0){cout<<"Already chosen";return false;}
                    //Escape out of call, return false
                }
                //Continue
                buffer[i]=1;
                hold^=buffer[i];
                break;
            case '2':
                //Test if already marked
                {
                    char tmp = hold;
                    tmp&=2;
                    tmp^=2;
                    if(tmp==0){cout<<"Already chosen";return false;}
                    //Escape out of call, return false
                }
                buffer[i]=2;
                hold^=buffer[i];
                break;
            case '3':
                //Test if already marked
                {
                    char tmp = hold;
                    tmp&=4;
                    tmp^=4;
                    if(tmp==0){cout<<"Already chosen";return false;}
                    //Escape out of call, return false
                }
                buffer[i]=4;
                hold^=buffer[i];
                break;
            case '4':
                //Test if already marked
                {
                    char tmp = hold;
                    tmp&=8;
                    tmp^=8;
                    if(tmp==0){cout<<"Already chosen";return false;}
                    //Escape out of call, return false
                }
                buffer[i]=8;
                hold^=buffer[i];
                break;
            case '5':
                //Test if already marked
                {
                    char tmp = hold;
                    tmp&=16;
                    tmp^=16;
                    if(tmp==0){cout<<"Already chosen";return false;}
                    //Escape out of call, return false
                }
                buffer[i]=16;
                hold^=buffer[i];
                break;
            default:
                cout<<"Incorrect selection"<<endl;
                return false;
        }
    }
    delete []buffer;
    //Return true for valid entry//
    return true;
}

int* Player::holdCheck(char hold,int numHold){
    int *index=new int[numHold];
    int count=0;
    //Check what bits are flagged
    for(int i=0;i<5;i++){
        unsigned char test=hold;
        //Auto sorts index
        switch(i){
            case 0:
                test&=1;//Clear all bits except the one we need
                if(test==1)index[count++]=i;//Check if true, use index 0
                break;
            case 1:
                test&=2;
                if(test==2)index[count++]=i;//Check if true, use index 1
                break;
            case 2:
                test&=4;
                if(test==4)index[count++]=i;//Check if true, use index 2
                break;
            case 3:
                test&=8;
                if(test==8)index[count++]=i;//Check if true, use index 3
                break;
            case 4:
                test&=16;
                if(test==16)index[count++]=i;//Check if true, use index 4
                break;
        }
    }
    return index;
}

int Player::keepDice(){
    int keep;
    cout<<setw(21)<<""<<"Enter how may dice you would like to keep:"<<endl;
    cout<<setw(21)<<"";
    cin>>keep;
    if(keep < 0 || keep > 5)keep = keepDice();
    return keep;

}

void Player::selCat(Dice dice){
    string category;
    card.printCategories();
    cout<<endl;
    
    cout<<setw(21)<<""<<"Select Category: ";
    
    cin.ignore(1000,'\n');
    getline(cin,category);
    
    bool filled = card.setScoreCell(category,dice);
    
    while(!filled){
        cout<<setw(21)<<""<<"Select Category:";
        getline(cin,category);
        filled=card.setScoreCell(category,dice);
    }
}

void Player::printCard(){
    cout<<endl;
    cout<<setw(21)<<""<<userName<<": ";
    card.printScoreCard();
    cout<<endl<<endl;
}

void Player::saveCard(){
    card.saveCard(userName);
}

void Player::setScore(){
    score=card.getScore();
}

bool Player::isEmpty(fstream& file){
    return file.peek() == fstream::traits_type::eof();
}

bool Player::isPlayerDone(){
    bool done=card.isCardFull();
    if(done){card.saveCard(userName);}
    return done;
}

void Player::debugPlayer(Dice &dice){
    dice.debugDice();
    selCat(dice);
    card.debugCard();
    printCard();
}