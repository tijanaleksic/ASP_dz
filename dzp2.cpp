//parametri koji su korisceni u  zadatku
//i=3
//j=2

#include <iostream>
#include <vector>
#include <cstdlib>
#include <list>
#include <stack>
#include <queue>
struct edge {
	int edge;
	int weight;
};

using namespace std;
//Vektor u kome redom sekvecnijalno stoje 1 3 ,2 3 4,...
vector <edge> edges;

//Vektor u kome redom stoje indeksi koji 
vector <int> indicies;
int number_of_nodes = 0;

struct branch {
	int node1;
	int node2;
	int w;
};
vector <branch> possible_branches;









void create() {
	cout << "**************************************************************************************************************" << endl;
	cout << "Unesite broj cvorova koji zelite da ima graf." << endl << "!!!->Napomena,samo se prave cvorovi,ni jedan nije povezan" << endl;
	cin >> number_of_nodes;

	indicies.resize(number_of_nodes + 1, sizeof(int));
	cout << "Trenutno ima " << indicies.size() << " clanova koji su alocirani";
	for (int i = 0; i < number_of_nodes + 1; i++) { indicies.at(i) = 0; }
	cout << "Niz indicies se sastoji od clanova : " << endl;
	for (int i = 0; i < indicies.size(); i++) {
		cout << indicies.at(i) << " ";
	}
	//vector_of_indicies.push_back(&indicies);
	//edges.push_back(-1);
	//vector_of_edges.push_back(&edges);
	cout << endl;
	cout << "Uspesno ste alocirali niz indicies sa " << number_of_nodes << " clanova niza i postavili sve njegove clanove na -1 sto znaci da su nepovezani" << endl;
	cout << endl << endl << endl;
}
void add_node() {
	cout << "**************************************************************************************************************" << endl;
	number_of_nodes++;
	cout << "Dodajete clan sa brojem " << number_of_nodes << " u niz indecies" << endl;

	int mesto = indicies.size() - 1;

	indicies.push_back(indicies.at(mesto));
	cout << "Uspesno ste dodali cvor koji je nepovezan u graf" << endl;
	cout << endl << endl << endl;
}
void add_branch(int node1,int node2,int w) {
	//cout << "**************************************************************************************************************" << endl;
	//cout << "Unesite vezu izmedju kojih zelite da uspostavite granu neusmerenog grafa na sledeci nacin : a b gde su a i b " << endl;
	//cin >> w2;
	//sredjivanje indicies
	for (int i = node1; i < indicies.size(); i++) {
		indicies.at(i)++;
	}
	for (int i = node2; i < indicies.size(); i++) {
		indicies.at(i)++;
	}
	if (node1 > node2) {
		int a = node1;
		node1 = node2;
		node2 = a;
	}
	//sredjivanje edges pri cemu nije sortirano vec pri dolasku upisivano
	edge pr1 = { node2, w };
	edges.insert(edges.begin() + indicies.at(node1 - 1), pr1);
	edge pr2 = { node1 ,w };
	edges.insert(edges.begin() + indicies.at(node2 - 1), pr2);
}
void decrement_indicies(int node) {
	for (int i = node; i < indicies.size(); i++) {
		indicies.at(i) = indicies.at(i) - 1;
	}
}
int find_index_in_indicies(int index) {
	for (int i = 0; i < indicies.size() - 1; i++) {
		if (indicies.at(i + 1) > index && indicies.at(i) <= index) {
			return i;
		}
	}
}
void delate_branch(int node1, int node2) {
	node1--; node2--;
	int place1 = indicies.at(node1);
	int place2 = indicies.at(node2);
	for (int i = indicies.at(node1); i < indicies.at(node1 + 1); i++) {
		if (edges.at(i).edge == node2 + 1) {
			edges.erase(edges.begin() + i);
			decrement_indicies(node1 + 1);
		}
	}
	for (int i = indicies.at(node2); i < indicies.at(node2 + 1); i++) {
		if (edges.at(i).edge == node1 + 1) {
			edges.erase(edges.begin() + i);
			decrement_indicies(node2 + 1);
		}
	}
}
void erase_node() {
	cout << "**************************************************************************************************************" << endl;
	cout << "Koji index cvora zelite da izbrisete?" << endl;
	cout << "Upisite broj od 1 do broja clanova niza" << endl;

	int node_to_erase;
	cin >> node_to_erase;


	//da bi se dobio index
	//node_to_erase--;
	//sredjivanje edges
	int place1 = indicies.at(node_to_erase - 1);
	int place2 = indicies.at(node_to_erase);
	//brisanje svih veza
	if (place1 != place2) { edges.erase(edges.begin() + place1, edges.begin() + place2); }
	//sredjivanje indicies nakon toga
	//cout << "razlika mesta je"<<place2-place1<<endl;


	for (int i = node_to_erase; i < indicies.size(); i++) {
		indicies.at(i) = indicies.at(i) - (place2 - place1);
	}
	//brisanje ponavljanja 3 u ostalim delovima 
	for (int j = 0; j < edges.size(); j++) {
		if (edges.at(j).edge == node_to_erase) {
			int a = find_index_in_indicies(j);
			decrement_indicies(a + 1);
			edges.erase(edges.begin() + j);
		}
	}
	//brisanje cvora u indicies
	indicies.erase(indicies.begin() + node_to_erase);
	//post obrada jeer su sad clanovi za 1 manji od ostalih
	cout << "Sada " << node_to_erase + 2 << "postaje " << node_to_erase + 1 << endl;
	for (int i = 0; i < edges.size(); i++) {
		if (edges.at(i).edge > node_to_erase) { edges.at(i).edge--; }
	}

}

