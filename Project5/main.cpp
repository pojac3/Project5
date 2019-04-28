//
//  main.cpp
//  Project5
//
//  Created by Jacob Courtney at the University of Oklahoma for CS 2413 on 4/22/19.
//  Copyright © 2019 Jacob Courtney. All rights reserved.
//

#include <iostream>
#include <queue>
using namespace std;

/**
 * L I N K E D  L I S T =================================================================================================================  L I N K E D  L I S T
 * Some algorithms were taken from "Data Structures for C++" by Sridhar Radhakrishnan, Lee Wise and Chandra Sekharan
 */

template <class DT>
class LinkedList {
protected:
    DT* _info; // the info this linked list is storing
    LinkedList<DT>* _next; // the next LinkedList in the array
public:
    LinkedList(); // default constructor
    LinkedList(DT& i, LinkedList<DT>* n); // constructor
    LinkedList(const LinkedList<DT>& ll);
    virtual ~LinkedList(); //destructor
    DT& operator[](int pos); // square bracket operator
    int size(); // returns the size of the LinkedList
    void add(LinkedList<DT>& newOne); // adds the new LinkedList to the beginning of the list
    void add(const DT& other); // adds a new LinkedList with DT& other as the info
    void insertAt(int pos, DT& x); // inserts a new LinkedList at the specified point in the LinkedList
    DT remove(); // removes the first element of the LinkedList
    DT removeAt(int pos); //goes to the posth element and removes that element
    DT& infoAt(int pos); // gets the info at the specified point in the LinkedList
};

//default constructor. sets _info and _next to NULL
template <class DT>
LinkedList<DT>::LinkedList() {
    _info = NULL;
    _next = NULL;
};

//constructor. sets _info to DT& i and sets _next to the specified LinkedList
template <class DT>
LinkedList<DT>::LinkedList(DT& i, LinkedList<DT>* n) {
    _info = &i;
    _next = n;
};

//deletes the LinkedList and all next values
template <class DT>
LinkedList<DT>::~LinkedList<DT>() {
    if (_info == NULL){
        return;
    }
    else {
        delete _info;
        delete _next;
    }
}

//returns the size of the LinkedList
template <class DT>
int LinkedList<DT>::size() {
    if (_next == NULL) {
        if (_info == NULL) {
            return 0;
        } else {
            return 1;
        }
    }
    return 1+(*_next).size();
};

//adds the specified LinkedList element to the beginning of the LinkedList
template <class DT>
void LinkedList<DT>::add(LinkedList<DT>& newOne) {
    LinkedList<DT>* temp = new LinkedList<DT>(_info,_next);
    _info = new DT(newOne.info());
    _next = temp;
    
};

//adds a new LinkedList element with _info as DT& other to the beginning of the LinkedList
template <class DT>
void LinkedList<DT>::add(const DT& other) {
    if (_info == NULL) {
        _info = new DT (other);
        
    } else {
        LinkedList<DT>* newOne = new LinkedList<DT>(*new DT(*_info),_next);
        *_info = other;
        _next = newOne;
    }
};

//inserts an element at the specified position with info DT& x
template <class DT>
void LinkedList<DT>::insertAt(int pos, DT& x) {
    if (pos == 0) {
        add(x);
    }
    else {
        (*_next).insertAt(pos-1,x);
    }
}

//deletes the LinkedList and then rejoins the pieces
template <class DT>
DT LinkedList<DT>::remove() {
    DT temp = *_info;
    delete _info;
    if (_next == NULL) {
        _info = NULL;
    } else {
        LinkedList<DT>* old = _next;
        _info = _next->_info;
        _next = _next->_next;
        old->_info = NULL;
        old->_next = NULL;
        delete old;
    }
    return temp;
}

//gets the info at the specified position
template<class DT>
DT& LinkedList<DT>::infoAt(int pos) {
    if (pos == 0) {
        return *_info;
    }
    else {
        return _next->infoAt(pos-1);
    }
}

template <class DT>
DT& LinkedList<DT>::operator[](int pos) {
    return infoAt(pos);
}

//coppy constructor
template <class DT>
LinkedList<DT>::LinkedList (const LinkedList<DT>& ll) {
    if (ll._info == NULL) {
        _info = NULL;
    }
    else {
        _info = new DT(*(ll._info));
    }
    if (ll._next == NULL) {
        _next = NULL;
    } else {
        _next = new LinkedList<DT> (*(ll._next));
    }
}

