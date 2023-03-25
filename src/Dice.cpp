/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/file.cc to edit this template
 */

#include "Dice.hpp"

Dice::Dice(){
    size=0;
    string one,two,three,four,five,six;
    
    getline(fstream("res/Faces/One.txt"),one,'\0');
    getline(fstream("res/Faces/Two.txt"),two,'\0');
    getline(fstream("res/Faces/Three.txt"),three,'\0');
    getline(fstream("res/Faces/Four.txt"),four,'\0');
    getline(fstream("res/Faces/Five.txt"),five,'\0');
    getline(fstream("res/Faces/Six.txt"),six,'\0');
    
    picDie[Face::ONE]=one;
    picDie[Face::TWO]=two;
    picDie[Face::THREE]=three;
    picDie[Face::FOUR]=four;
    picDie[Face::FIVE]=five;
    picDie[Face::SIX]=six;
}

Dice::Dice(int s){
    size=s;
    string one,two,three,four,five,six;
    
    getline(fstream("res/Faces/One.txt"),one,'\0');
    getline(fstream("res/Faces/Two.txt"),two,'\0');
    getline(fstream("res/Faces/Three.txt"),three,'\0');
    getline(fstream("res/Faces/Four.txt"),four,'\0');
    getline(fstream("res/Faces/Five.txt"),five,'\0');
    getline(fstream("res/Faces/Six.txt"),six,'\0');
    
    picDie[Face::ONE]=one;
    picDie[Face::TWO]=two;
    picDie[Face::THREE]=three;
    picDie[Face::FOUR]=four;
    picDie[Face::FIVE]=five;
    picDie[Face::SIX]=six;
}

void Dice::setSize(int s){
    size=s;
    
}

void Dice::printDice(){
    DiceType itr = dice.begin();

    int counter=1;
    cout<<endl;
    for(itr;itr!=dice.end();itr++){
        cout<<"  Dice "<<counter++<<endl;
        cout<<picDie[*itr]<<endl;
    }
}

void Dice::rollDice(int *keep,int length){
    list<Face> temp;
   
    //Convert dice to integer array
    int *array=listToArray();
    
    //Compare the dice kept to the dice array
    int i=0,j=0;
    for(i;(i<size) && (j<length);i++){
        if(i==keep[j]){
            j++;
        }
        else if(i!=keep[j]){
            array[i]=rand()%6;
        }
    }
    
    arrayToList(array);
    
    sort();
    
    delete []array;
}

void Dice::rollDice(){
    dice.clear();
    Face val;
    int rnd;
    for(int i=0;i<size;i++){
        rnd=rand()%6;
        val=static_cast<Face>(rnd);
        dice.push_back(val);
    }
    sort();
}

int Dice::getDiceVal(Face val){
    DiceType itr = dice.begin();
    int score=0;
    switch(val){
        //Add all the ones in dice
        case Face::ONE:{
            for(itr;itr!=dice.end();itr++){
                if(*itr==Face::ONE){
                    score+=1;
                }
            }
            break; 
        }
        //Add all the twos in dice
        case Face::TWO:{
            for(itr;itr!=dice.end();itr++){
                if(*itr==Face::TWO){
                    score+=2;
                }
            }
            break;
        }
        //Add all the threes in dice
        case Face::THREE:{
            for(itr;itr!=dice.end();itr++){
                if(*itr==Face::THREE){
                    score+=3;
                }
            }
            break;
        }
        //Add all the fours in dice
        case Face::FOUR:{
            for(itr;itr!=dice.end();itr++){
                if(*itr==Face::FOUR){
                    score+=4;
                }
            }
            break;
        }
        //Add all the fives in dice
        case Face::FIVE:{
            for(itr;itr!=dice.end();itr++){
                if(*itr==Face::FIVE){
                    score+=5;
                }
            }
            break;
        } 
        case Face::SIX:{
            for(itr;itr!=dice.end();itr++){
                if(*itr==Face::SIX){
                    score+=6;
                }
            }
            break;
        }
        //Add all dice
        case Face::ALL: {
            for(itr;itr!=dice.end();itr++){
                //Count ones
                if(*itr==Face::ONE)         score+=1;
                else if(*itr==Face::TWO)    score+=2;
                else if(*itr==Face::THREE)  score+=3;
                else if(*itr==Face::FOUR)   score+=4;
                else if(*itr==Face::FIVE)   score+=5;
                else if(*itr==Face::SIX)    score+=6;
            }
            break;//add all dice
        }
    }
    return score;
}

bool Dice::is3Kind(){
    //At least 3 are the same face
    DiceType itr = dice.begin();
    Face face=*itr;                     //Set first die as face to match
    itr++;                              //Move to next die
    int count=1;                        //Count 1 die for the face
    for(itr;itr!=dice.end();itr++){
        if(*itr==face) {                //curr die = face
            count++;                    //increment number of match
            if(count>=3)return true;
        }
        else{
            face=*itr; count=1;         //Set curr die as face to match
        }  
    }
    if(count<3) return false;           //If the count < 3 then no 3 kind
    return true;
}

