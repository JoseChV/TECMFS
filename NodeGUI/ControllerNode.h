//
// Created by jose on 21/11/18.
//
#ifndef TECMFS_CONTROLLERNODE_H
#define TECMFS_CONTROLLERNODE_H

#include <cstdio>
#include <iostream>



using namespace std;
class ControllerNode {
public:
    void saveToDiskNodes(char* name);

    void readFromDiskNodes(char* name);

    void reconstructBin(char* name, int disk);

    const char* setPath(char* initialPath, char* name, char* ext);

};


#endif //TECMFS_CONTROLLERNODE_H
