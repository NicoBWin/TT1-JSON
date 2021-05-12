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
#include <curl/curl.h>
#include <nlohmann/json.hpp>

/*******************************************************************************
* FUNCTION PROTOTYPES WITH GLOBAL SCOPE
******************************************************************************/
//Funci�n que descarga los json  
//Recibe el query y el json por referencia y guarda lo descargado ah�
//Devuelve en su nombre �true� si descarg� correctamente o �false" en caso contrario.
bool client(std::string query, nlohmann::json& j);

/*******************************************************************************
******************************************************************************/

#endif // _CLIENT_H_