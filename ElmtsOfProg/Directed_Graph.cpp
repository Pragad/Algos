#include <iostream>
#include <algorithm>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <stack>
#include <queue>
#include <functional>   // Contains function for hash
#include <ctime>
using namespace std;

// -----------------------------------------------------------------------------------------
// This is a Directed Graph
// -----------------------------------------------------------------------------------------

// -----------------------------------------------------------------------------------------
// Graph Class
        // Have a vector to store all Vertices of the Graph
        // MAP:
        //      The map is used to quickly tell if Vertex is present or not based on the the
        //      data. 
        //      Key: hash(data) given to Vertex
        //      Val: Place where Vertex is stored on the Vector
        //
        //      So with a Vertex's data, we can hash it to get the Key.
        //      Using the key, find if Vertex is present; Also where the Vertex is present
        //
        // The map also gives where the Vertex is stored in the vector
// -----------------------------------------------------------------------------------------
class Graph
{
    private:
        class Node; // Forward Declaration

        vector<Node*> _allNodes;
        unordered_map<uint32_t, Node*> _nodesMap;

        // Inner Class corresponding to a Node of a graph.
        // Each Node has
        //      1) Integer that uniquely represents the node
        //      2) List of Neighbor nodes that can be zero or more
        class Node
        {
        public:
            uint32_t _id;   // A unique integer to represent each node
            vector<Node*> _neighborNodes;
            unordered_set<uint32_t> _uniqNeighbors;

            Node(uint32_t id)
            {
                _id = id;
                _uniqNeighbors.insert(id);
            }

            uint32_t getId() { return _id; }

            // This function adds a Neighbor Node to the given node
            void addNeighborNode(Node* node)
            {
                auto itr = _uniqNeighbors.find(node->_id);

                if (itr != _uniqNeighbors.end())
                {
                    cout << "Duplicate Neighbor: " << node->_id << " for Parent: " << _id <<  ". Unable to add neighbor node" << endl;
                    return;
                }

                _uniqNeighbors.insert(node->_id);
                _neighborNodes.push_back(node);
            }

            // This utility function prints all edges of a Vertex
            void printNeighborNodes()
            {
                cout << _id << " -> ";

                if (_neighborNodes.empty())
                {
                    cout << "No Neighbors" << endl;
                    return;
                }
                
                Node* node = _neighborNodes[0];
                cout << node->_id;
                for(uint32_t i = 1; i < _neighborNodes.size(); i++)
                {
                    cout << ", " << _neighborNodes[i]->_id;
                }
                cout << endl;
            }
        };

    public:
        void createNode(uint32_t id);
        void insertNode(uint32_t parent, uint32_t neighbor);
        bool doesPathExist(uint32_t srcId, uint32_t destId);
        void printGraph();

        bool isCyclePresent();

        // BFS on graph
        void printGraphBfs(int);
        void printGraphBfs(Node*);

        // DFS on graph
        void printGraphDfs(int);
        void printGraphDfs(Node*);
        void printGraphDfsRec(Node* startNode, unordered_set<Node*>& isVisitedSet);

        // Topological Sort on Graph
        void topologicalSort();
        void printGraphDfsItrTopo(Node* startNode, unordered_set<Node*>& isVisitedSet);
        void printGraphDfsRecTopo(Node* startNode, unordered_set<Node*>& isVisitedSet, vector<uint32_t>& topoOrder);
        ~Graph();

};

// -----------------------------------------------------------------------------------------
// Graph Destructor
// -----------------------------------------------------------------------------------------
Graph::~Graph()
{
    for (auto node : _allNodes)
    {
        delete node;
    }
}

// -----------------------------------------------------------------------------------------
// createNode()
// -----------------------------------------------------------------------------------------
void
Graph::createNode(uint32_t id)
{
    Node* node = new Node(id);

    auto itr = _nodesMap.find(id);
    if (itr != _nodesMap.end())
    {
        cout << "ID is already present" << endl;
        return;
    }

    _allNodes.push_back(node);
    _nodesMap[id] = node;
}

// -----------------------------------------------------------------------------------------
// Function to check if there exists a path between two nodes
// -----------------------------------------------------------------------------------------
bool
Graph::doesPathExist(uint32_t srcId, uint32_t destId)
{
    Node* src = _nodesMap[srcId];
    Node* dest = _nodesMap[destId];
    stack<uint32_t> dfsStack;
    unordered_set<uint32_t> visitedNodes;

    if (srcId == destId)
    {
        return true;
    }

    dfsStack.push(srcId);    

    while(!dfsStack.empty())
    {
        uint32_t top = dfsStack.top();
        dfsStack.pop();

        for(auto neighborNode : _nodesMap[top]->_neighborNodes)
        {
            if (neighborNode->_id == destId)
            {
                // Path exists. Return true
                return true;
            }
            else
            {
                // Make sure this node is not visited already
                // If we have visited this node, go to next node
                auto itr = visitedNodes.find(neighborNode->_id);

                if (itr == visitedNodes.end())
                {
                    visitedNodes.insert(neighborNode->_id);
                    dfsStack.push(neighborNode->_id);
                }
            }
        }
    }

    return false;
}

