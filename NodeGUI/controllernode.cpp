
//
// Created by jose on 21/11/18.
//

#include "ControllerNode.h"
#include <cstring>
void ControllerNode::saveToDiskNodes(char* name) {
    FILE *d3, *d2, *d1, *file;
    char *buffer = new char[1];

    //Open video file
    char* path = "/home/kevinfgn/Qt Projects/NodeGUI/";
    char* disk1 = "/home/kevinfgn/Disk1";
    char* disk2 = "/home/kevinfgn/Disk2";
    char* disk3 = "/home/kevinfgn/Disk3";
    char* mp4 = ".mp4";
    const char* realFile = setPath(path,name,mp4);
    file = fopen(realFile, "rb");

    if(file){

        //Create bin file 1
        char* b1 = "1.bin";
        char* write = "wb";
        realFile = setPath(disk1, name, b1);
        d1 = fopen(realFile, write);

        //Create bin file 2
        char* b2 = "2.bin";
        realFile = setPath(disk2, name, b2);
        d2 = fopen(realFile, write);

        //Create bin file 3
        char* b3 = "3.bin";
        realFile = setPath(disk3, name, b3);
        d3 = fopen(realFile, write);

        int contParidad = 3;
        int cont = 1;

        char firstBuffer;
        char secondBuffer;

        char* firstBufferPtr = nullptr;
        char* secondBufferPtr = nullptr;

        char XOR;
        char* XORptr;

        while (1) {

            if (firstBufferPtr != nullptr && secondBufferPtr != nullptr) {
                XOR = *firstBufferPtr ^ *secondBufferPtr;
                firstBufferPtr = nullptr;
                secondBufferPtr = nullptr;
                size_t XORbyte = sizeof(XOR);
                XORptr = &XOR;
                if (contParidad == 3) {
                    //write XOR D3
                    fwrite(XORptr, 1, XORbyte, d3);
                } else if (contParidad == 2) {
                    //write XOR D2
                    fwrite(XORptr, 1, XORbyte, d2);
                } else {
                    //write XOR D1
                    fwrite(XORptr, 1, XORbyte, d1);
                }
                contParidad--;
                if (contParidad == 0) {
                    contParidad = 3;
                    cont = 0;
                }

            }else{

                size_t bytesRead = fread(buffer, 1, sizeof(buffer), file);

                if(cont == contParidad){
                    cont++;
                }
                if(cont == 4){
                    cont = 1;
                }
                if (cont == 1 && contParidad != 1) {
                    fwrite(buffer, 1, bytesRead, d1);
                } else if (cont == 2 && contParidad != 2) {
                    fwrite(buffer, 1, bytesRead, d2);
                } else if (cont == 3 && contParidad != 3) {
                    fwrite(buffer, 1, bytesRead, d3);
                }
                if (firstBufferPtr == nullptr) {
                    firstBuffer = *buffer;
                    firstBufferPtr = &firstBuffer;
                } else {
                    secondBuffer = *buffer;
                    secondBufferPtr = &secondBuffer;
                }
                if (bytesRead == 0) {
                    break;
                }
            }
            cont++;
            if (cont == 4) {
                cont = 1;
            }
            //if error enviando, print "error en el envio", break
        }

        fclose(d1);
        fclose(d2);
        fclose(d3);
        fclose(file);
    }else{
        cout<<"El mp4 no existe"<<endl;
    }
        ///Mandar files a los discos y borrar los del directorio principal
}
void ControllerNode::readFromDiskNodes(char* name) {
    FILE *d1, *d2, *d3, *video;
    char* path = "/home/kevinfgn/Qt Projects/NodeGUI/";
    char* disk1 = "/home/kevinfgn/Disk1";
    char* disk2 = "/home/kevinfgn/Disk2";
    char* disk3 = "/home/kevinfgn/Disk3";
    char* b1 = "1.bin";
    char* read = "rb";

    char *buffer = new char[1];

    const char* realFile1 = setPath(disk1, name, b1);
    d1 = fopen(realFile1,read);
    char* b2 = "2.bin";
    const char* realFile2 = setPath(disk2, name, b2);
    d2 = fopen(realFile2,read);
    char* b3 = "3.bin";
    const char* realFile3 = setPath(disk3, name, b3);
    d3 = fopen(realFile3,read);

    bool greenLight = false;

    if(d1 && d2 && d3){
        greenLight = true;
    }else if(!d1 && d2 && d3){
        reconstructBin(name, 1);
        const char* recFile = setPath(disk1, name, b1);
        this->saveToDiskNodes(name);
        d1 = fopen(recFile,read);
        greenLight = true;
    }else if(d1 && !d2 && d3){
        greenLight = true;
        reconstructBin(name, 2);
        const char* recFile = setPath(disk2, name, b2);
        this->saveToDiskNodes(name);
        d2 = fopen(recFile,read);
    }else if(d1 && d2 && !d3){
        greenLight = true;
        reconstructBin(name, 3);
        const char* recFile = setPath(disk3, name, b3);
        this->saveToDiskNodes(name);
        d3 = fopen(recFile,read);
    }else{
        //greenLight = false;
        cout<<"Daño irreparable"<<endl;
    }
    if(greenLight){
        char* write = "wb";
        video = fopen("/home/kevinfgn/Qt Projects/NodeGUI/NEWVIDEO.mp4", write);

        int cont = 1;
        bool d1b = true,d2b = true,d3b = true;
        int contParidad = 3;
        char* trash = new char[1];
        while (1) {

            if(cont == 1 && d1b) {
                if(contParidad != 1){
                    size_t bytesRead = 0;
                    bytesRead = fread(buffer, 1, sizeof(buffer), d1); //Leer del bin 1
                    if (bytesRead == 0) {
                        d1b = false;
                        fclose(d1);
                    }
                    fwrite(buffer, 1, bytesRead, video);
                }else{
                    size_t bytesRead = 0;
                    bytesRead = fread(trash, 1, 1, d1);
                }
            }else if(cont == 2 && d2b){
                if(contParidad != 2){
                    size_t bytesRead = 0;
                    bytesRead = fread(buffer, 1, sizeof(buffer), d2); //Leer del bin 2
                    if (bytesRead == 0) {
                        fclose(d2);
                        d2b = false;
                    }
                    fwrite(buffer, 1, bytesRead, video);
                }else{
                    size_t bytesRead = 0;
                    bytesRead = fread(trash, 1, 1, d2);
                }
            }else if(cont == 3 && d3b){
                if(contParidad != 3){
                    size_t bytesRead = 0;
                    bytesRead = fread(buffer, 1, sizeof(buffer), d3); //Leer del bin 3
                    if (bytesRead == 0) {
                        d3b = false;
                        fclose(d3);
                    }
                    fwrite(buffer, 1, bytesRead, video);
                }else{
                    size_t bytesRead = 0;
                    bytesRead = fread(trash, 1, 1, d3);
                }
            }
            if(!d1b && !d2b && !d3b){ //Los 3 bin se leyeron por completo
                fclose(video);
                cout << "file recovered" << endl;
                break;
            }
            cont++;

            if(cont > 3){
                contParidad--;
                cont = 1;
            }
            if(contParidad == 0){
                contParidad = 3;
            }
        }

    }
}

