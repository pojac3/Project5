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
    //setting _info and _next to NULL
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
    //if the info here is NULL, then we are at the end of this LinkedList
    if (_info == NULL) {
        //so we shall return
        return;
    }
    else {
        //otherwise, keep destructing
        delete _info;
        delete _next;
    }
}

//returns the size of the LinkedList
template <class DT>
int LinkedList<DT>::size() {
    // if next is NULL, then we are at the end of the LinkedList
    if (_next == NULL) {
        //if info is NULL, then we are near the end
        if (_info == NULL) {
            //so then just return 0
            return 0;
            //otherwise
        } else {
            //return 1!
            return 1;
        }
    }
    //returning the size of the LinkedList so far
    return 1+(*_next).size();
};

//adds the specified LinkedList element to the beginning of the LinkedList
template <class DT>
void LinkedList<DT>::add(LinkedList<DT>& newOne) {
    //creating the new LinkedList to chain the others onto
    LinkedList<DT>* temp = new LinkedList<DT>(_info,_next);
    //setting the info for it..
    _info = new DT(newOne.info());
    //and the chaining it in
    _next = temp;
    
};

//adds a new LinkedList element with _info as DT& other to the beginning of the LinkedList
template <class DT>
void LinkedList<DT>::add(const DT& other) {
    //if the info is NULL here then we are at the end of the LinkedList
    if (_info == NULL) {
        //so just add it into this one!
        _info = new DT (other);
        //otherwise..
    } else {
        //make a new one to add it in to..
        LinkedList<DT>* newOne = new LinkedList<DT>(*new DT(*_info),_next);
        //set its info..
        *_info = other;
        //and chain it in!
        _next = newOne;
    }
};

//inserts an element at the specified position with info DT& x
template <class DT>
void LinkedList<DT>::insertAt(int pos, DT& x) {
    //if the pos is zero, then just add it in right here
    if (pos == 0) {
        //adding it in
        add(x);
    }
    //otherwise..
    else {
        //recursively go down the LinkedList and get to where pos == 0
        (*_next).insertAt(pos-1,x);
    }
}

//deletes the LinkedList and then rejoins the pieces
template <class DT>
DT LinkedList<DT>::remove() {
    //making a temporary LinkedList which we will chain in later
    DT temp = *_info;
    //deleting the info
    delete _info;
    //if next is NULL then we are at the end of the LinkedList
    if (_next == NULL) {
        //so well delete it here by setting info to NULL
        _info = NULL;
        //otherwise..
    } else {
        //make this ones next into another temporary one
        LinkedList<DT>* old = _next;
        //set its info
        _info = _next->_info;
        //and its next
        _next = _next->_next;
        //and delete the old ones info
        old->_info = NULL;
        //and the old ones next
        old->_next = NULL;
        //and finally delete it from memory
        delete old;
    }
    //and then return the temp one we made earlier
    return temp;
}

//gets the info at the specified position. returns type DT
template<class DT>
DT& LinkedList<DT>::infoAt(int pos) {
    //if pos is 0 then we are where we need to be
    if (pos == 0) {
        //so get the info here
        return *_info;
    }
    //otherwise..
    else {
        //keep recursively going down!
        return _next->infoAt(pos-1);
    }
}

//square bracket operator!
template <class DT>
DT& LinkedList<DT>::operator[](int pos) {
    //simply returns the infoAt here
    return infoAt(pos);
}

//copy constructor
template <class DT>
LinkedList<DT>::LinkedList (const LinkedList<DT>& ll) {
    //if the info here is null then we are where we need to be
    if (ll._info == NULL) {
        //so we will also set the copies info to NULL
        _info = NULL;
    }
    //otherwise
    else {
        //copy the info into the new one
        _info = new DT(*(ll._info));
    }
    //if the next one is null, then we are at the end of the linkedlist
    if (ll._next == NULL) {
        //so set the end of the linkedlist for the new one too
        _next = NULL;
        //otherwise
    } else {
        //copy the next into the new one!
        _next = new LinkedList<DT> (*(ll._next));
    }
}

