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

    HalfEdge* h = halfedge(); 
    do {
        Vertex* v = h->vertex();   
        h = h->he_next();                 
    } while (h != halfedge());    
}


