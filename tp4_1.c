#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>


/* Estructuras */
typedef struct Tarea
{
    int tareaID;        // autoincrementar desde 1000
    char *descripcion;  // acordate de guardar memoria
    int duracion;       // entre 10 y 100
}Tarea;

typedef struct Nodo     // C te rompe si no tenes bien los nombre de las estructuras
{
    Tarea datos;
    struct Nodo *siguiente;   // cunado la estructura se usa a si misma tiene que llevar 'struct'
}Nodo;


/* Firmas de funciones */
int presentarMenu();
int buscarNodo(Nodo **Cabeza, int IDBuscado);
Nodo *CrearListaVacia();
Nodo *quitarNodo(Nodo **Cabeza);
void agregarTareaPendiente(Nodo **Cabeza, int id);     // esto es insertarNodo, puntero doble a la lista y simple al nodo
void mostrarUnaSolaLista(Nodo *lista);
void agregarTareaCompletada(Nodo **listaPend, Nodo **listaComp, int id);
Nodo buscarTareaPorID(Nodo **listaPend, Nodo **listaComp, int idABuscar);
Nodo buscarTareaPorPalabra();



int main(int argv, char *argc[])
{
    /* Variables */
    int auxID = 999, opcion, completadoID;
    char continuar = 'S', otraTareaNueva = 'N', completarOtraTarea = 'S', opcionBusqueda;

    // creas la lista de tareas pendientes, 'St' por Start
    Nodo *StPendientes;
    StPendientes = CrearListaVacia();
    // creas la lista de tareas completadas
    Nodo *StCompletadas;
    StCompletadas = CrearListaVacia();

    while (continuar == 'S')    // mientras continuar sea no, el programa sigue
    {
        opcion = presentarMenu();
        switch (opcion)
        {
            case 1:         // opcion para cargar tareas nuevas

                do
                {
                    auxID += 1;
                    agregarTareaPendiente(&StPendientes, auxID);

                    do
                    {
                        printf("\nQuiere agregar otra tarea? (S/N): ");
                        fflush(stdin);
                        scanf("%c", &otraTareaNueva);
                        otraTareaNueva = toupper(otraTareaNueva);
                    } while (otraTareaNueva != 'N' && otraTareaNueva != 'S');

                } while (otraTareaNueva == 'S');

                break;

            case 2:         // opcion para pasar una tarea a la lista de completadas

                mostrarUnaSolaLista(StPendientes);
                do
                {
                    printf("Ingrese el ID de la tarea completda: ");
                    fflush(stdin);
                    scanf("%d", &completadoID);

                    agregarTareaCompletada(&StPendientes, &StCompletadas, completadoID);

                    do
                    {
                        printf("\nQuiere pasar otra tarea a la lista de completadas? (S/N): ");
                        fflush(stdin);
                        scanf("%c", &completarOtraTarea);
                        completarOtraTarea = toupper(completarOtraTarea);
                    } while (completarOtraTarea != 'N' && completarOtraTarea != 'S');
                } while (completarOtraTarea == 'S');

                break;

            case 3:         // opcion para mostrar las listas

                if (StPendientes == NULL)
                {
                    printf("\nAun no se registraron tareas nuevas.\n");
                }
                else
                {
                    mostrarUnaSolaLista(StPendientes);    
                }

                if (StCompletadas == NULL)
                {
                    printf("\nAun no hay ninguna tarea completada.\n");
                }
                else
                {
                    mostrarUnaSolaLista(StCompletadas);
                }

                break;

            case 4:         // opcion para buscar una tarea

                do
                {
                    printf("Quiere buscar por ID o por palabra? (I/P)");
                    fflush(stdin);
                    scanf("%c", &opcionBusqueda);
                } while (opcionBusqueda != 'I' && opcionBusqueda != 'P');

                if (opcionBusqueda == 'I')
                {
                    /* code */
                }
                else
                {
                    /* code */
                }

                break;

        }

        do
        {
            printf("Desea continuar con otra opcion? (S/N): ");
            fflush(stdin);
            scanf("%c", &continuar);
            continuar = toupper(continuar);
        } while (continuar != 'S' && continuar != 'N');
    }

    /* supongo que cuando termines en este caso tendrias que borrar ambas listas */

    printf("\nHasta la proxima!\n");
    return 0;
}



/* Desarrollo de funciones */

Nodo *CrearListaVacia()
{
    return NULL;
}


