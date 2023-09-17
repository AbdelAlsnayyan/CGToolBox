#include "Vertex.h"
//#include "Point.h"

//Point &Vertex::point() { return m_point; };

//int Vertex::get_valence() { return m_valence; };


void Vertex::one_ring(){
 
    HalfEdge *h = halfedge();
    int i = 0;
    do
    {
     h = h->twin();
     h = h->he_next();
     h = h->he_next();
     m_one_ring.emplace_back(h->twin()->vertex());
     i++;
    }
    while( h != halfedge() );
    set_valence() = i;
}


//void Vertex::please_work(){
// std::cout << " KAK  " << std::endl;
// }

