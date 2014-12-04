//
//  pathPlanner.cpp
//  My cup functions
//
//  Created by Anders Launer Bæk on 03/12/14.
//  Copyright (c) 2014 Anders Launer Bæk. All rights reserved.
//

#include "pathPlanner.h"
#include "findPoints.h"

pathPlanner::pathPlanner()
{
    //ctor
}

//pathPlanner::~pathPlanner()
//{
//    //dtor
//}

void pathPlanner::getPath(){
    createEdges();
    createPathGrids();
    generatePath();
    int jj=0;
//    cout << path.size() << endl;
//    while (!path.empty()) {
//    
//    //cout << "topx: " << vertices[path.front()].top.x << " topy: " << vertices[path.front()].top.y << endl;
//    //        //cout << "botx: " << vertices[path.front()].bottom.x << " boty: " << vertices[path.front()].bottom.y << endl;
//    //for (list<unsigned int>::iterator ajd_it = path.begin(); ajd_it != path.end(); ajd_it++){
//        unsigned int xt=vertices[path.front()].top.x;
//        unsigned int yt=vertices[path.front()].top.y;
//        unsigned int xb=vertices[path.front()].bottom.x;
//        unsigned int yb=vertices[path.front()].bottom.y;
//    
//    //    cout << "topx: " << xt << " topy: " << yt << endl;
//    //    cout << "botx: " << xb << " boty: " << yb<< endl;
//    //
// 
//        path.pop_front();
//        toJannik.push(coordinatesPair(xt, yt, xb, yb));
    //
    //
    //    jj++;
    ////    unsigned int xt=vertices[path.front()].top.x;
    ////    unsigned int yt=vertices[path.front()].top.y;
    ////    unsigned int xb=vertices[path.front()].bottom.x;
    ////    unsigned int yb=vertices[path.front()].bottom.y;
    ////
    ////    cout << "topx: " << xt << " topy: " << yt << endl;
    ////    cout << "botx: " << xb << " boty: " << yb<< endl;
    ////        cleanCoord.push(std::make_pair(xt,yt));
    ////        cleanCoord.push(std::make_pair(xb,yb));
    ////        path.pop_front();
    //    }
    //    std::cout<<jj<<std::endl;
    //     std::cout<<toJannik.size()<<std::endl;
    //
    //
    
    
    
}

void pathPlanner::createPathGrids(){
    unsigned int currentVertex = 0, currentVertex_inner = 0;
    int times = 0;
    std::queue<unsigned int> q;
    for (vertices_t::iterator vertex_it = vertices.begin(); vertex_it != vertices.end(); vertex_it++){ //"Call" dijkstra
        currentVertex = times;
        vertices[currentVertex].pathGrid.resize(vertices.size());
        
        //Set all costs to infinity and path to zero
        for (vertices_t::iterator vertex_it_inner = vertices.begin(); vertex_it_inner != vertices.end(); vertex_it_inner++)
            vertex_it_inner->dist = infinityCost;
        
        //Start at vertex 0
        vertices[currentVertex].dist = 0;
        q.push(currentVertex);
        
        while (!q.empty()) {
            currentVertex_inner = q.front();
            q.pop();
            
            for (list<unsigned int>::iterator ajd_it = vertices[currentVertex_inner].adj.begin(); ajd_it != vertices[currentVertex_inner].adj.end(); ajd_it++){
                if (vertices[*ajd_it].dist == infinityCost){
                    vertices[*ajd_it].dist = vertices[currentVertex_inner].dist + 1;
                    vertices[currentVertex].pathGrid[*ajd_it] = currentVertex_inner;
                    q.push(*ajd_it);
                }
            }
        }
        times++;
    }
}

void pathPlanner::generatePath()
{
    unsigned int currentVertex = 0, destinationVertex = 0, neighbor = 0;
    std::queue<unsigned int> q;
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
            for (list<unsigned int>::iterator ajd_it = vertices[q.front()].adj.begin(); ajd_it != vertices[q.front()].adj.end(); ajd_it++){
                if (q.front() == *ajd_it)
                    neighbor = 1;
            }
            
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
            if (vertices[*ajd_it].dist == infinityCost){
                vertices[*ajd_it].dist = vertices[currentVertex].dist + 1;
                q.push(*ajd_it);
            }
        }
    }
}

void pathPlanner::createEdges(){
    unsigned int vertexIndex = 0, neighborIndex = 0;
    
    //Run throug every vertex to find it's edges
    for (vertices_t::iterator vertex_it = vertices.begin(); vertex_it != vertices.end(); vertex_it++){
        vertexIndex = (unsigned int)distance(vertices.begin(), vertex_it); // Get the vertex index/number
        vertex_it->identifier = vertexIndex;
        //Run throug every vertex again to see if it is a neihghbor
        for (vertices_t::iterator neighbor_it = vertices.begin(); neighbor_it != vertices.end(); neighbor_it++) {
            neighborIndex = (unsigned int)distance(vertices.begin(), neighbor_it); // Get the neighbor index/number
            //Only check if it is not itself
            if (neighborIndex != vertexIndex) {
                //Check right and add egde and cost
                if (vertex_it->bottom.x == neighbor_it->top.x && vertex_it->top.y == neighbor_it->top.y)
                    vertex_it->adj.push_back(neighborIndex);
                //adjMatrix[vertexIndex][neighborIndex] = neighbor->first.x/2 - vertex->first.x/2;
                
                //Check left and add egde and cost
                if (vertex_it->top.x == neighbor_it->bottom.x && vertex_it->bottom.y == neighbor_it->bottom.y)
                    vertex_it->adj.push_back(neighborIndex);
                //adjMatrix[vertexIndex][neighborIndex] = vertex->first.x/2 - neighbor->first.x/2;
                
                //Check top and add egde and cost
                if (vertex_it->bottom.x == neighbor_it->bottom.x && vertex_it->top.y == neighbor_it->bottom.y)
                    vertex_it->adj.push_back(neighborIndex);
                //adjMatrix[vertexIndex][neighborIndex] = vertex->first.y/2 - neighbor->first.y/2;
                
                //Check bottom and add egde and cost
                if (vertex_it->top.x == neighbor_it->top.x && vertex_it->bottom.y == neighbor_it->top.y)
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