void erase_branch() {
	cout << "**************************************************************************************************************" << endl;
	cout << "Upisite redom dva cvora koja su povezanan a ciju vezu zelite da raskinete?" << endl;
	cout << "Cvor 1 je :";
	int node1, node2;
	cin >> node1;
	cout << endl << "Cvor 2 je :";
	cin >> node2;
	//da bi se dobio indeks
	node1--; node2--;
	int place1 = indicies.at(node1);
	int place2 = indicies.at(node2);
	for (int i = indicies.at(node1); i < indicies.at(node1 + 1); i++) {
		if (edges.at(i).edge == node2 + 1) {
			edges.erase(edges.begin() + i);
			decrement_indicies(node1 + 1);
		}
	}
	for (int i = indicies.at(node2); i < indicies.at(node2 + 1); i++) {
		if (edges.at(i).edge == node1 + 1) {
			edges.erase(edges.begin() + i);
			decrement_indicies(node2 + 1);
		}
	}
}
void print_of_graf() {
	cout << "**************************************************************************************************************" << endl;
	cout << "Niz indicies se sastoji od clanova : " << endl;
	for (int i = 0; i < indicies.size(); i++) {
		cout << indicies.at(i) << " ";
	}
	cout << endl << "Niz edges se sastoji od clanova" << endl;
	for (int i = 0; i < edges.size(); i++) {
		cout << edges.at(i).edge << " ";
	}
	cout << endl << endl << endl;
}
//


