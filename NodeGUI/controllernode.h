//
// Created by jose on 21/11/18.
//
#ifndef TECMFS_CONTROLLERNODE_H
#define TECMFS_CONTROLLERNODE_H

#include <cstdio>
#include <iostream>
#include "disknode.h"

using namespace std;
class ControllerNode {
private:
    const char* a = "1";
    const char* b = "2";
    const char* c = "3";
    DiskNode* disk1 = new DiskNode(a);
    DiskNode* disk2 = new DiskNode(b);
    DiskNode* disk3 = new DiskNode(c);
public:
    void saveToDiskNodes(char* name);

    void readFromDiskNodes(char* name);

    void reconstructBin(char* name, int disk);

    const char* setPath(char* initialPath, char* name, char* ext);

};


#endif //TECMFS_CONTROLLERNODE_H
