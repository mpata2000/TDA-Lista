#include "lista.h"
#include "pa2mm.h"
#include "lista_minipruebas.h"

#define ERROR -1
#define EXITO 0
#define MAX_ELEMENTOS 6
#define MAX_INSERTAR 10000
#define MAX_BORRAR_1 5000
#define MAX_BORRAR_2 2000


void pruebas_puntero_nulo(){

	pa2m_afirmar(lista_insertar(NULL,NULL)==ERROR,"No se puede insertar al final de una lista nula.");
	pa2m_afirmar(lista_insertar_en_posicion(NULL,NULL,0)==ERROR,"No se puede insertar en posicion  arbitraria una lista nula.");
	pa2m_afirmar(lista_borrar(NULL)==ERROR,"No se puede borrar en ultima posicion de una lista nula.");
	pa2m_afirmar(lista_borrar_de_posicion(NULL,0)==ERROR,"No se puede borrar en  posicion arbitraria de una lista nula.");
	pa2m_afirmar(!lista_elemento_en_posicion(NULL,0),"No se puede buscar elemento en una lista nula.");
	pa2m_afirmar(lista_ultimo(NULL)==NULL,"No se puede devolver ultimo elemento en una lista nula.");
	pa2m_afirmar(lista_vacia(NULL),"Lista nula esta vacia.");
	pa2m_afirmar(!lista_elementos(NULL),"Lista nula no tiene elementos.");
	pa2m_afirmar(lista_apilar(NULL,NULL)==ERROR,"No se puede apilar en lista nula.");
	pa2m_afirmar(lista_desapilar(NULL)==ERROR,"No se puede desapilar en lista nula.");
	pa2m_afirmar(!lista_tope(NULL),"Lista nula no tiene tope.");
	pa2m_afirmar(lista_encolar(NULL,NULL)==ERROR,"No se puede encolar en lista nula.");
	pa2m_afirmar(lista_desencolar(NULL)==ERROR,"No se puede desencolar en lista nula.");
	pa2m_afirmar(!lista_primero(NULL),"Lista nula no tiene primer elemento.");
	pa2m_afirmar(!lista_iterador_crear(NULL),"No se puede crear iterador con lista nula.");
	pa2m_afirmar(!lista_iterador_tiene_siguiente(NULL),"Iterador nulo no tiene siguiente.");
	pa2m_afirmar(!lista_iterador_avanzar(NULL),"Iterador nulo no puede avanzar.");
	pa2m_afirmar(!lista_iterador_elemento_actual(NULL),"Iterador nulo no tiene elemento actual.");


}

void pruebas_crear_lista(){
	lista_t* lista = NULL;

	pa2m_afirmar((lista = lista_crear()) != NULL,"Se puede crear lista.");
	pa2m_afirmar(lista_vacia(lista),"La lista esta vacia.");
	pa2m_afirmar(lista_borrar(lista) == ERROR,"Borrar lista vacia da error.");
	pa2m_afirmar(lista_borrar_de_posicion(lista,0) == ERROR,"Borrar en posicion en lista vacia da error.");
	pa2m_afirmar(!lista_elemento_en_posicion(lista,0),"El elemento de una lista vacia da NULL.");
	pa2m_afirmar(!lista_ultimo(lista),"El ultimo elemento de una lista vacia da NULL.");
	pa2m_afirmar(lista_desapilar(lista) == ERROR,"No se puede desapilar en una lista vacia.");
	pa2m_afirmar(!lista_tope(lista) ,"Lista tope devuelve NULL con lista vacia.");
	pa2m_afirmar(lista_desencolar(lista)==ERROR ,"No se puede desencolar en una lista vacia.");
	pa2m_afirmar(!lista_primero(lista) ,"Lista primero devuelve NULL con lista vacia.");

	lista_destruir(lista);
}

