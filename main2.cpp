#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include "menu.h"
using namespace std;

// Estructura para guardar un borde del grafo
struct Edge {
    int source, dest;
    float weight;
};
 
// Estructura para guardar un nodo de "heap"
struct Node {
    int vertex;
	float weight;
};
 
// Una clase para representar un objeto de los grafos
class Graph
{
public:
    // un vector de vectores de `Edge` para representar una lista de adyacencia
    vector<vector<Edge>> adjList;
 
    // Constructor de graph
    Graph(vector<Edge> const &edges, int n)
    {
        // cambiar el tamaño del vector para contener `n` elementos de tipo `vector<int>`
        adjList.resize(n);
 
        // agrega bordes al grafo dirigido
        for (Edge const &edge: edges)
        {
            // insertar al final
            adjList[edge.source].push_back(edge);
        }
    }
};
 
void printPath(vector<int> const &prev, int i, int source) {
    if (i < 0) {
        return;
    }
    printPath(prev, prev[i], source);
    if (i != source) {
        cout << ", ";
    }
    cout << i;
}
 
// Objeto "struct" para comparar y ordenar el "heap"
struct comp {
    bool operator()(const Node &lhs, const Node &rhs) const {
        return lhs.weight > rhs.weight;
    }
};

// Funcion que mediante el indice recibido por parametros devuelve un string
string getPath(int n) {
	string options[] = {
		"Las Amazonas",
		"Core 8",
		"Zona Industrial 321",
		"Sierra Parima",
		"Unare",
		"Alta Vista",
		"Villa Brasil",
		"Trebol",
		"Villa Colombia",
		"Castillito",
		"Avenida Angosturita",
		"Avenida Las Americas"
	};
	return options[n];
}

// Ejecutar el algoritmo de Dijkstra en el grafo dado
void findShortestPaths(Graph const &graph, int source, int n, int endPath, bool isTwo) {
    // Crea un nodo de fuente min-heap y push(al final del vector) con distancia 0
    priority_queue<Node, vector<Node>, comp> min_heap;
    min_heap.push({source, 0});
 
    // Establece la distancia inicial desde la fuente a `v` como infinito
    vector<float> dist(n, INT_MAX);
 
    // la distancia de la fuente a sí misma es cero
    dist[source] = 0;
 
    // Array booleana para rastrear vertices para los cuales minimo
    // el costo ya se encuentra
    vector<bool> done(n, false);
    done[source] = true;
 
    // Guarda el "hijo" o "child" de un vertice
    vector<int> prev(n, -1);
 
    // Ejecutar hasta que el min-heap este vacio
    while (!min_heap.empty()) {
        // Elimina y retorna el mejor vertice
        Node node = min_heap.top();
        min_heap.pop();
 
        //Obtenemos el numero de vertice
        int u = node.vertex;
 
        for (auto i: graph.adjList[u]) {
            int v = i.dest;
            float weight = i.weight;
 
            if (!done[v] && (dist[u] + weight) < dist[v])
            {
                dist[v] = dist[u] + weight;
                prev[v] = u;
                min_heap.push({v, dist[v]});
            }
        }
 
        // marca el vértice `u` como hecho para que no se vuelva a recoger
        done[u] = true;
    }
	string path1;
	string path2;
    for (int i = 0; i < n; i++)
    {
        if (i != source && dist[i] != INT_MAX)
        {
        	path1 = getPath(source);
        	path2 = getPath(i);
        	if((i == endPath) && isTwo) {
	            cout << "Camino: (" << path1 << " => " << path2 << ")" << endl <<
				"Km recorridos: " << dist[i] << endl <<
				"Precio promedio: " << dist[i]*1.3 << endl <<
				"Ruta: [";
				printPath(prev, i, source);
	            cout << "]" << endl << endl;
			} else if(!isTwo) {
				cout << "Camino: (" << path1 << " => " << path2 << ")" << endl <<
				"Km recorridos: " << dist[i] << endl <<
				"Ruta: [";
				printPath(prev, i, source);
	            cout << "]" << endl << endl;
			}
        }
    }
}

