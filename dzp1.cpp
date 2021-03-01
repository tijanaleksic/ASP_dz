//parametri koji su korisceni u  zadatku
//i=3
//j=2

#include <iostream>
#include <vector>
#include <cstdlib>
#include <list>
struct edge {
	int edge;
	int weight;
};

using namespace std;
//Vektor u kome redom sekvecnijalno stoje 1 3 ,2 3 4,...
vector <int> edges;
//Vektor u kome redom stoje indeksi koji 
vector <int> indicies;
int number_of_nodes = 0;

//vector <int>* get_vector_indicies(int num) {
//	return vector_of_indicies.at(num);
//}
//vector <int>* get_vector_edges(int num) {
//	return vector_of_edges.at(num);
//}
void create() {
	cout << "**************************************************************************************************************" << endl;
	cout << "Unesite broj cvorova koji zelite da ima graf." << endl << "!!!->Napomena,samo se prave cvorovi,ni jedan nije povezan" << endl;
	bool flg = 1;
	while (flg) {
		cin >> number_of_nodes;
		if (number_of_nodes > 0) {
			flg = false;
			cout << "Unesite pozitivnu vrednost za velicinu grafa"<<endl;
		}
	}
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
void add_branch() {
	cout << "**************************************************************************************************************" << endl;
	cout << "Unesite vezu izmedju kojih zelite da uspostavite granu neusmerenog grafa na sledeci nacin : a b gde su a i b " << endl;
	int node1;
	int node2;
	bool flg=true;
	while (flg) {
		cout << "Cvor broj 1: ";
		cin >> node1;
		cout << endl << "Cvor broj 2: ";
		cin >> node2;
		cout << endl;
		if (node1 > 0 && node2 > 0 && node1 <= indicies.size() - 1 && node2 <= indicies.size() - 1) {
			flg = false;
		}
		else {
			cout << "Unesite ponovo cvorove iz opsega [1," << indicies.size() - 1 << "]";
		}
		
	}
	//cin >> w;
	//cin >> w2;
	//sredjivanje indicies
	for (int i = node1; i < indicies.size(); i++) {
		indicies.at(i)++;
	}
	for (int i = node2; i < indicies.size(); i++) {
		indicies.at(i)++;
	}

	if (node1 > node2) {
		int p = node1; node1 = node2; node2 = p;
	}
	//sredjivanje edges pri cemu nije sortirano vec pri dolasku upisivano
	//edge pr1 = { node2, w };
	//edges.insert(edges.begin() + indicies.at(node1 - 1), pr1);
	//edge pr2 = { node1 ,w };
	//edges.insert(edges.begin() + indicies.at(node2 - 1), pr2);
	edges.insert(edges.begin() + indicies.at(node1 - 1), node2);
	edges.insert(edges.begin() + indicies.at(node2 - 1), node1);

	cout << "Uspesno ste dodali granu u graf" << endl;
	cout << endl << endl << endl;

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
		if (edges.at(i) == node2 + 1) {
			edges.erase(edges.begin() + i);
			decrement_indicies(node1 + 1);
		}
	}
	for (int i = indicies.at(node2); i < indicies.at(node2 + 1); i++) {
		if (edges.at(i) == node1 + 1) {
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
	bool flg = true;
	while (flg) {
		cin >> node_to_erase;
		if (node_to_erase < indicies.size() && node_to_erase>0) {
			flg = false;
		}
		else {
			cout << "Pokusajte ponovo sa brojem izmedju [1," << indicies.size() - 1<<"]"<<endl;
		}
	}


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
	for (int i = 0; i < place2 - place1;i++) {
		for (int j = 0; j < edges.size(); j++) {
			if (edges.at(j) == node_to_erase) {
				int a = find_index_in_indicies(j);
				decrement_indicies(a + 1);
				edges.erase(edges.begin() + j);
			}
			//edges.erase(edges)
		}
	}
	//brisanje cvora u indicies
	indicies.erase(indicies.begin() + node_to_erase);
	//post obrada jeer su sad clanovi za 1 manji od ostalih
	cout << "Sada " << node_to_erase + 2 << "postaje " << node_to_erase + 1 << endl;
	for (int i = 0; i < edges.size(); i++) {
		if (edges.at(i) > node_to_erase) { edges.at(i)--; }
	}

}

void erase_branch() {
	cout << "**************************************************************************************************************" << endl;
	cout << "Upisite redom dva cvora koja su povezanan a ciju vezu zelite da raskinete?" << endl;
	bool flg = true;
	int node1, node2;
	while (flg) {
		cout << "Cvor 1 je :";
		cin >> node1;
		cout << endl << "Cvor 2 je :";
		cin >> node2;
		if (node1 > 0 && node2 > 0 && node1 <= indicies.size() - 1 && node2 <= indicies.size() - 1) {
			flg = false;
		}
		else {
			cout << "Unesite ponovo cvorove iz opsega [1," << indicies.size() - 1 << "]";
		}
	}
	//da bi se dobio indeks
	node1--; node2--;
	int place1 = indicies.at(node1);
	int place2 = indicies.at(node2);
	for (int i = indicies.at(node1); i < indicies.at(node1 + 1); i++) {
		if (edges.at(i) == node2 + 1) {
			edges.erase(edges.begin() + i);
			decrement_indicies(node1 + 1);
		}
	}
	for (int i = indicies.at(node2); i < indicies.at(node2 + 1); i++) {
		if (edges.at(i) == node1 + 1) {
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
		cout << edges.at(i) << " ";
	}
	cout << endl << endl << endl;


}

//meni
void main() {
	int input;
	while (true) {
		cout << "**************************************************************************************************************" << endl;
		cout << "Meni: " << endl;
		cout << "1.Kreiranje prazne strukture podataka za graf zadatih dimenzija" << endl;
		cout << "2.Dodavanje cvora u graf" << endl;
		cout << "3.Uklanjanje cvora iz grafa" << endl;
		cout << "4.Dodavanje grane iz grafa" << endl;
		cout << "5.Uklanjanje grane iz grafa" << endl;
		cout << "6.Ispis reprezantacije grafa" << endl;
		cout << "7.Brisanje	grafa iz memorije" << endl;
		cout << "8.prekid programa" << endl;
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
			add_node();
		}
		else if (input == 3) {
			erase_node();
		}
		else if (input == 4) {
			add_branch();
		}
		else if (input == 5) {
			erase_branch();
		}
		else if (input == 6) {
			print_of_graf();
		}
		else if (input == 7) {
			indicies.clear();
			edges.clear();
		}
		else if (input == 8) {
			exit(0);
		}
	}
}