/***************************************************************************//**
@file     +Allegro.h+
@brief    +Header con las funciones para usar Allegro+
@author   +Nicolás Bustelo+
******************************************************************************/

#ifndef _ALLEGRO_H_
#define _ALLEGRO_H_

/*******************************************************************************
* INCLUDE HEADER FILES
******************************************************************************/
#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>

/*******************************************************************************
* CONSTANT AND MACRO DEFINITIONS USING #DEFINE
******************************************************************************/
#define FONT_FILE	"resources/font.ttf"
#define BKG_FILE	"resources/weather.jpg"

#define W_PIXELS	759
#define H_PIXELS	520

/*PUNTEROS ALLEGRO*/
extern ALLEGRO_DISPLAY* display;
extern ALLEGRO_EVENT_QUEUE* event_queue;
extern ALLEGRO_FONT* font1;
extern ALLEGRO_BITMAP* bkg;

/*******************************************************************************
* FUNCTION PROTOTYPES WITH GLOBAL SCOPE
******************************************************************************/
//Funcion que le da la bienvenida al usuario por allegro
int init_allegro();

//Funcion que destruye todo allegro, no recibe nada y no devuelve nada
void destroy_allegro(void);

//Dibuja la interface
void draw_interface();


/*******************************************************************************
******************************************************************************/

#endif // _ALLEGRO_H_
