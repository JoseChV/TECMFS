#include <iostream>
#include "ControllerNode.h"

using namespace std;

int main() {
    ControllerNode* cn = new ControllerNode();
    char* name = "CocaineKid";
    //cn->saveToDiskNodes(name);
    cn->readFromDiskNodes(name);


    return 0;
}