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

#include "Imagen.h"


using namespace std;

void combinar(unsigned char* p1, unsigned char* p2, int* promR, int* promG, int* promB, int* cant, int rango){
    if(abs(*p1 - *p2) < rango && abs(p1[1] - p2[1]) < rango && abs(p1[2] - p2[2]) < rango){
        *promR = (*promR) + int(p2[0]);
        *promG = (*promG) + int(p2[1]);
        *promB = (*promB) + int(p2[2]);
        *cant = (*cant) + 1;
    }
}

/*
 * 
 */
int main(int argc, char** argv) {
    
    Imagen* im = new Imagen("cara.jpg");
    
    
    
    im->guardarJPG("caraSalida.jpg");
    
    im->cerrar();
            
    return 0;
}

