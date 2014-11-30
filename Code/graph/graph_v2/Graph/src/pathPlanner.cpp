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
    createPathGrids();
    generatePath();

    while (!path.empty()) {
        cout << "x: " << vertices[path.front()].top.x << " y: " << vertices[path.front()].top.y << endl;
        path.pop_front();
    }
}

void pathPlanner::createPathGrids()
{
    for (vertices_t::iterator vertex_it = vertices.begin(); vertex_it != vertices.end(); vertex_it++) {
        for (list<unsigned int>::iterator adj1_it = vertices[vertex_it->identifier].adj.begin(); adj1_it != vertices[vertex_it->identifier].adj.end(); adj1_it++) {
            if (vertex_it->pathGrid[*adj1_it] == infinityCost)
                vertex_it->pathGrid[*adj1_it] = vertex_it->identifier;
            for (list<unsigned int>::iterator adj2_it = vertices[*adj1_it].adj.begin(); adj2_it != vertices[*adj1_it].adj.end(); adj2_it++) {
                if (vertex_it->pathGrid[*adj2_it] == infinityCost)
                    vertex_it->pathGrid[*adj2_it] = *adj1_it;
                for (list<unsigned int>::iterator adj3_it = vertices[*adj2_it].adj.begin(); adj3_it != vertices[*adj2_it].adj.end(); adj3_it++) {
                    if (vertex_it->pathGrid[*adj3_it] == infinityCost)
                        vertex_it->pathGrid[*adj3_it] = *adj2_it;
                }
            }
        }
    }
}

void pathPlanner::generatePath()
{
    unsigned int currentVertex = 0, destinationVertex = 0, neighbor = 0;
    queue<unsigned int> q;
    list<unsigned int> queuePathGrid;

    //Set all costs to infinity and path to zero
    for (vertices_t::iterator vertex_it = vertices.begin(); vertex_it != vertices.end(); vertex_it++)
        vertex_it->dist = infinityCost;

    //Start at vertex 0
    vertices[currentVertex].dist = 0;
    q.push(currentVertex);

    while (!q.empty()) {
        currentVertex = q.front();
        q.pop();

        if (!q.empty()) {
            neighbor = 0;
            for (list<unsigned int>::iterator ajd_it = vertices[q.front()].adj.begin(); ajd_it != vertices[q.front()].adj.end(); ajd_it++)
                if (q.front() == *ajd_it)
                    neighbor = 1;

            if (!neighbor){
                queuePathGrid.clear();
                destinationVertex = q.front();
                while (destinationVertex != currentVertex) {
                    destinationVertex = vertices[currentVertex].pathGrid[destinationVertex];
                    queuePathGrid.push_back(destinationVertex);
                }
                queuePathGrid.reverse();
                while (!queuePathGrid.empty()){
                    path.push_back(queuePathGrid.front());
                    queuePathGrid.pop_front();
                }
            }
        } else
            path.push_back(currentVertex);


        for (list<unsigned int>::iterator ajd_it = vertices[currentVertex].adj.begin(); ajd_it != vertices[currentVertex].adj.end(); ajd_it++) {
            if (vertices[*ajd_it].dist == infinityCost)
            {
                vertices[*ajd_it].dist = vertices[currentVertex].dist + 1;
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
        vertex_it->identifier = vertexIndex;
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

