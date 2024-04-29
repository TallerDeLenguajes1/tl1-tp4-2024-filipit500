#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct{
int TareaID;//Numérico autoincremental comenzando en 1000
char *Descripcion; //
int Duracion; // entre 10 – 100
} typedef Tarea;

typedef struct Nodo
{
    Tarea T;
    struct Nodo *Siguiente;
} Nodo;

Nodo * CrearNodo(Tarea valor)
{
    //creamos el nodo utilizando memoria dinamica//
    Nodo * NuevoNodo = (Nodo *)malloc(sizeof(Nodo));
    //usamos el operador flecha pues es un puntero a estructura//
    NuevoNodo->T = valor;
    //asignamos en null el puntero (enlace)
    NuevoNodo->Siguiente = NULL;
    //retornamos el nuevo nodo//
    return NuevoNodo;
}

Nodo * crearListaVacia()
{
    return NULL;
}

void InsertarNodo(Nodo ** start, Nodo *nuevoNodo)
{
    nuevoNodo->Siguiente = *start;
    *start = nuevoNodo;
}

void InsertarAlFinal(Nodo *start,Nodo *nuevoNodo)
{
    Nodo * Aux = start;
    while(Aux->Siguiente){
        Aux = Aux->Siguiente;
    }
    Aux->Siguiente = nuevoNodo;
}


Tarea crearTareas();
void mostrarTareas(Tarea *tareas,int totales);
void mostrarNodos(Nodo **nodos,int totales);

int main()
{
    Nodo * start = crearListaVacia();
    int opcion = 1,i = 0,totales = 1;
    Tarea *tareasArreglo = (Tarea *)malloc(sizeof(Tarea) * totales);
    Nodo ** nodosArreglo = (Nodo **)malloc(sizeof(Nodo*) * totales);
    while(opcion == 1){
    tareasArreglo[i]= crearTareas();
    nodosArreglo[i] = CrearNodo(tareasArreglo[i]);
    InsertarNodo(&start,nodosArreglo[i]);
    printf("desea ingresar una nueva tarea?\n");
    printf("1: cargar nueva tarea -- otro: salir\n");
    fflush(stdin);
    scanf("%d",&opcion);
    if(opcion == 1){
        totales++;
        i++;
        tareasArreglo = realloc(tareasArreglo,sizeof(tareasArreglo) * totales);
    }
    }
    mostrarTareas(tareasArreglo,totales);
    mostrarNodos(nodosArreglo,totales);
}


Tarea crearTareas()
{
    char buff[100];
    Tarea tareaNueva;
    tareaNueva.TareaID = 1000;
    printf("ingrese la descripcion de la tarea:");
    fflush(stdin);
    gets(buff);
    tareaNueva.Descripcion = (char *)malloc((strlen(buff)+1) * sizeof(char));
    strcpy(tareaNueva.Descripcion,buff);
    tareaNueva.Duracion = rand() %91 + 10;
    return tareaNueva;
}

void mostrarTareas(Tarea *tareas,int totales)
{
    for(int i = 0; i < totales; i++){
        printf("******TAREA %d ******\n",i+1);
        printf("descripcion: ");
        puts(tareas[i].Descripcion);
    }
}

void mostrarNodos(Nodo **nodos,int totales)
{
    for(int i = 0; i < totales; i++){
        printf("******NODO %d ******\n",i+1);
        puts(nodos[i]->T.Descripcion);
    }
}