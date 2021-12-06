/**
    Class MyButton : Gestion d'un bouton TOUCH sur ESP32
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
        Aucune
    GPIO qui peuvent être utilisés en TOUCH sur le ESP32
            T0:GPIO4 (default)  T1:GPIO0     T2:GPIO2   T3:GPI15    T4:GPI13
            T5:GPI12            T6:GPI14     T7:GPI27   T8:GPI32    T9:GPI33
    Exemple d'utilisation 
        #include "MyButton.h"
        MyButton *myButton = new MyButton(&Wire, OLED_RESET, SCREEN_HEIGHT, SCREEN_WIDTH);
        myButton->init(T8);
        int sensibilisationButtonAction = myButton->autoSensibilisation(); //Trouve la sensibilité automatiquement

        loop:

        int buttonAction = myButtonAction->checkMyButton();
        if(buttonAction > 2)  {  //Si appuyé plus de 0.2 secondes
            Serial.println("Button pressed");
            }
        
**/

#include <Arduino.h>

#ifndef MYBUTTON_H
#define MYBUTTON_H

using namespace std;

class MyButton  {
    public:
        void init(int GPIONumber = T0, int toucheButtonSensibiliteToUse = 20);
        //Appeler pour vérifier le nombre de dixièmes de secondes le bouton a été appuyé
        int checkMyButton();
        //Trouver la sensibilité automatiquement
        int autoSensibilisation();

    private : 
        int buttonGPIO = T0;    //pin GPIO de le bouton
        int toucheButtonSensibilite = 20;
        
        //Pour calculer le temps qu'il faut pour activer le bouton
        bool toucheButtonActif;
        int toucheButtonActifStart;
        int toucheButtonActifEnd;
};
#endif