bool Dice::is4Kind(){
    DiceType itr = dice.begin();
    Face face=*itr;                 //Set first die as face to match
    itr++;                          //Move to next die
    int count=1;                    //Count 1 die for face
    for(itr;itr!=dice.end();itr++){
        if(*itr==face){             //curr die = face -> increment number of match
            count++;
            if(count>=4)return true;
        }      
        else{ face=*itr; count=1;}  //Set curr die as face to match
    }
    if(count<4) return false;       //If count < 4 then no 4 kind
    return true;
}

bool Dice::isFullHouse(){
    //Full House
    //3 of one die 2 of another
    DiceType itr = dice.begin();
    Face fFace = *itr;
    Face sFace;
    itr++;
    
    int frst=1;
    int scnd=1;
    for(itr;itr!=dice.end();itr++){
        if(*itr==fFace){
            frst++;
        }
        else{
            sFace=*itr;
            itr++;
            break;
        }
    }
    
    for(itr;itr!=dice.end();itr++){
        if(*itr==sFace){
            scnd++;
        }
    }
    
    if(frst==2 && scnd==3 || frst==3 && scnd==2) return true;
    
    return false;
}

bool Dice::isSStraight(){
    //Small Straight
    //4 Consecutive face values
    DiceType itr=dice.begin();
    //Find starting face value
    Face val = *itr;
    //Iterate to the next die
    itr++;
    //So we can increment through the enum face class
    int temp=(int)val;
    //Number of consecutive face values
    int consec=1;
    for(itr;itr!=dice.end();itr++){
        if((Face)(temp+1)==*itr){
            consec++;
            temp++;
            val=(Face)temp;
            if(consec==4)return true;
        }
        else if((Face)temp!=*itr){
            val=*itr;
            temp=(int)val;
            consec=1;
        }
    }
    if(consec<4)return false;
    
    return true;
}

bool Dice::isLStraight(){
    //large Straight
    //5 Consecutive face values
    DiceType itr=dice.begin();
    //Find starting face value
    Face val = *itr;
    //Iterate to the next die
    itr++;
    //So we can increment through the enum face class
    int temp=(int)val;
    //Number of consecutive face values
    for(itr;itr!=dice.end();itr++){
        if((Face)(temp+1)==*itr){
            temp++;
            val=(Face)temp;
        }
        else{
            return false;
        }
    }
    return true;
}

bool Dice::isYahtzee(){
    //All 5 die the same
    DiceType itr=dice.begin();
    Face face=*itr;
    for(itr;itr!=dice.end();itr++){
        if(*itr!=face)return false;
    }
    return true;
}

void Dice::merge(int *array, int beg, int mid, int end){
    const int array1 = mid - beg + 1;
    const int array2 = end - mid;
 
    int *lArray = new int[array1];
    int *rArray = new int[array2];

    for (int i = 0; i < array1; i++)
        lArray[i] = array[beg + i];
    for (int j = 0; j < array2; j++)
        rArray[j] = array[mid + 1 + j];
 
    int indxA1 = 0;
    int indxA2 = 0;
    int indx   = beg;

    while (indxA1 < array1 && indxA2 < array2) {
        if (lArray[indxA1] <= rArray[indxA2]) {
            array[indx] = lArray[indxA1];
            indxA1++;
        }
        else {
            array[indx] = rArray[indxA2];
            indxA2++;
        }
        indx++;
    }
    
    while (indxA1 < array1) {
        array[indx] = lArray[indxA1];
        indxA1++;
        indx++;
    }
    while (indxA2 < array2) {
        array[indx] = rArray[indxA2];
        indxA2++;
        indx++;
    }
    delete[] lArray;
    delete[] rArray;
}

void Dice::mergeSort(int *array,int beg,int end){
    if(beg>=end)return;
    int mid = beg + (end - beg)/2;
    mergeSort(array,beg,mid);
    mergeSort(array,mid+1,end);
    merge(array,beg,mid,end);
}

void Dice::sort(){
    //Convert list of die to array of int
    int *array=listToArray();
    //Sort the integer array
    mergeSort(array,0,size-1);
    //Convert integer array to list
    arrayToList(array);
    delete array;
}

void Dice::sort(int *array,int len){
    mergeSort(array,0,len);
}

int* Dice::listToArray(){
    int *array=new int[size];
    int indx=0;
    DiceType itr=dice.begin();
    for(itr;itr!=dice.end();itr++){
        array[indx++]=(int)*itr;
    }
    return array;
}

void Dice::arrayToList(int *array){
    int indx=0;
    DiceType itr = dice.begin();
    for(itr;itr!=dice.end();itr++){
        *itr=(Face)array[indx++];
    }
}

void Dice::debugDice(){
    dice.clear();
    int val;
    Face face;
    cout<<"Dice Debug:"<<endl;
    cout<<"Enter Desired Dice:";
    for(int i=0;i<size;i++){
        cin>>val;
        face=(Face)(val-1);
        dice.push_back(face);
    }
    printDice();
}