void ControllerNode::reconstructBin(char *name, int disk) {
    FILE *diskA, *diskB, *newDisk;
    char* disk1 = "/home/kevinfgn/Disk1";
    char* disk2 = "/home/kevinfgn/Disk2";
    char* disk3 = "/home/kevinfgn/Disk3";
    if(disk == 1){
        //El faltante es el 1
        char* path = "/home/kevinfgn/Qt Projects/NodeGUI/";

        char* b1 = "1.bin";
        char* write = "wr";
        char* read = "rb";
        const char* realFile1 = setPath(disk1, name, b1);
        newDisk = fopen(realFile1,write);
        char* b2 = "2.bin";
        const char* realFile2 = setPath(disk2, name, "2.bin");
        diskA = fopen(realFile2,"rb");

        const char* realFile3 = setPath(disk3, name, "3.bin");
        diskB = fopen(realFile3,"rb");

    }else if(disk == 2){
        //El faltante es el 2
        const char* realFile1 = setPath(disk1, name, "1.bin");
        diskA = fopen(realFile1,"rb");

        const char* realFile2 = setPath(disk2, name, "2.bin");
        newDisk = fopen(realFile2,"wb");

        const char* realFile3 = setPath(disk3, name, "3.bin");
        diskB = fopen(realFile3,"rb");

    }else{
        //El faltante es el 3
        const char* realFile1 = setPath(disk1, name, "1.bin");
        diskA = fopen(realFile1,"rb");

        const char* realFile2 = setPath(disk2, name, "2.bin");
        diskB = fopen(realFile2,"rb");

        const char* realFile3 = setPath(disk3, name, "3.bin");
        newDisk = fopen(realFile3,"wb");
    }
    bool endA = true, endB = true;
    int cont = 0;
    int contDiskA = 1;
    int contDiskB = 2;
    int contNewDisk = 3;
    char* buffer = new char [1];
    char firstBuffer;
    char secondBuffer;

    char* firstBufferPtr = nullptr;
    char* secondBufferPtr = nullptr;

    char XOR;
    char* XORptr = new char[1];
    while(1) {
        if (cont%2 == 0 && endA) {
            size_t bytesRead = 0;
            if(contDiskA == 3){
                contDiskA = 0;
                bytesRead = fread(buffer, 1, 1, diskA); //Leer del bit de paridad
            }else{
                bytesRead = fread(buffer, 1, 8, diskA); //Leer del bin 1
            }
            firstBuffer = *buffer;
            firstBufferPtr = &firstBuffer;
            contDiskA++;
            if (bytesRead == 0) {
                endA = false;
                fclose(diskA);
            }
        }else if (cont%2 == 1 && endB){
            size_t bytesRead = 0;
            if(contDiskB == 3){
                contDiskB = 0;
                bytesRead = fread(buffer, 1, 1, diskB); //Leer del bit de paridad
            }else{
                bytesRead = fread(buffer, 1, 8, diskB); //Leer del bin 2
            }
            secondBuffer = *buffer;
            secondBufferPtr = &secondBuffer;
            contDiskB++;
            if (bytesRead == 0) {
                fclose(diskB);
                endB = false;
            }
        }
        cont++;
        if (firstBufferPtr != nullptr && secondBufferPtr != nullptr) {
            XOR = *firstBufferPtr ^ *secondBufferPtr;
            XORptr = &XOR;
            firstBufferPtr = nullptr;
            secondBufferPtr = nullptr;
            if (contNewDisk == 3) {
                fwrite(XORptr, 1, 1, newDisk);
            } else {
                fwrite(XORptr, 1, 8, newDisk);
            }
            contNewDisk--;
            if (contNewDisk == 0) {
                contNewDisk = 3;
            }
        }
        if (!endA && !endB) {
            fclose(newDisk);
            cout << "reconstruccion completa" << endl;
            break;
        }
    }

}

const char* ControllerNode::setPath(char* initialPath, char* name, char* ext){
    char* fullPath = new char[45];
    strcpy(fullPath,initialPath);
    strcat(fullPath,name);
    strcat(fullPath,ext);
    const char* realPath = (const char*)fullPath;
    return realPath;
}

