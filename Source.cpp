#include <iostream>
#include <vector>

using namespace std;

//adjacency list graph implementation for a grid based graph	//stores only the adjacent vertices of each vertex
class graph
{
private:
	struct adjVert {
		char v;
		int weight;
	};
	vector<char> vertex;
	vector<vector<adjVert>> adjList;

	int vertSize;
public:
	graph(char verts[], int nVerts) {
		vertSize = nVerts;
		for (int i = 0; i < nVerts; i++)
		{
			vertex.push_back(verts[i]);
		}
	}
	void createEdges(int x) {						// refer to a drawn 5x3 grid consisting of 15 vertices to help understand the algorithm
		int xHolder{ x - 1 };

		adjVert v;
		int weight = 1;

		int upW = 8;				//controls weights for upwards edges
		int leftW = 2;				//controls weights for leftwards edges

		for (int i = 0; i < vertex.size(); i++)
		{
			adjList.push_back(vector<adjVert>());
		}

		for (int i = 0; i < adjList.size(); i++)			// refer to a drawn grid when working through this algorithm
		{
			for (int e = 0; e < adjList.size(); e++)
			{
				if (e == i + 1 && i != xHolder)		// links a vertex to the one to the right of it
				{
					v.v = vertex[e];
					v.weight = weight;

					adjList[i].push_back(v);
					weight += 1;
				}
				else if (e == i - 1 && e != xHolder)	// links a vertex to the one to the left of it
				{
					if (i > vertSize - x)
						leftW = 1;

					v.v = vertex[e];
					v.weight = (weight - leftW);

					adjList[i].push_back(v);
				}
				else if (e == i + x)				//links a vertex to the one under it
				{
					v.v = vertex[e];
					v.weight = weight;

					adjList[i].push_back(v);
					weight += 1;
				}
				else if (e == i - x)				//links a vertext to the one above it
				{
					
					v.v = vertex[e];
					if (e == xHolder)			//refer to a drawn 5x3 grid
						v.weight = (weight - upW) - 1;
					else
						v.weight = weight - upW;

					adjList[i].push_back(v);
				}

				if (e == xHolder + 1)					//xholder signals the end of a row. Doubling it moves the algorithm to the next row
				{
					xHolder += 5;
				}
			}

			if (i >= vertSize - x)		//changing upW in the e loop does not correctly decrease the variable
				upW -= 1;		
			leftW = 2;
			xHolder = x - 1;
		}
	}
	void adjVertices(int v) {
		for (int i = 0; i < adjList[v].size(); i++)
		{
			cout << adjList[v][i].v << ", " << adjList[v][i].weight << endl;
		}
	}
};

int main()
{
	char verts[] = "ABCDEFGHIJKLMNO";

	graph g(verts, 15);		// 15 is the num of vertices
	g.createEdges(5);		// 5 is the width. This specific graph of 15 vertices will be 5x3
	g.adjVertices(7);		// will get the adj

	cin.get();
	return 0;
}


