#include "pathPlanner.h"

pathPlanner::pathPlanner()
{
    //ctor
}

pathPlanner::~pathPlanner()
{
    //dtor
}

void pathPlanner::getPath()
{
    createEdges();
    generatePath();


    while (!path.empty()) {
        cout << "x: " << vertices[path.front()].top.x << " y: " << vertices[path.front()].top.y << endl;
        path.pop();
    }

    //cout << vertices[2].dist;

   /*unsigned int currentVertex = 23;
    while (vertices[currentVertex].dist != 0) {
        cout << "x: " << vertices[currentVertex].top.x << " y: " << vertices[currentVertex].top.y << endl;
        currentVertex = vertices[currentVertex].path;
    }*/

   /* for (vertices_t::iterator vertex_it = vertices.begin(); vertex_it != vertices.end(); vertex_it++) {
        cout << "x: " << vertex_it->top.x << " y: " << vertex_it->top.y << endl;
        for (list<unsigned int>::iterator ajd_it = vertex_it->adj.begin(); ajd_it != vertex_it->adj.end(); ajd_it++) {
            cout << "\t" << *ajd_it << endl;
        }
    }
*/
}

void pathPlanner::generatePath()
{
    unsigned int currentVertex = 0;
    queue<unsigned int> q;

    //Set all costs to infinity and path to zero
    for (vertices_t::iterator vertex_it = vertices.begin(); vertex_it != vertices.end(); vertex_it++) {
        vertex_it->dist = infinityCost;
        vertex_it->path = 0;
    }

    //Start at vertex 0
    vertices[currentVertex].dist = 0;
    q.push(currentVertex);

    while (!q.empty()) {
        currentVertex = q.front();
        q.pop();

        path.push(currentVertex);

        if (vertices[currentVertex].adj.size() == 1)
            path.push(vertices[currentVertex].path);

        for (list<unsigned int>::iterator ajd_it = vertices[currentVertex].adj.begin(); ajd_it != vertices[currentVertex].adj.end(); ajd_it++) {
            if (vertices[*ajd_it].dist == infinityCost)
            {
                vertices[*ajd_it].dist = vertices[currentVertex].dist + 1;
                vertices[*ajd_it].path = currentVertex;
                q.push(*ajd_it);
            }
        }
    }
}

void pathPlanner::createEdges()
{

    unsigned int vertexIndex = 0, neighborIndex = 0;

    //Run throug every vertex to find it's edges
    for (vertices_t::iterator vertex_it = vertices.begin(); vertex_it != vertices.end(); vertex_it++){
        vertexIndex = distance(vertices.begin(), vertex_it); // Get the vertex index/number
        //Run throug every vertex again to see if it is a neihghbor
        for (vertices_t::iterator neighbor_it = vertices.begin(); neighbor_it != vertices.end(); neighbor_it++) {
            neighborIndex = distance(vertices.begin(), neighbor_it); // Get the neighbor index/number
            //Only check if it is not itself
            if (neighborIndex != vertexIndex) {
                //Check right and add egde and cost
                if (vertex_it->bottom.x + 2 == neighbor_it->top.x && vertex_it->top.y == neighbor_it->top.y)
                    vertex_it->adj.push_back(neighborIndex);
                    //adjMatrix[vertexIndex][neighborIndex] = neighbor->first.x/2 - vertex->first.x/2;

                //Check left and add egde and cost
                if (vertex_it->top.x - 2 == neighbor_it->bottom.x && vertex_it->bottom.y == neighbor_it->bottom.y)
                    vertex_it->adj.push_back(neighborIndex);
                    //adjMatrix[vertexIndex][neighborIndex] = vertex->first.x/2 - neighbor->first.x/2;

                //Check top and add egde and cost
                if (vertex_it->bottom.x == neighbor_it->bottom.x && vertex_it->top.y - 2 == neighbor_it->bottom.y)
                    vertex_it->adj.push_back(neighborIndex);
                    //adjMatrix[vertexIndex][neighborIndex] = vertex->first.y/2 - neighbor->first.y/2;

                //Check bottom and add egde and cost
                if (vertex_it->top.x == neighbor_it->top.x && vertex_it->bottom.y + 2 == neighbor_it->top.y)
                    vertex_it->adj.push_back(neighborIndex);
                    //adjMatrix[vertexIndex][neighborIndex] = neighbor->first.y/2 - vertex->first.y/2;
             }
        }
    }
}

void pathPlanner::addVertex(unsigned int topX, unsigned int topY, unsigned int bottomX, unsigned int bottomY)
{
    //Insert all vertices in a table so it is associated with a number/index
    vertex temp;
    temp.setCoord(topX, topY, bottomX, bottomY);
    vertices.push_back(temp);
}

