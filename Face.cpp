#include "Face.h"
#include <iostream>

void Face::normal(){
    Vector3D normal;

    HalfEdge *h = halfedge();

    do
    {
      Vector3D pi = h->vertex()->point();
      Vector3D pj = h->he_next()->vertex()->point();

      normal = normal +  pi.cross(pj);

      h = h->he_next();
    }
    while( h != halfedge() );

    norm() = normal.unit(); 
}

void Face::printVertexPositions(){

    HalfEdge* h = halfedge(); // get the first halfedge of the face
    do {
        Vertex* v = h->vertex();   // get the vertex of the current halfedge
        std::cout << v->id() << " " << v->point()[0] << " " << v->point()[1] << " " << v->point()[2]  << std::endl;   // print the vertex position
        h = h->he_next();                 // move to the next halfedge around the face
    } while (h != halfedge());    // keep going until we're back at the beginning
}


