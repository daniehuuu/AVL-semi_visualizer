#pragma once 
#include "NodoAVL.hpp"
#include <algorithm>
#include <string>
#include <queue>
#include <functional>
#include <cstdlib>
#include <conio.h>
#include <fstream>
using namespace std;

template<class T>
class ArbolAVL {
private:
	Nodo<T>* raiz;
	void(*procesar)(T); //puntero a función
	//Operaciones privadas
	int _altura(Nodo<T>* nodo) {
		int h = 0;
		if (nodo != NULL) {
			int hizq = _altura(nodo->izq);
			int hder = _altura(nodo->der);
			int max_h = max(hizq, hder);
			h = max_h + 1;
		}
		return h;
	}

	void _rotarDerecha(Nodo<T>*& nodo) { // [RSD] [Alt_der < Alt_izq] 
		Nodo<T>* p = nodo->izq;
		nodo->izq = p->der;
		p->der = nodo;
		nodo = p;
	}
	/*
	[RSD]

	  A
	  B      =>       B
	C               C   A

	nodo <- A
	p <- B

	*/

	void _rotarIzquierda(Nodo<T>*& nodo) { // [RSI] [Alt_der > Alt_izq] 
		Nodo<T>* p = nodo->der;
		nodo->der = p->izq;
		p->izq = nodo;
		nodo = p;
	}
	/*
	[RSI]

	A
	  B      =>       B
	  C           A   C

	nodo <- A
	p <- B

	*/
	//Balanceo --------------------------------------------
	void _balanceo(Nodo<T>*& nodo) {
		int hizq = _altura(nodo->izq);
		int hder = _altura(nodo->der);
		int fb = hder - hizq;
		//int fb = hizq - hder; [Opcion2]

		//[Opcion2]if (fb < -1) { //rotar a la izq [hizq < hder]
		if (fb > 1) { //rotar a la izq [hizq < hder]
			int hhizq = _altura(nodo->der->izq);
			int hhder = _altura(nodo->der->der);
			if (hhizq > hhder) { //verificar si aplica doble rotación RDI
				_rotarDerecha(nodo->der);	// RSD
			}
			_rotarIzquierda(nodo);	// RSI
		}
		//[Opcion2]else if (fb > 1) { //rotar a la der [hizq > hder]
		else if (fb < -1) { //rotar a la der [hizq > hder]
			int hhizq = _altura(nodo->izq->izq);
			int hhder = _altura(nodo->izq->der);
			if (hhizq < hhder) { //verificar si aplica doble rotación RDD
				_rotarIzquierda(nodo->izq);	// RSI
			}
			_rotarDerecha(nodo);	// RSD
		}
	}


	void _balanceoDemoCompleta(Nodo<T>*& nodo) {
		int hizq = _altura(nodo->izq);
		int hder = _altura(nodo->der);
		int fb = hder - hizq;
		//int fb = hizq - hder; [Opcion2]

		//[Opcion2]if (fb < -1) { //rotar a la izq [hizq < hder]
		if (fb > 1) { //rotar a la izq [hizq < hder]
			int hhizq = _altura(nodo->der->izq);
			int hhder = _altura(nodo->der->der);
			cout << "El nodo " << nodo->elemento << " violo el factor de balanceo (" << fb << ") " << endl;
			if (hhizq > hhder) { //verificar si aplica doble rotación RDI
				cout << "Rotacion derecha (R. doble D-I)...\n";
				_rotarDerecha(nodo->der);	// RSD
				cin.get();
				dibujarArbol();
			}
			cout << "R. izquierda..." << endl;
			_rotarIzquierda(nodo);	// RSI
			cin.get();
			dibujarArbol();
		}
		//[Opcion2]else if (fb > 1) { //rotar a la der [hizq > hder]
		else if (fb < -1) { //rotar a la der [hizq > hder]
			int hhizq = _altura(nodo->izq->izq);
			int hhder = _altura(nodo->izq->der);
			cout << "El nodo " << nodo->elemento << " violo el factor de balanceo (" << fb << ") " << endl;
			if (hhizq < hhder) { //verificar si aplica doble rotación RDD
				cout << "Rotacion izquierda (R. doble I-D)...\n";
				_rotarIzquierda(nodo->izq);	// RSI
				cin.get();
				dibujarArbol();
			}
			cout << "R. derecha..." << endl;
			_rotarDerecha(nodo);	// RSD
			cin.get();
			dibujarArbol();
		}
	}