void pruebas_lista_insertar_borrar(){
	int elementos[MAX_ELEMENTOS]={1,2,3,4,5,6};

	lista_t* lista = lista_crear();
	pa2m_afirmar(lista_vacia(lista),"La lista esta vacia.");

	pa2m_afirmar(lista_insertar(lista, &elementos[0])==EXITO,"Se puede insertar el primer elemento.");     //Lista: 1
	pa2m_afirmar(lista_elementos(lista)==1,"La lista tiene 1 elemento.");
	pa2m_afirmar(!lista_vacia(lista),"La lista ya no esta vacia vacia.");
	
	pa2m_afirmar(lista_insertar(lista, &elementos[1])==EXITO,"Se puede insertar el segundo elemento.");    //Lista: 1 2
	pa2m_afirmar(lista_elementos(lista)==2,"La lista tiene 2 elemento.");

	pa2m_afirmar(lista_insertar(lista, &elementos[2])==EXITO,"Se puede insertar el tercero elemento.");    //Lista: 1 2 3
	pa2m_afirmar(lista_elementos(lista)==3,"La lista tiene 3 elemento.");

	pa2m_afirmar(lista_insertar(lista, &elementos[3])==EXITO,"Se puede insertar el cuarto elemento.");     //Lista: 1 2 3 4
	pa2m_afirmar(lista_elementos(lista)==4,"La lista tiene 4 elemento.");

	pa2m_afirmar((int*)lista_primero(lista) == &elementos[0],"El primer elemento esta bien");
	pa2m_afirmar((int*)lista_elemento_en_posicion(lista,1)==&elementos[1],"El segundo elemento es el correcto.");
	pa2m_afirmar((int*)lista_elemento_en_posicion(lista,2)==&elementos[2],"El tercer elemento es el correcto.");
	pa2m_afirmar((int*)lista_ultimo(lista)== &elementos[3],"El ultimo elemento es correcto.");

	for (size_t i = 0; i < 3; i++){
		pa2m_afirmar(lista_borrar(lista)==EXITO,"Se puede eliminar el ultimo nodo.");
		pa2m_afirmar((int*)lista_ultimo(lista)== &elementos[2-i],"El ultimo elemento es correcto.");
	}
	pa2m_afirmar(lista_borrar(lista)==EXITO,"Se puede eliminar el ultimo nodo restante.");
	pa2m_afirmar(lista_vacia(lista),"La lista esta vacia.");
	pa2m_afirmar(lista_borrar(lista)==ERROR,"No se puede eliminar el ultimo nodo con la lista vacia.");	

	lista_destruir(lista);

}

