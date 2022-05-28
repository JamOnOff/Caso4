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
#include <vector>

#include "Imagen.h"
#include "Random.h"
#include "Grupo.h"

#include "cromodistribution.h"
#include "geneticbase.h"
#include "Frame.h"

using namespace std;

cromodistribution* definirRepCrom(list<Grupo*> grupos){
    int cantGrupos = grupos.size();
    
    cromodistribution* dist = new cromodistribution[cantGrupos];
    
    Grupo* g;
    list<Grupo*>::iterator itFin = grupos.end();
    int cantPuntos = 0;
    
    for (list<Grupo*>::iterator it = grupos.begin(); it != itFin; ++it) {
        g = *it;
        
        cantPuntos += g->getCantidad();
        
    }
    
    int pos = 0;
    float porcMaxAnt = 0; // porcentaje maximo del grupo anterior
    unsigned int maxValueAnt = 0; // valor máximo anterior
    int cantPuntosGrupo;
    for (list<Grupo*>::iterator it = grupos.begin(); it != itFin; ++it) {
        g = *it;
        
        cantPuntosGrupo = g->getCantidad();
        
        
        dist[pos].totalPopulation = cantPuntos;
        
        dist[pos].quantity = cantPuntosGrupo;
        
        float porcentaje = cantPuntosGrupo / float(cantPuntos);
        
        dist[pos].minProbability = porcMaxAnt;
        porcMaxAnt += porcentaje;
        dist[pos].maxProbability = porcMaxAnt;
        
        dist[pos].minValue = maxValueAnt;
        
        if(pos == cantGrupos-1)
            dist[pos].maxValue = CROMO_MAX_VALUE;
        else{
            maxValueAnt += float(CROMO_MAX_VALUE) * porcentaje;
            dist[pos].maxValue = maxValueAnt;
        }
        dist[pos].color = g->getColorRango()->getColorPromedio();
        
        dist[pos].puntoInicio = g->getArea()->getPuntoInicio();
        dist[pos].puntoFin = g->getArea()->getPuntoFin();
        
        pos++;
    }
    
    return dist;
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
    int rango = 15;
    
    
    // Selecciona los puntos del circulo y los asocia con un grupo
    // según su color y distancia
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
    
    
    // Elimina los grupos con más de 1080*0.2 puntos y los de area mayor a 1080-rango 
    Grupo* g;
    list<Grupo*>::iterator itFin = grupos.end();
    for (list<Grupo*>::iterator it = grupos.begin(); it != itFin; ++it) {
        g = *it;

        if(g->getCantidad() > dim*0.2 || g->getArea()->muyGrande(dim)){
            
            it = grupos.erase(it);
            --it;
        }
    }
    
    // Une los grupos cercanos con color similar
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
    
    // Guarda las imagenes puntos y areas
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
    /*
    for (int i = 0; i < grupos.size(); i++) {
        cout << i << endl;
        cout << dist[i].puntoInicio[0] << "," << dist[i].puntoInicio[1] << "; " 
             << dist[i].puntoFin[0] << "," << dist[i].puntoFin[1] << "; "
             << int(dist[i].color[0]) << "," << int(dist[i].color[1]) << "," << int(dist[i].color[2]) << "; "
             << to_string(dist[i].minValue) << "," << to_string(dist[i].maxValue) << "; "
             << dist[i].minProbability << "," << dist[i].maxProbability << "; "
             << dist[i].quantity << "," << dist[i].totalPopulation << "\n";
    }
    */
    
    GeneticBase* genetic = new GeneticBase(dim, random);
    cromodistribution* dist = definirRepCrom(grupos);
    
    int cantGrupos = grupos.size();
    for (int i = 0; i < cantGrupos; i++) 
        genetic->addDistribution(&dist[i]);
    
    genetic->initPopulation(100000);
    
    Frame* frame = new Frame(genetic->getPopulation(), random, dim);
    for (int i = 0; i < 1000; i++) {
        for (int j = 0; j < 3; j++)
            frame->mover();

        
        genetic->produceGenerations(1,10000);
        frame->guardarFrame();
    }
    
    
    return 0;
}

