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

double distancia(double x1, double y1, double x2, double y2){
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}

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
    
    void pintarAreaColorPromedio(Imagen* im, unsigned char* c){
        unsigned char* color;
         
        for (int i = this->puntoInicio[1]; i < this->puntoFin[1]; i++) {
           for (int j = this->puntoInicio[0]; j < this->puntoFin[0]; j++) {
               color = im->getPixel(j, i);

               color[0] = c[0];
               color[1] = c[1];
               color[2] = c[2];
           }
       }
    }
    void unir(Area* a){
        int* puntoInicio = a->puntoInicio;
        int* puntoFin = a->puntoFin;
        
        addPunto(puntoInicio);
        addPunto(puntoFin);
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
    
    bool isArea(Area* a){
        int* puntoInicio = a->puntoInicio;
        int* puntoFin = a->puntoFin;
        
        return isArea(puntoInicio) || isArea(puntoFin) || isArea(puntoInicio[0], puntoFin[1]) || isArea(puntoFin[0], puntoInicio[1])
            || a->isArea(this->puntoInicio) || a->isArea(this->puntoFin) || a->isArea(this->puntoInicio[0], this->puntoFin[1]) 
            || a->isArea(this->puntoFin[0], this->puntoInicio[1]) ;
    }
    
    bool isArea(int x, int y){
        int* punto = new int[2];
        punto[0] = x;
        punto[1] = y;
        
        bool ret = isArea(punto);
        
        delete[] punto;
        
        return ret;
    }
    
    bool muyGrande(int dim){
        return distancia(this->puntoInicio[0], this->puntoInicio[1], this->puntoFin[0], this->puntoFin[1]) > dim - this->rango;
    }
    
    void setRango(int rango) {
        this->rango = rango;
    }

    
    int getRango() const {
        return rango;
    }

    int* getPuntoFin(){
        return puntoFin;
    }

    int* getPuntoInicio(){
        return puntoInicio;
    }

};

#endif /* AREA_H */

