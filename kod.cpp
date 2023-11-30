#include<bits/stdc++.h>

#define st first
#define nd second
#define pb(x) push_back(x)
#define pp(x) pop_back(x)
#define mp(a, b) make_pair(a, b)
#define all(x) (x).begin(), (x).end()
#define rev(x) reverse(all(x))
#define sor(x) sort(all(x))
#define sz(x) (int)(x).size()
#define rsz(x) resize(x)

using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<pii > vii;
typedef vector<ll> vl;
typedef vector<pll> vll;
typedef string str;
#define BOOST ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);  
const int MN = 531, MM = 531; 
int tab[MN][MN]; // 1 -> B, 2 -> C, 0 -> default pusty  
int n, m; 
string row;   
char kier[200]; 
string task; int tasklen; 
void read(){ 
	cin >> n >> m;    
	
	for(int i =0 ; i < 200; i++) 
		kier[i] = -1;  
	kier['L'] = 0; 
	kier['P'] = 1; 
	kier['D'] = 2; 
	kier['G'] = 3; 
	
	char c; 
	for(int i = 0; i < n; i++){  
		cin >> row; 
		for(int j = 0 ; j < m; j++){ 
			if(row[j] != '.'){ 
				tab[i][j] = ((row[j] == 'B') ? 1 : 2); 
			} 
		} 
	}  
	cin >> tasklen; 
	cin >> task; 
}  
queue<int> Q;  
// (0, L), (1, P), (2, D), (3, G)
void move(char typ){  
	int ind; 
	if(typ == 'L' || typ == 0){ 
		for(int i = 0; i < n; i++){  
			ind = 0; 
			for(int j = 0; j < m; j++){ 
				if(tab[i][j]){
					Q.push(tab[i][j]); 
					tab[i][j] = 0 ;
				} 
			} 
			while(!Q.empty()){ 
				tab[i][ind++] = Q.front(); 
				Q.pop(); 
			} 
		} 
		return;  
	}  
	if(typ == 'P' || typ ==1){ 
		for(int i = 0; i < n; i++){  
			ind = m-1; 
			for(int j = m-1; j > -1; j--){ 
				if(tab[i][j]){
					Q.push(tab[i][j]); 
					tab[i][j] = 0 ;
				} 
			}  
			while(!Q.empty()){ 
				tab[i][ind--] = Q.front(); 
				Q.pop(); 
			} 
		}  
		return; 
	} 
	if(typ == 'G' || typ == 3){ 
		for(int j = 0; j < m; j++){ 
			for(int i =0; i < n; i++){ 
				if(tab[i][j]){ 
					Q.push(tab[i][j]); 
					tab[i][j] = 0; 
				} 
			} 
			ind = 0; 
			while(!Q.empty()){ 
				tab[ind++][j] = Q.front(); 
				Q.pop(); 
			} 
		}  
		return; 
	} 
	if(typ == 'D' || typ == 2){ 
		for(int j = 0; j < m; j++){ 
			for(int i =n-1; i > -1; i--){ 
				if(tab[i][j]){ 
					Q.push(tab[i][j]); 
					tab[i][j] = 0; 
				} 
			} 
			ind = n-1; 
			while(!Q.empty()){ 
				tab[ind--][j] = Q.front(); 
				Q.pop(); 
			} 
		} 
		return;  
	}		
}  


void wyp(){ 
	for(int i = 0; i < n; i++){  
		for(int j = 0; j < m; j++){ 
			if(tab[i][j]) 
				cout << (char)('A' + tab[i][j]); 
			else 
				cout << '.'; 
		} 
		cout << "\n"; 
	}
}  

