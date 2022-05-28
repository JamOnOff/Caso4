#ifndef _CROMODISTRIBUTION_
#define _CROMODISTRIBUTION_ 1

#define CROMO_MAX_VALUE 4294967295
#define NIBBLE_SIZE 32

using namespace std;

struct cromodistribution {
    int* puntoInicio;
    int* puntoFin;
    unsigned int minValue;
    unsigned int maxValue;
    unsigned char* color;
    float minProbability;
    float maxProbability;
    int quantity;
    int totalPopulation;
};


#endif