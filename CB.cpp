#include<iostream>
#include<set>
#include<list>
#include<fstream>
#include<stdlib.h>
using namespace std;

set<int> sum(set<int> a, set<int> b){
  set<int> c;
  for (set<int>::const_iterator it = a.begin(); it != a.end(); it++)
	c.insert(*it);
  for (set<int>::const_iterator it = b.begin(); it != b.end(); it++)
	c.insert(*it);
  for (set<int>::const_iterator it = a.begin(); it != a.end(); it++)
	if (b.find(*it) != b.end()) c.erase(*it);

return c;
}
struct Edje{
	bool exists;
	bool examined;
};
class Vertex{
	public:
	Vertex(int N){
		
		New = true;
		Prev = N;
	}
	bool isNew(){
		return this->New;
	}
	void notNew(){
		this->New = false;
	}
	void setPrev(int N){
		Prev = N;
	}
	int getPrev(){
		return Prev;
	}
	private:
	bool New;
	int Prev;
	
 
};
class Graph{
	public:
	Graph (int N){
		G = (Edje**)calloc(sizeof(Edje*), N);
		for (int i = 0; i < N; i++)
			G[i] = (Edje*)calloc(sizeof(Edje), N);
		QuantityOfCB = 0;
		for (int i = 0; i < N; i++)
			for (int j = 0;  j < N; j++){
				G[i][j].exists = false;
				G[i][j].examined = false;
			}
			Size = N;
	}
	void inc(){
		QuantityOfCB++;
	}
	void setExamined(int i, int j){
		G[i][j].examined = true;
		G[j][i].examined = true;
	}
	void input(){
		cout << "Please, write all edjes (x,y), to stop write negative integer" << endl;
		int a,b;
		cin >> a >> b;
		while ((a>=0)&&(b>=0)){
			G[a-1][b-1].exists = true;
			G[b-1][a-1].exists = true;
			cin >> a >> b;
		}
	}
	bool examined(int i, int j){
		return G[i][j].examined;
	}
	
	bool exists(int i, int j){
		return G[i][j].exists;
	}
	
	void print(){
		for (int i = 0; i < Size; i++){
			for (int j = 0;  j < Size; j++){
				if (G[i][j].exists == true) cout << "1 "; else cout << "0 ";
			}
			cout << endl;
		}
	}
	Edje **G;
	int QuantityOfCB;
	int Size;	
};	

void NC(Graph G, Vertex *V[],int x, int y){
	G.inc();
	int z = x;
	while (z != y)
		z = V[z]->getPrev();
	
	
	
}

void CycleBase(Graph G, Vertex * V[], int N){
 	while (V[N]->isNew()){
		 for (int i = 0; i < N; i++){
			 if (!G.examined(i,N))  G.setExamined(i,N);
			 if (V[i]->isNew()) {V[i]->setPrev(N); N = i;} else NC(G, V, N , i);
		}
		V[N]->notNew();
	 }
}


int main(){

	
	
int N;
cin >> N;
set<int> CB[N];

Vertex * V[N];
for (int i = 0; i < N; i++)
	V[i] = new Vertex(N);
	


Graph G(N);
G.input();
G.print();

for (int i = 0; i < N; i++)
	if (V[i]->isNew())  CycleBase(G, V, i);

if (G.examined(1,2)) cout << "ex"; else cout << "notex";
cout << endl;
cout << G.QuantityOfCB << endl;
  /*for (set<int>::const_iterator it = c.begin(); it != c.end(); it++)
	cout << *it << " ";*/

return 0;
}