int main() {
	// Vector con libreria "vector"
    vector<Edge> edges = {
    	// Caminos posibles
    	/*
		0 = Las Amazonas
		1 = Core 8
		2 = Zona Industrial 321
		3 = Sierra Parima
		4 = Unare
		5 = Alta Vista
		6 = Villa Brasil
		7 = El Trebol
		8 = Villa Colombia
		9 = Castillito
		*/
    	// (u, v, w) 'u' Origen, 'v' destino, 'w' peso(weight) o distancia a recorrer en kilometros(km)
    	// Ida
        {0, 1, 2.2}, {1, 2, 2.7},
		{2, 3, 3.6}, {3, 4, 7.5},
		{4, 5, 3.5}, {5, 6, 3.2},
		{6, 7, 1.3}, {7, 8, 2.8},
		{8, 9, 3.8}, {2, 4, 10.7},
		{2, 5, 12.4}, {10, 2, 4.0},
		{10, 4, 7.4}, {10, 3, 2.8},
		{10, 5, 10.5}, {10, 6, 13.8},
		{10, 7, 15.4}, {10, 9, 16.0},
		{11, 5, 2.3}, {11, 6, 1.5},
		{11, 7, 1.0}, {11, 8, 1.4}, {11, 9, 2.6},
		
		// Vuelta
		{1, 0, 2.2}, {2, 1, 2.7},
		{3, 2, 3.6}, {4, 3, 7.5},
		{5, 4, 3.5}, {6, 5, 3.2},
		{7, 6, 1.3}, {8, 7, 2.8},
		{9, 8, 3.8}, {4, 2, 10.7},
		{5, 2, 12.4}, {2, 10, 4.0},
		{3, 10, 2.8}, {4, 10, 7.4},
		{5, 10, 10.5}, {6, 10, 15.5},
		{7, 10, 15.4}, {9, 10, 16.0},
		{5, 11, 2.3}, {6, 11, 1.5},
		{7, 11, 1.0}, {8, 11, 1.4}, {9, 11, 2.6}
    };
 
    // Numero total de nodos en el grafo (etiquetados de 0 a 11)
    int n = 12;
 
    // Generar grafo
    Graph graph(edges, n);

	string options[] = {
		"Ver rutas posibles",
		"Ver rutas mas cortas entre dos paradas",
		"Ver todas las rutas posibles de una parada",
		"Salir"
	};
	
	int option = menu("Mejora tu ruta", options);

	int path1 = 0, path2 = 0;

	while(option != 4) {
		if(option == 1) {
			system("cls");
		    // Ejecuta el algoritmo de Dijkstra de cada nodo de tal forma que muestra todas las rutas posibles
		    for (int source = 0; source < n; source++) {
		        findShortestPaths(graph, source, n, 0, false);
		    }
		    system("pause");
		    system("cls");
		    option = menu("Mejora tu ruta", options);
		} else if(option == 2) {
			system("cls");
			for(int i = 0; i < n-2; i++) {
				cout << "(" << i << ")" << getPath(i) << endl;
			}
			cout << "Ingrese el inicio de su ruta: ";
			cin >> path1;
			cout << endl << "Ingrese el destino de su ruta: ";
			cin >> path2;
			cout << endl;
			findShortestPaths(graph, path1, n, path2, true);
			system("pause");
			system("cls");
			option = menu("Mejora tu ruta", options);
		} else if(option == 3) {
			system("cls");
			for(int i = 0; i < n-2; i++) {
				cout << "(" << i << ")" << getPath(i) << endl;
			}
			cout << "Ingrese la parada de la que desea conocer todas las rutas posibles: ";
			cin >> path1;
			cout << endl;
			findShortestPaths(graph, path1, n, 0, false);
			system("pause");
			system("cls");
			option = menu("Mejora tu ruta", options);
		} else if(option == 4) {
			return 0;
		}	
	}
    return 0;
}