void pruebas_lista_insertar_arbitraria(){
	int elementos[MAX_ELEMENTOS]={1,2,3,4,5,6};
	lista_t* lista = lista_crear();

	pa2m_afirmar(lista_insertar_en_posicion(lista, &elementos[0], 100)==EXITO,"Se pudo agregar insercion arbitraria en una lista vacia.");   //Lista: 1
	pa2m_afirmar(lista_elementos(lista)==1,"La lista tiene un elemento");

	pa2m_afirmar(lista_insertar_en_posicion(lista, &elementos[1], 100)==EXITO,"Se pudo agregar en una posicion invalida.");   //Lista: 1 2
	pa2m_afirmar(lista_elementos(lista)==2,"La lista tiene un elemento");
	pa2m_afirmar((int*)lista_ultimo(lista)== &elementos[1],"El elemento es el esperado.");

	pa2m_afirmar(lista_insertar_en_posicion(lista, &elementos[2], 0)==EXITO,"Se pudo agregar al inicio.");   //Lista: 3 1 2
	pa2m_afirmar(lista_elementos(lista)==3,"La lista tiene tres elemento");
	pa2m_afirmar((int*)lista_primero(lista)== &elementos[2],"El elemento es el esperado en la posicion 0.");
	pa2m_afirmar((int*)lista_elemento_en_posicion(lista,1)==&elementos[0],"El segundo elemento es el correcto.");

	pa2m_afirmar(lista_insertar_en_posicion(lista, &elementos[3], 0)==EXITO,"Se pudo agregar devuelta al inicio.");   //Lista: 4 3 1 2
	pa2m_afirmar(lista_elementos(lista)==4,"La lista tiene cuatro elemento");
	pa2m_afirmar((int*)lista_primero(lista)== &elementos[3],"El elemento es el esperado en la posicion 0.");
	pa2m_afirmar((int*)lista_elemento_en_posicion(lista,1)==&elementos[2],"El segundo elemento es el correcto.");

	pa2m_afirmar(lista_insertar_en_posicion(lista, &elementos[4], 2)==EXITO,"Se pudo agregar en la posicion 2.");   //Lista: 4 3 5 1 2
	pa2m_afirmar(lista_elementos(lista)==5,"La lista tiene cinco elemento");
	pa2m_afirmar((int*)lista_elemento_en_posicion(lista,2)==&elementos[4],"El elemento es el esperado en la posicion 2.");
	pa2m_afirmar((int*)lista_elemento_en_posicion(lista,3)==&elementos[0],"El elemento es el esperado en la posicion 3.");

	pa2m_afirmar(lista_insertar_en_posicion(lista, &elementos[5], 4)==EXITO,"Se pudo agregar en la posicion 2.");   //Lista: 4 3 5 1 6 2
	pa2m_afirmar(lista_elementos(lista)==6,"La lista tiene cinco elemento");
	pa2m_afirmar((int*)lista_elemento_en_posicion(lista,4)==&elementos[5],"El anteultima elemento es el esperado.");
	pa2m_afirmar((int*)lista_ultimo(lista)== &elementos[1],"El ultimo elemento es el esperado.");

	lista_destruir(lista);
}

void pruebas_lista_borrar_arbitraria(){
	int elementos[MAX_ELEMENTOS]={1,2,3,4,5,6};
	lista_t* lista = lista_crear();

	for(int i=0; i < MAX_ELEMENTOS; i++){
		lista_insertar(lista, &elementos[i]);
	}                                                                                                                           //Lista: 1 2 3 4 5 6
	pa2m_afirmar(lista_elementos(lista)==6,"La lista tiene 6 elemento.");

	pa2m_afirmar(lista_borrar_de_posicion(lista, 0) == EXITO,"Se pudo eliminar el primer nodo.");                               //Lista: 2 3 4 5 6
	pa2m_afirmar(lista_elementos(lista)==5,"La lista tiene 5 elemento.");
	pa2m_afirmar((int*)lista_primero(lista)== &elementos[1],"El elemento es el esperado en la posicion 0.");

	pa2m_afirmar(lista_borrar_de_posicion(lista, 0) == EXITO,"Se pudo volver a eliminar el primer nodo.");                      //Lista: 3 4 5 6
	pa2m_afirmar(lista_elementos(lista)==4,"La lista tiene 4 elemento.");
	pa2m_afirmar((int*)lista_primero(lista)== &elementos[2],"El elemento es el esperado en la posicion 0.");

	pa2m_afirmar(lista_borrar_de_posicion(lista, 2) == EXITO,"Se pudo volver a eliminar el elemento en posicion 2");            //Lista: 3 4 6
	pa2m_afirmar(lista_elementos(lista)==3,"La lista tiene 3 elemento.");
	pa2m_afirmar((int*)lista_elemento_en_posicion(lista, 2)== &elementos[5],"El elemento es el esperado en la posicion 2.");

	pa2m_afirmar(lista_borrar_de_posicion(lista, 1) == EXITO,"Se pudo volver a eliminar el elemento en posicion 1");            //Lista: 3 6
	pa2m_afirmar(lista_elementos(lista)==2,"La lista tiene 2 elemento.");
	pa2m_afirmar((int*)lista_elemento_en_posicion(lista, 1)== &elementos[5],"El elemento es el esperado en la posicion 1.");

	pa2m_afirmar(lista_borrar_de_posicion(lista, 100) == EXITO,"Se elimina el ultimo nodo con una posicion invalida.");         //Lista: 3      
	pa2m_afirmar(lista_elementos(lista)==1,"La lista tiene 1 elemento.");
	pa2m_afirmar((int*)lista_ultimo(lista)== &elementos[2],"El ultimo elemento es el esperado.");

	pa2m_afirmar(lista_borrar_de_posicion(lista, 100) == EXITO,"Se elimina el ultimo nodo con una posicion invalida.");         //Lista:       
	pa2m_afirmar(lista_vacia(lista),"Lista vacia.");

	lista_destruir(lista);
}

