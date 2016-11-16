#include "main.h"

/*Función que inserta números aleatorios en una lista*/
void inserta_datos_de_prueba(Lista lista);

int main()
{
    // Se crea la lista
    Lista lista = crea_lista();
    printf("La lista tiene %d elementos\n", longitud(lista));

    // Se insertan datos de prueba
    inserta_datos_de_prueba(lista);
    printf("La lista tiene %d elementos\n", longitud(lista));

    // Se remueve un elemento de la lista
    Elemento *borrado = quita_elemento(lista, 0);
    if (borrado != NULL) {free(borrado->valor);}
    free(borrado);
    printf("La lista tiene %d elementos\n", longitud(lista));

    // Se remueve un elemento que no existe en la lista
    quita_elemento(lista, longitud(lista));
    printf("La lista tiene %d elementos\n", longitud(lista));

    //Se imprime la lista antes de ordenar
    imprime_lista_int(lista);
    ordena_lista(lista, &cmp_int);

    //Se imprime la lista después de ordenar
    imprime_lista_int(lista);

    //Se libera la memoria ocupada
    borra_lista(lista);
}

void inserta_datos_de_prueba(Lista lista)
{
    srand(time(NULL));
    int *num_a_insertar;
    int indice;
    for (indice = 0; indice < 20; ++indice) {
        num_a_insertar = malloc(sizeof(int));
        *num_a_insertar = rand() % 100;
        inserta_elemento(lista, num_a_insertar);
    };
}


int cmp_int(const void* a, const void* b){
	int val_a = *(int *)a;							//Obtenemos el valor del apuntadosr
	int val_b = *(int *)b;							//Obtenemos el valor del apuntadosr
		if (val_a > val_b){
			return 1;
		}
		else if (val_a < val_b){
			return -1;
		}
		return 0;

}

void ordena_lista(Lista lista, int(*cmp)(const void*, const void*)){
	int l = longitud(lista);
	int arreglo[l]; 
	Elemento* ele = *lista;							//Creamos un elemento para iterar la lista
	for(int i= 0; i < l; i++){						//Copiamos la lista a un arreglo
		arreglo[i]= *(int*)ele -> valor; 			//Obtenemos el valor del apuntadosr
		ele= ele -> siguiente;						//Actualizamos el iterador
	}
	qsort(arreglo, l, sizeof(int), (*cmp)); 		//Ordenamos el arreglo con la funcion qsort
	ele= *lista;
	for(int i= 0; i < l; i++){						//Actualizamos la lista con los elementos ordenados
		*(int*)ele -> valor = arreglo[i]; 			//Obtenemos el valor del apuntadosr
		ele= ele -> siguiente;
	}
}

void borra_lista(Lista lista){
	Elemento* ele = *lista;							//Creamos un iterador para borrar la lista
	for (int i = 0; i < longitud(lista); ++i)
	{
		Elemento* nuevo = ele -> siguiente;			//Auxiliar para el borrado
		free(ele-> valor);							//Liberamos el la memoria del valor del elemento
		free(ele);									//liberamos la memoria del elemento
		ele = nuevo;								//actualizamos el elemento
	}
}

Elemento *quita_elemento(Lista lista, size_t posicion){
	if(posicion >= longitud(lista)){				//verificamos que no exeda el tamaño de la lista
		return NULL;
	}

	Elemento* ele =  *lista;						//Auxiliar para el borrado (iterador)
	for (int i = 1; i < posicion; ++i)				//Nos ubicamos en la posicion del elemento a borrar
	{
		ele = ele -> siguiente;
	}
	Elemento* prox = ele -> siguiente;				//Auxiliar para la actualizacion de referencias
	Elemento* prox2 = prox -> siguiente;			//Auxiliar para la actualizacion de referencias
	ele -> siguiente = prox2;						//Actualizacion de referencias
	free(prox);										//liberado de memoria
	return NULL;									
}
void imprime_lista_int(Lista lista){
	Elemento* ele = *lista;							//Auxiliar para iterar
	printf("[");
	for (int i = 0; i < longitud(lista); ++i)		//Iteracion de los elementos
	{	
		int val_a = *(int *)ele->valor;				//Obtencion del valor de la referencia
		printf("%d ", val_a);						//Impresion de los valores
		ele = ele -> siguiente;						//Actualizacion del iterador
	}
	printf("]\n");
	
}

Lista crea_lista(){
	Lista nueva = 	malloc(sizeof(Lista));			//Declaracion de una nueva lista y recervacion de memoria
	return nueva;
}

int inserta_elemento(Lista lista, void *valor){
	int tam = longitud(lista);
	Elemento* nuevo= malloc(sizeof(Elemento));		//Creacion del elemento a incertar
	nuevo -> siguiente= *lista;						//El siguiente elemento del incertado es la cabeza
	nuevo -> valor= valor;							//Valor del nuevo elemento
	*lista = nuevo;									//Actualizacion de la cabeza de la lista
	return tam+1;									//Tamaño anterior + 1
}
size_t longitud(Lista lista){
	if (*lista == NULL){							//Verifica que la lista no sea vacia
		return 0;
	}
	int l = 1;										//Inicializacion del tamaño de la lista
	Elemento* ele = *lista;
	Elemento* sig = ele -> siguiente;				//siguiente elemento
	while(sig != NULL){
		sig = sig -> siguiente;						//se actualiza el siguiente elemento
		l++;										//Se suman los elementos encontrados hasta que sea NULL
	}
	return l;
}