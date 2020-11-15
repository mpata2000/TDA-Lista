#include "lista.h"
#include <stdlib.h>

#define ERROR -1
#define EXITO 0
/*
 * Crea la lista reservando la memoria necesaria.
 * Devuelve un puntero a la lista creada o NULL en caso de error.
 */
lista_t* lista_crear(){
	return calloc(1,sizeof(lista_t));
}

/*
* Recive un nodo y su posicion, con la posicion que se esta buscando
* Esy devuelve el nodo de la posicion buscada. 
* Si la posicion no existe devuelve el ultimo nodo
*/
nodo_t* buscar_nodo(nodo_t* nodo,size_t posicion_buscada){
	if(!nodo->siguiente || ( posicion_buscada == 0) ){
		return nodo;
	}
	return buscar_nodo(nodo->siguiente,posicion_buscada-1);
}

/*
 * Inserta un elemento al final de la lista.
 * Devuelve 0 si pudo insertar o -1 si no pudo.
 */
int lista_insertar(lista_t* lista, void* elemento){
	if(!lista) return ERROR;

	nodo_t* nodo_aux = calloc(1,sizeof(nodo_t));
	if(!nodo_aux){
		return ERROR;
	}

	if(!lista->nodo_inicio){
		lista->nodo_inicio = nodo_aux;
	}else{
		lista->nodo_fin->siguiente = nodo_aux;
	}
	
	lista->nodo_fin = nodo_aux;
	lista->nodo_fin->elemento = elemento;
	lista->cantidad++;

	return EXITO;
}

/*
 * Inserta un elemento en la posicion indicada, donde 0 es insertar
 * como primer elemento y 1 es insertar luego del primer elemento.  
 * En caso de no existir la posicion indicada, lo inserta al final.
 * Devuelve 0 si pudo insertar o -1 si no pudo.
 */
int lista_insertar_en_posicion(lista_t* lista, void* elemento, size_t posicion){
	if(!lista) return ERROR;

	if(posicion >= (lista->cantidad)){  //Si la lista esta vacio o posicion es igual al ultimo nodo o mayor es lo mismo que lista_insertar
		return lista_insertar(lista,elemento);
	}
	if(!posicion){                     //Si la posicion es igual a 0 es lo mismo que lista_apilar
		return lista_apilar(lista,elemento);
	}

	nodo_t* nodo_colocar = calloc(1,sizeof(nodo_t));
	if(!nodo_colocar){
		return ERROR;
	}
	nodo_t* nodo_anterior = buscar_nodo(lista->nodo_inicio,posicion-1);

	nodo_colocar->siguiente = nodo_anterior->siguiente;
	nodo_anterior->siguiente =  nodo_colocar;
	nodo_colocar->elemento = elemento;
	lista->cantidad++;

	return 	EXITO;
}

/*
 * Recive una referenci a un nodo anterior al que quiere ser borrado 
 * y la catidad de elementos de la lista.
 * Borra el nodo y actualiza el nodo anterior:
 * Devuelve la nueva cantidad de elementos de la lista.
 */
size_t borrar_nodo(nodo_t* nodo_anterior,size_t cantidad){
	nodo_t* nodo_posicion = nodo_anterior->siguiente;
	nodo_anterior->siguiente = nodo_posicion->siguiente;	
	free(nodo_posicion);

	return (cantidad-1);
}

/*
 * Quita de la lista el elemento que se encuentra en la ultima posición.
 * Devuelve 0 si pudo eliminar o -1 si no pudo.
 */
int lista_borrar(lista_t* lista){
	if(lista_vacia(lista)) return ERROR;
	
	if(lista->cantidad == 1){
		free(lista->nodo_fin);
		lista->nodo_inicio = lista->nodo_fin = NULL;
		lista->cantidad--;
		return EXITO;
	}

	nodo_t* nodo_aux = buscar_nodo(lista->nodo_inicio,lista->cantidad-2);
	lista->nodo_fin = nodo_aux;
	lista->cantidad = borrar_nodo(nodo_aux,lista->cantidad);

	return EXITO;
}

