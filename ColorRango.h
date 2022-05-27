/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/file.h to edit this template
 */

/* 
 * File:   ColorRango.h
 * Author: Josue Alvarez M
 *
 * Created on 25 de mayo de 2022, 22:14
 */

#ifndef COLORRANGO_H
#define COLORRANGO_H

#include <stdlib.h>


class ColorRango{
private:
    unsigned char* min;
    unsigned char* max;
    
    unsigned char rango;
    
    int* colorProm;
    int cantidad;
    
public:
    ColorRango(unsigned char* c, unsigned char rango){
        this->rango = rango;
        
        this->min = new unsigned char[3];
        this->max = new unsigned char[3];
        
        this->min[0] = c[0];
        this->min[1] = c[1];
        this->min[2] = c[2];
        
        this->max[0] = c[0];
        this->max[1] = c[1];
        this->max[2] = c[2];
        
        this->colorProm = new int[3];
        this->colorProm[0] = c[0];
        this->colorProm[1] = c[1];
        this->colorProm[2] = c[2];
        this->cantidad = 1;
    }
    
    bool isRango(unsigned char* c){
        return this->min[0] - rango < c[0] && this->min[1] - rango < c[1] && this->min[2] - rango < c[2] 
            && this->min[0] + rango > c[0] && this->min[1] + rango > c[1] && this->min[2] + rango > c[2];
    }
    
    void addColor(unsigned char* c){
        if(c[0] < this->min[0])
            this->min[0] = c[0];
        else if(c[0] > this->max[0])
            this->max[0] = c[0];
        
        if(c[1] < this->min[1])
            this->min[1] = c[1];
        else if(c[1] > this->max[1])
            this->max[1] = c[1];
        
        if(c[2] < this->min[2])
            this->min[2] = c[2];
        else if(c[2] > this->max[2])
            this->max[2] = c[2];
        
        this->colorProm[0] += c[0];
        this->colorProm[1] += c[1];
        this->colorProm[2] += c[2];
        this->cantidad++;
    }
    
    unsigned char* getColorPromedio(){
        unsigned char* colorProm = new unsigned char[3];
        colorProm[0] = this->colorProm[0] / cantidad;
        colorProm[1] = this->colorProm[1] / cantidad;
        colorProm[2] = this->colorProm[2] / cantidad;
        
        return colorProm;
    }
};

#endif /* COLORRANGO_H */

