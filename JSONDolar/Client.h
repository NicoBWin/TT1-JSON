/***************************************************************************//**
@file     +Client.h+
@brief    +Header con las funciones para descargar los JSON+
@author   +Nicol�s Bustelo+
******************************************************************************/

#ifndef _CLIENT_H_
#define _CLIENT_H_

/*******************************************************************************
* INCLUDE HEADER FILES
******************************************************************************/
#include <iostream>
#include <exception>
#include <fstream>
#include <list>
#include <curl/curl.h>
#include <nlohmann/json.hpp>

//Vamos a usar la librer�a NLOHMANN JSON 
using json = nlohmann::json;
/*******************************************************************************
* CONSTANT AND MACRO DEFINITIONS USING #DEFINE
******************************************************************************/



/*******************************************************************************
* ENUMERATIONS AND STRUCTURES AND TYPEDEFS
******************************************************************************/


/*******************************************************************************
* VARIABLE PROTOTYPES WITH GLOBAL SCOPE
******************************************************************************/

// +ej: extern unsigned int anio_actual;+


/*******************************************************************************
* FUNCTION PROTOTYPES WITH GLOBAL SCOPE
******************************************************************************/
//Funci�n que descarga los json
//Recibe el query y el json por referencia y guarda lo descargado ah�
//Devuelve en su nombre �true� si descarg� correctamente o �false" en caso contrario.
bool client(std::string query, json& j);


/*******************************************************************************
******************************************************************************/

#endif // _CLIENT_H_