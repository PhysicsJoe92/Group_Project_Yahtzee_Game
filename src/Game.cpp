/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/file.cc to edit this template
 */
#include "Game.hpp"
#include "Menu.hpp"

Game::Game(){
    numP=1;
    dice.setSize(5);
}

void Game::start(){
    srand((unsigned int)time(0));
    
    int temp;
    string name;
    
    
    //Get the number of players
    cout<<setw(21)<<""<<"Enter the number of players: ";
    cin>>temp;
    while(temp<1 || temp>4){
        if(temp<1)cout<<setw(21)<<""<<"Needs at least 1 player."<<endl;
        else cout<<setw(21)<<""<<"Maximum number of 4 players."<<endl;
        cin>>temp;
    }
    
    numP=temp;
    string names[numP];
    cout<<setw(21)<<""<<"Enter player name: "<<endl;
    cin.ignore(1000,'\n');
    for(int i=0;i<numP;i++){
        //Get name of each player
        cout<<setw(21)<<"";
        getline(cin,name);
        //Put players into vector
        names[i]=name;
        cin.clear();
    }
    
    if(numP>1){
        cout<<setw(21)<<""<<"Randomizing player rotation"<<endl;
        for(int i=0;i<5;i++){
            for(int j=0;j<numP;j++){
                //Swap names
                int indx1=rand()%numP;
                int indx2=rand()%numP;
                while(indx2==indx1)indx2=rand()%numP;

                //Swap
                string tName=names[indx1];
                names[indx1]=names[indx2];
                names[indx2]=tName;

            }
        }
    }
    //Put players into queue
    for(int i=0;i<numP;i++){
        Player player(names[i]);
        players.push(player);
    }
}

void Game::play(){
    //Calculate Score Cards/Winners
    string winner;
    int highScore=0;    
    
    //Get the first player
    Player currPlayer = players.front();
    //Multiplayer
    if(numP>1){
        bool endGame=gameOver();
        while(!endGame){
            //Continue?
            pause();
            currPlayer.takeTurn(dice);
            if(!currPlayer.isPlayerDone())printCard(currPlayer);
            players.push(currPlayer);
            players.pop();
            endGame=gameOver();
        }
        
        currPlayer = players.front();
    
        currPlayer.setScore();
        currPlayer.saveCard();
        
        winner=currPlayer.getName();
        highScore=currPlayer.getScore();
        
        players.push(currPlayer);
        players.pop();

        for(int i=1;i<players.size();i++){
            currPlayer = players.front();
            currPlayer.setScore();
            currPlayer.saveCard();
            
            int score=currPlayer.getScore();
            if(score>highScore){
                winner=currPlayer.getName();
                highScore=score;
            }
            currPlayer.printCard();
            players.push(currPlayer);
            players.pop();
        }
        cout<<setw(21)<<""<<"Game winner: "<<winner<<endl;
        cout<<setw(21)<<""<<"Total Score: "<<highScore<<endl;
        
        
    }
    //Single Player
    else{
        while(!currPlayer.isPlayerDone()){
            currPlayer.takeTurn(dice);
            if(!currPlayer.isPlayerDone())printCard(currPlayer);
            pause();
        }
        currPlayer.setScore();
        currPlayer.saveCard();
        highScore=currPlayer.getScore();
        cout<<setw(21)<<""<<"Total Score: "<<highScore<<endl;
        currPlayer.printCard();
    }
}

void Game::printCard(Player currPlayer){
    cout<<setw(21)<<""<<currPlayer.getName()<<", "<<endl;
    cout<<setw(21)<<""<<"Would you like to view your score card?"<<endl;
    cout<<setw(21)<<""<<"Enter Yes/No: ";
    string ans;
    getline(cin,ans);
    ans = ScoreCard::format(ans);
    if(ans!="Yes" && ans!="No"){
        getline(cin,ans);
    }
    if(ans=="Yes"){
        currPlayer.printCard();
    }
}

void Game::pause(){
    char key;
    cout<<setw(21)<<""<<"Press ENTER to continue...   ";
    cin.get();
}

void Game::end(){
    menu.printExit();
}

bool Game::gameMenu(bool &debugGame){
    int dec;
    
    menu.printMainMenu();
    cout<<setw(32)<<"Selection: ";
    cin>>dec;
    if(dec==8675309){debugGame=true;return false;}
    //Check if decision is within range
    while(dec>3 || dec<1){
        cout<<setw(21)<<""<<"INVALID SELECTION:"<<endl;
        cout<<setw(21)<<""<<"Try Again: ";
        cin>>dec;
    }
    //Print Rules
    if(dec==2){
        menu.printRules();
        cout<<endl<<endl<<endl;
        return gameMenu(debugGame);
    }
    //Play the game
    else if(dec==1) return true;
    return false;
}

bool Game::playAgain(){
    cout<<setw(21)<<""<<"Would you like to play another game?(Yes/No)"<<endl;
    string ans;
    cout<<setw(21)<<"";
    getline(cin,ans);
    ans=ScoreCard::format(ans);
    if(ans=="Yes") return true;
    return false;
}

bool Game::gameOver(){
    Player player;
    bool gameOver;
    int count=0;
    if(numP>1){
        while(count<numP){
            player=players.front();
            //Check if player has finished scoring
            if(!player.isPlayerDone()){
                //Put front player in back of queue
                players.push(player);
                //Pop front player
                players.pop();
                gameOver=false;
            }
            else gameOver=true;
            count++;
        }
    }
    //Return if queue is empty or not
    return gameOver;
}

void Game::debugGame(){
    //Create a fake player
    Player player("Debug");
    players.push(player);
    numP=1;
    Player currPlayer=players.front();

    while(!currPlayer.isPlayerDone()){
        //Change player score card
        currPlayer.debugPlayer(dice);
    }
    currPlayer.setScore();
    int score=currPlayer.getScore();
    currPlayer.printCard();
    cout<<"currPlayer="<<currPlayer.getName()<<endl;
    cout<<"score="<<score<<endl;
    currPlayer.saveCard();
}