pii begpoint;  
int begmoment;  // na wolne miejsce
pii begtime; 
void prerun(){
	begpoint = {-1, -1}; 
	for(int i = 0; i < tasklen; i++){ 
		if(task[i] == 'L' || task[i] == 'P'){ 
			begpoint.st = kier[task[i]];  
			begtime.st = i; 
		}
		else{
			begpoint.nd = kier[task[i]];  
			begtime.nd = i; 
		}
		if(begpoint.st != -1 && begpoint.nd != -1){ 
			begmoment = i+1; 
			break; 
		} 
	}  
} 
// (0, L), (1, P), (2, D), (3, G)
void runsimple(){ 
	if(begpoint.st == -1){ 
		if(begpoint.nd == 2){ 
			move('D'); 
			wyp(); 
			return; 
		} 
		if(begpoint.nd == 3){ 
			move('G'); 
			wyp();  
			return; 
		} 
	} 
	if(begpoint.nd == -1){ 
		if(begpoint.st == 0){ 
			move('L');  
			wyp();  
			return; 
		} 
		if(begpoint.st == 1){ 
			move('P'); 
			wyp(); 
			return; 
		} 
	}		
}  
// pozycja -> kierunek zegarowy
int dir[4][4]= {{-1, 1, -1, 0}, {0, -1, -1, 1}, {1, -1, 0, -1}, {-1, 0, 1, -1}};  
int destiny[4][4] = {{-1, 1, -1, 3}, {0, -1, -1, 2}, {3, -1, 1, -1}, {-1, 2, 0, -1}};
stack<int> poz;  

int start(pii cos){ 
	if(cos.st == 0){ 
		if(cos.nd == 2)  
			return 0; 
		if(cos.nd == 3) 
			return 3; 
	} 
	if(cos.st == 1){ 
		if(cos.nd == 2) 
			return 1; 
		if(cos.nd == 3) 
			return 2; 
	}
}
 
stack<int> S; 
int poczatek;  
int movetyp[4][2] = {{3, 1}, {0, 3}, {2, 0}, {1, 2} }; 
stack <int> M;  
int aktudir; 
void runfull(){ 
	 poczatek = start(begpoint);  
	aktudir = -1;  
	S.push(poczatek);  
	int x, d; 
	for(int i = begmoment; i < tasklen; i++){ 
		if(sz(S) == 1){   
			aktudir = -1; 
			x = destiny[S.top()][kier[task[i]]]; 
			if(x != -1){
				aktudir = dir[S.top()][kier[task[i]]]; 
				S.push(x); 
			} 
		} 
		else { 
			d = dir[S.top()][kier[task[i]]]; 
			if(d == -1) 
				continue; 
			if(d == aktudir){ 
				S.push(destiny[S.top()][kier[task[i]]]); 
			} 
			else 
				S.pop(); 
		} 
	} 
}  
int pom[MN][MN]; 
void movepom(char typ){  
	int ind; 
	if(typ == 'L' || typ == 0){ 
		for(int i = 0; i < n; i++){  
			ind = 0; 
			for(int j = 0; j < m; j++){ 
				if(pom[i][j]){
					Q.push(pom[i][j]); 
					pom[i][j] = 0 ;
				} 
			} 
			while(!Q.empty()){ 
				pom[i][ind++] = Q.front(); 
				Q.pop(); 
			} 
		} 
		return;  
	}  
	if(typ == 'P' || typ ==1){ 
		for(int i = 0; i < n; i++){  
			ind = m-1; 
			for(int j = m-1; j > -1; j--){ 
				if(pom[i][j]){
					Q.push(pom[i][j]); 
					pom[i][j] = 0 ;
				} 
			}  
			while(!Q.empty()){ 
				pom[i][ind--] = Q.front(); 
				Q.pop(); 
			} 
		}  
		return; 
	} 
	if(typ == 'G' || typ == 3){ 
		for(int j = 0; j < m; j++){ 
			for(int i =0; i < n; i++){ 
				if(pom[i][j]){ 
					Q.push(tab[i][j]); 
					pom[i][j] = 0; 
				} 
			} 
			ind = 0; 
			while(!Q.empty()){ 
				pom[ind++][j] = Q.front(); 
				Q.pop(); 
			} 
		}  
		return; 
	} 
	if(typ == 'D' || typ == 2){ 
		for(int j = 0; j < m; j++){ 
			for(int i =n-1; i > -1; i--){ 
				if(pom[i][j]){ 
					Q.push(tab[i][j]); 
					pom[i][j] = 0; 
				} 
			} 
			ind = n-1; 
			while(!Q.empty()){ 
				pom[ind--][j] = Q.front(); 
				Q.pop(); 
			} 
		} 
		return;  
	}		
}  
  