//Prueba integradora de operaciones sobre la lista
void probar_operaciones_lista(){ 
	lista_t* lista = lista_crear();
	char a='a', b='b', c='c', d='d', w='w';
  
	pa2m_afirmar(lista_insertar(lista, &a)==EXITO,"Se puede insertar el primer elemento.");                                        //Lista: a
	pa2m_afirmar(lista_elementos(lista)==1,"La lista tiene un elemento.");
	pa2m_afirmar((char*)lista_ultimo(lista)==&a,"El elemento es el correcto.");

	pa2m_afirmar(lista_insertar(lista, &b)==EXITO,"Se puede insertar el segundo elemento.");                                       //Lista: a,b
	pa2m_afirmar(lista_elementos(lista)==2,"La lista tiene dos elemento.");
	pa2m_afirmar((char*)lista_ultimo(lista)== &b,"El elemento es el correcto.");


	pa2m_afirmar(lista_insertar_en_posicion(lista, &c, 100)==EXITO,"Se pudo agregar al final en posicion mayor a la cantidad.");   //Lista: a,b,c
	pa2m_afirmar(lista_elementos(lista)==3,"La lista tiene dos elemento");
	pa2m_afirmar((char*)lista_ultimo(lista)== &c,"El elemento es el correcto.");

	pa2m_afirmar(lista_insertar_en_posicion(lista, &d, 0)==EXITO,"Se pudo insertar en la primera posicion");                      //Lista: d,a,b,c
	pa2m_afirmar(lista_elementos(lista)==4,"La lista tiene cuatro elemento.");
	pa2m_afirmar((char*)lista_elemento_en_posicion(lista,0)==&d,"El elemento es el correcto.");

	pa2m_afirmar(lista_insertar_en_posicion(lista, &w, 3)==EXITO,"Se pudo insertar en una posicion arbritaria.");                 //Lista: d,a,b,w,c
	pa2m_afirmar(lista_elementos(lista)==5,"La lista tiene cinco elemento.");
	pa2m_afirmar((char*)lista_elemento_en_posicion(lista,3)==&w,"El elemento es el correcto.");

	pa2m_afirmar(lista_borrar(lista)==EXITO,"Se puede eliminar el ultimo nodo.");                                                //Lista: d,a,b,w
	pa2m_afirmar(lista_elementos(lista)==4,"La lista tiene cuatro elemento.");
	pa2m_afirmar((char*)lista_ultimo(lista)!=&b,"El elemento es el correcto.");


	pa2m_afirmar(lista_borrar_de_posicion(lista, 0) == EXITO,"Se pudo eliminar el primer nodo.");                               //Lista: a,b,w
	pa2m_afirmar(lista_elementos(lista)==3,"La lista tiene tres elemento.");

	pa2m_afirmar(lista_borrar_de_posicion(lista, 1) == EXITO,"Se pudo eliminar un nodo de posicion arbitraria.");              //Lista: a,w
	pa2m_afirmar(lista_elementos(lista)==2,"La lista tiene dos elemento.");
	pa2m_afirmar((char*)lista_elemento_en_posicion(lista,2)!=&b,"El elemento es el correcto.");

	pa2m_afirmar(lista_borrar_de_posicion(lista, 100) == EXITO,"Se pudo eliminar el ultimo nodo mandando posicion invalida");              //Lista: a
	pa2m_afirmar(lista_elementos(lista)==1,"La lista tiene uno elemento.");

	pa2m_afirmar(lista_borrar(lista)==EXITO,"Se puede eliminar el ultimo nodo.");                                                //Lista: d,a,b,w
	pa2m_afirmar(lista_vacia(lista),"Lista vacia.");


	lista_destruir(lista);
}