//removes the element at the pos position
template <class DT>
DT LinkedList<DT>::removeAt(int pos) {
    //if pos is 0 then we are where we need to be
    if (pos == 0) {
        //so then remove it
        return remove();
        //otherwise
    } else {
        //keep recursively going down
        return _next->removeAt(pos-1);
    }
}

/**
 * A D J A C E N C Y  M A T R I X ============================================================================================== A D J A C E N C Y  M A T R I X
 */

class AdjMatrix {
public:
    AdjMatrix(); //default constructor
    AdjMatrix(int noVertices); //regular constructor
    AdjMatrix(AdjMatrix &M); //copy constructor
    virtual ~AdjMatrix(); //destructor
    AdjMatrix& operator= (AdjMatrix &M); //assignment operator
    void addEdge(int x, int y); //adds an edge to the graph
    friend ostream &operator << (ostream&, AdjMatrix &M); //ostream operator
    int size(); //returns the number of vertices of the graph
    int* BFS(int startingPoint); //returns an array with the Breadth First Search traversal of the graph
    int noConnectedComponents(int x); //returns the number of components connected to the node x
    int nextConnectedComponent(int of, int after); //returns the next smallest connected node to "of" after "after"
protected:
    int _size; //stores the number of vertices
    bool** matrix; //stores the 2d matrix representation of the graph
};

//default constructor
AdjMatrix::AdjMatrix() {
    //sets size to 0
    _size = 0;
    //sets the x component array to be of size 0
    matrix = new bool*[0];
    //and also sets the y component array to be of size 0
    matrix[0] = new bool[0];    
    
}

//regular constructor. takes in the number of vertices as an integer
AdjMatrix::AdjMatrix(int noVertices) {
    //setting _size to be the number of vertices
    _size = noVertices;
    //instantiating the x axis component to be of size _size
    matrix = new bool*[size()];
    //and looping through each component of the x axis and instantiating each y axis component to be an array of size _size
    for (int i = 0; i < size(); i++) {
        matrix[i] = new bool[size()];
    }
}

//copy constructor
AdjMatrix::AdjMatrix(AdjMatrix &M) {
    //copying the size
    _size = M.size();
    //copying the size of the x axis component
    matrix = new bool*[M.size()];
    //instantiating each y axis array
    for (int i = 0; i < M.size(); i++) {
        matrix[i] = new bool[M.size()];
    }
    //and finally copying over data to the xy plane
    for (int i = 0; i < M.size(); i++) {
        //nested for loop
        for (int j = 0; j < M.size(); j++) {
            //doing the copying on (i,j)
            matrix[i][j] = M.matrix[i][j];
        }
    }
}

//destructor. calls the defauly garbage collector
AdjMatrix::~AdjMatrix() {}

//assignment operator calls the copy constructor
AdjMatrix& AdjMatrix::operator=(AdjMatrix &M) {
    //making the copy
    AdjMatrix* copy = new AdjMatrix(M);
    //and returning it
    return *copy;
}

//addEdge method. adds an edge between x and y
void AdjMatrix::addEdge(int x, int y) {
    //setting the value stored at (x,y) to be true
    matrix[x][y] = true;
}

//ostream operator
ostream& operator << (ostream& output, AdjMatrix &M) {
    //keeping track of whether or not to put a ", "
    bool first = true;
    //looping through the x components
    for (int i = 0; i < M.size(); i++) {
        //looping through the y components
        for (int j = 0; j < M.size(); j++) {
            //if the value at (i, j) is true
            if (M.matrix[i][j]) {
                //and if this value isnt the first one
                if (!first) {
                    //cout ", "
                    cout << ", ";
                }
                //and always cout the (i, j)
                cout << "(" << i << ", " << j <<")";
                //no longer first
                first = false;
            }
        }
    }
    //returning th output
    return output;
}

//simply returns the noVertices
int AdjMatrix::size() {
    //returning _size
    return _size;
}