/*
 * Quita de la lista el elemento que se encuentra en la posición
 * indicada, donde 0 es el primer elemento.  
 * En caso de no existir esa posición se intentará borrar el último
 * elemento.  
 * Devuelve 0 si pudo eliminar o -1 si no pudo.
 */
int lista_borrar_de_posicion(lista_t* lista, size_t posicion){
	if(lista_vacia(lista)) return ERROR;

	if(posicion >= lista->cantidad-1){  //Si la posicion es igual al ultimo nodo o mayor es lo mismo que lista_borrar
		return lista_borrar(lista);
	}
	if(!posicion){                     //Si la posicion es igual a 0 es lo mismo que lista_desencolar
		return lista_desencolar(lista);
	}

	nodo_t* nodo_anterior = buscar_nodo(lista->nodo_inicio,posicion-1);
	lista->cantidad = borrar_nodo(nodo_anterior,lista->cantidad);

	return EXITO;
}


/*
 * Devuelve el elemento en la posicion indicada, donde 0 es el primer
 * elemento.
 *
 * Si no existe dicha posicion devuelve NULL.
 */
void* lista_elemento_en_posicion(lista_t* lista, size_t posicion){
	if(lista_vacia(lista) || (posicion >= lista->cantidad)) return NULL;

	nodo_t* nodo_posicion = buscar_nodo(lista->nodo_inicio,posicion);
	return nodo_posicion->elemento;
}

/* 
 * Devuelve el último elemento de la lista o NULL si la lista se
 * encuentra vacía.
 */
void* lista_ultimo(lista_t* lista){
	if(lista_vacia(lista)) return NULL;

	return lista->nodo_fin->elemento;
}

/* 
 * Devuelve true si la lista está vacía o false en caso contrario.
 */
bool lista_vacia(lista_t* lista){
	if(!lista) return true;

	return(!(lista->nodo_inicio) || !(lista->nodo_fin) || !(lista->cantidad));
}

/*
 * Devuelve la cantidad de elementos almacenados en la lista.
 */
size_t lista_elementos(lista_t* lista){
	if(lista_vacia(lista)) return 0;
	
	return lista->cantidad;
}

/* 
 * Apila un elemento.
 * Devuelve 0 si pudo o -1 en caso contrario.
 */
int lista_apilar(lista_t* lista, void* elemento){
	if(!lista){
		return ERROR;
	}

	nodo_t* nodo_aux = calloc(1,sizeof(nodo_t));
	if(!nodo_aux){
		return ERROR;
	}

	nodo_aux->elemento = elemento;
	nodo_aux->siguiente = lista->nodo_inicio;
	if(lista_vacia(lista)){
		lista->nodo_fin= nodo_aux;
	}
	lista->nodo_inicio = nodo_aux;
	lista->cantidad++;
	return EXITO;
}

/* 
 * Desapila un elemento.
 * Devuelve 0 si pudo desapilar o -1 si no pudo.
 */
int lista_desapilar(lista_t* lista){
	if(lista_vacia(lista)){
		return ERROR;
	}

	nodo_t* nodo_aux = lista->nodo_inicio;
	lista->nodo_inicio = nodo_aux->siguiente;
	free(nodo_aux);
	lista->cantidad--;
	return EXITO;
}

/*
 * Devuelve el elemento en el tope de la pila o NULL
 * en caso de estar vacía.
 */
void* lista_tope(lista_t* lista){
	if(lista_vacia(lista)) return NULL;
	
	return lista->nodo_inicio->elemento;
}

/* 
 * Encola un elemento.
 * Devuelve 0 si pudo encolar o -1 si no pudo.
 */
int lista_encolar(lista_t* lista, void* elemento){
	return lista_insertar(lista, elemento);
}

/* 
 * Desencola un elemento.
 * Devuelve 0 si pudo desencolar o -1 si no pudo.
 */
