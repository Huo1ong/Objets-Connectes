/**
    Gestion d'un bouton pour permettre au système de démarrer
    @file MyButton.cpp
    @author Alain Dubé
    @version 1.0 17/03/21  
*/

#include "MyButton.h"

/**
 * init Initialisation de l'objet
 *
 * La classe nécessite une initialisation préalable après d'instanciation
 * 
 * @param toucheButtonSensibiliteToUse Sensibilité du bouton à utiliser (par defaut : 20)
 * @param GPIONumber Le GPIO utilisé pour le bouton T0:pin24(default)  T1:Pin23     T2:Pin22   T3:Pin21
 */
void MyButton::init(int GPIONumber, int toucheButtonSensibiliteToUse) {
    buttonGPIO = GPIONumber;
    pinMode(buttonGPIO, INPUT);
    toucheButtonSensibilite = toucheButtonSensibiliteToUse;
    }

/**
 * Demarrage de l'auto initialisation de la sensibilité du bouton
 *
 * @param toucheButtonSensibiliteToUse Sensibilité du bouton à utiliser (par defaut : 20)
 * @param GPIONumber Le GPIO utilisé pour le bouton T0:pin24(default)  T1:Pin23     T2:Pin22   T3:Pin21
 */
int MyButton::autoSensibilisation() {
    Serial.println("Debut de autoSensibilisation");
    toucheButtonSensibilite = 0;
    for(int t=1; t<500; t++){
        toucheButtonSensibilite += touchRead(buttonGPIO);
        delay(10);
    }
    toucheButtonSensibilite = toucheButtonSensibilite / 500 - 2;
    return (toucheButtonSensibilite);
    }

/**
 * checkMyButton Teste si le bouton est activé et retourne le nombre de dixiemes de secondes 
 *
 * 
  * @return int 0 : Si rien   NbreSec : Nbre de dixiemes de secondes que le bouton est appuye et relaché   Négatif:si le bouton est appuyé mais non relaché
 */
int MyButton::checkMyButton() {
    //Vérification si l'usager a appuyé sur le bouton 
    if (touchRead(buttonGPIO) < toucheButtonSensibilite) {
        if (!toucheButtonActif) {
            toucheButtonActif = true;
            toucheButtonActifStart = (unsigned long)(esp_timer_get_time()) / 100000;
            toucheButtonActifEnd = 0;
            return (0);
        }
        toucheButtonActifEnd = (unsigned long)(esp_timer_get_time()) / 100000;
        toucheButtonActifEnd -= toucheButtonActifStart;
        return (-toucheButtonActifEnd);
    }
    else {
        if(toucheButtonActif) {
            toucheButtonActif = false;
            return (toucheButtonActifEnd);
        }
    }
    return (0);
    }