// -----------------------------------------------------------------------------------------
// insertNode()
// -----------------------------------------------------------------------------------------
void
Graph::insertNode(uint32_t parentId, uint32_t neighborId)
{
    auto itr1 = _nodesMap.find(parentId);
    auto itr2 = _nodesMap.find(neighborId);

    // Make sure that parent and neighbor nodes are present
    if (itr1 == _nodesMap.end() || itr2 == _nodesMap.end())
    {
        cout << "Invalid Node IDs" << endl;
        return;
    }

    // If there is a path from neighbor to parent then adding this Edge from parent to
    // neighbor will result in a cycle
    if (doesPathExist(neighborId, parentId))
    {
        cout << "Path Exists from " << neighborId << " to " << parentId  <<  ". Unable to add neighbor node" << endl;
        return;
    }

    _nodesMap[parentId]->addNeighborNode(itr2->second);
}

// -----------------------------------------------------------------------------------------
// Utility function to print the complete graph
// -----------------------------------------------------------------------------------------
void
Graph::printGraph()
{
    cout << endl;
    for (auto node : _allNodes)
    {
        node->printNeighborNodes();
    }
}

// -----------------------------------------------------------------------------------------
// Utility function to print the complete graph in BFS
// -----------------------------------------------------------------------------------------
void
Graph::printGraphBfs(Node* startNode)
{
    cout << endl << "Graph in BFS" << endl;
    queue<Node*> bfsNodesQueue;
    unordered_set<Node*> isVisitedMap;

    if (startNode == NULL)
    {
        return;
    }

    bfsNodesQueue.push(startNode);
    isVisitedMap.insert(startNode);

    while (!bfsNodesQueue.empty())
    {
        Node* curNode = bfsNodesQueue.front();
        bfsNodesQueue.pop();

        cout << curNode->_id << ", ";
        
        for (auto neighborNode : curNode->_neighborNodes)
        {
            auto itr = isVisitedMap.find(neighborNode);
            if (itr == isVisitedMap.end())
            {
                bfsNodesQueue.push(neighborNode);
                isVisitedMap.insert(neighborNode);
            }
        }
    }

    cout << endl;
}

void
Graph::printGraphBfs(int nodeId)
{
    auto itr = _nodesMap.find(nodeId);

    if (itr == _nodesMap.end())
    {
        cout << "Invalid Node ID for BFS" << endl;
    }
    printGraphBfs(_nodesMap[nodeId]);
}

// -----------------------------------------------------------------------------------------
// Utility function to print the complete graph in DFS Iteratively
// -----------------------------------------------------------------------------------------
void
Graph::printGraphDfs(Node* startNode)
{
    stack<Node*> dfsNodesStack;
    unordered_set<Node*> isVisitedSet;

    if (startNode == NULL)
    {
        return;
    }

    dfsNodesStack.push(startNode);
    isVisitedSet.insert(startNode);

    while (!dfsNodesStack.empty())
    {
        Node* curNode = dfsNodesStack.top();
        dfsNodesStack.pop();

        cout << curNode->_id << ", ";
        
        for (auto neighborNode : curNode->_neighborNodes)
        {
            auto itr = isVisitedSet.find(neighborNode);
            if (itr == isVisitedSet.end())
            {
                dfsNodesStack.push(neighborNode);
                isVisitedSet.insert(neighborNode);
            }
        }
    }

    cout << endl;
}

// -----------------------------------------------------------------------------------------
// Utility function to print the complete graph in DFS Recursively
// -----------------------------------------------------------------------------------------
void
Graph::printGraphDfsRec(Node* startNode, unordered_set<Node*>& isVisitedSet)
{
    if (startNode == NULL)
    {
        return;
    }

    isVisitedSet.insert(startNode);
    cout << startNode->_id << ", ";
        
    for (auto neighborNode : startNode->_neighborNodes)
    {
        auto itr = isVisitedSet.find(neighborNode);
        if (itr == isVisitedSet.end())
        {
            printGraphDfsRec(neighborNode, isVisitedSet);
        }
    }
}

