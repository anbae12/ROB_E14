#include "graph.h"

graph::graph()
{
    //ctor
}

graph::~graph()
{
    //dtor
}

void graph::printEdges()
{
    for (edges_t::iterator edge = edges.begin(); edge != edges.end(); edge++)
    {
        cout << "Src: " << edge->src << " TopX: " << vertices[edge->src].first.x << " TopY: " << vertices[edge->src].first.y << endl;
        cout << "Dest: " << edge->dest << " TopX: " << vertices[edge->dest].first.x << " TopY: " << vertices[edge->dest].first.y << endl;
        cout << "Cost: " << edge->cost << endl << endl;
    }
}

void graph::routePlanning()
{

}

void graph::createEdges()
{
    unsigned int vertexIndex = 0, neighborIndex = 0;

    //Run throug every vertex to find it's edges
    for (vertices_t::iterator vertex = vertices.begin(); vertex != vertices.end(); vertex++){
        vertexIndex = distance(vertices.begin(), vertex); // Get the vertex index/number
        //Run throug every vertex again to see if it is a neihghbor
        for (vertices_t::iterator neighbor = vertices.begin(); neighbor != vertices.end(); neighbor++) {
            neighborIndex = distance(vertices.begin(), neighbor); // Get the neighbor index/number
            //Only check if it is not itself
            if (neighborIndex != vertexIndex) {
                //Check right and add egde and cost
                if (vertex->second.x + 2 == neighbor->first.x && vertex->first.y == neighbor->first.y)
                    edges.push_back(edge(vertexIndex, neighborIndex, neighbor->first.x/2 - vertex->first.x/2));

                //Check left and add egde and cost
                if (vertex->first.x - 2 == neighbor->second.x && vertex->second.y == neighbor->second.y)
                    edges.push_back(edge(vertexIndex, neighborIndex, vertex->first.x/2 - neighbor->first.x/2));

                //Check top and add egde and cost
                if (vertex->second.x == neighbor->second.x && vertex->first.y - 2 == neighbor->second.y)
                    edges.push_back(edge(vertexIndex, neighborIndex, vertex->first.y/2 - neighbor->first.y/2));

                //Check bottom and add egde and cost
                if (vertex->first.x == neighbor->first.x && vertex->second.y + 2 == neighbor->first.y)
                    edges.push_back(edge(vertexIndex, neighborIndex, neighbor->first.y/2 - vertex->first.y/2));
             }
        }
    }
}

void graph::addVertex(unsigned int topX, unsigned int topY, unsigned int bottomX, unsigned int bottomY)
{
    //Insert all vertices in a table so it is associated with a number/index
    vertices.push_back(make_pair(coord(topX, topY), coord(bottomX, bottomY)));
}
