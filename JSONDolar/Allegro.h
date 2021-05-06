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
#define FONT1_FILE "fonts/font.ttf"

#define W_PIXELS	900
#define H_PIXELS	900

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
