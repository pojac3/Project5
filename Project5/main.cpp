//
//  main.cpp
//  Project5
//
//  Created by Jacob Courtney at the University of Oklahoma for CS 2413 on 4/22/19.
//  Copyright © 2019 Jacob Courtney. All rights reserved.
//

#include <iostream>
#include <list>
#include <queue>
using namespace std;

/**
 * A D J A C E N C Y  M A T R I X ==================== A D J A C E N C Y  M A T R I X
 */

class AdjMatrix {
public:
    AdjMatrix();
    AdjMatrix(int noVertices);
    virtual ~AdjMatrix();
    void addEdge(int x, int y);
protected:
    int size;
    bool** matrix;
};

AdjMatrix::AdjMatrix() {
    size = 0;
    matrix = new bool*[0];
    matrix[0] = new bool[0];    
    
}

AdjMatrix::AdjMatrix(int noVertices) {
    size = noVertices;
    matrix = new bool*[size];
    for (int i = 0; i < size; i++) {
        matrix[i] = new bool[size];
    }
}

AdjMatrix::~AdjMatrix() {}

void AdjMatrix::addEdge(int x, int y) {
    
}

/**
 * A D J A C E N C Y  L I S T ================= A D J A C E N C Y  L I S T
 */

class AdjList {
public:
    AdjList();
    AdjList(int noVertices);
    virtual ~AdjList();
    void addEdge(int x, int y);
protected:
    int size;
    list<int>* array;
};

AdjList::AdjList(int noVertices) {
    size = noVertices;
    array = new list<int>[noVertices];
}

AdjList::~AdjList() {}

void AdjList::addEdge(int x, int y) {
    
}


int main() {
    int noVertices, x, y;
    
    cin >> noVertices;
    
    AdjMatrix* myMatrix = new AdjMatrix(noVertices);
    AdjList* myList = new AdjList(noVertices);
    
    while (!cin.eof()) {
        cin >> x >> y;
        (*myMatrix).addEdge(x,y);
        (*myList).addEdge(x,y);
    }
}
