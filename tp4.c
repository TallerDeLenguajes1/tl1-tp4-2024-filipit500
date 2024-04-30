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

Nodo *crearListaVacia();
Nodo *crearNodo(int *id);
void insertarNodo(Nodo **start, Nodo *nodo);
void mostrarNodos(Nodo **start);
Nodo buscarNodo(Nodo **start, int idBuscado);
void eliminarNodo(Nodo **start,int idBuscado);


int main()
{
    int id_autoincremental = 1000,opcion = 1,opcion2 = 1,id_buscado;
    Nodo *TareasPendientes = crearListaVacia();
    Nodo *TareasRealizadas = crearListaVacia();
    while(opcion == 1 || opcion == 2 || opcion == 3){
        printf("1: cargar tareas\n");
        printf("2: mostrar tareas\n");
        printf("3:modificar estado de las tareas\n");
        printf("eliga una opcion:");
        fflush(stdin);
        scanf("%d",&opcion);
        switch(opcion){
            case 1:
            while(opcion2 == 1){
            insertarNodo(&TareasPendientes,crearNodo(&id_autoincremental));
            printf("1: para cargar otra tarea\n");
            fflush(stdin);
            scanf("%d",&opcion2);
            }
            break;
            case 2:
            printf("******TAREAS PENDIENTES******\n");
            mostrarNodos(&TareasPendientes);
            printf("******TAREAS REALIZADAS******\n");
            mostrarNodos(&TareasRealizadas);
            break;
            case 3:
            printf("******TAREAS PENDIENTES******\n");
            mostrarNodos(&TareasPendientes);
            printf("eliga una tarea para marcar como realizada por su id:");
            fflush(stdin);
            scanf("%d",&id_buscado);
            Nodo nodoEncontrado = buscarNodo(&TareasPendientes,id_buscado);
            insertarNodo(&TareasRealizadas,&nodoEncontrado);
            eliminarNodo(&TareasPendientes,id_buscado);
            break;
        }
    }
}



Nodo *crearListaVacia()
{
    return NULL;
}

Nodo *crearNodo(int *id)
{
    Nodo * nodoCreado = (Nodo *)malloc(sizeof(Nodo));
    nodoCreado->T.TareaID = *id;
    (*id)++;
    char buff[100];
    printf("ingrese la descripcion de la tarea:");
    fflush(stdin);
    gets(buff);
    nodoCreado->T.Descripcion = (char *)malloc((strlen(buff) + 1) * sizeof(char));
    strcpy(nodoCreado->T.Descripcion,buff);
    printf("ingrese la duracion de la tarea:");
    fflush(stdin);
    scanf("%d",&nodoCreado->T.Duracion);
    nodoCreado->Siguiente = NULL;
    return nodoCreado;
}

void insertarNodo(Nodo **start, Nodo *nodo)
{
    nodo->Siguiente = *start;
    *start = nodo;
}

void mostrarNodos(Nodo **start)
{
    if(*start == NULL){
        printf("----------LA LISTA ESTA VACIA------\n");
    }
    else{
    Nodo *Aux = *start;
    while(Aux != NULL){
        printf("id: %d\n", Aux->T.TareaID);
        printf("descripcion: ");
        puts(Aux->T.Descripcion);
        printf("duracion: %d\n", Aux->T.Duracion);
        Aux = Aux->Siguiente;
    }
    }
}

Nodo buscarNodo(Nodo **start, int idBuscado)
{
    Nodo * Aux = *start;
    while(Aux != NULL && Aux->T.TareaID != idBuscado){
        Aux = Aux->Siguiente;
    }
    return *Aux;
}

void eliminarNodo(Nodo **start,int idBuscado)
{
    Nodo ** Aux = start;
    while(*Aux != NULL && (*Aux)->T.TareaID != idBuscado){
        Aux = &(*Aux)->Siguiente;
    }

    if(*Aux){
        Nodo * Temp = *Aux;
        *Aux = (*Aux)->Siguiente;
        free(Temp);
    }
}