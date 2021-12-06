/* Copyright (C) 2021 Alain Dube
 * All rights reserved.
 *
 * Projet Sac
 * Ecole du Web
 * Cours Objets connectés (c)2021
 *  
    @file     main.cpp
    @author   Alain Dubé
    @version  1.1 21/08/15 

    Historique des versions
           Version    Date       Auteur       Description
           1.1        21/08/15  Alain       Première version du logiciel

    platform = espressif32
    board = esp32doit-devkit-v1
    framework = arduino
    lib_deps = 
                      
            ESPAsyncWebServer-esphome                   (Pour accéder au Wifi)
            AsyncTCP-esphome                            (Pour utiliser les focntionnalités TCP)
            bblanchon/ArduinoJson@^6.17.2               (Pour accéder au fonctionnalités Json)

    Autres librairies (à copier dans le répertoire lib)
         WifiManagerDevelopment
            //Remarques
            //Pour trouver le WifiManager (dans la branche development)
            //   https://github.com/tzapu/WiFiManager/tree/development
            //   Ne pas oublier d'appuyez sur l'ampoule et choisir : ajouter Lib
    
    Fonctions utiles (utilitaires)
        /lib/MYLIB/myFunctions.cpp
            //Pour vérifier plus simplement que deux chaines sont identiques
            bool isEqualString(std::string line1, std::string line2)
            //Pour extraire une partie d'une chaine de caractères avec l'aide d'un index
            std::string getValue(std::string data, char separator, int index)
            //Pour remplacer plus facilement une sous chaine
            bool replaceAll(std::string& source, const std::string& from, const std::string& to)
            //Pour obtenir un chaine aléatoire d'une certaine longeur
            std::string get_random_string(unsigned int len)

    Classes du système
         
        MyServer                        V1.0    Pour la gestion des routes pour le site WEB
            /data                               Répertoire qui contient les fichiers du site WEB 
                index.html              V1.0    Page index du site WEB
                index.css               V1.0    CSS
                script.js               V1.0    JS (fonctions JavaScript)
              
 * */

#include <iostream>
#include <string>
#include <TemperatureStub.h>
#define DHTPIN 15
#define DHTTYPE DHT22
TemperatureStub *temperatureStub = NULL;
#include <Arduino.h>
#include <ArduinoJson.h>

#include "myFunctions.cpp" //fonctions utilitaires

using namespace std;

#include <HTTPClient.h>
#include <WiFiManager.h>
WiFiManager wm;
#define WEBSERVER_H

//Pour la gestion du serveur ESP32
#include "MyServer.h"
MyServer *myServer = NULL;

//Variable pour la connection Wifi
const char *SSID = "SAC_";
const char *PASSWORD = "sac_";
String ssIDRandom;

float temperature =0;
//fonction statique qui permet aux objets d'envoyer des messages (callBack) 
//  arg0 : Action 
// arg1 ... : Parametres
std::string CallBackMessageListener(string message) {
    while(replaceAll(message, std::string("  "), std::string(" ")));
    //Décortiquer le message
    string actionToDo = getValue(message, ' ', 0);
    string arg1 = getValue(message, ' ', 1);
    
  
    //  return (temp.c_str());
    
    string arg2 = getValue(message, ' ', 2);
    string arg3 = getValue(message, ' ', 3);
    string arg4 = getValue(message, ' ', 4);
    string arg5 = getValue(message, ' ', 5);
    string arg6 = getValue(message, ' ', 6);
    string arg7 = getValue(message, ' ', 7);
    string arg8 = getValue(message, ' ', 8);
    string arg9 = getValue(message, ' ', 9);
    string arg10 = getValue(message, ' ', 10);
  
    if (string(actionToDo.c_str()).compare(string("action")) == 0) {
         return(String("Ok").c_str());
        }
        else if(string(actionToDo.c_str()).compare(string("temperature")) == 0){
              String temp = String(temperature).c_str();
            return (temp.c_str());
        }
   
    std::string result = "";
    return result;
    }

void setup() { 
    Serial.begin(9600);
    delay(100);

 //Connection au WifiManager
    String ssIDRandom, PASSRandom;
    String stringRandom;
    stringRandom = get_random_string(4).c_str();
    ssIDRandom = SSID;
    ssIDRandom = ssIDRandom + stringRandom;
    stringRandom = get_random_string(4).c_str();
    PASSRandom = PASSWORD;
    PASSRandom = PASSRandom + stringRandom;

char strToPrint[128];
    sprintf(strToPrint, "Identification : %s   MotDePasse: %s", ssIDRandom, PASSRandom);
    Serial.println(strToPrint);


 if (!wm.autoConnect(ssIDRandom.c_str(), PASSRandom.c_str())){
        Serial.println("Erreur de connexion.");
      
        }
    else {
        Serial.println("Connexion Établie.");
         }

    // ----------- Routes du serveur ----------------
    myServer = new MyServer(80);
    myServer->initAllRoutes();
    myServer->initCallback(&CallBackMessageListener);

    temperatureStub=new TemperatureStub;
    temperatureStub->init(DHTPIN,DHTTYPE);
    Serial.println("ça marche !");
 }

void loop() {
     temperature = temperatureStub->getTemperature();
  }