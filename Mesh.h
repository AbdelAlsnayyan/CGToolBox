#include <vector>
#include <map>
#include <iterator>
//#include "Face.h"
//#include "Vertex.h"
#include "HalfEdge.h"

class Mesh{

 public:
  //using   std::vector<Vertex>::const_iterator   VertexCIter;
  //using   std::vector<Edge>::const_iterator     EdgeCIter;
  //typedef   std::vector<Face>::iterator     FaceCIter;
  //using   std::vector<Halfedge>::const_iterator HalfedgeCIter;

  int read_obj(int a);

  Vertex *create_vertex(int id);
  Vertex *id_vertex(int id);

  Face *create_face(Vertex *v[],int id);
  Face *id_face(int id);

  Edge *create_edge(Vertex *v1, Vertex *v2);

  void create_1ring_neighborhood();
  void printVertexPositions(Face *&f);

  void normals();
 
 protected:		
  std::vector<Edge*> m_edges;
  std::vector<Face*> m_faces;
  std::vector<Vertex*> m_vertices;

  std::map<int, Vertex*> m_map_vertex;
  std::map<int, Face*> m_map_face;
  std::map<EdgeKey, Edge*> m_map_edge;

};