	void _balanceoDemoRotaciones(Nodo<T>*& nodo) {
		int hizq = _altura(nodo->izq);
		int hder = _altura(nodo->der);
		int fb = hder - hizq;
		//int fb = hizq - hder; [Opcion2]

		//[Opcion2]if (fb < -1) { //rotar a la izq [hizq < hder]
		if (fb > 1) { //rotar a la izq [hizq < hder]
			int hhizq = _altura(nodo->der->izq);
			int hhder = _altura(nodo->der->der);
			cout << "El nodo " << nodo->elemento << " violo el factor de balanceo (fb = " << fb << ") " << endl;
			cout << "Mostrar AVL antes de las rotaciones... " << endl;
			cin.get();
			dibujarArbol();
			if (hhizq > hhder) { //verificar si aplica doble rotación RDI
				cout << "Rotacion derecha (R. doble D-I)...\n";
				_rotarDerecha(nodo->der);	// RSD
				cin.get();
				dibujarArbol();
			}
			cout << "R. izquierda..." << endl;
			_rotarIzquierda(nodo);	// RSI
			cin.get();
			dibujarArbol();
		}
		//[Opcion2]else if (fb > 1) { //rotar a la der [hizq > hder]
		else if (fb < -1) { //rotar a la der [hizq > hder]
			int hhizq = _altura(nodo->izq->izq);
			int hhder = _altura(nodo->izq->der);
			cout << "El nodo " << nodo->elemento << " violo el factor de balanceo (fb = " << fb << ") " << endl;
			cout << "Mostrar AVL antes de las rotaciones... " << endl;
			cin.get();
			dibujarArbol();
			if (hhizq < hhder) { //verificar si aplica doble rotación RDD
				cout << "Rotacion izquierda (R. doble I-D)...\n";
				_rotarIzquierda(nodo->izq);	// RSI
				cin.get();
				dibujarArbol();
			}
			cout << "R. derecha..." << endl;
			_rotarDerecha(nodo);	// RSD
			cin.get();
			dibujarArbol();
		}
	}

	void _balanceoSinRotaciones(Nodo<T>*& nodo) {
		int hizq = _altura(nodo->izq);
		int hder = _altura(nodo->der);
		int fb = hder - hizq;
		//int fb = hizq - hder; [Opcion2]

		//[Opcion2]if (fb < -1) { //rotar a la izq [hizq < hder]
		if (fb > 1) { //rotar a la izq [hizq < hder]
			int hhizq = _altura(nodo->der->izq);
			int hhder = _altura(nodo->der->der);
			if (hhizq > hhder) { //verificar si aplica doble rotación RDI
				_rotarDerecha(nodo->der);	// RSD
			}
			_rotarIzquierda(nodo);	// RSI
		}
		//[Opcion2]else if (fb > 1) { //rotar a la der [hizq > hder]
		else if (fb < -1) { //rotar a la der [hizq > hder]
			int hhizq = _altura(nodo->izq->izq);
			int hhder = _altura(nodo->izq->der);
			if (hhizq < hhder) { //verificar si aplica doble rotación RDD
				_rotarIzquierda(nodo->izq);	// RSI
			}
			_rotarDerecha(nodo);	// RSD
		}

		if (abs(fb) > 1) {
			cout << "El nodo " << nodo->elemento << " violo el fb entonces quedaria..." << endl;
			dibujarArbol();
		}
	}

	//insertar ----------------------------------------------------- 
	bool _insertar(Nodo<T>*& nodo, T e) {
		if (nodo == nullptr) { //Nuevo elemento
			nodo = new Nodo<T>();
			nodo->elemento = e;
			return true;
		}
		else if (e == nodo->elemento) {
			return false;
		}
		else if (e < nodo->elemento) {
			_insertar(nodo->izq, e);
		}
		else if (e > nodo->elemento) {
			_insertar(nodo->der, e);
		}
		_balanceo(nodo);
		return true;
	}

	bool _demoCompletaInsertar(Nodo<T>*& nodo, T e) {
		if (nodo == nullptr) { //Nuevo elemento
			nodo = new Nodo<T>();
			nodo->elemento = e;
			cout << "Presione cualquier tecla para ver el AVL con el nodo insertado...\n";
			cin.get();
			dibujarArbol();
			return true;
		}
		else if (e == nodo->elemento) {
			return false;
		}
		else if (e < nodo->elemento) {
			_demoCompletaInsertar(nodo->izq, e);
		}
		else if (e > nodo->elemento) {
			_demoCompletaInsertar(nodo->der, e);
		}
		_balanceoDemoCompleta(nodo);
		return true;
	}

	bool _demoRotacionesInsertar(Nodo<T>*& nodo, T e) {
		if (nodo == nullptr) { //Nuevo elemento
			nodo = new Nodo<T>();
			nodo->elemento = e;
			return true;
		}
		else if (e == nodo->elemento) {
			return false;
		}
		else if (e < nodo->elemento) {
			_demoRotacionesInsertar(nodo->izq, e);
		}
		else if (e > nodo->elemento) {
			_demoRotacionesInsertar(nodo->der, e);
		}
		_balanceoDemoRotaciones(nodo);
		return true;
	}