int lista_desencolar(lista_t* lista){
	if(lista_vacia(lista)){
		return ERROR;
	}
	nodo_t* nodo_aux = lista->nodo_inicio;
	lista->nodo_inicio = nodo_aux->siguiente;
	free(nodo_aux);
	lista->cantidad--;
	return EXITO;
}

/*
 * Devuelve el primer elemento de la cola o NULL en caso de estar
 * vacía.
 */
void* lista_primero(lista_t* lista){
	if(lista_vacia(lista)){
		return NULL;
	}

	return lista->nodo_inicio->elemento;
}

/*
* Recive un nodo_t y libera todos sus nodos siguientes
* hasta el final
*/
void destruir_nodos(nodo_t* nodo){
	if(!nodo) return;
	destruir_nodos(nodo->siguiente);
	free(nodo);
}
/*
 * Libera la memoria reservada por la lista.
 */
void lista_destruir(lista_t* lista){
	if(!lista) return;
	if(lista->nodo_inicio){
		destruir_nodos(lista->nodo_inicio);
	}
	free(lista);
}

/*
 * Crea un iterador para una lista. El iterador creado es válido desde
 * el momento de su creación hasta que no haya mas elementos por
 * recorrer o se modifique la lista iterada (agregando o quitando
 * elementos de la lista). 
 *
 * Al momento de la creación, el iterador queda listo para devolver el
 * primer elemento utilizando lista_iterador_elemento_actual.
 *
 * Devuelve el puntero al iterador creado o NULL en caso de error.
 */
lista_iterador_t* lista_iterador_crear(lista_t* lista){
	if(!lista) return NULL;

	lista_iterador_t* iterador=calloc(1,sizeof(lista_iterador_t));
	if(!iterador) return NULL;
	
	iterador->lista = lista;

	if(!lista_vacia(lista)){
		iterador->corriente = lista->nodo_inicio;
	}
	return iterador;
}

/*
 * Devuelve true si hay mas elementos sobre los cuales iterar o false
 * si no hay mas.
 */
bool lista_iterador_tiene_siguiente(lista_iterador_t* iterador){
	if(!iterador){
		return false;
	}

	return iterador->corriente;
}

/*
 * Avanza el iterador al siguiente elemento.
 * Devuelve true si pudo avanzar el iterador o false en caso de
 * que no queden elementos o en caso de error.
 *
 * Una vez llegado al último elemento, si se invoca a
 * lista_iterador_elemento_actual, el resultado siempre será NULL.
 */
bool lista_iterador_avanzar(lista_iterador_t* iterador){
	if(!iterador || !iterador->corriente){
		return false;
	}

	iterador->corriente = iterador->corriente->siguiente;
	return iterador->corriente;
}

/*
 * Devuelve el elemento actual del iterador o NULL en caso de que no
 * exista dicho elemento o en caso de error.
 */
void* lista_iterador_elemento_actual(lista_iterador_t* iterador){
	if(!iterador || !iterador->corriente){
		return NULL;
	}
	return iterador->corriente->elemento;
}

/*
 * Libera la memoria reservada por el iterador.
 */
void lista_iterador_destruir(lista_iterador_t* iterador){
	free(iterador);
}

/*
 * Iterador interno. Recorre la lista e invoca la funcion con cada elemento de
 * la misma. Dicha función puede devolver true si se deben seguir recorriendo
 * elementos o false si se debe dejar de iterar elementos.
 *
 * La función retorna la cantidad de elementos iterados o 0 en caso de error.
 */
size_t lista_con_cada_elemento(lista_t* lista, bool (*funcion)(void*, void*), void *contexto){
	if(lista_vacia(lista) || !funcion) return 0;

	nodo_t* nodo = lista->nodo_inicio;
	size_t contador=0;

	while((nodo) && (funcion(nodo->elemento,contexto))){
		nodo = nodo->siguiente;
		contador++;
	}
	
	return contador;
}