#include <iostream>
#include <vector>
#include <fstream>
#include <queue>
#include <climits>
using namespace std;

#define inf 999999
struct Edge { //create a structure for one edge and each edge contains the start,end,cost
	int from;//start
	int dest;//end locations
	int cost;//cost
};

struct Node { //the node is to compare between the spot and cost of two nodes
	int spot, cost;
};
class Graph //create a class to actually "graph" the shortest path
{
public:
	vector<vector<Edge>> adjList; //used a vector of a vector in order to create adjacent nodes
	Graph(vector<Edge> const& edges, int N) //constructor
	{
		adjList.resize(N);//resizes the vector of vectors
		for (Edge const& edge : edges)//iteration formal for loop
		{
			adjList[edge.from].push_back(edge);//creates something similar to a hash
		}
	}
};
void print_route(vector<int> &vect, int i)//uses recursion to print out the path
{
	if (i < 0)
		return;
	print_route(vect, vect[i]);
	cout << i << " ";
}
struct comp //comparison operator
{
	bool operator()(const Node& left, const Node& right) const //returns the great of the costs from the nodes
	{
		return left.cost > right.cost;
	}
};
void shortestPath(Graph const& graph, int from, int N,int min) //parameters is the graph. starting location. Number of paths. and first path
{
	priority_queue<Node, vector<Node>, comp> pQheap; //creates a priority queue heap
	pQheap.push({ from, 0 });
	vector<int> total(N, INT_MAX); //makes a vector of integers where the values from 0-6 are max integers. intially
	total[from] = 0;
	vector<bool> done(N, false);//an N number of boolean vectors that initially contain false. This checks if the path is avaialible.
	done[0] = true; //the first spot is guarenteed to be there so its true
	vector<int> prev(N, -1);
	while (!pQheap.empty())
	{
		Node node = pQheap.top();
		pQheap.pop();
		int u = node.spot; //this is the spot in the node structure
		for (auto i : graph.adjList[u])
		{
			int v = i.dest; // i is the edge of a graph. and its destination location is set to V
			int cost1 = i.cost; //cost1 stores the cost to get from one location to the destination
			if (!done[v] && (total[u] + cost1) < total[v])
			{
				total[v] = total[u] + cost1;//total is set to cost
				prev[v] = u;
				pQheap.push({ v, total[v] }); //push new value onto queue
			}
		}
		done[u] = true;
	}

	for (int i = min; i < N; i++)//just to print it
	{
		if (i != from) {
			cout << "\n";
			cout << "Cheapest path from location " << from << " to location " << i << " has a cost of " << total[i] << " and the route is [ ";
			print_route(prev, i); //recursive function
			cout << "]\n";
		}
	}
}

void getEdges(vector<Edge>& V)
{
	struct Edge edge;//creates new stucture to add onto vector
	ifstream file;
	file.open("a5.txt");
	float val = 0;
	int count = 0;
	file >> val; //take first input
	while (val != 0) {//val==0 when Q is show
		count++; //inc count
		if (count % 3 == 1) //if count remainder 3 == 1 since 3 inputs per line this will make first input be from and 2nd dest and 3rd cost
			edge.from = val;
		else if (count % 3 == 2)
			edge.dest = val;
		else if (count % 3 == 0)
			edge.cost = val;
		if (count % 3 == 0)
			V.push_back(edge);//at the end of each line push edge unto the vector

		file >> val;
	}
}

int selectPath(vector <Edge> edges) {
	int num;
	while (1) {
		cout << "Please select starting location: ";
		cin >> num; //asks user for the starting location
		for (int i = 0; i < edges.size(); i++)//makes sure that the starting location is equal to the selected path
		{
			if (num == edges[i].from) //if its equal to one of the location that means it is present and you can return
				return num;
		}
		cout << num << " is not a valid location. Please try again." << endl; //if it gets out of loop t hat means it wasnt found therefore try again
	}
}

int main()
{
	int min=inf;//is going to be equal to minumum value of vector
	vector<Edge> edges;
	getEdges(edges); //sends edge to be filled with edges
	int N=- inf; //max valuue of vector
	for (int i = 0; i < edges.size(); i++)
	{
		if (edges[i].from > N) //N becomes greatest value in vector
			N = edges[i].from;
		if (edges[i].from < min)//Min because smallest value in vector
			min = edges[i].from;
	}
	N++;
	char cont; //continueing the program
	Graph graph(edges, N); //creates the graph
	do { //do while the user keeps selecting paths
		int select = selectPath(edges); //select = path chosen
		shortestPath(graph, select, N,min);
		cout << "\nWould you like to find another path? Y/N";
		while (1) {
			cin >> cont;
			if (cont == 'Y' || cont == 'y' || cont == 'n' || cont == 'N') //makes sure user enters correct input
				break;
			cout << "Invalid Input. Try again";
		}
	} while (cont == 'Y' || cont == 'y');
	return 0;
}