	bool _demoSinRotacionesInsertar(Nodo<T>*& nodo, T e) {
		if (nodo == nullptr) { //Nuevo elemento
			nodo = new Nodo<T>();
			nodo->elemento = e;
			cout << "Presione cualquier tecla para ver el AVL con el nodo insertado...\n";
			cin.get();
			dibujarArbol();
			return true;
		}
		else if (e == nodo->elemento) {
			return false;
		}
		else if (e < nodo->elemento) {
			_demoSinRotacionesInsertar(nodo->izq, e);
		}
		else if (e > nodo->elemento) {
			_demoSinRotacionesInsertar(nodo->der, e);
		}
		_balanceoSinRotaciones(nodo);
		return true;
	}

	void _inOrden(Nodo<T>* nodo) {
		if (nodo == nullptr) return;
		_inOrden(nodo->izq);
		procesar(nodo->elemento);
		_inOrden(nodo->der);
	}
	void _inOrdenH(Nodo<T>* nodo) {
		if (nodo == nullptr) return;
		_inOrdenH(nodo->izq);
		//procesar(nodo->altura);
		procesar(_altura(nodo));
		_inOrdenH(nodo->der);
	}
	void _preOrden(Nodo<T>* nodo) {	//Raiz => Izq => Der
		if (nodo == nullptr) return;
		procesar(nodo->elemento);
		_preOrden(nodo->izq);
		_preOrden(nodo->der);
	}
	void _postOrden(Nodo<T>* nodo) {	//Izq => Der => Raiz
		if (nodo == nullptr) return;
		_postOrden(nodo->izq);
		_postOrden(nodo->der);
		procesar(nodo->elemento);
	}

	void _imprimeArbol(Nodo<T>* nodo, string indent, bool last) {
		if (nodo != nullptr) {
			cout << indent;
			if (last) {
				cout << "R----";
				indent += "   ";
			}
			else {
				cout << "L----";
				indent += "|  ";
			}
			cout << nodo->elemento << endl;
			_imprimeArbol(nodo->izq, indent, false);
			_imprimeArbol(nodo->der, indent, true);
		}
	}

	bool _eliminar(Nodo<T>*& nodo, T e) {
		if (nodo == nullptr) return false;
		//Buscamos el Nodo que contiene el elemento e
		else {
			//int r = comparar(nodo->elemento, e);
			if (e > nodo->elemento) {	//si (nodo->elemento < e)
				//return _eliminar(nodo->der, e);
				_eliminar(nodo->der, e);
			}
			else if (e < nodo->elemento) {	//si (nodo->elemento > e)
				//return _eliminar(nodo->izq, e);
				_eliminar(nodo->izq, e);
			}

			//Analizamos el escenario en el que se encuentra el Nodo a eliminar
			else { // r==0 es porque se encontró el elemento e en el arbol	| si (nodo->elemento == e)
				if (nodo->der == nullptr && nodo->izq == nullptr) {	//Caso 1: Hoja
					nodo = nullptr;
					delete nodo;	//*REZC: Sí se puede hacer delete nullptr, porque nullptr es un puntero
					return true;
				}
				else if (nodo->izq == nullptr) { //Caso 2: Izq Vacío y Der No Vacío
					nodo = nodo->der;
					return true;
				}
				else if (nodo->der == nullptr) { //Caso 3: Der Vacío e Izq No Vacío
					nodo = nodo->izq;
					return true;
				}
				else { //Caso 4: Izq y Der No Vacíos
					/*
					// [OPCION 1] El elegido será el menor (el que esta mas a la izquierda) de la derecha
					Nodo<T>* aux = nodo->der; //Se establece buscar el menor elemento por la derecha [PPT: Nodo es la Raiz, aux es 35]
					while (aux->izq != nullptr)
					{
					  aux = aux->izq; //Se obtiene la hoja menor
					}
					nodo->elemento = aux->elemento; //Se actualiza el elemento en el nodo raiz y
					//return _eliminar(nodo->der, aux->elemento); //se envía a eliminar el elemento en el arbol por la derecha
					_eliminar(nodo->der, aux->elemento); //se envía a eliminar el elemento en el arbol por la derecha
					*/

					// [OPCION 2] El elegido será el mayor (el que esta mas a la derecha) de la izquierda
					Nodo<T>* aux = nodo->izq; //Se establece buscar el menor elemento por la derecha [PPT: Nodo es la Raiz, aux es 35]
					while (aux->der != nullptr)
					{
						aux = aux->der; //Se obtiene la hoja menor
					}
					nodo->elemento = aux->elemento; //Se actualiza el elemento en el nodo raiz y
					//return _eliminar(nodo->der, aux->elemento); //se envía a eliminar el elemento en el arbol por la derecha
					_eliminar(nodo->izq, aux->elemento); //se envía a eliminar el elemento en el arbol por la derecha

				}
			}
		}

		_balanceo(nodo);

		return true;
	}


public:
	ArbolAVL(void(*nuevaFuncion)(T)) {
		this->procesar = nuevaFuncion;
		this->raiz = nullptr;
	}

