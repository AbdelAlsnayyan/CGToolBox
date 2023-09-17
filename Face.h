#ifndef FACE_H
#define FACE_H
//#pragma once
//class Vector3D;
#include "Vector3D.h"
#include "HalfEdge.h"

class HalfEdge;

class Face{

  public:

   //return it as reference means we cant get id of const Face   
   int &id(){return m_id;}

   HalfEdge *&halfedge() { return m_halfedge; };
   Vector3D &norm() { return m_norm; };
   void normal();
   void printVertexPositions();

  private:
   int m_id;
   HalfEdge *m_halfedge;
   Vector3D m_norm;

};

#endif