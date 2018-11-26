//Creado por Bradly Valverde F.
//Referencia utilizada para la creacion del servidor: https://www.geeksforgeeks.org/socket-programming-cc/

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>
#include <string.h>
#include <stdlib.h>
#include <fstream>
#include "rapidjson/document.h"
#include "rapidjson/prettywriter.h"
#include "rapidxml/rapidxml.hpp"

using namespace rapidxml;
using namespace rapidjson;
using namespace std;


#define PORT 8170//puerto a conectar

int main(int argc, char const *argv[])
{


    int server_fd, new_socket, valread;//sockets y variable para leer el mensaje del servidor
    struct sockaddr_in address;//Direccion a la que se conecta el servidor
    int opt = 1;
    int addrlen = sizeof(address);//Largo de la direccion



    int* memory = (int*) malloc(5 * sizeof(int));//El unico malloc del programa donde se almacenaran
    //los datos de los Mpointers

    int totalMemory =  5 * sizeof(int);//Memoria restante

    // //Metodo para crear el socket y su descriptor y metodo para verificar que se cree correctamente
    //Se utiliza para acceder a recursos de entrada y salida de un sistemas
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }



    address.sin_family = AF_INET;//Dice de que tipo sera el direccion
    address.sin_addr.s_addr = INADDR_ANY;//Conecta a la direccion local
    address.sin_port = htons( PORT );//Pasa el puerto donde se va a conectar

    // Fuerza al socket a conectarse al puerto antes referenciado
    if (bind(server_fd, (struct sockaddr *)&address,
             sizeof(address))<0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    //Metodo que pone al servidor en un estado pasivo esperando a que algun cliente se conecte con el
    if (listen(server_fd, 3) < 0)
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    int id = 0;

    while(true) {
        char buffer[1024] = {0};

        //extrae la primera conexion con el cliente, crea un new socket de conexion y retorna un decriptor referenciandolo
        if ((new_socket = accept(server_fd, (struct sockaddr *) &address,
                                 (socklen_t *) &addrlen)) < 0) {
            perror("accept");
            exit(EXIT_FAILURE);
        }



        valread = read(new_socket, buffer, 1024);//lee el mensaje del servidor y lo almacena en el buffer


        Document JSON;//Crea un documento JSON del header RAPIDJson
        JSON.Parse(buffer);//Parsea el buffer
        assert(JSON["code"].IsNumber());//Confirma si la referencia del JSON el es valor esperado

        assert(JSON["code"].IsInt());

        printf("code = %d\n", JSON["code"].GetInt());//obtiene su valor su el assert fue correcto

        int code = JSON["code"].GetInt();


        //Parte en la que se solicita memoria y se guarda el valor en el heap, ademas resta la cantidad memoria total para almacenar
        if (code == 1) {




            const char *SendJson = "{\"code\": 1}";

            send(new_socket, SendJson, strlen(SendJson), 0);
            cout << "Recibe el video" << endl;

        }
            //Cambia los valores en el heap dependiendo del id que se mande desde el cliente
        else if (code == 2)
        {
//
//
//            assert(JSON["id"].IsNumber());
//            assert(JSON["id"].IsInt());
//
//            int selectID = JSON["id"].GetInt();
//
//
//
//            if (JSON["id"].GetInt() < id && JSON["id"].GetInt() > -1) {
//
//                cout << "MPointer con valor ID: " << selectID << endl;
//
//                assert(JSON["valor"].IsNumber());
//                assert(JSON["valor"].IsInt());
//
//                int selectValor = JSON["valor"].GetInt();
//
//                cout << "Cambiado por: " << selectValor << endl;
//
//                memory[selectID] = selectValor;
//
//
//
//            } else {
//                cout << "No se puede almacenar un valor con ese ID porque no existe Mpointer con el mismo"  << endl;
//            }
        }
            //Printea todos los valores en la memoria con su respectivo id
        else if (code == 3)
        {

         cout << "eliminar video"<< endl;

         string video = JSON["nombre"].GetString();

        }
            //Envia la memoria restante al cliente
        else if (code == 4)
        {
//            Value& node = JSON["memoria"];
//            node.SetInt(totalMemory);
//
//            StringBuffer newJson;
//            Writer<StringBuffer> writer(newJson);
//            JSON.Accept(writer);
//
//            send(new_socket, newJson.GetString(), strlen(buffer), 0);
        }
            //Decision para cerrar la conexion
        else{
//            free(memory);
//            return 0;
        }


    }
}
