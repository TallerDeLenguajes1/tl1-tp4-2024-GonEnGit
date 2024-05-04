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
Nodo *crearListaVacia();
Nodo *crearNuevoNodo(int nuevoID);
void *agregarNodoALista(Nodo **cabezaDeLista, Nodo *nuevoNodo);
void *mostrarUnaLista(Nodo **lista);




int main(int argv, char *argc[])
{
    /* Variables */
    int auxID = 999, opcion, completadoID, IDBuscado;
    char continuar = 'S', otraTareaNueva, completarOtraTarea = 'G', opcionBusqueda, palabraBuscada[20];

    // creas la lista de tareas pendientes, 'St' por Start
    Nodo *StPendientes;
    StPendientes = crearListaVacia();
    // creas la lista de tareas completadas
    Nodo *StCompletadas;
    StCompletadas = crearListaVacia();

    while (continuar == 'S')    // mientras continuar sea no, el programa sigue
    {
        opcion = presentarMenu();
        switch (opcion)
        {
            case 1:            // opcion para cargar tareas nuevas

                do
                {
                    // aumentas el indice, creas el nodo y lo agregas a Pendientes
                    auxID += 1;
                    Nodo *nuevaTarea = crearNuevoNodo(auxID);
                    agregarNodoALista(&StPendientes, nuevaTarea);

                    //  checkeo para seguir agregando tareas pendientes
                    otraTareaNueva = 'G';
                    while (otraTareaNueva != 'S' && otraTareaNueva != 'N')
                    {
                        printf("\nAgregar otra tarea pendiente? (S/N) ");
                        fflush(stdin);
                        scanf("%c", &otraTareaNueva);
                        otraTareaNueva = toupper(otraTareaNueva);

                        if (otraTareaNueva != 'S' && otraTareaNueva != 'N')
                        {
                            printf("\nIngrese S para continuar o N para terminar.\n");
                        }
                    }

                } while (otraTareaNueva == 'S');

                break;

            case 2:            // opcion para pasar una tarea a la lista de completadas

                break;

            case 3:             // opcion para mostrar las listas

                printf("\n/--- Tareas Pendientes ---/\n");
                if (StPendientes == NULL)
                {
                    printf("\nAun no agregaste tareas nuevas.\n");
                }
                else
                {
                    mostrarUnaLista(&StPendientes);
                }

                printf("\n/--- Tareas Pendientes ---/\n");
                if (StCompletadas == NULL)
                {
                    printf("\nAun no hay tareas completadas.\n");
                }
                else
                {
                    mostrarUnaLista(&StCompletadas);
                }

                break;

            case 4:             // opcion para buscar una tarea

                break;
        }

        // checkeo para volver al principio
        do
        {
            printf("\nContinuar con otra opcion? (S/N): ");
            fflush(stdin);
            scanf("%c", &continuar);
            continuar = toupper(continuar);
        } while (continuar != 'S' && continuar != 'N');
    }

    // liberar toda la memoria usada


    printf("\nHasta la proxima!\n");        // despedida, nada mas
    return 0;
}



/* Desarrollo de funciones */

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


Nodo *crearListaVacia()
{
    return NULL;
}


Nodo *crearNuevoNodo(int nuevoID)
{
    int duracion;
    char *buffer = (char *)malloc(sizeof(char) * 100);      // memoria para una descripcion de hasta 100 caracteres
    Nodo *nodoAuxiliar = (Nodo *)malloc(sizeof(Nodo));

    printf("\nIngrese una descripcion para la tarea:\n");
    fflush(stdin);
    gets(buffer);

    printf("\nIngrese una duracion para la tarea: ");
    fflush(stdin);
    scanf("%d", &duracion);

    nodoAuxiliar->datos.tareaID = nuevoID;              // guardas el id

    nodoAuxiliar->datos.descripcion = (char *)malloc(sizeof(char) * strlen(buffer) + 1);
    strcpy(nodoAuxiliar->datos.descripcion, buffer);    // copias le descripcion

    nodoAuxiliar->datos.duracion = duracion;            // guardas la duracion

    nodoAuxiliar->siguiente = NULL;                     // apuntas el nodo a NULL

    free(buffer);                                       // limpias la memoria que pediste

    return nodoAuxiliar;                                // devolves el nodo armado
}


void *agregarNodoALista(Nodo **cabezaDeLista, Nodo *nuevoNodo)
{
    nuevoNodo->siguiente = *cabezaDeLista;
    *cabezaDeLista = nuevoNodo;
}


void *mostrarUnaLista(Nodo **lista)
{
    Nodo *listaAux = *lista;
    while (listaAux != NULL)
    {
        printf("\nID = %d\n", listaAux->datos.tareaID);
        printf("Descripcion: %s.\n", listaAux->datos.descripcion);
        printf("Duracion: %d Dias.\n", listaAux->datos.duracion);

        listaAux = listaAux->siguiente;
    }
}