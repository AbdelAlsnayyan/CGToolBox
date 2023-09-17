#include <iostream>
#include <stdio.h>
#include <cstring>
#include "Mesh.h"

int Mesh::read_obj(int a){
 FILE * file = fopen("box.obj", "r");
 if( file == NULL ){
  printf("Impossible to open the file !\n");
  return 0;
 }

 int id_vert=0;
 int id_face=0;
 while( 1 ){
  char lineHeader[128];
  int res = fscanf(file, "%s", lineHeader);
  if (res == EOF) break; 

  if ( strcmp( lineHeader, "v" ) == 0 ){
   float x;
   float y;
   float z;
   double vv[3];
   fscanf(file, "%lf %lf %lf\n", &vv[0], &vv[1], &vv[2] );
   Vector3D p(vv[0],vv[1],vv[2]);

   Vertex * v = create_vertex(id_vert);
   v->point() = p;
   id_vert++;
  } else if ( strcmp( lineHeader, "f" ) == 0 ){
   int fface[3];
   Vertex *v[3];
   fscanf(file, "%d %d %d\n", &fface[0], &fface[1], &fface[2] );
   v[0] = m_map_vertex[fface[0]-1];
   v[1] = m_map_vertex[fface[1]-1];
   v[2] = m_map_vertex[fface[2]-1];
   Face *f = create_face(v,id_face);
   id_face++;
  }

 }
 return 0;
}


Vertex *Mesh::create_vertex(int id) {
	Vertex *v = new Vertex();
	v->id()  = id;
	m_vertices.push_back(v);
	m_map_vertex.insert(std::pair<int, Vertex*>(id, v));
	return v;
}

Face *Mesh::create_face(Vertex * v[], int id){
 Face *f = new Face();
 f->id() = id;
 m_faces.push_back(f);

//create halfedges
 HalfEdge *hes[3];

 for (int i = 0; i < 3; i++) {
  hes[i] = new HalfEdge;
  Vertex * vert = v[i];
  hes[i]->vertex() = vert;
  vert->halfedge() = hes[i];
 }

//link halfedges
 for (int i = 0; i < 3; i++) {
  hes[i]->he_next() = hes[(i + 1) % 3];
  hes[i]->he_prev() = hes[(i + 2) % 3];
 }

//link to face
for (int i = 0; i < 3; i++) {
  hes[i]->face() = f;
  f->halfedge() = hes[i];
}


//connect halfedges to edge
for (int i = 0; i < 3; i++) {
 Edge *e = create_edge(v[i], v[(i + 2) % 3]);
 if (e->halfedge(0) == NULL) {
  e->halfedge(0) = hes[i];
 }
 else {
 e->halfedge(1) = hes[i];
 }

 hes[i]->edge() = e;

 //connect twins
 if( e->halfedge(0) && e->halfedge(1) ) {
  e->halfedge(0)->twin() = e->halfedge(1);
  e->halfedge(1)->twin() = e->halfedge(0);
 }

}

 return f;
}

Edge *Mesh::create_edge(Vertex *v1, Vertex *v2) {
	EdgeKey key(v1, v2);

	Edge *e = NULL;

	if (m_map_edge.find(key) != m_map_edge.end()) {
		e = m_map_edge[key];
		return e;
	}

	e = new Edge;

	m_map_edge.insert(std::pair<EdgeKey, Edge*>(key, e));
	m_edges.push_back(e);

	return e;
}

void Mesh::create_1ring_neighborhood() {
 for(auto v : m_vertices) {
  v->one_ring();
 }  
}

void Mesh::normals() {

 for(auto f : m_faces) f->normal();

}

Vertex *Mesh::id_vertex(int id) {
	return m_map_vertex[id];
}
