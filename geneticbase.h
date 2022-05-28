#ifndef _GENETICBASE_
#define _GENETICBASE_ 1
#include <vector>
#include "cromodistribution.h"
#include "individual.h"
#include "Random.h"

using namespace std;

unsigned int negar(unsigned int n, int pos){
    int der = NIBBLE_SIZE - pos - 1;
    
    unsigned int filtro = n << pos;
    filtro = filtro >> pos + der;
    
    filtro = ~(filtro << der);
    
    n = n | (1 << der);
    
    return n & filtro;
}

class GeneticBase {
    private:
        vector<cromodistribution*> *representation;
        vector<individual*> *population;
        vector<individual*> *fitnessPopulation;
        vector<individual*> *unfitnessPopulation;
        int populationQuantity;
        int targetGenerations;

        Random* random;
        int dim;
        
        void evaluateFitness() {
            fitnessPopulation->clear();
            unfitnessPopulation->clear();

            for(int i=0;i<population->size(); i++) {
               population->at(i)->setFitnessValue(fitness(population->at(i)));
                // ajustarlo al fitness y fitness criteria del problema
                if (population->at(i)->getFitnessValue()> this->dim * 0.75) {  // fitness criteria of selection NEVER will be an absolute value, always is relative to the population
                    fitnessPopulation->push_back(population->at(i));
                } else {
                    unfitnessPopulation->push_back(population->at(i));
                }
            }
        }

        float fitness(individual *pIndividual) {
            // aqui es donde más hay que hacer mente, cuál va a ser mi función de fitness
            // la función de fitness tiene la responsabilidad de guiar la población
            // pues es la que selecciona los mejores dado que esos están cada vez más cerca de la respuesta
            return this->dim - pIndividual->distanciaArea();
        }

        void reproduce(int pAmountOfChildrens) {
            // previous population will be cleared, full saved, partial saved --> depending on the problem
            population->clear();

            for(int i=0; i<pAmountOfChildrens; i++) {
                // select any two fitness parents
                int parent_a_index = this->random->getNum(fitnessPopulation->size());
                individual* parent_a = fitnessPopulation->at(parent_a_index);

                population->push_back(cross(parent_a));
            }
        }

        individual* cross(individual *pParent_a) {
            // this operation will depends on: nibble size, si el punto de corte es fixed o variable point
            unsigned int kid = pParent_a->getCromosoma();
            
            if(this->random->getNum() < 0.25){
                negar(kid, this->random->getNum(NIBBLE_SIZE));
                negar(kid, this->random->getNum(NIBBLE_SIZE));
            }
            int movX = random->getNum(-1,3) * 15; // -1, 0 , 1
            int movY = random->getNum(-1,3) * 15; // -1, 0 , 1
            
            if(pParent_a->getX() + movX < 0 || pParent_a->getX() + movX > this->dim)
                movX = 0;
            if(pParent_a->getY() + movY < 0 || pParent_a->getY() + movY > this->dim)
                movY = 0;
            
            individual *children = new individual(kid, pParent_a->getX() + movX, pParent_a->getY() + movY);
            children->defInfo(this->representation);
            
            // hace falta la mutación, hay que agregar el % de mutación y la mutación en si misma
            return children;
        }

    public:
        GeneticBase(int dim, Random* random) {
            this->population = new vector<individual*>();
            this->fitnessPopulation = new vector<individual*>();
            this->unfitnessPopulation = new vector<individual*>();
            this->representation = new vector<cromodistribution*>(); 
            this->populationQuantity = 0;
            this->targetGenerations = 20;
            
            this->random = random;
            this->dim = dim;
        }

        void addDistribution(cromodistribution* pDistribution) {
            representation->push_back(pDistribution);
        }

        void initPopulation(int pAmountOfIndividuals) {
            population->clear();

            for(int i=0; i<pAmountOfIndividuals; i++) {
                // aqui está asumiendo nibble de 8 bits, unsigned char
                individual* p = new individual(this->random->getNum(CROMO_MAX_VALUE + 1), this->random->getNum(this->dim), this->random->getNum(this->dim));
                p->defInfo(this->representation);
                population->push_back(p);
            }
        }
        
        void produceGenerations(int ptargetGenerations, int pChildrensPerGenerations) {
            for(int i = 0; i<ptargetGenerations; i++) {
                evaluateFitness();
                reproduce(pChildrensPerGenerations);
            }
        }

        vector<individual*>* getPopulation() {
            return this->population;
        }
};

#endif