//
// Created by jose on 21/11/18.
//

#include "ControllerNode.h"

void ControllerNode::saveToDiskNodes() {
    FILE *d4, *d3, *d2, *d1, *file;
    char *buffer;
    file = fopen("/home/jose/CLionProjects/TECMFS/CocaineKid.mp4","rb");
    d1 = fopen("/home/jose/CLionProjects/TECMFS/prueba1.bin","wb");
    d2 = fopen("/home/jose/CLionProjects/TECMFS/prueba2.bin","wb");
    d3 = fopen("/home/jose/CLionProjects/TECMFS/prueba3.bin","wb");
    d4 = fopen("/home/jose/CLionProjects/TECMFS/prueba4.bin","wb");
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

void ControllerNode::readFromDiskNodes() {
    FILE *d1, *d2, *d3,*d4, *video;
    d1 = fopen("/home/jose/CLionProjects/TECMFS/prueba1.bin", "rb");
    d2 = fopen("/home/jose/CLionProjects/TECMFS/prueba2.bin", "rb");
    d3 = fopen("/home/jose/CLionProjects/TECMFS/prueba3.bin", "rb");
    d4 = fopen("/home/jose/CLionProjects/TECMFS/prueba4.bin", "rb");
    video = fopen("/home/jose/CLionProjects/TECMFS/NEWVIDEO.mp4", "wb");
    char *buffer;
    int cont = 0;
    bool d1b = true,d2b = true,d3b = true;
    while (1) {
        if(cont%3 == 0 && d1b) {
            ssize_t bytesRead = 0;
            bytesRead = fread(buffer, 1, sizeof(buffer), d1);
            if (bytesRead == 0) {
                cout << "1 ended" << endl;
                fclose(d1);
                d1b = false;
            }
            fwrite(buffer, 1, (size_t) bytesRead, video);
        }else if(cont%3 == 1 && d2b){
            ssize_t bytesRead = 0;
            bytesRead = fread(buffer, 1, sizeof(buffer), d2);
            if (bytesRead == 0) {
                cout << "2 ended" << endl;
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
                cout << "3 ended" << endl;
            }
            fwrite(buffer, 1, (size_t) bytesRead, video);
        }
        if(!d1b && !d2b && !d3b){
            fclose(video);
            break;
        }

        cont++;
    }

}