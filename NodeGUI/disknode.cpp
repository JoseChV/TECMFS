//
// Created by jose on 21/11/18.
//

#include "disknode.h"

DiskNode::DiskNode(const char *number) {
    cout << "puta madre" << endl;
    const char* mkdir = "mkdir /home/kevinfgn/Disk";
    char fullPath[50];
    strcpy(fullPath,mkdir);
    strcat(fullPath,number);
    system(fullPath);

    const char* dir = "/home/kevinfgn/Disk";
    strcpy(path,dir);
    strcat(path,number);


    cout<<this->path<<endl;
}
