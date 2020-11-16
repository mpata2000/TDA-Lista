# **TDA Lista**

Este trabajo es el resultado de lo pedido por la catedra de Mendez de algoritmos dos que es una combinacion de TDA Lista,Cola y Pila, y adems cuenta con un Iterador externo y interno. Se realizaron 191 pruebas sobre mi implementacion del TDA paa comprobar que su comportamiento se el correcto.

## **Tabla de Contenidos**

- [**TDA Lista**](#tda-lista)
  - [**Tabla de Contenidos**](#tabla-de-contenidos)
  - [**Compilacion:**](#compilacion)
  - [**Makefile:**](#makefile)
    - [**Comandos:**](#comandos)
      - [**make o make $(EXEC):**](#make-o-make-exec)
      - [**make debug:**](#make-debug)
      - [**make test:**](#make-test)
      - [**make run:**](#make-run)
      - [**make zip:**](#make-zip)
      - [**make clean:**](#make-clean)
      - [**make %.o:**](#make-o)
  - [**Funcionamiento:**](#funcionamiento)
    - [**pruebas.c (el main):**](#pruebasc-el-main)
    - [**Puntero NULL**](#puntero-null)
    - [**Creacion de Lista:**](#creacion-de-lista)
    - [**Lista vacia:**](#lista-vacia)
    - [**Funciones equivalentes:**](#funciones-equivalentes)
    - [**Listas como pilas:**](#listas-como-pilas)
    - [**Busqueda y liberacion de nodos:**](#busqueda-y-liberacion-de-nodos)
    - [**Creacion del iterador externo:**](#creacion-del-iterador-externo)
    - [**Iterador interno:**](#iterador-interno)
  - [**Teorico:**](#teorico)
    - [**TDA Lista-Teorico**](#tda-lista-teorico)
      - [**¿Qué es lo que entendés por una lista?**](#qué-es-lo-que-entendés-por-una-lista)
      - [**¿Cuáles son las diferencias entre ser simple o doblemente enlazada?**](#cuáles-son-las-diferencias-entre-ser-simple-o-doblemente-enlazada)
      - [**¿Cuáles son las características fundamentales de las Pilas?**](#cuáles-son-las-características-fundamentales-de-las-pilas)
      - [**¿Cuáles son las características fundamentales de las Colas?**](#cuáles-son-las-características-fundamentales-de-las-colas)
    - [**Iterador-Teorico**](#iterador-teorico)
      - [**¿Qué es un iterador? ¿Cuál es su función?**](#qué-es-un-iterador-cuál-es-su-función)
      - [**¿En qué se diferencia un iterador interno de uno externo?**](#en-qué-se-diferencia-un-iterador-interno-de-uno-externo)
  - [**Creditos:**](#creditos)

## **Compilacion:**


Para compilar y usar este TDA se utiliza un makefile.

**La linea principal de compilacion es:**
> `make` o `make lista_se`

**La linea principal de para ejecutar con mis pruebas:**
>`make run`

**La linea principal de para ejecutar con las pruebas de la catedra:**
>`make run arg_1=...`

- Se puede poner algo atras del arg_1.

**La linea principal de para ejecutar con valgrind:**
>`make test`

- Aplica lo mismo que en `make run`, si se inicializa arg_1 corre la pruebas de la catedra si no corre mis pruebas.

## **Makefile:**

----

```makefile
CC = gcc
CFILES = *.c
HFILES = *.h
OBJETOS = lista.o lista_minipruebas.o
FILES = Enunciado README.md
EXEC = lista_se
CFLAGS = -g -std=c99 -Wall -Wconversion -Wtype-limits -pedantic -Werror -O0
VFLAGS = --leak-check=full --track-origins=yes --show-reachable=yes

$(EXEC): pruebas.c $(OBJETOS)
    $(CC) $^ $(CFLAGS) -o $(EXEC)

debug: $(EXEC)
    gdb $(EXEC)

test: $(EXEC)
   valgrind $(VFLAGS) ./$(EXEC)

run: $(EXEC)
   ./$(EXEC) $(arg_1) $(arg_2) $(arg_3)

%.o: %.c %.h
   $(CC) $(CFLAGS) -c $< -o $@

zip:
   zip -r $(EXEC).zip $(CFILES) $(HFILES) $(FILES)

.PHONY: clean
clean:
   rm -f *.o $(EXEC)
```

### **Comandos:**

#### **make o make $(EXEC):**

```makefile
$(EXEC): pruebas.c $(OBJETOS)
    $(CC) $^ $(CFLAGS) -o $(EXEC)
```

 Este comando compila el programa si y solo si el archivo de jecucion (EXEC) esta desactulizado.

- `EXEC = lista_se`
  - El nombre del ejecutable que se quiere crear
- `OBJETOS = lista.o lista_minipruebas.o -O0`
  - Los objetos que se quieren compilar para compilar el ejecutable(solo se vuelven a compilar lo objetos si estan des acutializados)
- `CC = gcc`
  - El nombre del compilador que se va usar-
- `CFLAGS = -g -std=c99 -Wall -Wconversion -Wtype-limits -pedantic -Werror -O0`
  - Los flags de gcc que se van a usar al compilar el ejecutable.
- `$^`
  - Es una instruccion de make que agarra todo lo que esta depues del `:` y lo copia donde esta
  
#### **make debug:**

```makefile
debug: $(EXEC)
    gdb $(EXEC)
```

 Este comando primero chequea que `$(EXEC)` este compilado y actualizado(si no lo esta lo actualiza) y corre `gdb $(EXEC)` para debuggear el programa.

#### **make test:**

```makefile
test: $(EXEC)
   valgrind $(VFLAGS) ./$(EXEC) $(arg_1) $(arg_2) $(arg_3)
```

  Este comando primero chequea que evento `$(EXEC)` este compilado y actualizado; y corre valgrind para testear perdidas de memoria.

- `arg_n`
  - Estas variables se pueden utilizar cuando se quiere dar argumentos al main. Se inicializa escribiendo despues del comando `make test arg_1=i` y asi con cada arg_n que se quiera inicilazar.

#### **make run:**

```makefile
run: $(EXEC)
   ./$(EXEC) $(arg_1) $(arg_2) $(arg_3)
```

 Se usa para ejecutar el programa. El comando primero chequea que `$(EXEC)` este compilado y actualizado(si no lo esta lo actualiza).

- `arg_n`
  - Estas variables se pueden utilizar cuando se quiere dar argumentos al main. Se inicializa escribiendo despues del comando `make run arg_1=i` y asi con cada arg_n que se quiera inicilazar.

#### **make zip:**

```makefile
zip:
   zip -r $(EXEC).zip $(CFILES) $(HFILES) $(FILES)
```

Este comando crea un zip con los archivos `$(CFILES)`,`$(HFILES)` y `$(FILES)` con el nombre `$(EXEC).zip` (osea el nombre del ejecutable con .zip al final).

#### **make clean:**

```makefile
.PHONY: clean
clean:
   rm -f *.o $(EXEC)
```

make clean borra todos los objetos (*.o se remplaza por todos los ojetos en la carpeta) y el ejecutable (`$(EXEC)`)

- `.PHONY : clean.`
  - Esto hace un clean mas robusto. Si existiera un archivo que se llamara clean, y no la pusieramos, vamos a tener un comportamiento indefinido.

#### **make %.o:**

```makefile
%.o: %.c %.h
   $(CC) $(CFLAGS) -c $< -o $@
```

Esta es una funcion interna del make la cual es llamada por `make $(EXEC)`. Solo se llama cuando los `$(OBJETOS)` estan desactualizados.

- `$@`
  - Indica que ahi se escribir a el nombre de lo que queremos generar, el target de la regla que es %.o
- `%.o`
  - Indica que es la regla para cualquier cosa terminada en .o .
- `$<`
  - Es una instruccion de make que agarra la primer instruccion prerequisito despues del `:` que es %.c.
- `%.c`
  - Chequea para cada .o este compilado con el ultimo .c mas actualizado.

## **Funcionamiento:**


### **pruebas.c (el main):**

Si el main recive mas de un argumento ela pruebas que se van a correr son las prueba de `lista_minipruebas.c` dada por la catedra. Si no se recive nada las pruebas que se van a correr son las que yo cree.

### **Puntero NULL**

Ninguna de las funciones que recive punteros va a funcionar si el puntero enviado es NULL.

### **Creacion de Lista:**

Cuando se crea una lista se crea vacia. Con cantidad en 0 y ambos nodos apuntando a NULL. **Una lista creada siempre tiene que ser destuida.**

### **Lista vacia:**

Una lista esta vacia cuandor la cantidad es cero a alguno de sus dos nodos apunta a NULL( *Se utiliza o ya que si algun nodo apunta a NULL significa que algo salio mal y no sedeberia utilizar* ).

- A una lista vacia se le puede insertar un elemento con cualquier funcion de insertar que se desee y va a parar de estar vacia.
- Con una lisa vacia no se puede borrar ni leer ningun tipo de elemento.
- Si se borra el ultimo elemento restante de la lista queda vacia.

### **Funciones equivalentes:**

- `lista_insertar_en_posicion(lista,elemento,posicion_invalida)` == `lista_insertar(lista,elemento)`
- `lista_insertar_en_posicion(lista,elemento,0)` == `lista_apilar(lista,elemento)`
- `lista_encolar(lista,elemento)` == `lista_insertar(lista,elemento)`
- `lista_borrar_de_posicion(lista,posicion_invalid/ultima)` == `lista_borrar(lista)`
- `lista_borrar_de_posicion(lista,0)` == `lista_desencolar(lista)`

### **Listas como pilas:**

En las pilas el primer nodo se considera como el elemento en el tope de la pila,o sea el ultimo insertado. Y el ultimo elemento es el que su siguiente esta apuntando a NULL.

### **Busqueda y liberacion de nodos:**

Para la busqueda y liberacion de nodos se utilizaron funciones recursivas.

### **Creacion del iterador externo:**

Si al iterador se le manda una lista vacia, el iterador se va a crear apuntado a esa lista pero con un nodo coriente apuntado a NULL. **Se tiene que destuir el iterador**

### **Iterador interno:**

Un iterador interno tiene que recivir si o si una lista no vacia y una funcion valida.

## **Teorico:**



### **TDA Lista-Teorico**

#### **¿Qué es lo que entendés por una lista?**

Un TDA lista sirve para agrupar elementos donde yo puedo agregar y borrar elementos en la posicion en cualquier posicion arbitraria

#### **¿Cuáles son las diferencias entre ser simple o doblemente enlazada?**

Eun una lista simplemente enlazada cada nodo solo tiene una referencia a su nodo siguiente mientras que una lista doblemente enlazada cada nodo tiene referiencia al siguente como al anterior.

#### **¿Cuáles son las características fundamentales de las Pilas?**

La caracteristica fundamental de las pilas es LIFO ( last in, first out) que se refiere a que el ultimo elemento que entro es el plrmero en salir. Por eso se dice que los elementos se apilan y forman una pila.
Las dos operaciones principales son:

- `apilar()` o `push()`: pone un elemento en el tope de la pila.
- `desapilar()` o `pop()`: saca un elemento del tope de la pila.

#### **¿Cuáles son las características fundamentales de las Colas?**

La caracteristica fundamental de las pilas es FIFO ( first in, first out) que se refiere a que el primer elemento que entro es el primero en salir.
Las dos operaciones principales son:

- `encolar()` o `enqueue()`: pone un elemento al final de la cola.
- `desencolar()` o `dequeue()`: saca el primer elemento de la cola

### **Iterador-Teorico**

#### **¿Qué es un iterador? ¿Cuál es su función?**

Es una estructura o TDA que permite recorrer los datos almacenados en un TDA sin tener que ser consientes de la estructura del mismo.

#### **¿En qué se diferencia un iterador interno de uno externo?**

- Interador Interno:
  - Un iteradro interno permite recorrer todos los elementos de un TDA sin tener que controlar el ciclo en el cual se puede recorrer el mismo.
  - Funcion que suele utilizar:

```c
tipo_retorno lista_iterador(lista_t* lista,bool funcion(void* elemento,void* extra),void* extra);
```

- Iterador Externo:
  - Un iterador externo es un TDA que provee un set de primitivas especiales para recorrer una lista. Esta primitivas suelen ser:
    - `crear()`
    - `primero()`
    - `siguiente()`
    - `hay_siguiente()`
    - `elemento_acutal()`
    - `destruir()`
  - El iterador externo puede ser implementado como un objeto opaco que mantiene un puntero a  un elemento de la lista. Cada vez que avance solo hay que pedirle que se mueva un elemento, reduciendo la complejidad ya que sin iterador se tendria que recorrer todos los elementos hasta el actual+1.
  - El iterador externo debe saber como esta representada la lista ( *implementacion en conjunto* ).

## **Creditos:**

Los creditos de este hermoso TDA Lista son mios(Martin Pata AKA Patineta) y un poco corrector (Santiago Fernadez) que esta vez no voy a rick rollear.
