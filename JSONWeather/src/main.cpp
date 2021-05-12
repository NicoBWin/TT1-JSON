/***************************************************************************//**
@file     +main.cpp+
@brief    +Ejemplo práctico de JSON integrado con API sobre el clima+
@version  +1.0+
@author   +Nicolás Bustelo+
******************************************************************************/

/*******************************************************************************
* INCLUDE HEADER FILES
******************************************************************************/
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>  //For setw() 
//https://www.cplusplus.com/reference/iomanip/setw/

#include "Client.h"
#include "Allegro.h"

#include <nlohmann/json.hpp>
//Ya que vamos a usar la librería NLOHMANN JSON 
using json = nlohmann::json;

using namespace std;
/*******************************************************************************
* CONSTANT AND MACRO DEFINITIONS USING #DEFINE
******************************************************************************/
#define PATH "JSONS/"

/*******************************************************************************
* FUNCTION PROTOTYPES FOR PRIVATE FUNCTIONS WITH FILE LEVEL SCOPE
******************************************************************************/
//Funcion para mostrar los datos en allegro
void draw(json& j);

//Funcion para guardar el JSON recibido
void save(json& j);
/*******************************************************************************
*******************************************************************************
    GLOBAL FUNCTION DEFINITIONS
*******************************************************************************
******************************************************************************/
int main(void) {
    if (!init_allegro()) {  //Iniciamos la pequeña interfaz para imprimir los datos
        cout << "Error in allegro inicialization" << endl;
        return 0;
    }
    
    //Ciudades posibles para ver el clima
    string cities[] = { "Buenos Aires", "New York", "London", "Paris", "Estaciudad Noexiste" };

    //JSON donde estarán los datos
    json jw;

    int citiNumber = 0; //Numero de ciudad a mostrar datos
    bool reDraw = true; 
    bool do_exit = false;
    while (!do_exit)
    {
        ALLEGRO_EVENT ev;
        if (al_get_next_event(event_queue, &ev)) //Toma un evento de la cola, VER RETURN EN DOCUMENT.
        {
            if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {   // Presiona cerrar
                do_exit = true;                             //salgo del while
            }
            else if (ev.type == ALLEGRO_EVENT_KEY_DOWN)     //apreto tecla?
            {
                switch (ev.keyboard.keycode)            //que tecla apreto?
                {
                case ALLEGRO_KEY_UP: //  Cambio de ciudad
                    if(citiNumber < (size(cities) - 1) )
                        citiNumber++;
                    reDraw = true;
                    break;
                case ALLEGRO_KEY_DOWN: //  Cambio de ciudad
                    if(citiNumber>0)
                        citiNumber--;
                    reDraw = true;
                    break;
                }
            }
        }
        if (reDraw){
            if (!client(cities[citiNumber], jw)) { //Cliente con libCurl
                cout << "Error in downloading JSON" << endl;
            }
            else {
                save(jw);
                draw(jw);
            }
            reDraw = false;
        }
    }

    destroy_allegro();      //Destruye recursos y finaliza la simulación
    cout << "See you next time..." << endl;
    return 0;
}

void save(json& j) {
    // Guardamos el JSON creado
    if (j["cod"] == "200") {
        string path = PATH;
        path.append(j["name"]);
        path.append(".json");
        ofstream outputFile(path, std::ios::out | std::ios::binary);
        if (outputFile.is_open()) {
            outputFile << j.dump() << endl;    //Lo guardamos como string
        }
        else
            std::cout << "Unable to open file " << std::endl;
        outputFile.close();
    }
}

void draw(json& j) {
    al_draw_bitmap(bkg, 0, 0, 0);  
    string aux;

    if (j["cod"] == "404") {
        al_draw_text(font1, al_map_rgb(0, 0, 0), 20, 50, 0, "ERROR: 404");
        aux = j["message"];
        al_draw_text(font1, al_map_rgb(0, 0, 0), 20, 150, 0, aux.c_str());
    }
    else {
        al_draw_text(font1, al_map_rgb(0, 0, 0), 20, 15, 0, "City: ");
        aux = j["name"];
        al_draw_text(font1, al_map_rgb(0, 0, 0), 180, 15, 0, aux.c_str());

        int var = j["main"]["temp"];
        var -= 273; //Para expresarla en grados celcius
        al_draw_textf(font1, al_map_rgb(0, 0, 0), 20, 100, 0, "Temp: %d C", var);

        var = j["main"]["humidity"];
        al_draw_textf(font1, al_map_rgb(0, 0, 0), 20, 180, 0, "Hum: %d %% ", var);

        var = j["main"]["pressure"];
        al_draw_textf(font1, al_map_rgb(0, 0, 0), 20, 260, 0, "Pres: %d hPa ", var);

        al_draw_text(font1, al_map_rgb(200, 200, 200), 20, 350, 0, "Sky Description:");
        aux = j["weather"][0]["description"];
        al_draw_text(font1, al_map_rgb(255, 255, 255), 20, 400, 0, aux.c_str());
    }

    al_flip_display();
}