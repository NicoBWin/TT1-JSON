#include <iostream>
#include <exception>
#include <fstream>
#include <list>
#include <curl/curl.h>
#include <nlohmann/json.hpp>

//Vamos a usar la librer�a NLOHMANN JSON 
using json = nlohmann::json;

//Funciones auxiliares
void printNames(std::list<std::string> names);
static size_t myCallback(void* contents, size_t size, size_t nmemb, void* userp);

/*
* Main de prueba.
* Obtiene twits de una cuenta p�blica (en este caso, los �ltimos 10 twits de La Naci�n)
*
*/

int main(void)
{
	json j;                    //Variable donde vamos a guardar lo que devuelva Twitter

	// Vamos a utilizar la librer�a CURL ya que debemos conectarons a un servidor HTTPS
	// (HTTP seguro) el cual requeire un protocolo especial de encriptaci�n
	// m�s complejo que el plain HTTP que utilizamos en el TP de Networking.

	CURL* curl;					//Variable donde vamos a guardar las configuraciones de una transferencia
	CURLM* multiHandle;			//Variable donde vamos a atachear los easy handles
	CURLcode res;
	std::string readString, token;

	// Query es la direcci�n de Twitter que vamos a consultar. vamos a bajar los &count twits de screen_name en formato JSON.
	std::string query2 = "https://www.dolarsi.com/api/api.php?type=valoresprincipales";
	std::string query = "https://api-dolar-argentina.herokuapp.com/api/dolarblue";

	std::string names;

	/************************************************************************************
	*									GET DE DOLAR									*
	************************************************************************************/
	// Nuevamente reinicializo todo curl.
	res = CURLE_OK;
	curl = curl_easy_init();
	multiHandle = curl_multi_init();
	readString = "";
	int stillRunning = 0;
	if ((curl != NULL) & (multiHandle != NULL))
	{
		//Attacheo el easy handle para manejar una coneccion no bloqueante.
		curl_multi_add_handle(multiHandle, curl);

		//Seteamos URL FOLLOWLOCATION y los protocolos a utilizar igual que antes.
		curl_easy_setopt(curl, CURLOPT_URL, query2.c_str());
		curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
		curl_easy_setopt(curl, CURLOPT_PROTOCOLS, CURLPROTO_HTTP | CURLPROTO_HTTPS);


		//Seteamos los callback igual que antes
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, myCallback);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readString);

		//Realizamos ahora un perform no bloqueante
		curl_multi_perform(multiHandle, &stillRunning);
		while (stillRunning)
		{
			//Debemos hacer polling de la transferencia hasta que haya terminado
			curl_multi_perform(multiHandle, &stillRunning);

			//Mientras tanto podemos hacer otras cosas
		}

		//Checkeamos errores
		if (res != CURLE_OK)
		{
			std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
			//Hacemos un clean up de curl antes de salir.
			curl_easy_cleanup(curl);
			return 0;
		}

		//Siempre realizamos el cleanup al final
		curl_easy_cleanup(curl);

		//Si el request de CURL fue exitoso entonces twitter devuelve un JSON
		//con toda la informacion de los tweets que le pedimos
		j = json::parse(readString);

		//Save all twetts as json format
		std::ofstream file("JSONS/dolar.json", std::ios::out | std::ios::binary);
		if (file.is_open()) {
			file << j;
			file.close();
		}
		else {
			std::cout << "Unable to open file " << std::endl;
		}
		
		std::cout << "DOLAR BLUE" << std::endl;
		for (auto& it : j.items())
		{
			if (it.key() == "1") {
				json valores = it.value();
				valores = valores["casa"];
				std::cout << valores["venta"] << std::endl;
				//std::cout << it.key() << ": " << it.value() << std::endl;
			}
		}

	}
	else
		std::cout << "Cannot download tweets. Unable to start cURL" << std::endl;


	getchar();
	return 0;
}


//Funcion auxiliar para imprimir los tweets en pantalla una vez parseados
void printNames(std::string names)
{
	names.append("...");
		std::cout << names << std::endl;
		std::cout << "-----------------------------------------" << std::endl;
}

//Concatena lo recibido en content a s
static size_t myCallback(void* contents, size_t size, size_t nmemb, void* userp)
{
	size_t realsize = size * nmemb;
	char* data = (char*)contents;
	//fprintf(stdout, "%s",data);
	std::string* s = (std::string*)userp;
	s->append(data, realsize);
	return realsize;						//recordar siempre devolver realsize
}