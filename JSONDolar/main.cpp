/***************************************************************************//**
@file     +main.cpp+
@brief    +Mostrar el precio actual del Dolar+
@author   +Nicolás Bustelo+
******************************************************************************/

/*******************************************************************************
* INCLUDE HEADER FILES
******************************************************************************/
#include <iostream>

#include "Client.h"
#include "Allegro.h"


using namespace std;
/*******************************************************************************
* CONSTANT AND MACRO DEFINITIONS USING #DEFINE
******************************************************************************/
//API de https://github.com/Castrogiovanni20/api-dolar-argentina

#define DOFICIAL    "https://api-dolar-argentina.herokuapp.com/api/dolarblue"
#define DBLUE       "https://api-dolar-argentina.herokuapp.com/api/dolarblue"
#define DCCL        "https://api-dolar-argentina.herokuapp.com/api/contadoliqui"
#define DTURISTA    "https://api-dolar-argentina.herokuapp.com/api/dolarturista"

#define EXTRA   "https://www.dolarsi.com/api/api.php?type=valoresprincipales"

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
    if (!init_allegro()) {
        cout << "Error in allegro inicialization" << endl;
    }
    string query;
    json j;
    query = DOFICIAL;
    if (!client(query, j)) {
        cout << "Error in downloading JSON" << endl;
    }
    getchar();

    destroy_allegro();
}


/*******************************************************************************
*******************************************************************************
        LOCAL FUNCTION DEFINITIONS
*******************************************************************************
******************************************************************************/

