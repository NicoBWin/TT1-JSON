/***************************************************************************//**
@file     +main.cpp+
@brief    +Mostrar el precio actual del Dolar+
@version  +1.0+
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


//https://www.roadshow.com.ar/dolar-hoy-a-cuanto-cotiza-el-lunes-4-de-enero-de-2021/#:~:text=D%C3%B3lar%20hoy%3A%20a%20cu%C3%A1nto%20cotiza%20el%20lunes%204%20de%20enero%20de%202021,-0&text=84%2C70%20pesos.
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
    if (!init_allegro()) {  //Iniciamos la pequeña interfaz para imprimir los datos
        cout << "Error in allegro inicialization" << endl;
        return 0;
    }
    string pathD[] = { "dolarOficial", "dolarBlue", "dolarCCL", "dolarTurista" };

    //Cargar datos en formato JSON
    //Cargamos los datos de principio de año para comparar con los actuales
    json jd;

    //Creamos un objeto
    jd["dolar"] = json::object();
    //Cargamos algunos datos tipo KEY-VALUE
    jd["dolar"] = { {"fecha", "04/01/2021"} , {"link", "https://www.roadshow.com.ar/dolar-hoy-a-cuanto-cotiza-el-lunes-4-de-enero-de-2021/#:~:text=D%C3%B3lar%20hoy%3A%20a%20cu%C3%A1nto%20cotiza%20el%20lunes%204%20de%20enero%20de%202021,-0&text=84%2C70%20pesos."} };

    //Creamos un array dentro del objeto
    //json data = json::array(); // Not necessary, but to show that you can declare empty Object or Array with json::...()
    //data["name"] = pathD[i];
    //data["languages"] = { "C++", "C", "Assembler", "Python", "JavaScript", "C#", "TypeScript" };

    // Guardamos el JSON creado
    ofstream outputFile;
    outputFile = ofstream("JSONS/oldDolar.json");
    outputFile << jd.dump() << endl;    //Lo guardamos como string
    outputFile.close();
    cout << endl;

    // -------------------------------------------------------------------------------------//
    json j;
    string query[] = { DOFICIAL, DBLUE, DCCL, DTURISTA } ;
    //Descargar y guardar todos los tipos de dolar
    for (int i = 0; i < 4; i++) {
        if (!client(query[i], j)) {
            cout << "Error in downloading JSON" << endl;
        }
        else {
            //Save file as json format
            string path = "JSONS/";
            path.append(pathD[i]);
            path.append(".json");
            std::ofstream file(path, std::ios::out | std::ios::binary);
            if (file.is_open()) {
                file << j;
                file.close();
            }
            else
                std::cout << "Unable to open file " << std::endl;
        }
    }

    //std::cout << "DOLAR BLUE\n" << std::endl;
    //for (auto& it : j.items())
    //    std::cout << it.key() << ": " << it.value() << std::endl;

    cout << setw(4) << j << endl;   //Para imprimir el json de forma "linda"
    getchar();

    destroy_allegro();
}


/*******************************************************************************
*******************************************************************************
        LOCAL FUNCTION DEFINITIONS
*******************************************************************************
******************************************************************************/