//Breadth First Search Algorithm. This function is exactly equivalent to the implementation of BFS for
//AdjList as well, all that needs changed are the helper methods
int* AdjMatrix::BFS(int startingPoint) {
    //this is the array we will return
    int* BFSnums = new int[size()];
    //keeping track of which nodes have been visited
    int visited[size()];
    //the queue we are using for this algorithm
    queue<int>* Q = new queue<int>();
    //the current position
    int currentPos = 0;
    //and the index in the BFSnums array
    int index = 0;
    
    //initializing BFSnums and visited to all be zeros and falses
    for (int i = 0; i < size(); i++) {
        //setting to false
        visited[i] = false;
    }
    //setting all of BFSnums to be 0's
    for (int i = 0; i < size(); i++) {
        //setting to 0
        BFSnums[i] = 0;
    }
    
    //pushing the first element to the queue
    Q->push(startingPoint);
    //and making sure to mark it as visited
    visited[startingPoint] = true;
    
    //go through until the queue is empty
    while (!Q->empty()) {
        //we will make our current position the node that is at the front of the queue
        currentPos = Q->front();
        //and then pop it off once we have grabbed it
        Q->pop();
        //setting the corresponding value in BFSnums to whatever is at the current position
        BFSnums[index] = currentPos;
        //incrementing the index
        index++;
        
        //w is another type of "currentPos" and we will start at the first connected component to currentPos 
        //greater than 0
        int w = nextConnectedComponent(currentPos,0);
        //this loop adds every component to currentPos to the queue
        for (int i = 0; i < noConnectedComponents(currentPos); i++) {
            //making sure we havent already visited this position
            if (!visited[w]) {
                //if we havent then we mark it as visited
                visited[w] = true;
                //and push it to the queue
                Q->push(w);
            }
            //then go to the next component connected to currentPos greater than the one we are already one
            w = nextConnectedComponent(currentPos, w);
        }
    }
    //and return the BFSnums
    return BFSnums;
}

//this helper method finds the total number of components connected to a node x
int AdjMatrix::noConnectedComponents(int x) {
    //our counter will start at 0
    int counter = 0;
    //and we will loop through the x component of the matrix
    for (int i = 0; i < size(); i++) {
        //if the value there is true then we will increment the counter
        if (matrix[x][i] || matrix[i][x]) {
            //incrementing the counter
            counter++;
        }
    }
    //once weve looped through, we will return the counter
    return counter;
}

//this helper method finds the next component connected to "of" that is greater than "after"
int AdjMatrix::nextConnectedComponent(int of, int after) {
    //we will loop through the x component, starting after "after" + 1. this will ensure that we dont 
    //get values smaller than of "after"
    for (int i = after + 1; i < size(); i++) {
        //since we want to find the node connected to of, then we will use that as our other axis
        if (matrix[of][i] || matrix[i][of]) {
            //if its true, then return where we found it
            return i;
        }
    }
    //if we found nothing, than return -1. we shouldnt ever have to call this line of code though
    return -1;
}

/**
 * A D J A C E N C Y  L I S T ====================================================================================================== A D J A C E N C Y  L I S T
 */

class AdjList {
public:
    AdjList(); //default constructor
    AdjList(int noVertices); //regular constructor takes in the number of vertices as an int
    AdjList(AdjList &M); //copy constructor
    virtual ~AdjList(); //destructor
    AdjList& operator= (AdjList &M); //assignment operator
    void addEdge(int x, int y); //adds the edge (x, y) to the graph
    friend ostream &operator << (ostream&, AdjList &M); //ostream operator
    int size(); //returns the number of vertices
    int* BFS(int startingPoint); //breadth first search algorithm returns an array with the BFS containted, starting at startingPoint
//    int* DFS(int startingPoint); //depth first search algorithm returns an array with the BFS containted, starting at startingPoint
    int noConnectedComponents(int x); //gets the number of nodes connected to a node x
    int nextConnectedComponent(int of, int after); //gets the next connected node to of after after
protected:
    int _size; //stores the number of vertices as an int
    LinkedList<int>* array; //array that stores lists as its components, and those lists contain data
};

