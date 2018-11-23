//
// Created by jose on 21/11/18.
//

#include "DiskNode.h"

DiskNode::DiskNode(const char *number) {
    const char* mkdir = "mkdir /home/jose/CLionProjects/TECMFS/Disk";
    char fullPath[50];
    strcpy(fullPath,mkdir);
    strcat(fullPath,number);
    system(fullPath);

    const char* dir = "/home/jose/CLionProjects/TECMFS/Disk";
    strcpy(path,dir);
    strcat(path,number);

    cout<<this->path<<endl;
};