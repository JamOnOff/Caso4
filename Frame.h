/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/file.h to edit this template
 */

/* 
 * File:   Frame.h
 * Author: Josue Alvarez M
 *
 * Created on 28 de mayo de 2022, 09:17
 */

#ifndef FRAME_H
#define FRAME_H

#include <thread>

#include "Random.h"
#include "geneticbase.h"
#include "Imagen.h"

class Frame{
private:
    Imagen* im;
    
    int frameNum;
    
    vector<individual*>* population;
    Random* random;
    
    
public:
    Frame(vector<individual*>* population, Random* random, int dim){
        this->im = new Imagen("frame1.jpg", dim, dim, 3);
        
        this->population = population;
        this->random = random;
        
        this->frameNum = 1;
    }
    
    
    void mover(){
        int tam = this->population->size();
        individual* punto;
        
        for (int i = 0; i < tam; i ++) {
            punto = this->population->at(i);
            
            punto->mover(this->random, this->im->getAlto());
        }
    }
    
    void guardarFrame(){
        individual* punto;
        
        this->im->limpiar(255);
        
        int tam = this->population->size();
        for (int i = 0; i < tam; i++) {
            punto = this->population->at(i);
            
            punto->pintar(this->im, this->im->getAlto());
        }
        
        this->im->guardarJPG("frame" + to_string(frameNum) + ".jpg");
        //this->frameNum++;
    }
};

#endif /* FRAME_H */