//default constructor
AdjList::AdjList() {
    //sets the size to 0
    _size = 0;
    //and the size of the array of lists to 0
    array = new LinkedList<int>[0];
}

//regular constructor takes in an int which is the specified number of vertices
AdjList::AdjList(int noVertices) {
    //sets _size to be the number of vertices
    _size = noVertices;
    //sets the size of the array of lists to be the number of vertices
    array = new LinkedList<int>[noVertices];
}

//assignment operator
AdjList& AdjList::operator=(AdjList &M) {
    //makes a new copy using the copy constructor
    AdjList* copy = new AdjList(M);
    //and returns it
    return *copy;
}

//destructor calls the default garbage collector
AdjList::~AdjList() {}

//copy constructor
AdjList::AdjList(AdjList &M) {
    //setting the copies size to be the size of this one
    _size = M.size();
    //and making the array with that same size
    array = new LinkedList<int>[M.size()];
    //looping through and copying each piece of data by hand
    for (int i = 0; i < M.size(); i++) {
        //setting the data
        array[i] = M.array[i];
    }
}

//Breadth First Search Algorithm. This function is exactly equivalent to the implementation of BFS for
//AdjMatrix as well, all that needs changed are the helper methods
int* AdjList::BFS(int startingPoint) {
    //this is the array we will return
    int* BFSnums = new int[size()];
    //keeping track of which nodes have been visited
    int visited[size()];
    //the queue we are using for this algorithm
    queue<int>* Q = new queue<int>();
    //the current position
    int currentPos = 0;
    //and the index in the BFSnums array
    int index = 0;
    
    //initializing BFSnums and visited to all be zeros and falses
    for (int i = 0; i < size(); i++) {
        //setting to false
        visited[i] = false;
    }
    //setting all of BFSnums to be 0's
    for (int i = 0; i < size(); i++) {
        //setting to 0
        BFSnums[i] = 0;
    }
    
    //pushing the first element to the queue
    Q->push(startingPoint);
    //and making sure to mark it as visited
    visited[startingPoint] = true;
    
    //go through until the queue is empty
    while (!Q->empty()) {
        //we will make our current position the node that is at the front of the queue
        currentPos = Q->front();
        //and then pop it off once we have grabbed it
        Q->pop();
        //setting the corresponding value in BFSnums to whatever is at the current position
        BFSnums[index] = currentPos;
        //incrementing the index
        index++;
        
        //w is another type of "currentPos" and we will start at the first connected component to currentPos 
        //greater than 0
        int w = nextConnectedComponent(currentPos,0);
        //this loop adds every component to currentPos to the queue
        for (int i = 0; i < noConnectedComponents(currentPos); i++) {
            //making sure we havent already visited this position
            if (!visited[w]) {
                //if we havent then we mark it as visited
                visited[w] = true;
                //and push it to the queue
                Q->push(w);
            }
            //then go to the next component connected to currentPos greater than the one we are already one
            w = nextConnectedComponent(currentPos, w);
        }
    }
    //and return the BFSnums
    return BFSnums;
}
/*
//depth first search algorithm. still needs to be implemented
int* AdjList::DFS(int startingPoint) {
    //creating the array that we will return
    int* DFSnums = new int[size()];
    
    //nothing to see here *whistles
    
    //and returning it
    return DFSnums;
}
*/
//adds an edge to the graph between x and y. it is undirected so we will add it going both ways
void AdjList::addEdge(int x, int y) {
    //adding it as (x, y)
    array[x].add(y);
    //adding it as (y, x)
    array[y].add(x);
}

//finds the number of nodes connected to this node
int AdjList::noConnectedComponents(int x) {
    //simply returns the size of the LinkedList at that node
    return array[x].size();
}

