#include <stdio.h>
#include <stdlib.h>

#define TAMANO 7
#define edadMin 10 
#define edadMax 65

#define pesoMin 50.0f
#define pesoMax 100.0f

char *nombres[TAMANO] = {"Jose Perez","Maria Garcia","Ana Andrade", "Julio Como", "Julia Rodriguez", "Antonio Aguilar", "Diana Marcel" };


typedef struct personaTDA{
	int edad;
	int peso;
	char *nombre;
	struct listaHijosTDA *hijos;
}Persona;

typedef struct listaHijosTDA{
	Persona *per;
	struct listaHijosTDA *siguiente;
}ListaHijos;



//Problema 0: La funcion recibe un arguento peso de tipo float y se la asigna a una veriable de tipo int
// Soluci�n: hacer un casting a la variable que recibe o cambarle de argumento en este caso cambiare el argumento peso de tipo float a tipo int
Persona *crearPersona(char *nombre, int edad, int peso){
	//Problema1 : La veriable nuevo es un puntero y no tiene un espcio de memoria asignado.
	//solucion: inicializar puntero con malloc 
	Persona *nuevo=(Persona *)malloc(sizeof(Persona));
	//Condicion para comprobar el puntero no  es nulo y si es asi sale del programa
	if(nuevo == NULL){
			return NULL;		
		}

	nuevo->nombre = nombre;
	nuevo->edad = edad;
	nuevo->peso = peso;

	

	nuevo->hijos = NULL;
	//Problema 2 : Retorna la  direccion de memoria de variable nuevo
	//Solucion : Quitar el & y devover la variable nuevo que es un puntero.   
	return nuevo;				
}


int anadirHijo(Persona *padre, Persona *hijo){
	
	ListaHijos *lista_hijos = padre->hijos;

	if(lista_hijos == NULL){
		ListaHijos *lista = (ListaHijos *)malloc(sizeof(ListaHijos));
		if(lista == NULL){
			return -1;		
		}
		lista->per = hijo;
		lista->siguiente = NULL;
		padre->hijos = lista;
		return 0;
	}

	else{
		while(lista_hijos != NULL){
		
			if(lista_hijos->siguiente == NULL){
				break;
			}
			lista_hijos = lista_hijos->siguiente;
		}

					
		ListaHijos *nuevo = (ListaHijos *)malloc(sizeof(ListaHijos));
		if(nuevo == NULL){
			return -1;		
		}
		nuevo->per = hijo;
		//Problema 4: el puntero siguiente del puntero nuevo se apunta hacia si mismo lo cual har� que nunca acabe el ciclo while
		//Slucion. Hacer que nuevo->siguiente apunte a NULL
		nuevo->siguiente =NULL;
		//fin solucion
		lista_hijos->siguiente = nuevo;
		return 0;	
		
	}
	return -1;
}

void mostrarInfoPersona(Persona *persona){
	if(persona != NULL){
		printf("Nombre: %s\nPeso: %d kg\nEdad: %d\n",persona->nombre, persona->peso, persona->edad);
		if(persona->hijos == NULL){
			printf("Hijos: esta persona no tiene hijos\n");
			return;
		}
		else{
			ListaHijos *lista_hijos = persona->hijos;
			printf("Los hijos de %s son:\n", persona->nombre);

			while(lista_hijos != NULL){
				printf("- %s\n", lista_hijos->per->nombre);	
				lista_hijos = lista_hijos->siguiente;		
			}
		}
	}
}
int main(void){

	Persona *listaPersona[TAMANO];
	int i = 0;
	//problema 5 :  el = en la condicion del for hacia que acceda a mas  elementos del arreglo 
	//con lo que estaba accediendo a un espacio de memoria fuera del array
	//Soluci�n: Quitar el igual de la condicion del for
	for(i = 0; i </*=*/ TAMANO; i++){			
		int edad = edadMin + rand() / (RAND_MAX / (edadMax - edadMin + 1) + 1);
		int peso = pesoMin + rand() / (RAND_MAX / (pesoMax - pesoMin + 1) + 1);
		//problema 3: No se estaba asignando a una viariable o no se guardab en una array lo que retorna la funcion crear persona 
		//Solucion: Asignarle a lsitaPersona la funcion crear personas
		listaPersona[i]=crearPersona(nombres[i],  edad, peso);
	}
	anadirHijo(listaPersona[0], listaPersona[1]);
	anadirHijo(listaPersona[3], listaPersona[2]);
	anadirHijo(listaPersona[3], listaPersona[6]);
	anadirHijo(listaPersona[4], listaPersona[5]);
	for(i = 0; i < TAMANO; i++){			

		mostrarInfoPersona(listaPersona[i]);
		printf("\n");

	}
}


