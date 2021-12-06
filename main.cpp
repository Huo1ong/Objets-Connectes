/* Copyright (C) 2021 Alain Dube
 * All rights reserved.
 *
 * Projet Sac
 * Ecole du Web
 * Cours Objets connectés (c)2021
 *  
    @file     main.cpp
    @author   Alain Dubé - Guillou Quentin
    @version  1.1 21/08/15 
 * */

#include <iostream>
#include <string>

#include <Arduino.h>
#include <ArduinoJson.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET 4 // Reset pin # (or -1 if sharing Arduino reset pin)
#define OLED_I2C_ADDRESS 0x3C // Adresse I2C de l'écran Oled


//LEDS 
//Définition des trois leds de statut
#define GPIO_PIN_LED_OK_GREEN           14 //GPIO14
#define GPIO_PIN_LED_HEAT_BLUE        27 //GPIO27
#define GPIO_PIN_LED_LOCK_ROUGE         12 //GPIO12

#include "myFunctions.cpp" //fonctions utilitaires

using namespace std;

#include <HTTPClient.h>
#include <WiFiManager.h>
WiFiManager wm;
#define WEBSERVER_H

//Pour la gestion du serveur ESP32
#include "MyServer.h"
MyServer *myServer = NULL;

//Classes
#include "MyOled.h"
MyOled *myoled = NULL;

#include <wire.h>

#include "MyOledView.h"
MyOledView *myoledview = NULL;

#include "MyOledViewWifiAp.h"
MyOledViewWifiAp *myoledviewwifiap = NULL;

#include "MyOledViewInitialisation.h"
MyOledViewInitialisation *myoledviewinitialisation = NULL;

#include "MyOledViewWorking.h"
MyOledViewWorking *myoledviewworking = NULL;

#include "MyOledViewWorkingOFF.h"
MyOledViewWorkingOFF *myoledviewworkingoff = NULL;

#include "MyOledViewWorkingCOLD.h"
MyOledViewWorkingCOLD *myoledviewworkingcold = NULL;

#include "MyOledViewWorkingHEAT.h"
MyOledViewWorkingHEAT *myoledviewworkingheat = NULL;

#include "MyOledViewErrorWifiConnexion.h"
MyOledViewErrorWifiConnexion *myoledviewerrorwificonnexion = NULL;

//Pour la gestion des boutons
#include "MyButton.h"
MyButton *myButtonAction = NULL;
MyButton *myButtonReset = NULL;

//Variable pour la connection Wifi
const char *SSID = "SAC_";
const char *PASSWORD = "sac_";
String ssIDRandom;

//fonction statique qui permet aux objets d'envoyer des messages (callBack) 
//  arg0 : Action 
// arg1 ... : Parametres
std::string CallBackMessageListener(string message) {
    while(replaceAll(message, std::string("  "), std::string(" ")));
    //Décortiquer le message
    string actionToDo = getValue(message, ' ', 0);
    string arg1 = getValue(message, ' ', 1);
    string arg2 = getValue(message, ' ', 2);
    string arg3 = getValue(message, ' ', 3);
    string arg4 = getValue(message, ' ', 4);
    string arg5 = getValue(message, ' ', 5);
    string arg6 = getValue(message, ' ', 6);
    string arg7 = getValue(message, ' ', 7);
    string arg8 = getValue(message, ' ', 8);
    string arg9 = getValue(message, ' ', 9);
    string arg10 = getValue(message, ' ', 10);
    std::string nomDuFour =  "Four9394";
    if (string(actionToDo.c_str()).compare(string("lireNomDuFour ")) == 0) {   return(nomDuFour.c_str()); }
  
    if (string(actionToDo.c_str()).compare(string("action")) == 0) {
         return(String("Ok").c_str());
        }
   
    std::string result = "";
    return result;
    }

