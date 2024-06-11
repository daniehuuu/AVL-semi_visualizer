///*
#include <iostream>
#include "AVL.hpp"

using namespace std;

void imprimir(int e) {
	cout << " " << e;
}


int main() {
	ArbolAVL <int>* tree;
	
	tree = new ArbolAVL<int>(imprimir);
	vector<int> v = { 24, 39, 31, 46, 48, 34, 19, 5, 29 };
	for (int i = 0; i < v.size(); i++) {
		//tree->demoTarea(v[i]);
		tree->Insertar(v[i]);
		cout << "Presione cualquier tecla para la siguiente insercion...\n";
		cin.get();
		system("cls");
	}
	/*
	  tree->Insertar(15);
	  tree->Insertar(20);
	  tree->Insertar(24);
	  tree->Insertar(10);
	  tree->Insertar(13);
	  tree->Insertar(7);
	  tree->Insertar(30);
	  tree->Insertar(36);
	  tree->Insertar(25);
	*/
	//tree->Insertar(14);
	//tree->Insertar(17);
	//tree->Insertar(11);
	//tree->Insertar(7);
	//tree->Insertar(53);
	//tree->Insertar(4);
	//tree->Insertar(13);
	//tree->Insertar(12);
	//tree->Insertar(8);
	//tree->Insertar(18);
	//tree->Insertar(29);
	//tree->Insertar(16);
	//tree->Eliminar(53);
	//tree->Eliminar(11);
	//
	//
	//
	//tree->imprimeArbol();
	//
	//cout << "\nImpresion inOrden de elementos: " << endl;
	//tree->inOrden();
	//cout << endl;
	//tree->dibujarArbol();
	//cout << "\nImpresion inOrden de alturas: " << endl;
	//tree->inOrdenH();
	//cout << endl;
	cin.get();

	return 0;
}