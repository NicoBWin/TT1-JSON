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
* VARIABLES WITH GLOBAL SCOPE
******************************************************************************/
/*PUNTEROS ALLEGRO*/
ALLEGRO_DISPLAY* display = NULL;
ALLEGRO_EVENT_QUEUE* event_queue = NULL;
ALLEGRO_FONT* font1 = NULL;
ALLEGRO_BITMAP* bkg = NULL;


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
    else if (!(font1 = al_load_font(FONT_FILE, 40, 0))) {
        cout << "failed to load Font!" << endl;
        al_shutdown_font_addon();
        al_shutdown_ttf_addon();
        al_shutdown_image_addon();
        al_uninstall_keyboard();
        al_shutdown_primitives_addon();
    }
    else if (!(bkg = al_load_bitmap(BKG_FILE))) {
        cout << "failed to load BKG image!" << endl;
        al_shutdown_font_addon();
        al_shutdown_ttf_addon();
        al_shutdown_image_addon();
        al_uninstall_keyboard();
        al_shutdown_primitives_addon();
        al_destroy_font(font1);
    }
    display = al_create_display(W_PIXELS, H_PIXELS);
    if (!display) {
        cout << "failed to create display!" << endl;
        al_shutdown_font_addon();
        al_shutdown_ttf_addon();
        al_shutdown_image_addon();
        al_uninstall_keyboard();
        al_shutdown_primitives_addon();
        al_destroy_font(font1);
        al_destroy_bitmap(bkg);
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
        al_destroy_font(font1);
        al_destroy_bitmap(bkg);
        al_destroy_display(display);
        return false;
    }

    al_set_window_title(display, "WEATHER WITH JSON");
    al_draw_bitmap(bkg, 0, 0, 0);
    al_flip_display();
    al_register_event_source(event_queue, al_get_display_event_source(display));  //Agrego los eventos a la cola
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    return true;
}

//Funcion que destruye todos los recursos de allegro
void destroy_allegro(void) {
    al_destroy_font(font1);
    al_destroy_bitmap(bkg);
    al_destroy_event_queue(event_queue);
    al_destroy_display(display);

    al_shutdown_font_addon();
    al_shutdown_ttf_addon();
    al_shutdown_image_addon();
    al_shutdown_primitives_addon();

    al_uninstall_keyboard();
}