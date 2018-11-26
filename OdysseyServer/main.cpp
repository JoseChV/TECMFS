//Creado por Bradly Valverde F.
//Referencia utilizada para la creacion del cliente: https://www.geeksforgeeks.org/socket-programming-cc/

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <fstream>

#include "rapidjson/document.h"
#include "rapidjson/prettywriter.h"
#include "rapidxml/rapidxml.hpp"



#include <string>

using namespace rapidxml;
using namespace rapidjson;

using namespace std;

#include <arpa/inet.h>
#define PORT 8170//puerto a conectar



int ubicacion = 0;// Variable para guardar los MPointers en su lugar correspondiente

int main() {

    cout << "Inicializando MPointer_init" << endl;




    struct sockaddr_in address;//Direccion a la que se conecta el cliente
    int sock = 0, valread; //socket y variable para leer el mensaje del servidor
    struct sockaddr_in serv_addr;//Direccion en la que está el servidor

    //Metodo para crear el socket y su descriptor y metodo para verificar que se cree correctamente
    //Se utiliza para acceder a recursos de entrada y salida de un sistemas
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\n Socket creation error \n");
        return -1;
    }
    //Pone el primer numero de bytes de memoria por el puntero a un valor especifico
    memset(&serv_addr, '0', sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;//Dice de que tipo sera el direccion
    serv_addr.sin_port = htons(PORT);//Pasa el puerto en el que se encuentra el servidor

    // convierte las direcciones de IPv4 y IPv6 de texto a forma binaria
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }

    //Conecta al socket refenciando por el descriptor sockfd a una direccion especificada
    if (connect(sock, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        printf("\nConnection Failed \n");
        return -1;
    }


    int decision = 0;// variable para saber ver que quiere hacer el cliente


    char buffer[1024];// buffer que almacenará el mensaje proveniente del servidor


    cout << "¿Que desea hacer?" << endl;
    cout << "1: Subir un video" << endl;
    cout << "2: Modificar metadata" << endl;
    cout << "3: Eliminar video" << endl;
    cout << "4: Buscar video" << endl;
    cout << "5: Enviar un video" << endl;

    cin >> decision;

    //Crea un nuevo pointer y almacena sus datos
    if (decision == 1) {

        cout << "Escribe la fecha del video" << endl;
        string fecha;
        cin >> fecha;
        cout << "Escribe el director del video" << endl;
        string director;
        cin >> director;
        cout << "Escribe la descripcion del video" << endl;
        string descripcion;
        cin >> descripcion;
        cout << "Escribe el nombre del video" << endl;
        string nombre;
        cin >> nombre;
        cout << "Escribe la duracion del video" << endl;
        string duracion ;
        cin >> duracion;

        const char* a = fecha.c_str();
        const char* b = director.c_str();
        const char* c = descripcion.c_str();
        const char* d = nombre.c_str();
        const char* e = duracion.c_str();
        //JSON
        const char *SendJson = "{\"code\": 1 ,\n"
                           "    \"fecha\": \"nada\",\n"
                           "    \"director\": \"nada\",\n"
                           "    \"descripcion\": \"nada\",\n"
                           "    \"nombre\": \"nada\",\n"
                           "    \"duracion\": \"nada\" }";

//        cout << SendJson << endl;


        Document JSON;//Crea un documento JSON del header RAPIDJson
        JSON.Parse(SendJson);

        Value &nodeF = JSON["fecha"];
        nodeF.SetString(a, strlen(a));

        Value &nodeDI = JSON["director"];
        nodeDI.SetString(b, strlen(b));

        Value &nodeD = JSON["descripcion"];
        nodeD.SetString(c, strlen(c));

        Value &nodeN = JSON["nombre"];
        nodeN.SetString(d, strlen(d));

        Value &nodeDU = JSON["duracion"];
        nodeDU.SetString(e, strlen(e));

        StringBuffer json;
        Writer <StringBuffer> writer(json);
        JSON.Accept(writer);

        char path [60];

        strcpy(path,"C:/Users/Ba/Desktop/DataBase/");
        strcat(path, JSON["nombre"].GetString());
        strcat(path, ".json");

        ofstream myfile;
        myfile.open(path);
        myfile << json.GetString();
        myfile.close();

//        cout << json.GetString() << endl;

        send(sock, json.GetString(), strlen(json.GetString()), 0);//Envia el socket a el servidor

        printf("Se envio una solicitud para subir un video\n");

        valread = read(sock, buffer, 1024);//lee el mensaje del servidor y lo almacena en el buffer


        Document NewJSON;//Crea un documento JSON del header RAPIDJson
        NewJSON.Parse(buffer);//Parsea el JSON

        assert(NewJSON["code"].IsNumber());
        assert(NewJSON["code"].IsInt());

        int code = NewJSON["code"].GetInt();

        if (code == 1){
            cout << "envia la mica" << endl;
        }


    } else if (decision == 2) {
        const char *Json =  "{\"code\": 2 ,\n"
                                "    \"fecha\": \"nada\",\n"
                                "    \"director\": \"nada\",\n"
                                "    \"descripcion\": \"nada\",\n"
                                "    \"nombre\": \"nada\",\n"
                                "    \"duracion\": \"nada\" }";

        cout << "Escribe el nombre del video al que le desea cambiar la metadata" << endl;
        string nombre;
        cin >> nombre;

        const char* a = nombre.c_str();

        cout << "Escribe la fecha del video" << endl;
        string fecha;
        cin >> fecha;
        cout << "Escribe el director del video" << endl;
        string director;
        cin >> director;
        cout << "Escribe la descripcion del video" << endl;
        string descripcion;
        cin >> descripcion;
        cout << "Escribe la duracion del video" << endl;
        string duracion ;
        cin >> duracion;

        const char* b = fecha.c_str();
        const char* c = director.c_str();
        const char* d = descripcion.c_str();
        const char* e = duracion.c_str();

        Document JSON;
        JSON.Parse(Json);

        Value &nodeN = JSON["nombre"];
        nodeN.SetString(a, strlen(a));

        Value &nodeF = JSON["fecha"];
        nodeF.SetString(b, strlen(b));

        Value &nodeDI = JSON["director"];
        nodeDI.SetString(c, strlen(c));

        Value &nodeD = JSON["descripcion"];
        nodeD.SetString(d, strlen(d));

        Value &nodeDU = JSON["duracion"];
        nodeDU.SetString(e, strlen(e));

        StringBuffer newJson;
        Writer<StringBuffer> writer(newJson);
        JSON.Accept(writer);


        char path [60];

        strcpy(path,"C:/Users/Ba/Desktop/DataBase/");
        strcat(path, JSON["nombre"].GetString());
        strcat(path, ".json");

        ofstream myfile;
        myfile.open(path);
        myfile << newJson.GetString();
        myfile.close();


        //Se imprimen los valores en memoria en la terminal del servidor
    } else if (decision == 3) {
        const char *SendJson = "{\"code\": 3 ,\n"
                           "    \"fecha\": \"nada\",\n"
                           "    \"director\": \"nada\",\n"
                           "    \"descripcion\": \"nada\",\n"
                           "    \"nombre\": \"nada\",\n"
                           "    \"duracion\": \"nada\" }";

        cout << "Escribe el nombre del video al que le desea eliminar" << endl;
        string nombre;
        cin >> nombre;

        const char* a = nombre.c_str();

        Document JSON;
        JSON.Parse(SendJson);

        Value &nodeN = JSON["nombre"];
        nodeN.SetString(a, strlen(a));

        StringBuffer newJson;
        Writer<StringBuffer> writer(newJson);
        JSON.Accept(writer);

        send(sock, newJson.GetString(), strlen(newJson.GetString()), 0);

        printf("Se envio una solicitud para eliminar un video\n");

        //Se pide la memoria restante que hay en el servidor a manera de bytes
    } else if (decision == 4) {
        cout << "revisa si el video existe"<< endl;

        //Imprime los valores de los Mpointers almacenados con su respectivo id
    } else if (decision == 5) {


        cout << "le manda un video a cliente"<< endl;
        //Decision para cerrar la conexion
    }else if (decision == 6){
        const char *json = "{\"code\": 4 ,\n"
                           "    \"valores\": \"nada\",\n"
                           "    \"id\": 0,\n"
                           "    \"memoria\": 0,\n"
                           "    \"valor\": 0}";

        send(sock, json, strlen(json), 0);
        printf("Se cerrará la conexion\n");
        return 0;
    }

    main();


}