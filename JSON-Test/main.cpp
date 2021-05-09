/***************************************************************************//**
@file     +main.cpp+
@brief    +Mostrar el precio actual del Dolar+
@author   +Nicolás Bustelo+
******************************************************************************/

/*******************************************************************************
* INCLUDE HEADER FILES
******************************************************************************/
#include <iostream>
#include <string>
#include <fstream>
#include <list>
#include <exception>
#include <sstream>
#include <iomanip>
#include <nlohmann/json.hpp>
//Vamos a usar la librería NLOHMANN JSON 
using json = nlohmann::json;

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

/*******************************************************************************
* FUNCTION PROTOTYPES FOR PRIVATE FUNCTIONS WITH FILE LEVEL SCOPE
******************************************************************************/

/*******************************************************************************
* ROM CONST VARIABLES WITH FILE LEVEL SCOPE
******************************************************************************/

/*******************************************************************************
* STATIC VARIABLES AND CONST VARIABLES WITH FILE LEVEL SCOPE
******************************************************************************/

/*******************************************************************************
*******************************************************************************
    GLOBAL FUNCTION DEFINITIONS
*******************************************************************************
******************************************************************************/
int main(void) {
    json j;
    std::fstream fs;
    fs.open("twittLN.json", std::fstream::in);
    fs >> j;


    if (j.is_object()) {
        std::cout << "es objeto" << std::endl;
    }

    if (j.is_array()) {
        std::cout << "es array" << std::endl;
    }

    //cout << j << endl;

    std::cout << std::endl;

    //j = j.array();
    j = j[1];
    std::cout << std::setw(4) << j << std::endl;

    //for (auto& it : j.items()) {
    //    if (it.key() == "1") {
    //        json valores = it.value();
    //        std::cout << "Date:" << valores["created_at"] << std::endl;
    //        std::cout << "Tweet:" << valores["text"] << std::endl;
    //        valores = valores["user"];
    //        std::cout << "User:" << valores["name"] << std::endl;
    //    }
    //}
    getchar();
}