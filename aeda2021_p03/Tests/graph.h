#include <iostream>
#include <vector>

using namespace std;

template <class N, class E> class Edge;

template <class N, class E>
class Node {
public:
    N info;
    vector< Edge<N,E> > edges;
    Node(N inf) {
        info = inf;
    }
};

template <class N, class E>
class Edge {
public:
    E value;
    Node<N,E> *destination;
    Edge(Node<N,E> *dest, E val) {
        value = val;
        destination = dest;
    }
};

template <class N, class E>
class Graph {
    vector< Node<N,E> *> nodes;
public:
    Graph();
    ~Graph();
    Graph & addNode(const N &inf);
    Graph & addEdge(const N &begin, const N &end, const E &val);
//    Graph & removeEdge(const N &begin, const N &end);
//    E & edgeValue(const N &begin, const N &end);
    unsigned numEdges(void) const;
    unsigned numNodes(void) const;
//    void print(std::ostream &os) const;
};

template <class N, class E>
std::ostream & operator<<(std::ostream &out, const Graph<N,E> &g);


// exception NodeAlreadyExists
template <class N>
class NodeAlreadyExists
{
public:
    N info;
    NodeAlreadyExists(N inf) { info=inf; }
};

template <class N>
std::ostream & operator<<(std::ostream &out, const NodeAlreadyExists<N> &no)
{ out << "Node already exists: " << no.info; return out; }


// exception NodeDoesNotExist
template <class N>
class NodeDoesNotExist {
public:
    N info;
    NodeDoesNotExist(N inf) {
        info = inf;
    }
};


template <class E>
class EdgeAlreadyExists {
public:
    E value;
    EdgeAlreadyExists(E val) {
        value = val;
    }
};


template <class N>
std::ostream & operator<<(std::ostream &out, const NodeDoesNotExist<N> &no)
{ out << "Node does not exist: " << no.info; return out; }

template <class N, class E>
Graph<N,E>::Graph(){

}

template <class N, class E>
Graph<N,E>::~Graph(){
    typename vector< Node<N,E> *>::const_iterator it;
    for (it = nodes.begin(); it != nodes.end(); it++)
    {
        delete *it;
    }
    nodes.clear();
}

template <class N, class E>
unsigned Graph<N,E>::numNodes() const {
    return nodes.size();
}

template <class N, class E>
unsigned Graph<N,E>::numEdges() const {
    unsigned num_edges = 0;
    typename vector< Node<N,E> *>::const_iterator it;
    for (it = nodes.begin(); it != nodes.end(); it++)
    {
        num_edges += (*it)->edges.size();
    }
    return num_edges;
}

template <class N, class E>
Graph<N, E> & Graph<N,E>::addNode(const N &inf) {
    typename vector< Node<N,E> *>::const_iterator it;
    for (it = nodes.begin(); it != nodes.end(); it++)
    {
        if ((*it)->info == inf) throw NodeAlreadyExists<N>(inf);
    }
    nodes.push_back(new Node<N,E>(inf));
    return *this;
}

template <class N, class E>
Graph<N, E> & Graph<N,E>::addEdge(const N &begin, const N &end, const E &val) {
    typename vector< Node<N,E> *>::const_iterator node_it;
    typename vector< Edge<N,E> >::const_iterator edge_it;
    bool found_begin = false;
    bool found_end = false;
    Node<N,E> *node_begin = NULL;
    Node<N,E> *node_end = NULL;
    for (node_it = nodes.begin(); node_it != nodes.end(); node_it++){
        if((*node_it)->info == begin){
            found_begin = true;
            node_begin = *node_it;
            for (edge_it = (*node_it)->edges.begin(); edge_it != (*node_it)->edges.end(); edge_it++){
                if (edge_it->valuea == val) throw EdgeAlreadyExists<E>(val);
            }
        }
    }
}