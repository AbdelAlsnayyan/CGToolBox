#ifndef VERTEX_H
#define VERTEX_H

#include "Vector3D.h"
#include <vector>
#include "HalfEdge.h"
#include <iostream>

class HalfEdge;


class Vertex{
 public:
  int & id() { return m_id; };
  int get_valence() const {return m_valence;};
  int &set_valence() {return m_valence;};
  void one_ring();
  void two_ring();
  Vector3D & point() { return m_point; };

  HalfEdge *& halfedge() { return m_halfedge; };

 private:
  int   m_id;
  int   m_valence;
  Vector3D m_point;
  HalfEdge *m_halfedge;
  std::vector<Vertex*> m_one_ring;

};


#endif
