/*
 * BFS.cpp
 *
 *  Created on: Apr 4, 2014
 *      Author: Santhosh Ramaiah
 */

#include <cstdio>
#include <iostream>
#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <fstream>
#include <cstring>
#include <sstream>
#include <cstdlib>

#define MAX 300 // maximum number of nodes or edges
using namespace std;

enum colors {BLACK, WHITE, GRAY}; // description for node state
int color[MAX], d[MAX], p[MAX], vertex, edge,k=0,snode,roat=0,kh=0,khh=0,checkDirected;
int INF = numeric_limits<int>::max(); // max value representing infinity
int NIL = numeric_limits<int>::min(); // min value representing zero
bool bflag=false,sflag=true; //bflag- flag for back edge represents cyclic or not. sflag- flag for edge repeat.
vector<int> bkeeping[MAX]={}; // book keeping for edges

void BFS(vector<int>[],int); // do DFS
int Source(int,int);

int main(void)
{
	string line,lineR,filename;
	char filename1[40];
	int intArray[MAX][MAX]={}; //temporary variable which stores node and its adjacent edges
	string resArray[MAX][MAX]={}; // temporary variable which stores resource file
	int temp; // checks if the graph is directed or not.
    vector<int> adjList[MAX]; // list of node and its adjacent edges
  //  char tempvar;

    cout<<"Enter the name of the graph file: "<<endl;
    cin>>filename;
    strcpy(filename1, filename.c_str()); //string to character store to pass

    ifstream myfile; // read the file.
    myfile.open(filename1);// open the file.


		ifstream resourcefile; // read the file
		resourcefile.open("RESOURCE_FILE.txt"); // open the resource file

		if(resourcefile.is_open()){
			while ( getline (resourcefile,lineR) ) // get every line and store it to line
				{
					std::stringstream ss1(lineR); // converts string to int
					int templength=lineR.length();
					//cout<<ss1;
					for(int idx = 0; idx < templength; idx++)
						{
							ss1>>resArray[kh][idx]; // store the int to array

						}//cout<<endl;
					kh++;
				}


			resourcefile.close();
		}
		else{
			cout<<"resource file not available"<<endl; // close resource file // used later on.
		}



		if (myfile.is_open()) // check if the file is open.
			{
				while ( getline (myfile,line) ) // get every line and store it to line
					{
					  std::stringstream ss(line); // converts string to int
					  int templength1=line.length();
					  for(int idx = 0; idx < templength1; idx++)
					  {
						  ss>>intArray[k][idx]; // store the int to array
					  }
					  k++;
				  }
				  myfile.close();


		vertex=intArray[1][0]; // store the vertex
		checkDirected=intArray[0][0]; // store the directed/undirected graph

		cout<<"Enter the first node to start"<<"(0 to "<<(vertex-1)<<"):"<<endl;
		cin>>snode; // selected node or source node

		for(int e=0; e<vertex; e++) { // read all the vertices
			for(int ed=0; ed<intArray[e+2][2];ed++){ // read all the edges
				temp=intArray[e+2][ed+3];
				adjList[e].push_back(temp);//for directed graph
				if(checkDirected==(-1)){
					adjList[temp].push_back(e);//for undirected graph.
				}
			}
		  }

		cout<<endl;
		cout<<"Classification of edges"<<endl;

		BFS(adjList, snode); // do BFS visit

		cout<<endl;
		cout<<"Vertex (Discovery Time)"<<endl;
		for(int v=0; v<vertex; v++) {// print all the vertices and their discovery time
			if(d[v]==INF){
				printf("v%d (INF)\n", v);
			}
			else{
				printf("v%d (%d)\n", v, d[v]);
			}
		}

		cout<<endl;
		if (checkDirected==0){ // graph is directed
				if (bflag){ // graph is cyclic
					cout<<"Graph is Directed Cyclic."<<endl;
				}
				else{
					cout<<"Graph is Directed Acyclic."<<endl;
				}
			}

		else if (checkDirected==(-1)){ // graph is undirected
				if(bflag){ // graph is cyclic
					cout<<"Graph is Undirected Cyclic."<<endl;
				}
				else{
					cout<<"Graph is Undirected Acyclic."<<endl;
				}
			}
		else {
			cout<<"File Read Error.";
		}

			}
							else cout <<endl<< "Unable to open file";
    return 0;
}

void BFS(vector<int> G[], int s) {
    for(int u=0; u<=vertex; u++) { // initially paint all nodes white
        color[u] = WHITE; // paint node white
        d[u] = INF; // initial discovery time is infinity
        p[u] = NIL; //
    }

    color[s] = GRAY;
    d[s] = 0; // put discovery time for node
    p[s] = NIL;

   std::queue<int> Q; Q.push(s); //initialize queue Q
// no forward edges in BFS
    while( !Q.empty()) { // check if queue is empty
        int u = Q.front(); Q.pop();
        int tempsize2=G[u].size();
        for(int i=0; i<tempsize2; i++) { // do for all adjacent nodes

        	for (int sj=0;sj<roat;sj++){ //check for edge repetition.
            	if(((bkeeping[sj][1]==u)&&(bkeeping[sj][0]==G[u][i]))||((bkeeping[sj][1]==u)&&(bkeeping[sj][0]==G[u][i]))){
            		sflag=false;
            		break;
            	}
            	else{
            		sflag=true;

            	}
        	}
        	bkeeping[roat].push_back(u); //put edge in book keeping array.
        	bkeeping[roat].push_back(G[u][i]); //put edge in book keeping array.
        	roat++;
        	if (checkDirected==(-1)){
        		if(color[G[u][i]]!=WHITE&&sflag==true){ //check for cross edge
        			if(G[u][i]==u){
        				cout<<"Edge "<<u<<"----"<<G[u][i]<<" Back Edge"<<endl;
        				bflag=true;
        			}else{
        			cout<<"Edge "<<u<<"----"<<G[u][i]<<" Cross Edge"<<endl;
        			}
        		}

        	}
        	else{
        		bool efl=Source(u, G[u][i]);
        		if(color[G[u][i]]!=WHITE&&sflag==true&&efl==true){ //check for back edge
        			cout<<"Edge "<<u<<"----"<<G[u][i]<<" Back Edge"<<endl;
        			bflag=true;
        		}
        		else if(color[G[u][i]]!=WHITE&&sflag==true&&efl==false){ //check for back edge
            			cout<<"Edge "<<u<<"----"<<G[u][i]<<" Cross Edge"<<endl;
            			//bflag=true;
        		}

        	}
        	if(color[G[u][i]] == WHITE) { // check for nodes which are undiscovered
                color[G[u][i]] = GRAY;
                cout<<"Edge "<<u<<"----"<<G[u][i]<<" Tree Edge"<<endl;
                d[G[u][i]] = d[u] + 1; // increment discovery time
                p[G[u][i]] = u;
                Q.push(G[u][i]);
            }

        }
        color[u] = BLACK; // paint the node black
    }
}


int Source(int initial, int final){ // getting to know if the traversal as the same node origin
	bool eflag=false;
	int t;
	if(initial==final){
		eflag=true;
	}
	t=p[initial];
	while(t!=NIL){
		t=p[initial];
		initial=t;
		if (initial==final){
			eflag=true;
		}
	}
	return eflag;
}