void
Graph::printGraphDfs(int nodeId)
{
    auto itr = _nodesMap.find(nodeId);
    unordered_set<Node*> isVisitedSet;

    if (itr == _nodesMap.end())
    {
        cout << "Invalid Node ID for DFS" << endl;
    }

    cout << endl << "Graph in DFS Iterative" << endl;
    printGraphDfs(_nodesMap[nodeId]);

    cout << endl << "Graph in DFS Recursive" << endl;
    printGraphDfsRec(_nodesMap[nodeId], isVisitedSet);
    cout << endl;
}

// -----------------------------------------------------------------------------------------
// Is Cycle Present
// -----------------------------------------------------------------------------------------
bool
Graph::isCyclePresent()
{
    bool isCycle = false;

    return isCycle;
}

// -----------------------------------------------------------------------------------------
// Topological Sort
// -----------------------------------------------------------------------------------------
/*
void
Graph::printGraphDfsItrTopo(Node* startNode, unordered_set<Node*>& isVisitedSet)
{
    stack<Node*> dfsNodesStack;
    if (startNode == NULL)
    {
        return;
    }

    dfsNodesStack.push(startNode);
    isVisitedSet.insert(startNode);

    while (!dfsNodesStack.empty())
    {
        Node* curNode = dfsNodesStack.top();
        dfsNodesStack.pop();
        cout << "Stack Entry: " << curNode->_id << endl;

        bool hasNeighbors = false;
        for (auto neighborNode : curNode->_neighborNodes)
        {
            auto itr = isVisitedSet.find(neighborNode);
            if (itr == isVisitedSet.end())
            {
                hasNeighbors = true;
                dfsNodesStack.push(neighborNode);
                isVisitedSet.insert(neighborNode);
            }
        }

        if (!hasNeighbors)
        {
            cout << "C: " << curNode->_id << ", ";
        }
    }
        
    cout << "S: " << startNode->_id << ", ";
}
*/

void
Graph::printGraphDfsRecTopo(Node* startNode, unordered_set<Node*>& isVisitedSet, vector<uint32_t>& topoOrder)
{
    if (startNode == NULL)
    {
        return;
    }

    isVisitedSet.insert(startNode);
        
    for (auto neighborNode : startNode->_neighborNodes)
    {
        auto itr = isVisitedSet.find(neighborNode);
        if (itr == isVisitedSet.end())
        {
            printGraphDfsRecTopo(neighborNode, isVisitedSet, topoOrder);
        }
    }

    // Instead of printing you can push everything to stack and get it back in reverse order
    cout << startNode->_id << ", ";
    topoOrder.push_back(startNode->_id);
}

void
Graph::topologicalSort()
{
    /*
    {
        cout << endl << "Topological Sort In Reverse Order Iterative" << endl;
        unordered_set<Node*> isVisitedSet;

        for (auto node : _allNodes)
        {
            auto itr = isVisitedSet.find(node);
            if (itr == isVisitedSet.end())
            {
                printGraphDfsItrTopo(node, isVisitedSet);
            }
        }
    }
    */

    {
        cout << endl << "Topological Sort In Reverse Order Recursive" << endl;
        unordered_set<Node*> isVisitedSet;
        vector<uint32_t> topoOrder;

        for (auto node : _allNodes)
        {
            auto itr = isVisitedSet.find(node);
            if (itr == isVisitedSet.end())
            {
                printGraphDfsRecTopo(node, isVisitedSet, topoOrder);
            }
        }
        cout << endl;

        std::reverse(topoOrder.begin(), topoOrder.end()); 

        for (auto i : topoOrder)
        {
            cout << i << ", ";
        }
        cout << endl;
    }
}

// -----------------------------------------------------------------------------------------
// Main Function
// -----------------------------------------------------------------------------------------
int main()
{
    /*
     * Imagine a directed version of the below graph
     *
     *      2 ----- 5 
     *    /       /  \
     *  1 ---- 4 ---- 6
     *    \   /       |   
     *      3 --------
     */

    Graph g;
    g.createNode(1);

    g.createNode(2);
    g.createNode(3);
    g.createNode(4);
    g.createNode(5);
    g.createNode(6);

    g.insertNode(1, 2);
    g.insertNode(1, 3);
    g.insertNode(1, 4);
    g.insertNode(1, 4);
    g.insertNode(1, 1);

    g.insertNode(2, 5);

    g.insertNode(3, 6);

    g.insertNode(4, 3);
    g.insertNode(4, 6);

    g.insertNode(5, 6);
    g.insertNode(6, 1);
    g.insertNode(6, 2);

    // Print Graph
    g.printGraph();
    g.printGraphBfs(1);
    g.printGraphDfs(1);

    // Topological Sort
    g.topologicalSort();
    cout << endl;
    return 0;
}

