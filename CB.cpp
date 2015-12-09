#include<iostream>
#include<set>
#include<list>
#include<fstream>
#include<stdlib.h>
using namespace std;


void genCombinations (int * arr , int n , int curPos, list<int> * CB[], list<int> mycycle, int N){
        int a[N][N], b[N][N], c[N][N];
		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++){
				a[i][j] = 0;
				b[i][j] = 0;
				c[i][j] = 0;
			}
		std::list<int>::const_iterator it_next, first, last;	
		for (std::list<int>::const_iterator it = mycycle.begin(), end = mycycle.end(); it != end; ++it) { 
			it_next = it;
			++it_next ;
			if (it_next !=  end) {
    			c[*it - 1][*it_next - 1] = 1;
    			c[*it_next - 1][*it - 1] = 1;
			}
			else
			{
				first = mycycle.begin();
				
				c[*it - 1][*first - 1] = 1;
				c[*first - 1][*it - 1] = 1;
			}
		}
		

			
	
				
        if (n == curPos){
               // printf ("\n-------------we have got next combination---------\n");
                        for (int i=0; i < n ; i++)  
							if (arr[i] == 1) {
								std::list<int>::const_iterator it_next, first, last;	
								for (std::list<int>::const_iterator it = CB[i]->begin(), end = CB[i]->end(); it != end; ++it) { 
									it_next = it;
									++it_next ;
									if (it_next !=  end) {
    									if (a[*it - 1][*it_next - 1] == 1){ 
											a[*it - 1][*it_next - 1] = 0; 
											a[*it_next - 1][*it - 1] = 0;
										} else {
											a[*it - 1][*it_next - 1] = 1; 
											a[*it_next - 1][*it - 1] = 1;
										}
									}
									else
									{
										first = CB[i]->begin();
										if (a[*it - 1][*first - 1] == 1){ 
											a[*it - 1][*first - 1] = 0; 
											a[*first - 1][*it - 1] = 0;
										} else {
											a[*it - 1][*first - 1] = 1; 
											a[*first - 1][*it - 1] = 1;
										}
									}
								}
								
							}
							bool comp = true;
							for (int i = 0; i < N; i++){
								
								for (int j = 0; j < N; j++){
								if (a[i][j] != c[i][j]) comp = false;
								}

							}
							for (int i = 0; i < N; i++)
								for (int j = 0; j < N; j++){
									a[i][j] = 0;
							}

							
							if (comp) {
								cout << "it's sum of:";
								for (int k = 0; k < n; k ++)
									if (arr[k] == 1) cout << k+1 << " ";
								cout << endl;
							}						
							comp = false;
                }
        else{
                arr [curPos] = 0;
                genCombinations (arr , n , curPos+1, CB, mycycle, N);
                arr [curPos] = 1;
                genCombinations (arr , n , curPos+1, CB, mycycle, N);
                }
}



struct Edje{
	bool exists;
	bool examined;
};
class Vertex{
	public:
	Vertex(int N){
		
		New = true;
		Prev = 0;
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
		while ((a>0)&&(b>0)){
			G[a-1][b-1].exists = true;
			G[b-1][a-1].exists = true;
			cin >> a;
			if (a <= 0) break;
			cin >> b;
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
				if (G[i][j].examined == true) cout << "1 "; else cout << "0 ";
			}
			cout << endl;
		}
	}
	Edje **G;
	int  QuantityOfCB;
	int Size;	
};	

void NC(Graph G, Vertex *V[],int y, int curr, int *pK, list<int> * CB[]){
	int z = curr;
	CB[*pK]->push_back(z+1);
	cout << *pK+1 << ":";
	cout << z+1 << " ";
	while (z != y){
		z = V[z]->getPrev();
		cout << z+1 << " ";
		CB[*pK]->push_back(z+1);
		 
	}
	cout << endl;
	*pK = *pK + 1;
}
	


void CycleBase(Graph G, Vertex * V[], int curr, int N, int * pK, list<int> * CB[]){
	int y;
	//V[curr]->setPrev(curr);
	V[curr]-> notNew();
	for (y = 0; y < N; y++){
		if (!G.examined(y,curr) && G.exists(y,curr)){ 
			 G.setExamined(y,curr); 
			 if (V[y]->isNew()) {
				 	V[y]->setPrev(curr);
				 	CycleBase(G,V,y, N, pK, CB); 	 
				 } else {
				 	NC(G, V, y , curr, pK, CB); 
				 }
			 }
	}
		
}


int main(){

	
	
int N;
cin >> N;
list<int> * CB[N];
for (int i = 0; i < N; i++)
	CB [i] = new list<int>;
Vertex * V[N];
for (int i = 0; i < N; i++)
	V[i] = new Vertex(N);
	


Graph G(N);
G.input();
int K = 0;
int *pK = &K;
int i = 0;
//for (int i = 0; i < N; i++)
	if (V[i]->isNew())   CycleBase(G, V, i, N, pK, CB);

list<int> mycycle;
int a;
cout << "Now please write your cycle and finish it with 0" << endl;
cin >> a;
while (a > 0){
	mycycle.push_back(a);
	cin >> a;	
}
int arrT [N];
genCombinations (arrT , *pK , 0, CB, mycycle, N);
  

return 0;
}
