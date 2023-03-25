#include "BSTMenu.hpp"

BSTMenu::BSTMenu(){
    root=nullptr;
}

void BSTMenu::insert(string mnu){
    if(root==nullptr)
        root=newNode(mnu);
    else if(root->left==nullptr){
        root->left=newNode(mnu);
    }
    else if(root->right==nullptr){
        root->right=newNode(mnu);
    }
}

void BSTMenu::print(int indx){
    BSTNode *temp;
    if(indx==0) cout<<root->menu;
    else if(indx==1){
        temp=root->left;
        cout<<temp->menu;
    }
    else if(indx==2){
        temp=root->right;
        cout<<temp->menu;
    }
}

BSTNode* BSTMenu::newNode(string mnu){
    BSTNode* temp = new BSTNode;
    temp->menu=mnu;
    temp->left=nullptr;
    temp->right=nullptr;
    return temp;
}
