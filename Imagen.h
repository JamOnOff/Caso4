/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/file.h to edit this template
 */

/* 
 * File:   Imagen.h
 * Author: Josue Alvarez M
 *
 * Created on 24 de mayo de 2022, 20:33
 */

#ifndef IMAGEN_H
#define IMAGEN_H

#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

#define STBI_MSC_SECURE_CRT
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb/stb_image_write.h"

using namespace std;


class Imagen{
private:
    // dimenciones
    int ancho, alto;
    // RBG, RGBA ...
    int canales;
    
    unsigned char *imagen;
    
    char* nombre;
    
public:
    Imagen(char* nombre){
        this->nombre = nombre;
        this->imagen = stbi_load(nombre, &this->ancho, &this->alto, &this->canales, 0);
    }
    
    unsigned char* getPixel(int x, int y){
        unsigned char* pixel = this->imagen;
        pixel += this->canales * ((this->ancho * y) + x);
        
        return pixel;
    }
    
    void guardarJPG(){
        stbi_write_jpg(this->nombre, this->ancho, this->alto, 3, this->imagen, 100);
    }
    
    void guardarJPG(char* nombre){
        stbi_write_jpg(nombre, this->ancho, this->alto, 3, this->imagen, 100);
    }
    
    void cerrar(){
        stbi_image_free(imagen);
    }
    
    //get
    int getAlto() const {
        return alto;
    }

    int getAncho() const {
        return ancho;
    }
    
    int getCanales() const {
        return canales;
    }

};


#endif /* IMAGEN_H */

