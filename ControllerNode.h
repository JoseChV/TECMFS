//
// Created by jose on 21/11/18.
//
#ifndef TECMFS_CONTROLLERNODE_H
#define TECMFS_CONTROLLERNODE_H

#include <cstdio>
#include <iostream>
#include <vector>
#include <fstream>
#include "DiskNode.h"

using namespace std;
class ControllerNode {
private:
    const char* a = "1";
    const char* b = "2";
    const char* c = "3";
    const char* d = "4";
    DiskNode* disk1 = new DiskNode(a);
    DiskNode* disk2 = new DiskNode(b);
    DiskNode* disk3 = new DiskNode(c);
    DiskNode* disk4 = new DiskNode(d);
public:
    void saveToDiskNodes();

    void readFromDiskNodes();
};


#endif //TECMFS_CONTROLLERNODE_H
