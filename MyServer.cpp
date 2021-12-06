/**
    Gestion d'un serveur WEB
    @file MyServer.cpp
    @author Alain Dubé
    @version 1.1 20/11/20 
*/
#include <Arduino.h>
#include "MyServer.h"
using namespace std;

typedef std::string (*CallbackType)(std::string);
CallbackType MyServer::ptrToCallBackFunction = NULL;

//Exemple pour appeler une fonction CallBack
//if (ptrToCallBackFunction) (*ptrToCallBackFunction)(stringToSend); 
void MyServer::initCallback(CallbackType callback) {
    ptrToCallBackFunction = callback;
    }

void MyServer::initAllRoutes() { 
    currentTemperature = 3.3f;

    //Initialisation du SPIFF.
    if (!SPIFFS.begin(true)) {
        Serial.println("An Error has occurred while mounting SPIFFS");
        return;
        }

    //Route initiale (page html)
    this->on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send(SPIFFS, "/web.html", "text/html");
        });

    //Route du script JavaScript
    this->on("/script.js", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send(SPIFFS, "/script.js", "text/javascript");
        });

    this->on("/style.css", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send(SPIFFS, "/style.css", "text/css");
        });

    this->on("/Logo.png", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send(SPIFFS, "/Logo.png", "image/png");
        });
   
    this->onNotFound([](AsyncWebServerRequest *request){
        request->send(404, "text/plain", "Page Not Found");
        });
    
    this->begin();

    this->on("/getNomEsp", HTTP_GET, [](AsyncWebServerRequest *request) {
    std::string repString = "";
    if (ptrToCallBackFunction) repString = (*ptrToCallBackFunction)("askNomFour");
    String lireNomDuFour =String(repString.c_str());
    request->send(200, "text/plain", lireNomDuFour );
    });

    this->on("/lireNomDuSysteme", HTTP_GET, [](AsyncWebServerRequest *request) {
        std::string repString = "";
        if (ptrToCallBackFunction) repString = (*ptrToCallBackFunction)("askNomFour"); //Exemple pour appeler une fonction CallBack
        String lireNomDuFour =String(repString.c_str());
        request->send(200, "text/plain", lireNomDuFour );
        });



    this->on("/get_all_typebois", HTTP_GET, [](AsyncWebServerRequest *request) {
        Serial.println("get_all_typebois... ");

        HTTPClient http;
        String woodApiRestAddress = "http://172.16.204.121:3000/get_all_typebois";
        http.begin(woodApiRestAddress);
        http.GET();
        String response = http.getString();
        Serial.println(response);
       /*  String tempToSend;
        StaticJsonDocument<2048> doc;
        deserializeJson(doc, response);
        JsonObject obj1 = doc.as<JsonObject>();
        std::string wood;
        String  woodName;
      
        for (JsonPair kv1 : obj1) {
            wood = kv1.key().c_str();
            Serial.print("Element : ");Serial.println(wood.c_str());

            JsonObject elem = obj1[wood];
            woodName = elem["name"].as<String>();
            if(tempToSend!="") tempToSend += "&";
            tempToSend +=  String(wood.c_str()) + String("&") + String(woodName.c_str());
           
            Serial.print(woodName);Serial.print(" ");
                           */
            //Pour parcourir les éléments de l'objet
            //for (JsonPair kv2 : elem) {
            //    Serial.print("   Sous element : ");Serial.print(kv2.key().c_str());
            //    Serial.print("    :  ");Serial.println(kv2.value().as<char*>());
            //    }
            //}
        
        request->send(200, "text/plain", response);
    });
};