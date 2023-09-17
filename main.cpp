#include <iostream>
#include "Mesh.h"

int main(){

std::cout << "--> Read mesh..." << std::endl;
Mesh *oldMesh = new Mesh();
oldMesh->read_obj(1);

std::cout << "--> Compute normals..." << std::endl;
oldMesh->normals();
oldMesh->create_1ring_neighborhood();


return 0;

};