//removes the element at the pos position
template <class DT>
DT LinkedList<DT>::removeAt(int pos) {
    if (pos == 0) {
        return remove();
    } else {
        return _next->removeAt(pos-1);
    }
}

/**
 * A D J A C E N C Y  M A T R I X ============================================================================================== A D J A C E N C Y  M A T R I X
 */

class AdjMatrix {
public:
    AdjMatrix();
    AdjMatrix(int noVertices);
    AdjMatrix(AdjMatrix &M);
    virtual ~AdjMatrix();
    AdjMatrix& operator= (AdjMatrix &M);
    void addEdge(int x, int y);
    friend ostream &operator << (ostream&, AdjMatrix &M); //ostream operator
    int size();
    int* BFS(int startingPoint);
    int noConnectedComponents(int x);
    int nextConnectedComponent(int of, int after);
protected:
    int _size;
    bool** matrix;
};

AdjMatrix::AdjMatrix() {
    _size = 0;
    matrix = new bool*[0];
    matrix[0] = new bool[0];    
    
}

AdjMatrix::AdjMatrix(int noVertices) {
    _size = noVertices;
    matrix = new bool*[size()];
    for (int i = 0; i < size(); i++) {
        matrix[i] = new bool[size()];
    }
}

AdjMatrix::AdjMatrix(AdjMatrix &M) {
    _size = M.size();
    matrix = new bool*[M.size()];
    for (int i = 0; i < M.size(); i++) {
        matrix[i] = new bool[M.size()];
    }
    for (int i = 0; i < M.size(); i++) {
        for (int j = 0; j < M.size(); j++) {
            matrix[i][j] = M.matrix[i][j];
        }
    }
}

AdjMatrix::~AdjMatrix() {}

AdjMatrix& AdjMatrix::operator=(AdjMatrix &M) {
    AdjMatrix* copy = new AdjMatrix(M);
    return *copy;
}

void AdjMatrix::addEdge(int x, int y) {
    matrix[x][y] = true;
}

ostream& operator << (ostream& output, AdjMatrix &M) {
    bool first = true;
    for (int i = 0; i < M.size(); i++) {
        for (int j = 0; j < M.size(); j++) {
            if (M.matrix[i][j]) {
                if (!first) {
                    cout << ", ";
                }
                cout << "(" << i << ", " << j <<")";
                first = false;
            }
        }
    }
    return output;
}

int AdjMatrix::size() {
    return _size;
}

int* AdjMatrix::BFS(int startingPoint) {
    int* BFSnums = new int[size()];
    int visited[size()];
    queue<int>* Q = new queue<int>();
    int currentPos = 0;
    int index = 0;
    
    //initializing BFSnums and visited to all be zeros and falses
    for (int i = 0; i < size(); i++) {
        visited[i] = false;
    }
    for (int i = 0; i < size(); i++) {
        BFSnums[i] = 0;
    }
    
    Q->push(startingPoint);
    visited[startingPoint] = true;
    
    while (!Q->empty()) {
        currentPos = Q->front();
        Q->pop();
        BFSnums[index] = currentPos;
        index++;
        
        int w = nextConnectedComponent(currentPos,0);
        for (int i = 0; i < noConnectedComponents(currentPos); i++) {
            if (!visited[w]) {
                visited[w] = true;
                Q->push(w);
            }
            w = nextConnectedComponent(currentPos, w);
        }
    }
    return BFSnums;
}

int AdjMatrix::noConnectedComponents(int x) {
    int counter = 0;
    for (int i = 0; i < size(); i++) {
        if (matrix[x][i] || matrix[i][x]) {
            counter++;
        }
    }
    return counter;
}

int AdjMatrix::nextConnectedComponent(int of, int after) {
    for (int i = after + 1; i < size(); i++) {
        if (matrix[of][i] || matrix[i][of]) {
            return i;
        }
    }
    return -1;
}

/**
 * A D J A C E N C Y  L I S T ====================================================================================================== A D J A C E N C Y  L I S T
 */

class AdjList {
public:
    AdjList();
    AdjList(int noVertices);
    AdjList(AdjList &M);
    virtual ~AdjList();
    AdjList& operator= (AdjList &M);
    void addEdge(int x, int y);
    friend ostream &operator << (ostream&, AdjList &M); //ostream operator
    int size();
    int* BFS(int startingPoint);
    int* DFS(int startingPoint);
    int noConnectedComponents(int x);
    int nextConnectedComponent(int of, int after);
protected:
    int _size;
    LinkedList<int>* array;
};

