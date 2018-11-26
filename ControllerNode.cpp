//
// Created by jose on 21/11/18.
//

#include "ControllerNode.h"
void ControllerNode::saveToDiskNodes(char* name) {
    FILE  *d3, *d2, *d1, *file;
    char *buffer = new char[2];

    //Open video file
    char* fullPathFile = new char[45];
    strcpy(fullPathFile,"/home/jose/CLionProjects/TECMFS/");
    strcat(fullPathFile,name);
    strcat(fullPathFile,".mp4");
    const char* realFile = (const char*)fullPathFile;
    file = fopen(realFile,"rb");

    //Create bin file 1
    fullPathFile = new char[45];
    strcpy(fullPathFile,"/home/jose/CLionProjects/TECMFS/");
    strcat(fullPathFile,name);
    strcat(fullPathFile,"1.bin");
    realFile = (const char*)fullPathFile;
    d1 = fopen(realFile,"wb");

    //Create bin file 2
    fullPathFile = new char[45];
    strcpy(fullPathFile,"/home/jose/CLionProjects/TECMFS/");
    strcat(fullPathFile,name);
    strcat(fullPathFile,"2.bin");
    realFile = (const char*)fullPathFile;
    d2 = fopen(realFile,"wb");

    //Create bin file 3
    fullPathFile = new char[45];
    strcpy(fullPathFile,"/home/jose/CLionProjects/TECMFS/");
    strcat(fullPathFile,name);
    strcat(fullPathFile,"3.bin");
    realFile = (const char*)fullPathFile;
    d3 = fopen(realFile,"wb");


    int cont = 0;
    while(1){
        ssize_t bytesRead = fread(buffer, 1, sizeof(buffer), file);

        if(cont%3 == 0) {
            fwrite(buffer, 1, (size_t) bytesRead, d1);
        }else if(cont%3 == 1){
            fwrite(buffer,1,(size_t) bytesRead, d2);
        }else{
            fwrite(buffer,1,(size_t) bytesRead, d3);
        }
        if(bytesRead == 0){
            break;
        }
        cont++;
        //if error enviando, print "error en el envio", break
    }

    fclose(d1);
    fclose(d2);
    fclose(d3);
    fclose(file);

    ///Mandar files a los discos y borrar los del directorio principal
}

void ControllerNode::readFromDiskNodes(char* name) {
    FILE *d1, *d2, *d3, *video;

    char *buffer = new char[2];
    video = fopen("/home/jose/CLionProjects/TECMFS/NEWVIDEO.mp4", "wb");

    char* fullPathBin1 = new char[45];
    strcpy(fullPathBin1,"/home/jose/CLionProjects/TECMFS/");
    strcat(fullPathBin1,name);
    strcat(fullPathBin1,"1.bin");
    const char* realFile1 = (const char*)fullPathBin1;
    d1 = fopen(realFile1,"rb");


    char* fullPathBin2 = new char[44];
    strcpy(fullPathBin2,"/home/jose/CLionProjects/TECMFS/");
    strcat(fullPathBin2,name);
    strcat(fullPathBin2,"2.bin");
    const char* realFile2 = (const char*)fullPathBin2;
    d2 = fopen(realFile2,"rb");

    char* fullPathBin3 = new char[45];
    strcpy(fullPathBin3,"/home/jose/CLionProjects/TECMFS/");
    strcat(fullPathBin3,name);
    strcat(fullPathBin3,"3.bin");
    const char* realFile3 = (const char*)fullPathBin3;
    d3 = fopen(realFile3,"rb");


    int cont = 0;
    bool d1b = true,d2b = true,d3b = true;
    while (1) {
        if(cont%3 == 0 && d1b) {
            ssize_t bytesRead = 0;
            bytesRead = fread(buffer, 1, sizeof(buffer), d1);
            if (bytesRead == 0) {
                d1b = false;
                fclose(d1);
            }
            fwrite(buffer, 1, (size_t) bytesRead, video);
        }else if(cont%3 == 1 && d2b){
            ssize_t bytesRead = 0;
            bytesRead = fread(buffer, 1, sizeof(buffer), d2);
            if (bytesRead == 0) {
                fclose(d2);
                d2b = false;
            }
            fwrite(buffer, 1, (size_t) bytesRead, video);
        }else if(cont%3 == 2 && d3b){
            ssize_t bytesRead = 0;
            bytesRead = fread(buffer, 1, sizeof(buffer), d3);
            if (bytesRead == 0) {
                d3b = false;
                fclose(d3);
            }
            fwrite(buffer, 1, (size_t) bytesRead, video);
        }
        if(!d1b && !d2b && !d3b){
            fclose(video);
            cout << "file recovered" << endl;
            break;
        }

        cont++;
    }

}