void bfs(int a) {
	queue <int> kju;
	vector <bool> checked(indicies.size() - 1, 0);
	//int place1 = indicies.at(a);
	//int place2 = indicies.at(a + 1);
	kju.push(a);
	while (!kju.empty()) {
		int node = kju.front();
		kju.pop();
		checked[node - 1] = true;
		cout << node << endl;
		for (int i = indicies.at(node - 1); i < indicies.at(node); i++) {
			int num = edges.at(i).edge;
			if (!checked.at(num - 1))
			{
				kju.push(edges.at(i).edge);
			}
		}
	}
}
int get_weight(int node1,int node2) {
	int place1 = indicies.at(node1 - 1);
	int place2 = indicies.at(node1);

	for (int i = place1; i < place2; i++) {
		if (edges.at(i).edge == node2) {
			return edges.at(i).weight;
		}
	}

}
void  bfs_modified(int a) {
	vector<int> dist(indicies.size()-1, INT_MAX);
	vector <vector <int>> prev;
	//pair <>
	for (int i = 0; i < indicies.size() - 1; i++) {
		vector<int> v;
		//vector <int> v(1,-1);
		prev.push_back(v);
	}
	queue <int> kju;
	kju.push(a);
	dist.at(a-1) = 0;
	prev[a-1].push_back(-1);
	while (!kju.empty()) {
		int node = kju.front();
		kju.pop();
		for (int i = indicies.at(node - 1); i < indicies.at(node); i++) {
			int num = edges.at(i).edge;
			int w = edges.at(i).weight;
			
			if (dist.at(node-1)+abs(w)==dist.at(num-1))
			{
				dist.at(num - 1)=dist.at(node-1)+w;
				kju.push(num);
				prev[num - 1].push_back(node);
			}
			if (dist.at(node - 1) + abs(w) < dist.at(num - 1))
			{
				dist.at(num - 1) = dist.at(node - 1) + abs(w);
				kju.push(num);
				prev[num - 1].clear();
				prev[num - 1].push_back(node);
			}
		}
	}/*
	for (int i = 0; i < indicies.size() - 1; i++) {
		for (int j = 0; j < prev[i].size(); j++) {
			cout << " " << prev[i][j];
		}
		cout << "novi red"<<endl;
	}*/
	
	//ispis
	stack <int> stek;
	stack <int> currentPS;
	//
	vector <vector <int>> vv_to_sort;
	int br = 0;
	for (int i = 1; i < indicies.size(); i++) {
		if ((i) == a) { continue; }
		if (prev.at(i-1).empty()) {
			cout << "Do cvora sa brojem " << i << " ne posotji put ni moguci, ni izgradjen"<<endl;
			continue;
		}
		int end_of_path=i;
		cout << "Putanja od "<<end_of_path<<"do clana oznacenoog sa V";
		//cin >> end_of_path;
		cout << endl;
		for (int i = 0; i < prev.at(end_of_path - 1).size(); i++) {
			stek.push(prev[end_of_path - 1][i]);
		}
		while (!stek.empty()) {
			int curr = stek.top();
			stek.pop();
			if (curr == a) {
				vector <int> pr;
				pr.push_back(end_of_path);
				cout << end_of_path<<" - ";
				while (!currentPS.empty()) {
					int printt = currentPS.top();
					cout << printt << " - ";
					pr.push_back(printt);
					currentPS.pop();
				}
				pr.push_back(a);
				cout << "V" << endl;
				vv_to_sort.push_back(pr);
				br++;
				continue;
			}

			currentPS.push(curr);
			for (int j = 0; j < prev[curr - 1].size(); j++) {
				stek.push(prev[curr - 1][j]);
			}

		}
	}

	//sortiranje;
	vector <int> numb_of_not(br,0);
	for (int i = 0; i < br; i++) {
		for (int j = 0; j < vv_to_sort[i].size() - 1; j++) {
			int x=vv_to_sort[i][j] ;
			int y=vv_to_sort[i][j + 1] ;
			int w=get_weight(x, y);
			if (w < 0) { numb_of_not[i]++; }
		}
	}
	//sortiranje
	for (int i = 0; i < br; i++) {
		for (int j = i; j < br; j++) {
			if (numb_of_not.at(i)>numb_of_not.at(j)) {
				int pr = numb_of_not.at(i);
				numb_of_not[i] = numb_of_not[j];
				numb_of_not[j] = pr;
				vector <int> pr1=vv_to_sort[i];
				vv_to_sort[i] = vv_to_sort[j];
				vv_to_sort[j] = pr1;
			}
		}
	}
	//ispis
	cout << "Konacan ispis sortiranih je " << endl << endl;
	for (int i = 0; i < br; i++) {
		//for (int j = 0; j < vv_to_sort[i].size(); j++) {
		for (int j = vv_to_sort[i].size()-1; j >=0; j--) {
			if (vv_to_sort[i][j] == a) {
				cout << "V";
			}
			else {
				cout << " - "<< vv_to_sort[i][j] ;
			}
			
		}
		cout << "  Duzina puta je : "<<dist.at(vv_to_sort[i][0]-1)<< " a broj grana koje nisu izgradjene su:" << numb_of_not[i]<< endl;
		cout << endl;
	}


}