void probar_operaciones_cola(){
	lista_t* cola = lista_crear();

	char a='a', b='b', c='c';

	pa2m_afirmar(lista_encolar(cola,&a)==EXITO,"Se puede encolar el primer nodo");              //COLA: a
	pa2m_afirmar(lista_elementos(cola)==1,"La cola tiene un nodo.");
	pa2m_afirmar((char*)lista_primero(cola)==&a,"El nodo tiene el correcto elemento.");

	pa2m_afirmar(lista_encolar(cola,&b)==EXITO,"Se puede encolar el segundo nodo");            //COLA: b a 
	pa2m_afirmar(lista_elementos(cola)==2,"La cola tiene dos nodo.");
	pa2m_afirmar((char*)lista_primero(cola)== &a,"El nodo tiene el correcto elemento.");

	pa2m_afirmar(lista_encolar(cola,&c)==EXITO,"Se puede encolar el tercer nodo");             //COLA: c b a
	pa2m_afirmar(lista_elementos(cola)==3,"La cola tiene tres nodo.");
	pa2m_afirmar((char*)lista_primero(cola)== &a,"El nodo tiene el correcto elemento.");

	pa2m_afirmar(lista_desencolar(cola)==EXITO,"Se puede desencolar un nodo");                 //COLA: b a
	pa2m_afirmar(lista_elementos(cola)==2,"La cola tiene dos nodo.");

	pa2m_afirmar(lista_desencolar(cola)==EXITO,"Se puede apilar un nodo");                     //COLA: a
	pa2m_afirmar(lista_elementos(cola)==1,"La cola tiene un nodo.");
	
	pa2m_afirmar(lista_desencolar(cola)==EXITO,"Se puede desencolar el ultimo nodo");          //COLA: NULL
	pa2m_afirmar(lista_vacia(cola),"La cola vacia.");	

	
	lista_destruir(cola);
}

void pruebas_volumetricas_lista(){
	lista_t* lista = lista_crear();

	bool  se_inserto = true;

	for(size_t i=0; i < MAX_INSERTAR; i++){
		if(lista_insertar(lista, (void*)(size_t)(i+1)) == ERROR){
			se_inserto = false;
		}
	}
	pa2m_afirmar(se_inserto, "Se insertaron 10k elementos");

	bool  elementos_son_correctos = true;
	for(size_t i=0; i < MAX_INSERTAR; i++){
		void* elemento = lista_elemento_en_posicion(lista,i);

		if(elemento != (void*)(i+1)){
			elementos_son_correctos  = false;
		}
	}
	pa2m_afirmar(elementos_son_correctos, "Todos los elementos son correctos");

	bool  se_pudo_borrar = true;
	for(size_t i=0; i < MAX_BORRAR_1; i++){
		if(lista_borrar(lista) == ERROR){
			se_pudo_borrar = false;
		}
	}
	pa2m_afirmar(se_pudo_borrar, "Se pudo borrar 5k elementos.");

	se_pudo_borrar = true;
	for(size_t i=0; i < MAX_BORRAR_2; i++){
		if(lista_borrar(lista) == ERROR){
			se_pudo_borrar = false;
		}
	}
	pa2m_afirmar(se_pudo_borrar, "Se pudo borrar 2k elementos.");


	lista_destruir(lista);    //Pruebo que lista destruir pueda borrar muchos nodos
}

