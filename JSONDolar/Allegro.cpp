/***************************************************************************//**
@file     +Allegro.cpp+
@brief    +Funciones de la interfaz Allegro+
@author   +Nicolás Bustelo+
******************************************************************************/

/*******************************************************************************
* INCLUDE HEADER FILES
******************************************************************************/
#include <iostream>

#include "Allegro.h"

using namespace std;


/*******************************************************************************
* CONSTANT AND MACRO DEFINITIONS USING #DEFINE
******************************************************************************/



/*******************************************************************************
* ENUMERATIONS AND STRUCTURES AND TYPEDEFS
******************************************************************************/



/*******************************************************************************
* VARIABLES WITH GLOBAL SCOPE
******************************************************************************/
/*PUNTEROS ALLEGRO*/
ALLEGRO_DISPLAY* display = NULL;
ALLEGRO_EVENT_QUEUE* event_queue = NULL;
ALLEGRO_FONT* font1 = NULL;

/*******************************************************************************
* FUNCTION PROTOTYPES FOR PRIVATE FUNCTIONS WITH FILE LEVEL SCOPE
******************************************************************************/

// +ej: static void falta_envido (int);+


/*******************************************************************************
* ROM CONST VARIABLES WITH FILE LEVEL SCOPE
******************************************************************************/

// +ej: static const int temperaturas_medias[4] = {23, 26, 24, 29};+


/*******************************************************************************
* STATIC VARIABLES AND CONST VARIABLES WITH FILE LEVEL SCOPE
******************************************************************************/

// +ej: static int temperaturas_actuales[4];+


/*******************************************************************************
*******************************************************************************
    GLOBAL FUNCTION DEFINITIONS
*******************************************************************************
******************************************************************************/
//Funcion que inicializa todo lo que es allegro
int init_allegro() {
    if (!al_init()) {
        cout << "failed to initialize allegro!!" << endl;
        return false;
    }
    else if (!al_init_font_addon()) { // initialize the font addon
        cout << "failed to initialize font addon!!" << endl;
        return false;
    }
    else if (!al_init_ttf_addon()) { // Initialize the ttf (True Type Font) addon
        cout << "failed to initialize ttf addon!!" << endl;
        al_shutdown_font_addon();
        return false;
    }
    else if (!al_init_image_addon()) {
        cout << "failed to init image addon!" << endl;
        al_shutdown_font_addon();
        al_shutdown_ttf_addon();
        return false;
    }
    else if (!al_install_keyboard()) {
        cout << "failed to install keyboard!" << endl;
        al_shutdown_font_addon();
        al_shutdown_ttf_addon();
        al_shutdown_image_addon();
        return false;
    }
    else if (!al_init_primitives_addon()) {
        cout << "failed to init primitives addon!" << endl;
        al_shutdown_font_addon();
        al_shutdown_ttf_addon();
        al_shutdown_image_addon();
        al_uninstall_keyboard();
        return false;
    }
    display = al_create_display(W_PIXELS, H_PIXELS);
    if (!display) {
        cout << "failed to create display!" << endl;
        al_shutdown_font_addon();
        al_shutdown_ttf_addon();
        al_shutdown_image_addon();
        al_uninstall_keyboard();
        al_shutdown_primitives_addon();
        return false;
    }
    event_queue = al_create_event_queue();
    if (!event_queue) {
        cout << "failed to load event queue!" << endl;
        al_shutdown_font_addon();
        al_shutdown_ttf_addon();
        al_shutdown_image_addon();
        al_uninstall_keyboard();
        al_shutdown_primitives_addon();
        al_destroy_display(display);
        return false;
    }

    al_set_window_title(display, "DOLAR JSON");
    al_register_event_source(event_queue, al_get_display_event_source(display));  //Agrego los eventos a la cola
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    return true;
}

//Funcion que destruye todos los recursos de allegro
void destroy_allegro(void) {
    al_shutdown_font_addon();
    al_shutdown_ttf_addon();
    al_shutdown_image_addon();
    al_shutdown_primitives_addon();

    al_destroy_event_queue(event_queue);
    al_destroy_display(display);

    al_uninstall_keyboard();
}

//Dibuja la interface
void draw_interface() {
    al_clear_to_color(al_map_rgb(0, 0, 0));
    //
    //PONER TODO LINDO
    //
    al_flip_display();
}


/*******************************************************************************
*******************************************************************************
        LOCAL FUNCTION DEFINITIONS
*******************************************************************************
******************************************************************************/