bool is_connected(int a, int b) {
	queue <int> kju;
	vector <bool> checked(indicies.size() - 1, 0);
	//int place1 = indicies.at(a);
	//int place2 = indicies.at(a + 1);
	kju.push(a);
	while (!kju.empty()) {
		int node = kju.front();
		kju.pop();
		checked[node - 1] = true;
		//cout << node << endl;
		for (int i = indicies.at(node - 1); i < indicies.at(node); i++) {
			int num = edges.at(i).edge;
			if (!checked.at(num - 1))
			{
				kju.push(edges.at(i).edge);
				//naisli smo na cvor tako da je povezan sa pocetnim
				if (edges.at(i).edge == b) {
					return true;
				}
			}
		}
	}
	return false;
}
void kruskalov_algoritam() {
	int cost = 0;
	//pravljenje priority queue
	auto comp = [](const branch& a, const branch& b) { return a.w > b.w; };
	priority_queue<branch,vector <branch>, decltype(comp)> pq(comp);
	for (int i = 0; i < possible_branches.size(); i++) {
		pq.push(possible_branches.at(i));
	}
	//krusk
	int num = 0;
	while (num < indicies.size() - 2) {
		if (pq.empty() && num < indicies.size() - 2) {
			cout << "Nije u potpunosti povezan graf jer ne postoji veza koja moze da se stavi a da povezuje sve cvorove grafa" << endl;
				break;
		}
		branch x = pq.top(); pq.pop();
		if (!is_connected(x.node1, x.node2)) {
			add_branch(x.node1, x.node2,x.w);
			cost += x.w;
			num++;
			cout << "Povezujem " << x.node1 << " - " << x.node2 << " sa tezinom " << x.w << endl;
			//cout << "w je izvadjeno" << x.w<< endl;
		}
	}
	cout << "Cost je " << cost << endl;	
	//oslobadjanje memorije za dalj nastavak programa
	//posto je u drugom delu podrazumevano da smo napravili sa isto cvorova prazan graf potrebno je sve clanove vratiti na 0
	//for (int i = 0; i < indicies.size(); i++) { indicies.at(i) = 0; }
	//edges treba unistiti skroz;
	//edges.clear();
	//possible_branches.clear();
}
//vatrogasci deo
void dijkstra(int from, int to) {
	vector <int> t(indicies.size() - 1, 0);
	vector <int> d(indicies.size() - 1, INT_MAX);
	vector <bool> in_set(indicies.size() - 1, 0);
	vector<int> prev(indicies.size() - 1, -1);
	int ubaceni = 1;
	d[from-1] = 0;
	//pravljenje prioritetnog reda koji ce izbacivati u d sledeci najmanji

	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
	pq.push(make_pair(0, from));
	//sve dok ima nesto da se ubaci ili dok se ne stigne do kraja grafa
	while (!pq.empty() && ubaceni < indicies.size()-1)
	{
		if (pq.empty() && ubaceni < indicies.size() - 1) { cout << "cvorovi nisu povezani dovoljno!" << endl; }
		//izbacujemo element koji treba da odradimo(po tezini )
		pair<int, int> current = pq.top(); pq.pop();
		int prev_d_a = current.first;
		int node = current.second;
		if (in_set[node-1]) { continue; }
		//oznacimo ga u vectoru kao da smo ga prosli tj obradili da ga ne bi dva puta obradjivali(slucaj postojanja kontura)
		in_set[node-1] = true;
		//povecavamo broj ubacenih
		ubaceni++;	

		for (int i = indicies.at(node-1); i < indicies.at(node); i++)
		{
			int next = edges.at(i).edge;
			int w = edges.at(i).weight;
			if (d[next - 1] == d[node - 1] + abs(w)) {
				cout << "ima dva puta iste tezine" << endl;
				continue;
			}
			if (d[next-1] > (d[node-1] + abs(w)))
			{
				d[next-1] = d[node-1] + abs(w);
				cout << "d[next]  = " << d[next-1] << endl;
				prev[next-1] = node;
			}
			pq.push(make_pair(d[next-1], next));
		}
	}
	if (d[to] != INT_MAX) {
		cout << d[to-1] << endl;
	}
	
	else {
		cout << "NO" << endl;
	}
	cout << "Niz d :";
	for (int i = 0; i < d.size(); i++) {
		cout << d.at(i) << " ";
	}
	cout << "Niz prev :";
	for (int i = 0; i < prev.size(); i++) {
		cout << prev.at(i) << " ";
	}
	//ispis

	//for(int i=0; i< prev.size()-1;i<)
	//whil()

}
void dijkstra_upgrade(int from,int to) {
	vector <int> t(indicies.size() - 1, 0);
	vector <int> d(indicies.size() - 1, INT_MAX);
	vector <bool> in_set(indicies.size() - 1, 0);
	vector<vector<int>> prev;
	for (int i = 0; i < indicies.size() - 1; i++) {
		prev.at(i).push_back(-1);
	}
	int ubaceni = 1;
	d[from - 1] = 0;
	//pravljenje prioritetnog reda koji ce izbacivati u d sledeci najmanji

	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
	pq.push(make_pair(0, from));
	//sve dok ima nesto da se ubaci ili dok se ne stigne do kraja grafa
	while (!pq.empty() && ubaceni < indicies.size() - 1)
	{
		if (pq.empty() && ubaceni < indicies.size() - 1) { cout << "cvorovi nisu povezani dovoljno!" << endl; }
		//izbacujemo element koji treba da odradimo(po tezini )
		pair<int, int> current = pq.top(); pq.pop();
		int prev_d_a = current.first;
		int node = current.second;
		if (in_set[node - 1]) { continue; }
		//oznacimo ga u vectoru kao da smo ga prosli tj obradili da ga ne bi dva puta obradjivali(slucaj postojanja kontura)
		in_set[node - 1] = true;
		//povecavamo broj ubacenih
		ubaceni++;

		for (int i = indicies.at(node - 1); i < indicies.at(node); i++)
		{
			int next = edges.at(i).edge;
			int w = edges.at(i).weight;
			if (d[next - 1] == (d[node - 1] + abs(w))) {
				for (int i = 0; i < indicies.size() - 1; i++) {
					prev.at(i).push_back(prev.at(i).at(prev.at(i).size() - 1));
				}
			}
			if (d[next - 1] > (d[node - 1] + abs(w)))
			{
				d[next - 1] = d[node - 1] + abs(w);
				cout << "d[next]  = " << d[next - 1] << endl;
				prev[next - 1].push_back(node);
			}
			pq.push(make_pair(d[next - 1], next));
		}
	}
	if (d[to] != INT_MAX) {
		cout << d[to - 1] << endl;
	}

	else {
		cout << "NO" << endl;
	}
	cout << "Niz d :";
	for (int i = 0; i < d.size(); i++) {
		cout << d.at(i) << " ";
	}
	cout << "Niz prev :";
	for (int i = 0; i < prev.size(); i++) {
		cout << prev.at(i).at(0) << " ";
	}

}