void probar_operaciones_pila(){
	lista_t* pila = lista_crear();

	char a='a', b='b', c='c';

	pa2m_afirmar(lista_apilar(pila,&a)==EXITO,"Se puede apilar el primer nodo");              //Pila: a
	pa2m_afirmar(lista_elementos(pila)==1,"La lista tiene un nodo.");
	pa2m_afirmar((char*)lista_tope(pila)==&a,"El nodo tiene el correcto elemento.");

	pa2m_afirmar(lista_apilar(pila,&b)==EXITO,"Se puede apilar el segundo nodo");            //Pila: a b
	pa2m_afirmar(lista_elementos(pila)==2,"La lista tiene dos nodo.");
	pa2m_afirmar((char*)lista_tope(pila)==&b,"El nodo tiene el correcto elemento.");

	pa2m_afirmar(lista_apilar(pila,&c)==EXITO,"Se puede apilar el tercer nodo");             //Pila: a b c
	pa2m_afirmar(lista_elementos(pila)==3,"La lista tiene tres nodo.");
	pa2m_afirmar((char*)lista_tope(pila)==&c,"El nodo tiene el correcto elemento.");

	pa2m_afirmar(lista_desapilar(pila)==EXITO,"Se puede desapilar un nodo");                 //Pila: a b
	pa2m_afirmar(lista_elementos(pila)==2,"La lista tiene dos nodo.");
	pa2m_afirmar((char*)lista_tope(pila)==&b,"El nodo tiene el correcto elemento.");

	pa2m_afirmar(lista_desapilar(pila)==EXITO,"Se puede apilar un nodo");                    //Pila: a
	pa2m_afirmar(lista_elementos(pila)==1,"La lista tiene un nodo.");
	pa2m_afirmar((char*)lista_tope(pila)==&a,"El nodo tiene el correcto elemento.");
	
	pa2m_afirmar(lista_desapilar(pila)==EXITO,"Se puede desapilar el ultimo nodo");          //Pila: NULL
	pa2m_afirmar(lista_vacia(pila),"La lista vacia.");
	
	lista_destruir(pila);	
}

void pruebas_iterador_vacio(){
	lista_t* lista = lista_crear();
	
	lista_iterador_t* iterador = NULL;

	pa2m_afirmar((iterador = lista_iterador_crear(lista)), "Puedo crear un iterador con una lista vacia.");
	pa2m_afirmar(!lista_iterador_tiene_siguiente(iterador), "El iterador no tiene elemento siguiente.");
	pa2m_afirmar(!lista_iterador_avanzar(iterador), "El iterador no puede avanzar.");

	pa2m_afirmar(!lista_iterador_tiene_siguiente(iterador), "El iterador no tiene elemento siguiente(Despues de tratar avanzar).");
	pa2m_afirmar(!lista_iterador_avanzar(iterador), "El iterador no puede avanzar(Despues de tratar avanzar).");

	lista_iterador_destruir(iterador);
	lista_destruir(lista);
}

void pruebas_iterador_externo(){
	int elementos[MAX_ELEMENTOS]={1,2,3,4,5,6};
	lista_t* lista = lista_crear();

	for(int i=0; i < MAX_ELEMENTOS; i++){
		lista_insertar(lista, &elementos[i]);
	}
	lista_iterador_t* iterador = NULL;

	pa2m_afirmar((iterador = lista_iterador_crear(lista)), "Puedo crear un iterador con una lista con elementos.");
	
	for(int i=0; i < MAX_ELEMENTOS-1; i++){
		pa2m_afirmar(lista_iterador_tiene_siguiente(iterador), "El iterador tiene elemento actual no nulo.");
		pa2m_afirmar(((int*)lista_iterador_elemento_actual(iterador) == &elementos[i]), "El elemento es correcto");
		pa2m_afirmar(lista_iterador_avanzar(iterador), "El iterador puede avanzar y devuelve True.");
	}
	pa2m_afirmar(lista_iterador_tiene_siguiente(iterador), "El iterador tiene elemento actual no nulo.");
	pa2m_afirmar(((int*)lista_iterador_elemento_actual(iterador) == &elementos[MAX_ELEMENTOS-1]), "El elemento es correcto");
	pa2m_afirmar(!lista_iterador_avanzar(iterador), "El iterador puede avanzar y devuelve FALSE por estar en la utima posicion.");

	pa2m_afirmar(!lista_iterador_tiene_siguiente(iterador), "El iterador tiene elemento actual es NULL.");
	pa2m_afirmar(!lista_iterador_avanzar(iterador), "El iterador no puede avanzar y devuelve FALSE por estar en la utima posicion.");

	lista_iterador_destruir(iterador);
	lista_destruir(lista);
}