int nowy[MN][MN]; 
pii next0[MN][MN];  
pii pozstara[MN*MN]; 
pii poznowa[MN * MN];  
int cykpoz[MN][MN]; 
vector<pii> CYK[MN * MN]; 
bool visited[MN][MN];  
int cykid[MN][MN];  

void bfs(pii x, int wyzn){ 
	while(!visited[x.st][x.nd]){ 
		visited[x.st][x.nd] =1; 
		cykid[x.st][x.nd] = wyzn; 
		cykpoz[x.st][x.nd] = CYK[wyzn].size(); 
		CYK[wyzn].pb(x);  
		x = next0[x.st][x.nd]; 
	}
}


void cyklepart(){ 
	int ind = 1; 
	for(int i = 0; i < n; i++){ 
		for(int j = 0; j < m ; j++){ 
			if(tab[i][j] != 0){ 
				pom[i][j] = ind; 
				pozstara[ind] = mp(i, j) ; 
				ind++; 
			} 
		} 
	}
	 int pozycja = poczatek; 
	for(int i = 0; i < 4; i++){ 
		movepom(movetyp[pozycja][aktudir]); 
		pozycja = destiny[pozycja][movetyp[pozycja][aktudir]]; 
	} 
	for(int i = 0; i < n; i++){ 
		for(int j = 0; j < m; j++){ 
			if(pom[i][j]){ 
				poznowa[pom[i][j]] = mp(i, j); 
			}  
		}
	}  
	for(int i = 0 ; i < ind; i++){ 
		next0[pozstara[i].st][pozstara[i].nd] = poznowa[i]; 
	}  
	int wyzn = 1; 
	for(int i = 0; i < n; i++){ 
		for(int j = 0 ; j < m; j++){  
			if(!visited[i][j] && pom[i][j]){ 
				bfs(mp(i, j), wyzn); 
				wyzn++;
			} 
		} 
	}		
}   

void finalize(){ 
	if(begtime.st < begtime.nd){ 
		move(begpoint.st); 
		move(begpoint.nd); 
	} 
	else 
	{ 
		move(begpoint.nd); 
		move(begpoint.st); 
	} 
	int cykamo = (sz(S) -1 )/4;  
	
	// zrob czesc z cyklami
	cyklepart(); 
	pii pozycja; 
	for(int i = 0; i < n; i++){ 
		for(int j = 0; j < m; j++){ 
			if(tab[i][j]){ 
				pozycja = CYK[cykid[i][j]][(cykpoz[i][j] + cykamo)%sz(CYK[cykid[i][j]])]; 
				nowy[pozycja.st][pozycja.nd] = tab[i][j]; 
			} 
		} 
	}
	// end part with cykle   
	for(int i = 0; i < n; i++){ 
		for(int j = 0; j < m; j++){ 
			tab[i][j] = nowy[i][j]; 
		} 
	} 
	int pozz = poczatek; 
	int zost = cykamo%4; 
	for(int i = 0; i < zost; i++){ 
		move(movetyp[pozz][aktudir]); 
		pozz = destiny[pozz][movetyp[pozz][aktudir]]; 
	}
	
}


int main(){ 
	read(); 
	prerun(); 
	if(begpoint.st == -1 || begpoint.nd == -1){ 
		runsimple(); 
		return 0; 
	} 
	runfull();  
	finalize();  
	wyp(); 
} 
// koniec

