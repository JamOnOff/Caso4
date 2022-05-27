/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/file.h to edit this template
 */

/* 
 * File:   Area.h
 * Author: Josue Alvarez M
 *
 * Created on 26 de mayo de 2022, 16:37
 */

#ifndef AREA_H
#define AREA_H

#include <stdlib.h>

#include "Imagen.h"

class Area{
private:
    int* puntoInicio;
    int* puntoFin;
    
    int rango;
    
    int dim;
    
    void definirArea(int x, int y){
        this->puntoInicio = new int[2];
        this->puntoInicio[0] = x - this->rango;
        this->puntoInicio[1] = y - this->rango;
        
        this->puntoFin = new int[2];
        this->puntoFin[0] = x + this->rango;
        this->puntoFin[1] = y + this->rango;
        
        if(this->puntoInicio[0] < 0)
            this->puntoInicio[0] = 0;
        if(this->puntoInicio[1] < 0)
            this->puntoInicio[1] = 0;
        
        if(this->puntoFin[0] > this->dim)
            this->puntoFin[0] = this->dim;
        if(this->puntoFin[1] > this->dim)
            this->puntoFin[1] = this->dim;
    }
    void definirArea(int* punto){
        definirArea(punto[0], punto[1]);
    }
public:
    Area(int* punto, int rango, int dim){
        this->dim = dim;
        
        definirArea(punto);
        this->rango = rango;
    }
    Area(int x, int y, int rango, int dim){
        this->dim = dim;
        
        definirArea(x, y);
        this->rango = rango;
    }
    
    void pintarArea(Imagen* im){
        unsigned char* color;
        
        for (int i = this->puntoInicio[0]; i < this->puntoFin[0]; i++) {
            color = im->getPixel(i, this->puntoInicio[1]);
            
            color[0] = 255;
            color[1] = 0;
            color[2] = 0;
            
            color = im->getPixel(i, this->puntoFin[1]);
            
            color[0] = 255;
            color[1] = 0;
            color[2] = 0;
        }
        
        for (int i = this->puntoInicio[1]; i < this->puntoFin[1]; i++) {
            color = im->getPixel(this->puntoInicio[0], i);
            
            color[0] = 255;
            color[1] = 0;
            color[2] = 0;
            
            color = im->getPixel(this->puntoFin[0], i);
            
            color[0] = 255;
            color[1] = 0;
            color[2] = 0;
        }
        
         
    }
    
    void addPunto(int x, int y){
        if(x < this->puntoInicio[0])
            this->puntoInicio[0] = x;
        else if(x > this->puntoFin[0])
            this->puntoFin[0] = x;
        
        if(y < this->puntoInicio[1])
            this->puntoInicio[1] = y;
        else if(y > this->puntoFin[1])
            this->puntoFin[1] = y;
    }
    void addPunto(int* punto){
        addPunto(punto[0], punto[1]);
    }
    
    bool isArea(int* punto){
        // está dentro del area
        return (this->puntoInicio[0] - this->rango < punto[0] && punto[0] < this->puntoFin[0] + this->rango
             && this->puntoInicio[1] - this->rango < punto[1] && punto[1] < this->puntoFin[1] + this->rango);
           
    }
    
    bool isArea(int x, int y){
        int* punto = new int[2];
        punto[0] = x;
        punto[1] = y;
        
        bool ret = isArea(punto);
        
        delete[] punto;
        
        return ret;
    }
    
    int* getPuntoFin(){
        return puntoFin;
    }

    int* getPuntoInicio(){
        return puntoInicio;
    }

};

#endif /* AREA_H */

