//
// Created by jose on 21/11/18.
//

#ifndef TECMFS_DISKNODE_H
#define TECMFS_DISKNODE_H

#include <cstdlib>
#include <string>
#include <iostream>
#include <cstring>

using namespace std;
class DiskNode {

public:
    char path[45];
    int IP; //port, no se que tipo es esto


    DiskNode(const char* number);

    void save(ssize_t bytes, char* buffer){

    }

};


#endif //TECMFS_DISKNODE_H
