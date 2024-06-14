#include <iostream>
#include "AVL.hpp"
#include "utilidad.hpp"
using namespace std;

void imprimir(int e) {
	cout << " " << e;
}

int main() {
	srand(time(NULL));
	ArbolAVL <int>* tree;
	tree = new ArbolAVL<int>(imprimir);
	vector<int> v = { 24, 39, 31, 46, 48, 34, 19, 5, 29 }; // del ejercicio 4
	for (int i = 0; i < v.size(); i++) {
		tree->Insertar(v[i]);
	}
	cout << "Demo del dibujo de ";
	for (auto a : v)
		cout << a << " ";
	tree->dibujarArbol();
	delete tree;
	system("cls");

	ArbolAVL <int>* treeRand = new ArbolAVL<int>(imprimir);

	int n = rand() % (6) + 15;
	vector<int> rand(n);
	ascendinly_fill_container(rand, rand.size(), -100, 100, true);
	permutate(rand, rand.size());
	cout << "Demo completa del AVL: " << endl;
	for (int i = 0; i < rand.size(); i++) {
		for (auto sebastian : rand)
			cout << sebastian << " ";
		cout << endl;
		cout << "Elemento a insertar (ind. " << i << " de " << rand.size() - 1 << "): " << rand[i] << endl;
		treeRand->InsertarDemoCompleta(rand[i]);
		cout << "Presione cualquier tecla para la siguiente insercion...\n";
		cin.get();
		system("cls");
	}
	delete treeRand;

	ArbolAVL <int>* treeRand2 = new ArbolAVL<int>(imprimir);
	for (int i = 0; i < rand.size(); i++) {
		cout << "Demo solo de rotaciones del AVL: " << endl;
		for (auto sebastian : rand)
			cout << sebastian << " ";
		cout << endl;
		cout << "Elemento a insertar (ind. " << i << " de " << rand.size() - 1 << "): " << rand[i] << endl;
		treeRand2->InsertarDemoRotación(rand[i]);
		cout << "Presione cualquier tecla para la siguiente insercion...\n";
		cin.get();
		system("cls");
	}
	delete treeRand2;
	cin.get();

	ArbolAVL <int>* treeRand3 = new ArbolAVL<int>(imprimir);
	for (int i = 0; i < rand.size(); i++) {
		cout << "Demo sin rotaciones del AVL: " << endl;
		for (auto sebastian : rand)
			cout << sebastian << " ";
		cout << endl;
		cout << "Elemento a insertar (ind. " << i << " de " << rand.size() - 1 << "): " << rand[i] << endl;
		treeRand3->InsertarDemoSinRotación(rand[i]);
		cout << "Presione cualquier tecla para la siguiente insercion...\n";
		cin.get();
		system("cls");
	}
	delete treeRand3;
	cin.get();
	return 0;
}
