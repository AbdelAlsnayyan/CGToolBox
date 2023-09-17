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

 //std::cout<< "Flag A" << std::endl;   
 int id_vert=0;
 int id_face=0;
 while( 1 ){
  char lineHeader[128];
  // read the first word of the line
  int res = fscanf(file, "%s", lineHeader);
  if (res == EOF)
   break; // EOF = End Of File. Quit the loop.

  if ( strcmp( lineHeader, "v" ) == 0 ){
   //std::cout<< lineHeader << std::endl;   
   float x;
   float y;
   float z;
   double vv[3];
   fscanf(file, "%lf %lf %lf\n", &vv[0], &vv[1], &vv[2] );
   //std::cout << vv[0] << " " << vv[1] << " " << vv[2] << std::endl;
   Vector3D p(vv[0],vv[1],vv[2]);

   Vertex * v = create_vertex(id_vert);
   v->point() = p;
   //std::cout << v->id() << " " << v->point()[0] << " " << v->point()[1] << " " << v->point()[2] << std::endl;  
   //std::cout <<m_vertices.front()->point().x()<<std::endl; 
   //std::cout << id_vert << std::endl;
   id_vert++;
   //Vertices.push_back(vertex); 
   //std::cout << vv[0] << std::endl;
   //std::cout << vv[1] << std::endl;
   //std::cout << vv[2] << std::endl;
  } else if ( strcmp( lineHeader, "f" ) == 0 ){
   //std::cout<< lineHeader << std::endl;   
   int fface[3];
   Vertex *v[3];
   fscanf(file, "%d %d %d\n", &fface[0], &fface[1], &fface[2] );
   //std::cout << "issue " << std::endl;
   v[0] = m_map_vertex[fface[0]-1];
   v[1] = m_map_vertex[fface[1]-1];
   v[2] = m_map_vertex[fface[2]-1];
   //std::cout << v[0]->point()[0] << std::endl;
   Face *f = create_face(v,id_face);
   id_face++;
   //std::cout << fface[0] << " " << fface[1] << " " << fface[2] << std::endl;
   //std::cout<<Face[0]<<std::endl;
   //std::cout<<Face[1]<<std::endl;
   //std::cout<<Face[2]<<std::endl;
        //vertexIndices.push_back(vertexIndex[0]);
        //vertexIndices.push_back(vertexIndex[1]);
        //vertexIndices.push_back(vertexIndex[2]);
  }

 }
 return 0;
}


//create new gemetric simplexes
Vertex *Mesh::create_vertex(int id) {
	Vertex *v = new Vertex();
	//assert(v != NULL);
	v->id()  = id;
	//v->point() = x;
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

 //std::cout << "a "<<std::endl;

 for (int i = 0; i < 3; i++) {
  hes[i] = new HalfEdge;
  //assert(hes[i]);
  //std::cout<<v[i]->id()<<std::endl;
  Vertex * vert = v[i];
  hes[i]->vertex() = vert;
  vert->halfedge() = hes[i];
 }

 //std::cout << "b " << std::endl;

//linking to each other
 for (int i = 0; i < 3; i++) {
  hes[i]->he_next() = hes[(i + 1) % 3];
  hes[i]->he_prev() = hes[(i + 2) % 3];
 }

//linking to face
for (int i = 0; i < 3; i++) {
  hes[i]->face() = f;
  f->halfedge() = hes[i];
}


//connecting with edge
for (int i = 0; i < 3; i++) {
 Edge *e = create_edge(v[i], v[(i + 2) % 3]);
 if (e->halfedge(0) == NULL) {
  e->halfedge(0) = hes[i];
 }
 else {
 //assert(e->halfedge(1) == NULL);
 e->halfedge(1) = hes[i];
 }

 hes[i]->edge() = e;

 if( e->halfedge(0) && e->halfedge(1) ) {
  e->halfedge(0)->twin() = e->halfedge(1);
  e->halfedge(1)->twin() = e->halfedge(0);
  //std::cout << "0 e->vert_id " << e->halfedge(0)->vertex()->id() << std::endl;
  //std::cout << "1 e->vert_id " << e->halfedge(1)->vertex()->id() << std::endl;
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

	//assert(e != NULL);
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