//returns the next connected node to of after after
int AdjList::nextConnectedComponent(int of, int after) {
    //looping through the array
    for (int i = after + 1; i < size(); i++) {
        //looping through the list at that point in the array
        for (int j = 0; j < array[of].size(); j++) {
            //if the info is equal to i
            if (array[of].infoAt(j) == i) {
                //then just return i
                return i;
            }
        }
    }
    //shouldnt have to ever return -1, but xcode yells at me if i dont put this here
    return -1;
}

//ostream operator
ostream& operator << (ostream& output, AdjList &M) {
    //keeps track of whether we need to print the ", "
    bool first = true;
    //looping through the array
    for (int i = 0; i < M.size(); i++) {
        //looping through the list at that point in the array
        for (int j = 0; j < M.array[i].size(); j++) {
            //need this if statement so we dont print each vertice twice
            if (i >= M.array[i].infoAt(j)) {
                //if this is not the first one were printing then print ", "
                if (!first) {
                    cout << ", ";
                }
                //printing the i and the component we are on
                cout << "(" << i << ", " << M.array[i].infoAt(j) << ")";
                //setting first to false
                first = false;
            }
        }
    }
    //returning the output
    return output;
}

//returns the size (number of vertices)
int AdjList::size() {
    //returning it
    return _size;
}

/**
 * M A I N  M E T H O D ================================================================================================================== M A I N  M E T H O D
 */

int main() {
    //x and y are the edges, i is the index
    int noVertices, x, y, i;
    //index
    i = 0;
    
    //getting the number of vertices
    cin >> noVertices;
    
    //creating an AdjMatrix and AdjList
    AdjMatrix* myMatrix = new AdjMatrix(noVertices);
    //creating the AdjList
    AdjList* myList = new AdjList(noVertices);
    
    //go through until end of file (right now were only going through 10 times
    //since xcode doesnt support redirected input(:
    while (!cin.eof()) {
        //getting x and y
        cin >> x >> y;
        //adding the edge to the AdjMatrix
        (*myMatrix).addEdge(x,y);
        //adding the edge to the AdjList
        (*myList).addEdge(x,y);
        //increment i
        i++;
        cout << i << " ";
    }
    
    //making a copy of each
    AdjMatrix myMCopy = *myMatrix;
    //copy of AdjList
    AdjList myLCopy = *myList;
    
    //printing the originals and the copies
    cout << "Adjacency Matrix Representation:" << endl << (*myMatrix) << endl << endl;
    //original Adjacency List
    cout << "Adjacency List Representation:" << endl << (*myList) << endl << endl;
    //copy of AdjMatrix
    cout << "Adjacency Matrix Representation (Copied):" << endl << myMCopy << endl << endl;
    //copy of AdjList
    cout << "Adjacency List Representation (Copied):" << endl << myLCopy << endl << endl;
    
    //doing the Breadth First Search and storing it
    cout << "Breadth First Search on AdjacencyMatrix Representation:" << endl;
    //doing the bfs
    int* _bfs = (*myMatrix).BFS(5);
    //looping through the bfs array it gave us
    for (int i = 0; i < (*myMatrix).size(); i++) {
        //printing the value there
        cout << i << ": " << _bfs[i];
        //tells us whether to print a comma
        if (i != (*myMatrix).size() - 1) {
            //printing the comma
            cout << ", ";
            //otherwise..
        } else {
            //just end line and be done!
            cout << endl;
        }
    }
    //another endline just for prettiness
    cout << endl;
    
    //doing the Breadth First Search and storing it
    cout << "Breadth First Search on AdjacencyList Representation:" << endl;
    //doing the bfs
    int* _bfs2 = (*myList).BFS(5);
    //looping through the bfs array it gave us
    for (int i = 0; i < (*myList).size(); i++) {
        //printing the value there
        cout << i << ": " << _bfs2[i];
        //tells us whether to print a comma
        if (i != (*myList).size() - 1) {
            //printing the comma
            cout << ", ";
            //otherwise
        } else {
            //just endline and be done
            cout << endl;
        }
    }
    //and once again end line just for prettiness
    cout << endl;
}
