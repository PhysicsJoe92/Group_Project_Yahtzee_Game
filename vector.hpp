/* 
 * File:   vector.hpp
 * Author: Joseph Hernandez
 *
 * Created on March 23, 2023, 5:36 PM
 */

#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <iostream>
#include <cstdlib>
#include <new>

namespace SVec{
    template <class T>
    class vector{
        public:
            vector();
            ~vector();
            void push_back(T);
            void emplace_back(T);
            size_t size();
            T operator[](const int&);
        private:
            T* data;
            size_t length;
            
            void memErr();
    };
    //Vector implementation
    //Constructor
    template<class T>
    vector<T>::vector(){
        length=0;
    }

    template<class T>
    vector<T>::~vector(){
        free(data);
    }

    template<class T>
    void vector<T>::push_back(T val){
        
        if(length==0){
            //Set size
            length=1;
            //Create new obj
            try{
                data = (T*)malloc(length);
                //Put data into array;
                data[length-1]=val;
            }
            catch(std::bad_alloc){
                memErr();
            }

        }
        else{
            T* temp;
            try{
                // Create temporary 
                temp = (T*)malloc(length + 1);
                
            }catch(std::bad_alloc){
                memErr();
            }
            //Back UP DATA!
            for(int i=0;i<length;i++){
                *(temp + i) = *(data + i);
            }
            
            //Release the old data
            free(data);

            //Increase size by 1
            length+=1;
            
            //Allocate memory for new length
            try{
                data = (T*)malloc(length);
            }catch(std::bad_alloc){
                memErr();
            }
            
            //Restore the data
            for(int i=0;i<(length-1);i++){
                *(data + i) = *(temp + i);
            }

            //Add new element in last index
            data[length-1] = val;

            //Release memory for temp
            free(temp);
        }
    }

    template<class T>
    void vector<T>::emplace_back(T val){
        if(length==0){
            //Set size
            length=1;
            //Create new obj
            try{
                data = (T*)malloc(length);
                //Put data into array;
                data[length-1]=val;
            }
            catch(std::bad_alloc){
                memErr();
            }
        }
        else{
            length+=1;
            T* tmp;
            try{
                tmp = (T*)realloc(data,length*sizeof(T));
            }catch(std::bad_alloc){
                memErr();
            }
            tmp[length-1]=val;
        }
    }

    template<class T>
    size_t vector<T>::size(){
        return length;
    }

    template<class T>
    T vector<T>::operator [](const int& index){
        return data[index];
    }

    template<class T>
    void vector<T>::memErr(){
        std::cout<<"ERROR: Could not allocate memory"<<std::endl;
        exit(EXIT_FAILURE);
    }
}
#endif /* VECTOR_HPP */

