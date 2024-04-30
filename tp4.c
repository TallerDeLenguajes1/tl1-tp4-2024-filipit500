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
void consultarPorIdTarea(Nodo **tareasPendientes,Nodo **tareasRealizadas);
void liberarMemoria(Nodo **start);


int main()
{
    int id_autoincremental = 1000,opcion = 1,opcion2 = 1,id_buscado;
    Nodo *TareasPendientes = crearListaVacia();
    Nodo *TareasRealizadas = crearListaVacia();
    while(opcion == 1 || opcion == 2 || opcion == 3 || opcion == 4){
        printf("1: cargar tareas\n");
        printf("2: mostrar tareas\n");
        printf("3:modificar estado de las tareas\n");
        printf("4: buscar por id o palabra clave\n");
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
            opcion2 = 1;
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
            case 4:
            consultarPorIdTarea(&TareasPendientes,&TareasRealizadas);
            break;
        }
    }
    liberarMemoria(&TareasPendientes);
    liberarMemoria(&TareasRealizadas);
    return 0;
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

void consultarPorIdTarea(Nodo **tareasPendientes,Nodo **tareasRealizadas)
{
    int opcion;
    printf("1: buscar por palabra -- 2: buscar por id\n");
    printf("eliga una opcion:");
    fflush(stdin);
    scanf("%d",&opcion);
    if(opcion == 2){
        int id;
        printf("ingrese el id:");
        fflush(stdin);
        scanf("%d",&id);
        Nodo * Aux = *tareasPendientes;
        Nodo * Aux2 = *tareasRealizadas;
        int encontro = 0;
        while(Aux != NULL && Aux->T.TareaID != id){
            Aux = Aux->Siguiente;
        }
        if(Aux != NULL){
            encontro = 1;
        }
        while(Aux2 != NULL && Aux2->T.TareaID != id){
            Aux2 = Aux2->Siguiente;
        }
        if(Aux2 != NULL){
            encontro = 2;
        }

        if(encontro == 1){
            printf("------ se encontro la tarea en pendientes ------\n");
            printf("id: %d\n", Aux->T.TareaID);
            printf("descripcion: ");
            puts(Aux->T.Descripcion);
            printf("duracion: %d\n", Aux->T.Duracion);
        }
        else if(encontro == 2){
            printf("------ se encontro la tarea en Realizados ------\n");
            printf("id: %d\n", Aux2->T.TareaID);
            printf("descripcion: ");
            puts(Aux2->T.Descripcion);
            printf("duracion: %d\n", Aux2->T.Duracion);
        }
        else{
            printf("NO SE ENCONTRO UNA TAREA CON ESE ID\n");
        }
    }
    else if(opcion == 1){
        Nodo * Aux1 = *tareasPendientes;
        Nodo * Aux2 = *tareasRealizadas;
        int encontro = 0;
        char buff[30];
        printf("ingrese una palabra clave:");
        fflush(stdin);
        gets(buff);
        while(Aux1 != NULL){
            if(strstr(Aux1->T.Descripcion,buff)){
                encontro = 1;
                printf("------SE ENCONTRO LA TAREA EN PENDIENTES ------\n");
                printf("id: %d\n", Aux1->T.TareaID);
                printf("descripcion: ");
                puts(Aux1->T.Descripcion);
                printf("duracion: %d\n", Aux1->T.Duracion);
            }
            Aux1 = Aux1->Siguiente;
        }
        while(Aux2 != NULL){
            if(strstr(Aux2->T.Descripcion,buff)){
                encontro = 1;
                printf("------SE ENCONTRO LA TAREA EN REALIZADOS ------\n");
                printf("id: %d\n", Aux2->T.TareaID);
                printf("descripcion: ");
                puts(Aux2->T.Descripcion);
                printf("duracion: %d\n", Aux2->T.Duracion);
            }
            Aux2 = Aux2->Siguiente;
        }

        if(encontro == 0){
            printf("NO SE ENCONTRO UNA TAREA QUE CONTENGA LA PALABRA CLAVE\n");
        }
        
    }
}

void liberarMemoria(Nodo **start)
{
    Nodo *Aux = *start;
    while(Aux != NULL){
        Nodo *temp = Aux;
        Aux = Aux->Siguiente;
        free(temp->T.Descripcion);
        free(temp);
    }
}