/*
//adjacency matrix unweighted graph implementation for a 5x5 grid
class graph
{
private:
	vector<char> vertex;
	vector<vector<bool>> edge;
public:
	graph(char verts[],int nVerts) {
		for (int i = 0; i < nVerts; i++)
		{
			vertex.push_back(verts[i]);
		}
	}
	void createEdges(int x)
	{
		int xHolder{ x - 1 };

		for (int i = 0; i < vertex.size(); i++)
		{
			edge.push_back(vector<bool>());
			for (int e = 0; e < vertex.size(); e++)
			{
				edge[i].push_back(false);
			}
		}

		for (int i = 0; i < edge.size(); i++)			// refer to a drawn grid when working through this algorithm
		{
			for (int e = 0; e < edge[i].size(); e++)
			{
				if (e == i + 1 && i != xHolder)		// links a vertex to the one to the right of it
				{
					edge[i][e] = true;
				}
				else if (e == i - 1 && e != xHolder)	// links a vertex to the one to the left of it
				{
					edge[i][e] = true;
				}
				else if (e == i + x)				//links a vertex to the one under it
				{
					edge[i][e] = true;
				}
				else if (e == i - x)				//links a vertext to the one above it
				{
					edge[i][e] = true;
				}

				if (e == xHolder + 1)					//xholder signals the end of a row. Doubling it moves the algorithm to the next row
				{
					xHolder = ((xHolder + 1) * 2) - 1;
				}
			}

			xHolder = x - 1;
		}
	}
	void adjVerts(int vert)
	{
		for (int i = 0; i < edge[vert].size(); i++)
		{
			if (edge[vert][i] == true)
			{
				cout << vertex[i] << endl;
			}
		}
	}
};


int main()
{
	char verts[] = "ABCDEFGHIJKLMNO";

	graph g(verts, 15);
	g.createEdges(5);
	g.adjVerts(7);

	cin.get();
	return 0;
}
*/




/*
class vertexList
{
private:
	vector<char> vertex;
public:
	void insert(char& e) { vertex.push_back(e); }
	char operator[](int i) { return vertex[i]; }
	void display() {
		for (int i = 0; i < vertex.size(); i++)
		{
			cout << vertex[i] << endl;
		}
	}
};

class edgeList
{
public:
	struct edge {
		char vert1;
		char vert2;
	};
	void insert(char& v1, char& v2) {
		edges.push_back(edge());
		edges[edges.size() - 1].vert1 = v1;
		edges[edges.size() - 1].vert2 = v2;
	}
	void incidentEdges(vector<edge>& eList, char& vert) {
		for (int i = 0; i < edges.size(); i++)
		{
			if (edges[i].vert1 == vert || edges[i].vert2 == vert)
			{
				eList.push_back(edges[i]);

			}
		}
	}
	bool isAdjacent(char& v1, char& v2) {
		for (int i = 0; i < edges.size(); i++)
		{
			if (edges[i].vert1 == v1 && edges[i].vert2 == v2)
			{
				return true;
			}
			if (edges[i].vert2 == v1 && edges[i].vert1 == v2)
			{
				return true;
			}
		}
		return false;
	}
	void endVerts(vector<char>& verts, int i) {
		verts.push_back(edges[i].vert1);
		verts.push_back(edges[i].vert2);
	}
	void display() {
		for (int i = 0; i < edges.size(); i++)
		{
			cout << "{" << edges[i].vert1 << "," << edges[i].vert2 << "}" << endl;
		}
	}

private:
	vector<edge> edges;
};

class graph
{
private:
	char vertices[5]{ 'A','B','C','D','E' };
	vertexList vList;
	edgeList eList;

	vector<edgeList::edge> incEdges;
public:
	graph() {
		for (int i = 0; i < 5; i++)
		{
			vList.insert(vertices[i]);
		}
		for (int i = 0; i < 4; i++)
		{
			eList.insert(vertices[i], vertices[i + 1]);
		}

		vList.display();
		eList.display();
	}
	void isAdj(int v1, int v2) { cout << eList.isAdjacent(vertices[v1], vertices[v2]) << endl << endl; }
	void iEdges(int vert){
		eList.incidentEdges(incEdges, vertices[vert]);
		for (int i = 0; i < incEdges.size(); i++)
		{
			cout << "{" << incEdges[i].vert1 << "," << incEdges[i].vert2 << "}" << endl;
		}
	}
	void endVerts(int e) {
		vector<char>verts;
		eList.endVerts(verts, e);
		for (int i = 0; i < verts.size(); i++)
		{
			cout << verts[i] << endl;
		}
	}
};

int main()
{
	graph g;
	g.isAdj(0, 4);
	g.iEdges(4);
	g.endVerts(3);

	cin.get();
	return 0;
}
*/












