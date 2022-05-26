/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/main.cc to edit this template
 */

/* 
 * File:   main.cpp
 * Author: Josue Alvarez M
 *
 * Created on 24 de mayo de 2022, 17:18
 */

#include <iostream>
#include <complex>

#include "Imagen.h"
#include "Random.h"


using namespace std;

double distancia(double x1, double y1, double x2, double y2){
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}

/*
 * 
 */
int main(int argc, char** argv) {
    
    Imagen* im = new Imagen("cara.jpg");
    
    int dim = im->getAlto(); // dimencion (alto = ancho)
    
    //puntos
    float porcentaje = 0.05;
    int puntos = dim * dim * porcentaje;
    
     
    Random* r = new Random();
    
    unsigned char* p;
    int pX, pY;
    for (int i = 0; i < puntos; i++) {
        
        pX = r->getNum(0, dim);
        pY = r->getNum(0, dim);
        p = im->getPixel(pX, pY);
        
        if((p[0] == 0 && p[1] == 0 && p[2] == 0) || distancia(pX, pY, dim/2, dim/2) > dim/2){
            i--;
            continue;
        }

        p[0] = 0;
        p[1] = 0;
        p[2] = 0;
        
    }
    
    
    im->guardarJPG("caraSalida.jpg");
    
    im->cerrar();
            
    return 0;
}