AdjList::AdjList() {
    _size = 0;
    array = new LinkedList<int>[0];
}

AdjList::AdjList(int noVertices) {
    _size = noVertices;
    array = new LinkedList<int>[noVertices];
}

AdjList& AdjList::operator=(AdjList &M) {
    AdjList* copy = new AdjList(M);
    return *copy;
}
AdjList::~AdjList() {}

AdjList::AdjList(AdjList &M) {
    _size = M.size();
    array = new LinkedList<int>[M.size()];
    for (int i = 0; i < M.size(); i++) {
        array[i] = M.array[i];
    }
}

int* AdjList::BFS(int startingPoint) {
    int* BFSnums = new int[size()];
    int visited[size()];
    queue<int>* Q = new queue<int>();
    int currentPos = 0;
    int index = 0;
    
    //initializing BFSnums and visited to all be zeros and falses
    for (int i = 0; i < size(); i++) {
        visited[i] = false;
    }
    for (int i = 0; i < size(); i++) {
        BFSnums[i] = 0;
    }
    
    Q->push(startingPoint);
    visited[startingPoint] = true;
    
    while (!Q->empty()) {
        currentPos = Q->front();
        Q->pop();
        BFSnums[index] = currentPos;
        index++;
        
        int w = nextConnectedComponent(currentPos,0);
        for (int i = 0; i < noConnectedComponents(currentPos); i++) {
            if (!visited[w]) {
                visited[w] = true;
                Q->push(w);
            }
            w = nextConnectedComponent(currentPos, w);
        }
    }
    return BFSnums;
    
}

int* AdjList::DFS(int startingPoint) {
    int* DFSnums = new int[size()];
    
    
    
    return DFSnums;
}

void AdjList::addEdge(int x, int y) {
    array[x].add(y);
    array[y].add(x);
}

int AdjList::noConnectedComponents(int x) {
    return array[x].size();
}

int AdjList::nextConnectedComponent(int of, int after) {
    for (int i = after + 1; i < size(); i++) {
        for (int j = 0; j < array[of].size(); j++) {
            if (array[of].infoAt(j) == i) {
                return i;
            }
        }
    }
    return -1;
}

ostream& operator << (ostream& output, AdjList &M) {
    bool first = true;
    for (int i = 0; i < M.size(); i++) {
        for (int j = 0; j < M.array[i].size(); j++) {
            if (i >= M.array[i].infoAt(j)) {
                if (!first) {
                    cout << ", ";
                }
                cout << "(" << i << ", " << M.array[i].infoAt(j) << ")";
                first = false;
            }
        }
    }
    return output;
}

int AdjList::size() {
    return _size;
}

/**
 * M A I N  M E T H O D ================================================================================================================== M A I N  M E T H O D
 */

int main() {
    int noVertices, x, y, i;
    i = 0;
    
    cin >> noVertices;
    
    AdjMatrix* myMatrix = new AdjMatrix(noVertices);
    AdjList* myList = new AdjList(noVertices);
    
    while (i < 2500) {
        cin >> x >> y;
        (*myMatrix).addEdge(x,y);
        (*myList).addEdge(x,y);
        i++;
    }
    
    AdjMatrix myMCopy = *myMatrix;
    AdjList myLCopy = *myList;
    
    cout << "Adjacency Matrix Representation:" << endl << (*myMatrix) << endl << endl;
    cout << "Adjacency List Representation:" << endl << (*myList) << endl << endl;
    cout << "Adjacency Matrix Representation (Copied):" << endl << myMCopy << endl << endl;
    cout << "Adjacency List Representation (Copied):" << endl << myLCopy << endl << endl;
    
    cout << "Breadth First Search on AdjacencyMatrix Representation:" << endl;
    int* _bfs = (*myMatrix).BFS(5);
    for (int i = 0; i < (*myMatrix).size(); i++) {
        cout << i << ": " << _bfs[i];
        if (i != (*myMatrix).size() - 1) {
            cout << ", ";
        } else {
            cout << endl;
        }
    }
    cout << endl;
    
    cout << "Breadth First Search on AdjacencyList Representation:" << endl;
    int* _bfs2 = (*myList).BFS(5);
    for (int i = 0; i < (*myList).size(); i++) {
        cout << i << ": " << _bfs2[i];
        if (i != (*myList).size() - 1) {
            cout << ", ";
        } else {
            cout << endl;
        }
    }
    cout << endl;
}
