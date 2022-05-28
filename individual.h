#ifndef _INDIVIDUAL_
#define _INDIVIDUAL_ 1

#define MIN_GENOTYPE_SIZE_BY_PARENT 2

#include <vector>

#include "cromodistribution.h"
#include "Random.h"
#include "Imagen.h"

using namespace std;

class individual {
    private: 
        // any important related info
        // decide the size of your nibble for your problem
        
        int x, y;
        int* puntoInicio;
        int* puntoFin;
        
        unsigned char* color;
        
        float fitnessValue;
        unsigned int cromosoma;
    public:
        individual(unsigned int pValue, int x, int y) {
            this->cromosoma = pValue;
            
            this->x = x;
            this->y = y;
        }
        
        void defInfo(vector<cromodistribution*>* representation){
            int tam = representation->size();
            for (int i = 0; i < tam; i++) {
                cromodistribution* dist = representation->at(i);
                
                if(this->cromosoma <= dist->maxValue){
                    this->puntoInicio = dist->puntoInicio;
                    this->puntoFin = dist->puntoFin;
                    
                    this->color = dist->color;
                    
                    break;
                }
            }

        }
        
        void pintar(Imagen* im, int dim){
            unsigned char* colorPunto;
            
            int xFin = this->x + 20;
            int yFin = this->y + 20;
            
            if(xFin > dim)
                xFin = dim;
            if(yFin > dim)
                yFin = dim;
            
            for (int i = this->y; i < yFin; i++) {
                for (int j = this->x; j < xFin; j++) {
                    colorPunto = im->getPixel(j, i);
                    
                    colorPunto[0] = this->color[0];
                    colorPunto[1] = this->color[1];
                    colorPunto[2] = this->color[2];
                }
            }
            
            
        }
        
        void mover(Random* random, int dim){
            int dist = 15;
            int movX = random->getNum(-1,3) * dist; // -1, 0 , 1
            int movY = random->getNum(-1,3) * dist; // -1, 0 , 1
            
            int movX2 = random->getNum(dist + 1);
            int movY2 = random->getNum(dist + 1);
            
            if(this->x + movX2 < 0 || this->x + movX2 > dim)
                movX2 = 0;
            if(this->y + movY2 < 0 || this->y + movY2 > dim)
                movY2 = 0;
            if(this->x - movX2 < 0 || this->x - movX2 > dim)
                movX2 = 0;
            if(this->y - movY2 < 0 || this->y - movY2 > dim)
                movY2 = 0;
            
            if(this->puntoInicio[0] <= this->x + movX && this->x + movX <= this->puntoFin[0])
                this->x += movX;
            else{
                if(this-> x < this->puntoInicio[0])
                    this->x += movX2;
                else
                    this->x -= movX2;
            }
            
            if(this->puntoInicio[1] <= this->y + movY && this->y + movY <= this->puntoFin[1])
                this->y += movY;
            else{
                if(this-> y < this->puntoInicio[1])
                    this->y += movY2;
                else
                    this->y -= movY2;
            }
        }
        
        bool isArea(){
            return this->puntoInicio[0] <= this->x && this->x <= this->puntoFin[0] 
                && this->puntoInicio[1] <= this->y && this->y <= this->puntoFin[1];
        }
        
        void setFitnessValue(float pValue) {
            this->fitnessValue = pValue;
        }
        
        
        float distanciaArea(){
            int x2 = this->puntoInicio[0] + ((this->puntoFin[0] - this->puntoInicio[0]) / 2);
            int y2 = this->puntoInicio[1] + ((this->puntoFin[1] - this->puntoInicio[1]) / 2);
            
            return sqrt(pow(x2 - this->x, 2) + pow(y2 - this->y, 2));
        }
        
        unsigned int getCromosoma() {
            return this->cromosoma;
        }

        float getFitnessValue() {
            return this->fitnessValue;
        }
        
        int getX() const {
            return x;
        }

        int getY() const {
            return y;
        }

};


#endif