//meni
void main() {
	int input;
	while (true) {
		cout << "**************************************************************************************************************" << endl;
		cout << "Meni: " << endl;
		cout << "1.Kreiranje prazne strukture podataka za graf zadatih dimenzija" << endl;
		cout << "2.Dodavanje grane iz grafa" << endl;
		cout << "3.Kruskalov algoritam" << endl;
		cout << "4.Ispis reprezantacije grafa" << endl;
		cout << "5.Vatrogasci i njihovi putevi" << endl;
		cout << "6.prekid programa" << endl;
		cout << "Ukoliko zelite da izaberete nesto iz ove liste ponudjenih upisite broj ispred operacije koju zelite da uradite" << endl;
		cout << "**************************************************************************************************************" << endl;

		cout << endl << endl << endl;
		cin >> input;
		if (input == 1) {
			indicies.clear();
			edges.clear();
			create();
		}
		else if (input == 2) {
			cout << "**************************************************************************************************************" << endl;
			cout << "Unesite vezu izmedju kojih zelite da uspostavite granu neusmerenog grafa na sledeci nacin : a b  w " << endl;
			int node1, w;
			int node2;
			cin >> node1;
			cin >> node2;
			cin >> w;
			bool flg = false;
			branch pr = { node1,node2,w };
			for (int i = 0; i < possible_branches.size(); i++) {
				if ((possible_branches.at(i).node1 == node1 && possible_branches.at(i).node2 == node2) || (possible_branches.at(i).node1 == node2 && possible_branches.at(i).node1 == node2)) {
					cout << "Vec ste dodali ovu granu kao mogucu";
					flg = true;
					break;
				}
			}
			if (flg == false) {
				possible_branches.push_back(pr);
			}
			//add_branch();
		}
		else if (input == 3) {
			kruskalov_algoritam();
		}
		else if (input == 4) {
			print_of_graf();
		}/*
		else if (input == 7) {
			//brisanje grafa
			indicies.clear();
			edges.clear();
		}
		else if (input ==10) {
			cout << "**************************************************************************************************************" << endl;
			cout << "Unesite index indeksa na kome se nalaze vatrogasci : ";
			int id,to;
			cin >> id;
			cout << "unesite krajnji cvor" << endl;
			cin >> to;
			cout << endl;
			//cout<<"Unosite redom v=cvorove izmedju kojih postoji put sledecim redom "
			bool flg = true;
			while (flg) {
				int id1, id2, w;
				cout << "Unesite najpre cvorove koji su povezani :"<<endl;
				cout << "Id cvora 1: ";
				cin >> id1;
				cout << endl;
				cout << "ID cvora 2: ";
				cin >> id2;
				cout << endl;
				cout << "Tezina puta izmedju ova dva cvora: ";
				cin >> w;
				cout << endl;
				cout << "Ukoliko zelite da nastavite napisite 1,ukoliko ne zelite napisite 0";
				add_branch(id1, id2, w);
				bool flg2;
				cin >> flg2;
				flg = flg2;
			}
			flg = true;
			while (flg) {
				int id1, id2, w;
				cout << "Unesite potencijalne veze za cvorove " << endl;
				cout << "Id cvora 1: ";
				cin >> id1;
				cout << endl;
				cout << "ID cvora 2: ";
				cin >> id2;
				cout << endl;
				cout << "Tezina puta izmedju ova dva cvora: ";
				cin >> w;
				cout << endl;
				cout << "Ukoliko zelite da nastavite napisite 1,ukoliko ne zelite napisite 0";
				add_branch(id1, id2, -w);
				bool flg2;
				cin >> flg2;
				flg = flg2;
			}
			dijkstra(id,to);
			
		}*/
		else if (input == 6) {
			exit(0);
		}/*
		else if (input == 9) {
			int ks;
			cout << "KOji je pocetni" << endl;
			cin >> ks;
			bfs(ks);
		}*/
		else if (input == 5) {
			//posto je u drugom delu podrazumevano da smo napravili sa isto cvorova prazan graf potrebno je sve clanove vratiti na 0
			for (int i = 0; i < indicies.size(); i++) { indicies.at(i) = 0; }
			//edges treba unistiti skroz;
			edges.clear();
			possible_branches.clear();
			cout << "**************************************************************************************************************" << endl;
			cout << "Unesite index indeksa na kome se nalaze vatrogasci : ";
			int id, to;
			cin >> id;
			//cout << "unesite krajnji cvor" << endl;
			//cin >> to;
			cout << endl;
			//cout<<"Unosite redom v=cvorove izmedju kojih postoji put sledecim redom "
			bool flg = true;
			while (flg) {
				int id1, id2, w;
				cout << "Unesite najpre cvorove koji su povezani :" << endl;
				cout << "Id cvora 1: ";
				cin >> id1;
				cout << endl;
				cout << "ID cvora 2: ";
				cin >> id2;
				cout << endl;
				cout << "Tezina puta izmedju ova dva cvora: ";
				cin >> w;
				cout << endl;
				bool flg2;
				if (w >= 0) {
					add_branch(id1, id2, w);
					cout << "Ukoliko zelite da nastavite napisite 1,ukoliko ne zelite napisite 0 : ";
					cin >> flg2;
					flg = flg2;
				}
				else {
					cout << "Uneli ste granu koja ima negativnu duzinu puta,pokusajte ponovo. " << endl;
					flg = 1;

				}
				//bool flg2;
				//cin >> flg2;
				//flg = flg2;
			}
			flg = true;
			int ask;
			cout << "Sada ste prekinuli upis izgradjenih puteva, da li zelite da upisete neke neizgradjene? Ukoliko da napisite 1,ukoliko ne onda 0: ";
			cin >> ask;
			cout << endl;
			if (ask == 1) {
				while (flg) {
					int id1, id2, w;

					cout << "Unesite potencijalne veze za cvorove " << endl;
					cout << "Id cvora 1: ";
					cin >> id1;
					cout << endl;
					cout << "ID cvora 2: ";
					cin >> id2;
					cout << endl;
					cout << "Tezina puta izmedju ova dva cvora: ";
					cin >> w;
					cout << endl;
					bool flg2;
					if (w >= 0) {
						add_branch(id1, id2, -w);
						cout << "Ukoliko zelite da nastavite napisite 1,ukoliko ne zelite napisite 0 : ";
						cin >> flg2;
						flg = flg2;
					}
					else {
						cout << "Uneli ste granu koja ima negativnu duzinu puta,pokusajte ponovo. " << endl;
						flg = 1;

					}
					//cout << "Ukoliko zelite da nastavite napisite 1,ukoliko ne zelite napisite 0: ";
					//add_branch(id1, id2, -w);
					//bool flg2;
					//cin >> flg2;
					//flg = flg2;
				}
			}
			bfs_modified(id);

		}
		else {
			continue;
		}
	}
}