bool prueba_elemento_iterador_interno(void* elemento, void* contador){
    (*(int*)contador)++;																		 // Primero aumento contexto y despues comparo
	pa2m_afirmar((*(int*)elemento == *(int*)contador),"El elemento coincide con lo esperado");  // porque el primer elemento es 0

    return true;
}

/* Corta cuando el elemento es 4*/
bool prueba_iterador_interno_cortar(void* elemento, void* contador){
    if(*(int*)elemento == 4){
		return false;
	}

	(*(int*)contador)++;																		 // Primero aumento contexto y despues comparo
	pa2m_afirmar((*(int*)elemento == *(int*)contador),"El elemento coincide con lo esperado");  // porque el primer elemento es 0
    return true;
}

void pruebas_iterador_interno(){
	int elementos[MAX_ELEMENTOS]={1,2,3,4,5,6};
	lista_t* lista = lista_crear();

	for(int i=0; i < MAX_ELEMENTOS; i++){
		lista_insertar(lista, &elementos[i]);
	}
	
	int contexto = 0;
	pa2m_afirmar(!lista_con_cada_elemento(lista,NULL,(void*)&contexto),"Iterador interno devuelve 0 si no hay funcion");
	lista_con_cada_elemento(lista,prueba_elemento_iterador_interno,(void*)&contexto);
	pa2m_afirmar((contexto == lista_elementos(lista)),"El contexto coincide con la cantidad de elementos");

	contexto = 0;
	lista_con_cada_elemento(lista,prueba_iterador_interno_cortar,(void*)&contexto);
	pa2m_afirmar((contexto == 3),"La funcion puede cortar el iterador interno.");

	lista_destruir(lista);
}

int main(int argc, char *argv[] ) {

	if(argc > 1){
		pruebas_catedra();
	}else{
		
		pa2m_nuevo_grupo("Pruebas con puntero NULL");
		pruebas_puntero_nulo();

		pa2m_nuevo_grupo("Pruebas Lista: Crear");
		pruebas_crear_lista();

		pa2m_nuevo_grupo("Pruebas Lista: Insertar y borrar");
		pruebas_lista_insertar_borrar();

		pa2m_nuevo_grupo("Pruebas Lista: Insertar en posicion arbitraria");
		pruebas_lista_insertar_arbitraria();

		pa2m_nuevo_grupo("Pruebas Lista: Borrar en posicion arbitraria");
		pruebas_lista_borrar_arbitraria();

		pa2m_nuevo_grupo("Pruebas Lista: Prueba integradoras");
		probar_operaciones_lista();

		pa2m_nuevo_grupo("Pruebas Lista: Volumetricas");
		pruebas_volumetricas_lista();

		pa2m_nuevo_grupo("Pruebas Lista: Pila");
		probar_operaciones_pila();

		pa2m_nuevo_grupo("Pruebas Lista: Cola");
		probar_operaciones_cola();

		pa2m_nuevo_grupo("Pruebas Iterador externo con lista vacia");
		pruebas_iterador_vacio();

		pa2m_nuevo_grupo("Pruebas Iterador externo");
		pruebas_iterador_externo();

		pa2m_nuevo_grupo("Pruebas Iterador interno");
		pruebas_iterador_interno();

		pa2m_mostrar_reporte();
	}


	return 0;

	
}