void setup() { 
    Serial.begin(9600);
    delay(100);

    //INITIALISATION ÉCRAN INIT
    myoled = new MyOled(&Wire,OLED_RESET, SCREEN_HEIGHT, SCREEN_WIDTH);
    myoled->init(OLED_I2C_ADDRESS, true);

    myoledviewinitialisation = new MyOledViewInitialisation();
    myoledviewinitialisation->setNomDuSysteme("SAC system");
    myoledviewinitialisation->setIdDuSysteme("ID : ID1303");
    myoledviewinitialisation->setSensibiliteBoutonAction("????");
    myoledviewinitialisation->setSensibiliteBoutonReset("????");
    myoled->displayView(myoledviewinitialisation);

    //Gestion des boutons
    myButtonAction = new MyButton();        //Pour lire le bouton actions
    myButtonAction->init(T8);
    int sensibilisationButtonAction = myButtonAction->autoSensibilisation();

    myButtonReset = new MyButton();         //Pour lire le bouton hard reset
    myButtonReset->init(T9);
    int sensibilisationButtonReset = myButtonReset->autoSensibilisation();

    myoledviewinitialisation->setSensibiliteBoutonAction(String(sensibilisationButtonAction).c_str());
    myoledviewinitialisation->setSensibiliteBoutonReset(String(sensibilisationButtonReset).c_str());
    myoled->displayView(myoledviewinitialisation);


   Serial.print("sensibilisationButtonAction : "); Serial.println(sensibilisationButtonAction);
   Serial.print("sensibilisationButtonReset : "); Serial.println(sensibilisationButtonReset);


    // ÉCRAN WIFI AP

    //Gestion des boutons
    myoled = new MyOled(&Wire,OLED_RESET, SCREEN_HEIGHT, SCREEN_WIDTH);
    myoled->init(OLED_I2C_ADDRESS, true);

    myButtonAction = new MyButton();        //Pour lire le bouton actions
    myButtonAction->init(T8);
    int ssiddusysteme = myButtonAction->autoSensibilisation();

    myButtonReset = new MyButton();         //Pour lire le bouton hard reset
    myButtonReset->init(T9);
    int passdusysteme = myButtonReset->autoSensibilisation();


    // ÉCRAN WORKING OFF

    //Gestion des boutons
    myoled = new MyOled(&Wire,OLED_RESET, SCREEN_HEIGHT, SCREEN_WIDTH);
    myoled->init(OLED_I2C_ADDRESS, true);

    myButtonAction = new MyButton();        //Pour lire le bouton actions
    myButtonAction->init(T8);
    int tempdusysteme = myButtonAction->autoSensibilisation();

    myButtonReset = new MyButton();         //Pour lire le bouton hard reset
    myButtonReset->init(T9);
    int ipdusysteme = myButtonReset->autoSensibilisation();

    //LEDS
    //Initialisation des LED statuts
    pinMode(GPIO_PIN_LED_OK_GREEN, OUTPUT);
    pinMode(GPIO_PIN_LED_HEAT_BLUE, OUTPUT);
    pinMode(GPIO_PIN_LED_LOCK_ROUGE, OUTPUT);

    //Faire clignoter les Leds à l'initialisation
    for (int i=0;i<2;i++) {
        digitalWrite(GPIO_PIN_LED_OK_GREEN,HIGH);
        digitalWrite(GPIO_PIN_LED_HEAT_BLUE,HIGH);
        digitalWrite(GPIO_PIN_LED_LOCK_ROUGE,HIGH);
        delay(1000);
        digitalWrite(GPIO_PIN_LED_OK_GREEN,LOW);
        digitalWrite(GPIO_PIN_LED_HEAT_BLUE,LOW);
        digitalWrite(GPIO_PIN_LED_LOCK_ROUGE,LOW);
        delay(1000); 
    }


 //Connection au WifiManager
    String ssIDRandom, PASSRandom;
    String stringRandom;
    stringRandom = get_random_string(4).c_str();
    ssIDRandom = SSID;
    ssIDRandom = ssIDRandom + stringRandom;
    stringRandom = get_random_string(4).c_str();
    PASSRandom = PASSWORD;
    PASSRandom = PASSRandom + stringRandom;

    myoledviewwifiap = new MyOledViewWifiAp();
    myoledviewwifiap->setNomDuSysteme("SAC system");
    myoledviewwifiap->setNomDuSysteme("AP Configuration");
    myoledviewwifiap->setSsIdDuSysteme(String(ssIDRandom).c_str());
    myoledviewwifiap->setPassDuSysteme(String(PASSRandom).c_str()); 
    myoled->displayView(myoledviewwifiap);
   
    Serial.print("SSID : "); Serial.println(ssIDRandom);
    Serial.print("PASS : "); Serial.println(PASSRandom);

    // ÉCRAN WORKING OFF

    myoledviewworkingoff = new MyOledViewWorkingOFF();
    myoledviewworkingoff->setNomDuSysteme("SAC system");
    myoledviewworkingoff->setNomDuSysteme("ID : 1303");
    myoledviewworkingoff->setTempDuSysteme(String(tempdusysteme).c_str());
    myoledviewworkingoff->setIPDuSysteme(String(ipdusysteme).c_str()); 
    myoled->displayView(myoledviewworkingoff);
   
    Serial.print('23:00'); Serial.println(tempdusysteme);
    Serial.print('192.16.204.121'); Serial.println(ipdusysteme);

    char strToPrint[128];
        sprintf(strToPrint, "Identification : %s   MotDePasse: %s", ssIDRandom.c_str(), PASSRandom.c_str());
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

    }

    void loop() 
    {

    }