int presentarMenu()
{
    int eleccion;

    printf("\nQue tarea quiere realizar?\n");
    printf("1. Guardar tarea nueva.\n");
    printf("2. Marcar una tarea como completada.\n");
    printf("3. Listar todas las tareas.\n");
    printf("4. Buscar una tarea.\t\t\t");                     // dentro de buscar preguntas si es por id o por palabra
    printf("Opcion: ");
    scanf("%d", &eleccion);

    while (eleccion != 1 && eleccion != 2 && eleccion != 3 && eleccion != 4)
    {
        printf("\nEl numero elegido no corresponde a una tarea valida.\n");
        printf("Que tarea quiere realizar?\t\t");
        printf("Opcion: ");
        fflush(stdin);
        scanf("%d", &eleccion);
    }

    return eleccion;
}


void agregarTareaPendiente(Nodo **Cabeza, int id)
{
    int duracion;
    char *buffer = (char *)malloc(sizeof(char) * 100);              // 100 letras para una descripcion de la tarea
    Nodo *nodoNuevo = (Nodo *)malloc(sizeof(Nodo));

    printf("\nIngrese una descripcion para la tarea: \n");
    fflush(stdin);
    gets(buffer);
    printf("\nIngrese una duracion en horas para la tarea: ");
    scanf("%d", &duracion);

    nodoNuevo->datos.tareaID = id;
    nodoNuevo->datos.descripcion = (char *)malloc(sizeof(char) * strlen(buffer) + 1);
    strcpy(nodoNuevo->datos.descripcion, buffer);
    nodoNuevo->datos.duracion = duracion;
    nodoNuevo->siguiente = NULL;

    nodoNuevo->siguiente = *Cabeza;         // la cabecera de la lista se inicializa siempre en NULL
    *Cabeza = nodoNuevo;                    // no deberia haber problema con esta asignacion

    free(buffer);
}


void mostrarUnaSolaLista(Nodo *lista)
{
    Nodo *listaAuxiliar = lista;
    while (listaAuxiliar != NULL)
    {
        printf("\nTarea #%d\n", listaAuxiliar->datos.tareaID);
        printf("%s\n", listaAuxiliar->datos.descripcion);
        printf("Duracion: %dhs\n", listaAuxiliar->datos.duracion);
        listaAuxiliar = listaAuxiliar->siguiente;
    }
}


void agregarTareaCompletada(Nodo **listaPend, Nodo **listaComp, int id)
{
    Nodo **listaPendCopia = listaPend;                  // algo que no te diste cuenta ** = nombre apuntado por el segundo
    while (*listaPendCopia != NULL && (*listaPendCopia)->datos.tareaID != id)
    {
        listaPendCopia = &(*listaPendCopia)->siguiente;         // buscas el nodo del ID ingresado
    }
    if (*listaPendCopia)
    {
        Nodo *nodoAuxiliar = *listaPendCopia;                   // copias el nodo en un auxiliar
        *listaPendCopia = (*listaPendCopia)->siguiente;         // cambias el puntero de la lista StPendientes

        nodoAuxiliar->siguiente = *listaComp;                   // esta asignacion la haces igual que un nodo nuevo
        *listaComp = nodoAuxiliar; 

        // no podes liberar el nodoAuxiliar en este caso,
        // borras el item de la lista completados
    }
    else
    {
        printf("El ID ingresado no corresponde a una tarea en la lista de pendientes.");
    }
}

/* CONTROLAR ESTA FUNCION */
Nodo buscarTareaPorID(Nodo **listaPend, Nodo **listaComp, int idABuscar)
{
    Nodo *copia = *listaPend;
    while (copia != NULL && copia->datos.tareaID != idABuscar)
    {
        copia = copia->siguiente;
    }
    
    if (copia != NULL)              // si encuentra el nodo lo imprime
    {
        printf("/---- Tarea Pendiente ----/");
        printf("\nTarea #%d\n", copia->datos.tareaID);
        printf("%s\n", copia->datos.descripcion);
        printf("Duracion: %dhs\n", copia->datos.duracion);
    }
    else                            // si llega al final de la lista no encuentra la tarea
    {
        copia = *listaComp;   // aqui habia un error si ponias un * en copia...
        while (copia != NULL && copia->datos.tareaID != idABuscar)
        {
            copia = copia->siguiente;
        }

        if (copia != NULL)
        {
        printf("/---- Tarea Completada ----/");
        printf("\nTarea #%d\n", copia->datos.tareaID);
        printf("%s\n", copia->datos.descripcion);
        printf("Duracion: %dhs\n", copia->datos.duracion);
        }
        else
        {
            printf("No se encontró una tarea con ese ID.");
        }
    }
}

/*
Nodo buscarTareaPorPalabra()
{
}
*/