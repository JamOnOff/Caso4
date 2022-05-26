/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/file.h to edit this template
 */

/* 
 * File:   Random.h
 * Author: Josue Alvarez M
 *
 * Created on 25 de mayo de 2022, 16:20
 */

#ifndef RANDOM_H
#define RANDOM_H

#include <ctime>
#include <cstdlib>
#include <list>
#include <thread>
#include <functional>

#include <synchapi.h>

#include <iomanip>
#include <random>

using namespace std;

class Random{
private:
    random_device rd;
    mt19937 e2;

    list<double> numeros;
    
    int max;
    int cantidad = 0;
    
    thread h;
    
    void generar(){
        // números entre 0 y 1
        uniform_real_distribution<> dist(0, 1);
        while(true)
            if(this->cantidad < this->max){
                this->numeros.push_back(dist(e2));
                this->cantidad++;
            }
    }
    
    void semilla(){
        mt19937 e(rd());
        e2 = e; 
    }
    
public:
    Random(){
        this->max = 100;
        
        // Genera semilla
        semilla();
        
        h = thread(&Random::generar, this);
    }
    Random(int max){
        if(max > 0)
            this->max = max;
        else
            this->max = 100;
        
        // Genera semilla
        semilla();
        
        h = thread(&Random::generar, this);
    }
    
    double getNum(int min, int max){
        while(this->numeros.size() < 5){
        } // espera si no hay números
        
        this->cantidad--;
        float num = this->numeros.front();
        this->numeros.pop_front();
        
        return (num * float(max)) + float(min);
    }
    double getNum(int max){
        while(this->numeros.size() < 2){
        } // espera si no hay números
        
        this->cantidad--;
        float num = this->numeros.front();
        this->numeros.pop_front();
        
        return (num * float(max));
    }
};

#endif /* RANDOM_H */

