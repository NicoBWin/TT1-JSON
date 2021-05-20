/***************************************************************************//**
@file     +Client.cpp+
@brief    +Funciones para descargar los JSON+
@author   +Nicolás Bustelo+
******************************************************************************/

/*******************************************************************************
* INCLUDE HEADER FILES
******************************************************************************/
#include "Client.h"

//Vamos a usar la biblioteca NLOHMANN JSON 
using json = nlohmann::json;
/*******************************************************************************
* FUNCTION PROTOTYPES FOR PRIVATE FUNCTIONS WITH FILE LEVEL SCOPE
******************************************************************************/
static size_t myCallback(void* contents, size_t size, size_t nmemb, void* userp);

/*******************************************************************************
*******************************************************************************
    				GLOBAL FUNCTION DEFINITIONS
*******************************************************************************
******************************************************************************/
bool client(std::string query, json& j) {
	// Vamos a utilizar la librería CURL ya que debemos conectarons a un servidor HTTPS
	// (HTTP seguro) el cual requeire un protocolo especial de encriptación
	CURL* curl;					//Variable donde vamos a guardar las configuraciones de una transferencia
	CURLM* multiHandle;			//Variable donde vamos a atachear los easy handles
	CURLcode res;
	std::string readString;

	/************************************************************************************
	*									GET THE JSON									*
	************************************************************************************/
	// Inicializo todo curl.
	res = CURLE_OK;
	curl = curl_easy_init();
	multiHandle = curl_multi_init();
	readString = "";
	int stillRunning = 0;
	if ((curl != NULL) & (multiHandle != NULL)) {
		//Attacheo el easy handle para manejar una coneccion no bloqueante.
		curl_multi_add_handle(multiHandle, curl);

		//Seteamos URL FOLLOWLOCATION y los protocolos a utilizar.
		curl_easy_setopt(curl, CURLOPT_URL, query.c_str());
		curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
		curl_easy_setopt(curl, CURLOPT_PROTOCOLS, CURLPROTO_HTTP | CURLPROTO_HTTPS);

		//Seteamos el callback
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, myCallback);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readString);

		//Realizamos ahora un perform no bloqueante
		curl_multi_perform(multiHandle, &stillRunning);
		while (stillRunning) {
			//Debemos hacer polling de la transferencia hasta que haya terminado
			curl_multi_perform(multiHandle, &stillRunning);

			//Mientras tanto podemos hacer otras cosas
		}

		//Checkeamos errores
		if (res != CURLE_OK) {
			std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
			//Hacemos un clean up de curl antes de salir.
			curl_easy_cleanup(curl);
			return false;
		}

		//Siempre realizamos el cleanup al final
		curl_easy_cleanup(curl);

		//Si el request de CURL fue exitoso entonces la API devuelve un JSON
		//con toda la informacion que le pedimos
		j = json::parse(readString);
	}
	else
		std::cout << "Cannot download tweets. Unable to start cURL" << std::endl;

	return true;	//TODO FUE EXITOSO
}


/*******************************************************************************
*******************************************************************************
        LOCAL FUNCTION DEFINITIONS
*******************************************************************************
******************************************************************************/
//Concatena lo recibido en content a s
static size_t myCallback(void* contents, size_t size, size_t nmemb, void* userp) {
	size_t realsize = size * nmemb;
	char* data = (char*)contents;
	//fprintf(stdout, "%s",data);
	std::string* s = (std::string*)userp;
	s->append(data, realsize);
	return realsize;						//recordar siempre devolver realsize
}
