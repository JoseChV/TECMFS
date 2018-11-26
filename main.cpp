#include <iostream>
#include "ControllerNode.h"

using namespace std;

int main() {
    ControllerNode* cn = new ControllerNode();
    cn->saveToDiskNodes("TheLight");
    cn->readFromDiskNodes("TheLight");

    return 0;
}