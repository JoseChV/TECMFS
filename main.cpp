#include <iostream>
#include "ControllerNode.h"

using namespace std;

int main() {
    ControllerNode* cn = new ControllerNode();
    cn->saveToDiskNodes();
    cn->readFromDiskNodes();

    return 0;
}