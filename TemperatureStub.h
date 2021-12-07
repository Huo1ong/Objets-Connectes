/**
    Class MyButton : Gestion de la température (senseur) STUB
    @file MyButton.h 
    @author Alain Dubé
    @version 1.0 17/03/21  
    
    Historique des versions   
                            Versions  Date      Auteur      Description
                            1.0      17/03/21   Ald         Première version de la classe
                            
                            
    platform = espressif32
    board = esp32doit-devkit-v1
    framework = arduino
    lib_deps = 
        Aucune
    Autres librairies (à copier dans le répertoire lib)
        DHT
    GPIO 
        DHTPIN  15   // Définition de la Pin utilisée par le senseur DHT22 / DHT22
    TYPES possibles 
        DHTTYPE DHT22 ou DTH22  //Le type de senseur utilisé ( DHT22 a plus de précision)

    Exemple d'utilisation 
        #include "TemperatureStub.h"
        temperatureStub = new TemperatureStub;
        temperatureStub->init(DHTPIN, DHTTYPE); //Pin 15 et Type DHT22
        float t = temperatureStub->getTemperature();
        
**/

#include <Arduino.h>

#ifndef TEMPERATURE_STUB_H
#define TEMPERATURE_STUB_H
#include "DHT.h"
using namespace std;

class TemperatureStub  {
    public:
        void init(int _inputPinUsed = 15, int _typeSensorUsed = DHT22);
        ////0 : Celcius   1:Far
        bool setUniteUsed(int _UniteUsed = 0);
        //Retourne la température su senseur
        float getTemperature();

    private : 
        
        //here we use 14 of ESP32 to read data
        int inputPinUsed =  15;
        int typeSensorUsed =  DHT22;
        int UniteUsed = 0; //0 : Celcius   1:Far
        DHT *dht = NULL;
        float lastTemperatureRead = -999;
       
};
#endif