	bool Insertar(T e) {
		return _insertar(raiz, e);
	}

	bool InsertarDemoCompleta(T e) {
		return _demoCompletaInsertar(raiz, e);
	}

	bool InsertarDemoRotación(T e) {
		return _demoRotacionesInsertar(raiz, e);
	}

	bool InsertarDemoSinRotación(T e) {
		return _demoSinRotacionesInsertar(raiz, e);
	}
	void inOrden() {
		_inOrden(raiz);
	}
	void inOrdenH() {
		_inOrdenH(raiz);
	}

	void preOrden() {
		_preOrden(raiz);
	}
	void postOrden() {
		_postOrden(raiz);
	}

	void levelOrder(function<void(Nodo<T>*)> accion) {
		if (!raiz) return;

		queue<Nodo<T>*> cola;
		cola.push(raiz);

		while (!cola.empty()) {
			Nodo<T>* actual = cola.front();
			cola.pop();
			accion(actual);

			if (actual->izq)
				cola.push(actual->izq);
			if (actual->der)
				cola.push(actual->der);
		}
	}

	//que los nodos vacíos se añaden en base a la altura del árbol
	void dibujarArbol() {
		if (!this->raiz) return;
		string digraph = "digraph L {\nbgcolor = ""black""\nnode[color=white fontcolor=white shape=circle width=.6]\nedge[color=white]\n";
		bool esRaiz = true;
		levelOrder([&](Nodo<T>* nodo)-> void {
			if(esRaiz)
				digraph += to_string(nodo->elemento) + ";\n";

			if (nodo->izq && nodo->der) {
				digraph += to_string(nodo->elemento) + "->" + to_string(nodo->izq->elemento) + ";\n";
				digraph += "node[style=invis]\nedge[style=invis]\n"; //cambia el formato del nodo a uno "vacío"
				digraph += to_string(nodo->elemento) + "->" + "\"" + to_string(nodo->elemento) + "?\"" + ";\n"; //agrega un nodo vacío al medio
				digraph += "node[style=solid]\nedge[style=solid]\n"; //devuelve el formato del nodo a su estado original
				digraph += to_string(nodo->elemento) + "->" + to_string(nodo->der->elemento) + ";\n";
				esRaiz = false;
				return;
			}

			if (nodo->izq) {
				digraph += to_string(nodo->elemento) + "->" + to_string(nodo->izq->elemento) + ";\n";
				digraph += "node[style=invis]\nedge[style=invis]\n"; //cambia el formato del nodo a uno "vacío"
				digraph += to_string(nodo->elemento) + "->" + "\"" + to_string(nodo->elemento) + "?\"" + ";\n"; //agrega un nodo vacío al medio
				digraph += to_string(nodo->elemento) + "->" + "\"" + to_string(nodo->elemento) + "=\"" + ";\n"; //agrega un nodo vacío al final
				digraph += "node[style=solid]\nedge[style=solid]\n"; //devuelve el formato del nodo a su estado original
				esRaiz = false;
				return;
			}

			if (nodo->der) {
				digraph += "node[style=invis]\nedge[style=invis]\n";
				digraph += to_string(nodo->elemento) + "->" + "\"" + to_string(nodo->elemento) + "?\"" + ";\n";
				digraph += to_string(nodo->elemento) + "->" + "\"" + to_string(nodo->elemento) + "=\"" + ";\n";
				digraph += "node[style=solid]\nedge[style=solid]\n";
				digraph += to_string(nodo->elemento) + "->" + to_string(nodo->der->elemento) + ";\n";
				esRaiz = false;
			}

			});

		digraph += "}\n";
		ofstream archivographvs("Archivograph.dot");
		if (!archivographvs.is_open()) {
			cout << "Error al abrir el archivo";
			return;
		}
		else {
			archivographvs << digraph;
		}
		archivographvs.close();
		system("dot -Tpng Archivograph.dot -o Archivograph.png");
		system("start Archivograph.png");
		cout << "Continue..." << endl;
		cin.get();
		//system("close Archivo.png");
	}
	void imprimeArbol() {
		_imprimeArbol(raiz, "", true);
	}

	bool Eliminar(T e) {
		return _eliminar(raiz, e);
	}
};
