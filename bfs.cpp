#include <bits/stdc++.h>
#include <unistd.h>
#include <chrono>
#include <ctime>
using namespace std;
using namespace std::chrono;
  
// This class uses an adjacency list
class Graph
{
    int V;    // vertices in the graph
    int endingNode; // The end node or destination node
    list<int> *adj;    // adjacency lists
    
    // queue to store the most optimal path
    list<int> queue;
    
    
	public:
    Graph(int V);  // Constructor
    void addEdge(int v, int w, int weight); // adds an edge
    
    void setEndingNode(int e); //set Ending Node
  
    // finds shortest path where as s is the original position and d is the destination 
    int findShortestPath(int s, int d);

	// Prints out the most optimal path to reach the destination node
    int printShortestPath(int parent[], int s, int d);
    
    // getter for end node
    int getEndNode();
};
  
Graph::Graph(int V)
{
	// Set the number of vertices for the instance of the graph class and set the adj list to doube the size of V
    this->V = V;
    adj = new list<int>[2*V];
}
  
void Graph::addEdge(int v, int w, int weight)
{
    //Checks if weight is bigger or equal to 2
    if (weight>=2)
    {
    	//  at the index of v in the adj list push back the value of v+V and proceed to push back the weight w to the index of v+V in the adj list
        adj[v].push_back(v+V);
        adj[v+V].push_back(w);
    }
    else // Weight is 1
        adj[v].push_back(w); // Add w to v’s list.
}


// Setter for ending node / dest node
void Graph::setEndingNode(int e){
	cout<<e<<endl;
	this->endingNode = e;
}
  
int Graph::getEndNode(){
	return this->endingNode;
}


int Graph::printShortestPath(int parent[], int s, int d)
{
    static int level = 0;
  
    // If we reached root of shortest path tree	
    if (parent[s] == -1)
    {
        cout << "Shortest Path between " << s << " and "
             << d << " is "  << s << " ";
        return level;
    }
  
    printShortestPath(parent, parent[s], d);
  
    level++;
    if (s < V){
	
        cout << s << " ";
	}
  
    return level;
}
  
// Finds the shortest path
int Graph::findShortestPath(int src, int dest)
{
	// Initialize parent[] and visited[], set their values to flase and -1 respectively

    bool *visited = new bool[2*V];
    int *parent = new int[2*V];
  
  
    for (int i = 0; i < V; i++)
    {
        visited[i] = false;
        parent[i] = -1;
    }
  
    // Mark the current node as visited and enqueue it
    visited[src] = true;
    queue.push_back(src);
  
    // initializing the iterator for the adj list
    list<int>::iterator i;
  
    while (!queue.empty())
    {
        // Dequeue the initial vertex  stored within the queue
        int s = queue.front();
  
        if (s == dest)
            return printShortestPath(parent, s, dest);
  
        queue.pop_front();
  
        // Get all adjacent vertices of the dequeued vertex s
        // and checks if it has been visited or not
        for (i = adj[s].begin(); i != adj[s].end(); ++i)
        {
            if (!visited[*i])
            {
                visited[*i] = true;
                queue.push_back(*i);
                parent[*i] = s;
            }
        }
    }
}
  
// Driver program to test methods of graph class
int main()
{
	int opt;
	int size;
	bool on = true;
	bool create = true;

	
	cout<<"What are the number of vertices: ";
	cin>>size;
	Graph g(size);
	system("CLS");

	
	while(on){

		cout<<"What would you like to do?"<<endl;
		cout<<"Choose: \n 1. Insert Node \n 2. Set End Node \n 3. Find Shortest Path \n 4. Exit \n\nOption:";
		cin >> opt;
		cout<<endl;
		
		if(opt == 1){
			int newEdge, existingEdge, weight;
			
			cout<<"Provide the number of a node: ";
			cin>>newEdge;
			cout<<endl;
			cout<<"Provide the number of another node: ";
			cin>>existingEdge;
			cout<<endl;
			cout<<"What is the weighted distance between the Nodes: ";
			cin>>weight;
			cout<<endl;
			g.addEdge(newEdge, existingEdge, weight);
			
			system("CLS");
			
		}else if(opt == 2){
			int endNode;
			cout<<"What is the ending node: ";
			cin>>endNode;
			g.setEndingNode(endNode);
			
			system("CLS");
			
			
		}else if(opt == 3){
			int src;
			cout<<"What node do we start from: ";
			cin>>src;
			auto start1 = steady_clock::now();
			g.findShortestPath(src, g.getEndNode());
			auto end1 = steady_clock::now();
			
			cout<<endl;
			double elapsed_time1 = double(duration_cast<nanoseconds>(end1 - start1).count());
			cout << "Running time for Hard graph: " << elapsed_time1 * 1E-9 << " seconds" << endl;
			
			sleep(5);
			cout<<endl;
			
		}else if(opt == 4){
			on = false;
			
		}else{
			cout<<"Please pick a registered number"<<endl;
			sleep(1);
			system("CLS");
		}
	}
    return 0;
}
