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
#include "Grupo.h"


using namespace std;

double distancia(double x1, double y1, double x2, double y2){
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}

/*
 * 
 */
int main(int argc, char** argv) {
    Imagen* im = new Imagen("cara1.jpg");
    int dim = im->getAlto(); // dimencion (alto = ancho)
    
    Random* random = new Random();
    
    float porcentaje = 0.05;
    
    // Genera los puntos del circulo a seleccionar
    int cantPuntosCir = M_PI * (dim/2) * (dim/2);
    
    auto puntos = new int[cantPuntosCir][2];
    int pos = 0;
    
    for (int i = 0; i < dim; i++)
        for (int j = 0; j < dim; j++)
            if(distancia(j, i, dim/2, dim/2) < dim/2){
                puntos[pos][0] = j;
                puntos[pos][1] = i;
                pos++;
            }
    

    int posFin;
    for(int i = cantPuntosCir - 1; i >= 0; i--){
        if(puntos[i][0] != 0 || puntos[i][1] != 0){
            posFin = i;
            break;
        }
    }
    
    
    // posFin (ultima posición del array de puntos a seleccionar)
    // pos (posición del array seleccionada)
    
    unsigned char* color;
    int x;
    int y;
    
    list<Grupo*> grupos;
    unsigned char rangoColor = 5;
    int rango = 20;
    
    
    
    int cantSelec = dim * dim * porcentaje;
    for (int i = 0; i < cantSelec; i++) {
        pos = random->getNum(0, posFin+1);
        
        x = puntos[pos][0];
        y = puntos[pos][1];
        
        color = im->getPixel(x, y);
        
        
        Grupo* g;
        bool agregar = true;
        list<Grupo*>::iterator itFin = grupos.end();
        for (list<Grupo*>::iterator it = grupos.begin(); it != itFin; ++it) {
            g = *it;
            if(g->isCercano(x, y, color)){
                g->addPunto(x, y, color);
                agregar = false;
                break;
            }
        }
        
        if(agregar){
            g = new Grupo(x, y, color, rangoColor, rango, dim);
            grupos.push_back(g);
        }
        
        
        //Pasar el punto final a la posicion del seleccionado
        puntos[pos][0] = puntos[posFin][0];
        puntos[pos][1] = puntos[posFin][1];
        posFin--;
    }
    cout << grupos.size() << endl;
    Grupo* g;
    
    list<Grupo*>::iterator itFin = grupos.end();
    
    for (list<Grupo*>::iterator it = grupos.begin(); it != itFin; ++it) {
        g = *it;

        if(g->getCantidad() > dim*0.2){
            
            it = grupos.erase(it);
            --it;
        }
    }
    
    Grupo* gSig;
    itFin = grupos.end();
    list<Grupo*>::iterator itFin2 = grupos.end();
    --itFin2;
    for (list<Grupo*>::iterator it = grupos.begin(); it != itFin2; ++it) {
        g = *it;
        
        g->getColorRango()->setRango(rangoColor*1.25);
        g->getArea()->setRango(rango*2.5);
        
        for (list<Grupo*>::iterator itSig = it; itSig != itFin; ++itSig) {
            if(itSig == it)
                continue;
            
            gSig = *itSig;
            
            gSig->getColorRango()->setRango(rangoColor*1.25);
            gSig->getArea()->setRango(rango*2.5);
            
            if(g->colision(gSig)){
                g->unir(gSig);
                
                if(itSig == itFin2)
                    --itFin2;
                
                itSig = grupos.erase(itSig);
                --itSig;
                
            }
        }
    }
    cout << grupos.size() << endl;
    
    Imagen* imPuntos = new Imagen("puntos.jpg", dim, dim, 3);
    Imagen* imAreasColor = new Imagen("areasColor.jpg", dim, dim, 3);
    
    itFin = grupos.end();
    for (list<Grupo*>::iterator it = grupos.begin(); it != itFin; ++it) {
        
        g = *it;
        
        g->pintarArea(im);
        g->pintar(imPuntos);
        g->pintarAreaColorPromedio(imAreasColor, g->getColorRango()->getColorPromedio());
    }
    
    imPuntos->guardarJPG();
    imAreasColor->guardarJPG();
    
    im->guardarJPG("caraAreas.jpg");
    
            
    return 0;
}

