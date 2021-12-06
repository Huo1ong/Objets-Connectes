/**
    Class MyServer :  Pour la gestion des routes pour le site WEB
    @file MyServer.h 
    @author Alain Dubé
    @version 1.1 21/09/20 
    
    Historique des versions   
                            Versions  Date      Auteur      Description
                            1.0      21/09/20   Ald         Première version de la classe
                            
                            
    platform = espressif32
    board = esp32doit-devkit-v1
    framework = arduino
    lib_deps = 
        lib_deps = bblanchon/ArduinoJson @ ^6.17.2
    Autres librairies (à copier dans le répertoire lib)
        Aucune
    
    Exemple d'utilisation 
        #include "MyServer.h"
        MyServer *myServer = NULL;
        myServer = new MyServer(80);
        myServer->initAllRoutes();

        //Mettre les fichiers du site WEB dans le réportoire /data
        //et téléverser en utilisant "Upload Filesystem Image" dans PlatformIO

**/
#ifndef MYSERVER_H
#define MYSERVER_H
#include <AsyncTCP.h>
#include <SPIFFS.h>
#include <ESPAsyncWebServer.h>
#include <HTTPClient.h>
#include <string>

//Pour le json dans L'API.
#include <ArduinoJson.h>

class MyServer : public AsyncWebServer {
    public:
        MyServer(uint8_t port) : AsyncWebServer(port){ };        
        
        typedef std::string (*CallbackType)(std::string);
        void initCallback(CallbackType callback);
                
        void initAllRoutes();  

    private:
        static CallbackType ptrToCallBackFunction;
        float currentTemperature = 0;
   };
#endif