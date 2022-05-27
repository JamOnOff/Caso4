/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/file.h to edit this template
 */

/* 
 * File:   Grupo.h
 * Author: Josue Alvarez M
 *
 * Created on 26 de mayo de 2022, 17:30
 */

#ifndef GRUPO_H
#define GRUPO_H

#include <list>

#include "ColorRango.h"
#include "Area.h"
#include "Imagen.h"

class Grupo{
private:
    ColorRango* colorRango;
    Area* area;
    
    list<int*> puntos;
    int cantidad;
    
public:
    Grupo(int* punto, unsigned char* color, unsigned char rangoColor, int rango, int dim){
        this->colorRango = new ColorRango(color, rangoColor);
        this->area = new Area(punto, rango, dim);
        
        this->puntos.push_back(punto);
        this->cantidad = 1;
    }
    Grupo(int x, int y, unsigned char* color, unsigned char rangoColor, int rango, int dim){
        this->colorRango = new ColorRango(color, rangoColor);
        this->area = new Area(x, y, rango, dim);
        
        int* punto = new int[2];
        punto[0] = x;
        punto[1] = y;
        
        this->puntos.push_back(punto);
        this->cantidad = 1;
    }
    
    void pintar(Imagen* im){
        int* punto;
        unsigned char* colorProm = this->colorRango->getColorPromedio();
        
        unsigned char* color;
        
        list<int*>::iterator itFin = this->puntos.end();
        for (list<int*>::iterator it = this->puntos.begin(); it != itFin; ++it) {
            punto = *it;
            
            color = im->getPixel(punto[0], punto[1]);
            color[0] = colorProm[0];
            color[1] = colorProm[1];
            color[2] = colorProm[2];
        }
    }
    void pintarArea(Imagen* im){
        this->area->pintarArea(im);
    }
    
    bool isCercano(int x, int y, unsigned char* color){
        return this->colorRango->isRango(color) && this->area->isArea(x, y);
    }
    bool isCercano(int* punto, unsigned char* color){
        return this->colorRango->isRango(color) && this->area->isArea(punto);
    }
    
    
    void addPunto(int x, int y, unsigned char* color){
        this->colorRango->addColor(color);
        this->area->addPunto(x, y);
        
        int* punto = new int[2];
        punto[0] = x;
        punto[1] = y;
        
        this->puntos.push_back(punto);
        this->cantidad++;
    }
    void addPunto(int* punto, unsigned char* color){
        this->colorRango->addColor(color);
        this->area->addPunto(punto);
        
        this->puntos.push_back(punto);
        this->cantidad++;
    }
    
    int getCantidad() const {
        return cantidad;
    }
};

#endif /* GRUPO_H */

