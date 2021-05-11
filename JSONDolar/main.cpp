/***************************************************************************//**
@file     +main.cpp+
@brief    +Ejemplo práctico de JSON integrado con API sobre el dolar+
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

#include "Client.h" // Incluye la librería NLOHMANN JSON 

//Ya que vamos a usar la librería NLOHMANN JSON 
using json = nlohmann::json;

using namespace std;
/*******************************************************************************
* CONSTANT AND MACRO DEFINITIONS USING #DEFINE
******************************************************************************/
//API de https://github.com/Castrogiovanni20/api-dolar-argentina
#define DOFICIAL    "https://api-dolar-argentina.herokuapp.com/api/dolaroficial"
#define DBLUE       "https://api-dolar-argentina.herokuapp.com/api/dolarblue"
#define DCCL        "https://api-dolar-argentina.herokuapp.com/api/contadoliqui"
#define DTURISTA    "https://api-dolar-argentina.herokuapp.com/api/dolarturista"

#define EXTRA   "https://www.dolarsi.com/api/api.php?type=valoresprincipales"

#define OLDPATH    "JSONS/oldDolar.json" 

/*******************************************************************************
*******************************************************************************
    GLOBAL FUNCTION DEFINITIONS
*******************************************************************************
******************************************************************************/
int main(void) {
    string dTypes[] = { "dolarOficial", "dolarBlue", "dolarCCL", "dolarTurista" };
    double dPrices[] = { 89.5,155.0,142.3,147.7 };     //Precios al 04/01/2021 ordenados como dTypes
    string query[] = { DOFICIAL, DBLUE, DCCL, DTURISTA } ;

/******************************************************************************
* CREAMOS UN JSON
******************************************************************************/
    // Cargamos datos de diferentes formas
    // Lo guardamos como un archivo .json

    // Cargamos los datos de principio de año para comparar con los actuales
    json jd;
    // Creamos un objeto vacio
    jd["dolar"] = json::object();
    
    // ------------------------------------------------------------------------------------- //
    //EJEMPLO 1
    // Cargamos algunos datos tipo KEY-VALUE
    jd["dolar"] = { {"fecha", "04/01/2021"} , {"link", "https://www.roadshow.com.ar/dolar-hoy-a-cuanto-cotiza-el-lunes-4-de-enero-de-2021/#:~:text=D%C3%B3lar%20hoy%3A%20a%20cu%C3%A1nto%20cotiza%20el%20lunes%204%20de%20enero%20de%202021,-0&text=84%2C70%20pesos."} };
    //EJEMPLO 2
    // Veamos como creamos otro objeto llamado test y notamos una manera distinta de cargar pares key value
    jd["test"] = "{ \"inflacion\": true, \"estabilidad\": null, \"pi para ingenieros\": 3 }"_json;
    
    // ------------------------------------------------------------------------------------- //
    // Creamos un objeto dentro del objeto
    json data;
    data = json::object();
    for (int i = 0; i < 4; i++) {
        data[dTypes[i]] = dPrices[i];   //Vamos cargando el objeto data con los pares key value
    }
    //Cargamos el objeto data a dolar -> prices 
    jd["dolar"]["prices"].push_back(data);

    // ------------------------------------------------------------------------------------- //
    cout << "JSON TERMINADO:" << endl;
    // Forma linda de imprimir un JSON
    cout << setw(4) << jd << endl;   //Para imprimir el json de forma "linda"
    // Forma string de imprimir un JSON
    //cout << jd.dump() << endl;
    cout << endl;

    // ------------------------------------------------------------------------------------- //
    // Guardamos el JSON creado
    ofstream outputFile(OLDPATH, std::ios::out | std::ios::binary);
    outputFile << jd.dump() << endl;    //Lo guardamos como string
    outputFile.close();
    cout << endl;

/******************************************************************************
* MEDIANDE UNA API BUSCAMOS EL PRECIO ACTUAL Y COMPARAMOS CON EL GUARDADO
******************************************************************************/
    // Creamos un dato tipo json donde se guardarán los datos a descargar
    json j;
    // Creamos un dato tipo json donde se para leer el json guardado previamente
    json jd2;

    // ------------------------------------------------------------------------------------- //
    // Abrimos el archivo previamente guardado y se lo asignamos a jd2
    ifstream oldDolar = ifstream(OLDPATH);  //Abrimos el archivo
    if (!oldDolar.good()) {
        cout << "An error occurred, failed loading the file" << endl;
        return -1;
    }
    // Lo guardamos como json
    //EJEMPLO 1
    oldDolar >> jd2;
    //EJEMPLO 2
    //jd2.parse(oldDolar);
    oldDolar.close();   // Cerramos el archivo
    //Pequeño mensaje para iniciar la comparacion
    cout << "\nVariacion del dolar desde el " << jd2["dolar"]["fecha"] << " hasta la fecha" << endl;

    // ------------------------------------------------------------------------------------- //
    //Descargarmos y guardamos los 4 tipos de dolar 
    for (int i = 0; i < 4; i++) {
        if (!client(query[i], j)) { //Cliente con libCurl
            cout << "Error in downloading JSON" << endl;
        }
        else {
            // Guardamos el JSON obtenido de la API
            string path = "JSONS/";
            path.append(dTypes[i]);
            path.append(".json");
            std::ofstream file(path, std::ios::out | std::ios::binary);
            if (file.is_open()) {
                file << j;
                file.close();
            }
            else
                std::cout << "Unable to open file " << std::endl;

            // ------------------------------------------------------------------------------------- //
            // Comparamos e indicamos el precio actual y la diferencia con el de principio de año
           
            // El path debajo sería: el objeto "dolar" que tiene varias key, pero queremos la key "prices"
            //luego si notamos en el json se guardo como arreglo, entonces queremos el 0 (el único que hay) 
            //para finalmente pedir el key "dTypes" y nos devuelva el value del precio
            double oldP = jd2["dolar"]["prices"][0][dTypes[i]];
            //Convertimos el string del precio nuevo a float
            string temp = j["venta"];
            double newP = stof(temp);   
            //Calculamos la diferencia en %
            double perc = (((newP*100.0)/oldP) - 100);   

            std::cout << std::setprecision(2) << std::fixed; //Ajustamos el cout para dos decimales

            // Imprimimos el resultado
            cout << endl;
            cout << "Tipo: " << dTypes[i] << endl;
            cout << "Precio actual: " << j["venta"] << endl;
            cout << "Precio viejo: " << jd2["dolar"]["prices"][0][dTypes[i]] << endl;
            cout << "Variacion " << perc << "%" << endl;
            cout << endl;

        }

    }
    getchar();
    cout << "See you next time..." << endl;
    return 0;
}