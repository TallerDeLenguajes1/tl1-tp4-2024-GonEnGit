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
void agregarNodoALista(Nodo **cabezaDeLista, Nodo *nuevoNodo);
Nodo *quitarNodo(Nodo **lista, int id);
void mostrarUnaLista(Nodo *lista);
void filtrarTareaPorId(Nodo **listaPend, Nodo **listaComp, int id);
void filtrarTareaPorPalabra(Nodo **listaPend, Nodo **listaComp, char palabra[]);
void liberarNodos(Nodo **lista);



int main(int argv, char *argc[])
{
    /* Variables */
    int auxID = 999, contadorDeNodosPend = 0, opcion, idDeCompletada, idBuscado;
    char continuar = 'S', otraTareaNueva, completarOtraTarea, opcionBusqueda, palabraBuscada[20];
    Nodo *nodoACambiar;

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
                    contadorDeNodosPend += 1;
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

                printf("\n/--- Tareas Pendientes ---/\n");
                mostrarUnaLista(StPendientes);
                do
                {
                    completarOtraTarea = 'G';                   // con esta asignacion evitas que se trabe con completarOtraTarea = 'S'
                    do
                    {
                        printf("\nIngrese el id de la tarea que pasar%c a la lista de completadas: ", 160);
                        fflush(stdin);
                        scanf("%d", &idDeCompletada);
                        if (idDeCompletada <= 999)
                        {
                            printf("\nDebe ingresar un id que sea mayor a 999\n");
                        }
                    } while (idDeCompletada < 1000);
                    nodoACambiar = quitarNodo(&StPendientes, idDeCompletada);            // no lo declares aquí adentro o el VScode se pone pesado
                    if (nodoACambiar != NULL)
                    {
                        agregarNodoALista(&StCompletadas, nodoACambiar);
                        if (contadorDeNodosPend == 1)
                        {
                            StPendientes = NULL;
                        }
                        contadorDeNodosPend -= 1;
                    }
                    while (completarOtraTarea != 'S' && completarOtraTarea != 'N')
                    {
                        printf("\nPasar otra tarea? (S/N) ");
                        fflush(stdin);
                        scanf("%c", &completarOtraTarea);
                        completarOtraTarea = toupper(completarOtraTarea);
                        if (completarOtraTarea != 'S' && completarOtraTarea != 'N')
                        {
                            printf("\nIngrese S para pasar otra tarea o N para volver al menu.\n");
                        }
                    }
                } while (completarOtraTarea != 'N');

                break;

            case 3:             // opcion para mostrar las listas

                printf("\n/--- Tareas Pendientes ---/\n");
                if (StPendientes == NULL)
                {
                    printf("\nAun no agregaste tareas nuevas.\n");
                }
                else
                {
                    mostrarUnaLista(StPendientes);
                }

                printf("\n/--- Tareas Completadas ---/\n");
                if (StCompletadas == NULL)
                {
                    printf("\nAun no hay tareas completadas.\n");
                }
                else
                {
                    mostrarUnaLista(StCompletadas);
                }

                break;

            case 4:

                do
                {
                    printf("\nQuiere buscar una tarea por id o por palabra clave? (I/P) ");
                    fflush(stdin);
                    scanf("%c", &opcionBusqueda);
                    opcionBusqueda = toupper(opcionBusqueda);
                    if (opcionBusqueda != 'I' && opcionBusqueda != 'P')
                    {
                        printf("\nIngrese I para buscar por id o P para buscar usando una palabra clave.");
                    }
                } while (opcionBusqueda != 'I' && opcionBusqueda != 'P');

                if (opcionBusqueda == 'I')
                {
                    do
                    {
                        printf("\nIngrese el id de la tarea que quiere buscar: ");
                        fflush(stdin);
                        scanf("%d", &idBuscado);
                        if (idBuscado <= 999)
                        {
                            printf("\nDebe ingresar un id que sea mayor a 999\n");
                        }
                    } while (idBuscado < 1000);
                    filtrarTareaPorId(&StPendientes, &StCompletadas, idBuscado);
                }
                else                        // completar estas 2 y liberar memoria
                {
                    printf("\nIngrese una palabra clave: ");
                    fflush(stdin);
                    gets(palabraBuscada);
                    filtrarTareaPorPalabra(&StPendientes, &StCompletadas, palabraBuscada);
                }

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
    liberarNodos(&StPendientes);
    liberarNodos(&StCompletadas);

    free(StPendientes);
    free(StCompletadas);

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


void agregarNodoALista(Nodo **cabezaDeLista, Nodo *nuevoNodo)
{
    nuevoNodo->siguiente = *cabezaDeLista;
    *cabezaDeLista = nuevoNodo;
}


Nodo *quitarNodo(Nodo **lista, int id)
{
    Nodo *listaAux = *lista;
    Nodo *nodoAnterior = *lista;

    while (listaAux != NULL && listaAux->datos.tareaID != id)
    {
        nodoAnterior = listaAux;
        listaAux = listaAux->siguiente;
    }
    if (listaAux == NULL)
    {
        printf("No se encontr%c ninguna tarea con ese id.", 162);
    }
    else
    {
        nodoAnterior->siguiente = listaAux->siguiente;
        listaAux->siguiente = NULL;
    }
    return listaAux;
}


void mostrarUnaLista(Nodo *lista)
{
    Nodo *listaAux = lista;
    while (listaAux != NULL)
    {
        printf("\nID: #%d\n", listaAux->datos.tareaID);
        printf("Descripcion: %s.\n", listaAux->datos.descripcion);
        printf("Duracion: %d Dias.\n", listaAux->datos.duracion);

        listaAux = listaAux->siguiente;
    }
}

void filtrarTareaPorId(Nodo **listaPend, Nodo **listaComp, int id)
{
    Nodo *listaCopia = *listaPend;
    while (listaCopia != NULL && listaCopia->datos.tareaID != id)
    {
        listaCopia = listaCopia->siguiente;
    }
    if (listaCopia != NULL)
    {
        printf("\nSe encontr%c la siguiente tarea entre las tareas pendientes: \n", 162);
        printf("\nID: #%d", listaCopia->datos.tareaID);
        printf("\nDescripcion: %s", listaCopia->datos.descripcion);
        printf("\nDuracion: %d.\n", listaCopia->datos.duracion);
    }
    else
    {
        listaCopia = *listaComp;
        while (listaCopia != NULL && listaCopia->datos.tareaID != id)
        {
            listaCopia = listaCopia->siguiente;
        }
        if (listaCopia != NULL)
        {
            printf("\nSe encontr%c la siguiente tarea entre las tareas completadas: \n", 162);
            printf("\nID: #%d", listaCopia->datos.tareaID);
            printf("\nDescripcion: %s", listaCopia->datos.descripcion);
            printf("\nDuracion: %d.\n", listaCopia->datos.duracion);
        }
        else
        {
            printf("\nNo se en contr%c ninguna tarea con el id #%d.\n", 162, id);
        }
    }
}


void filtrarTareaPorPalabra(Nodo **listaPend, Nodo **listaComp, char palabra[])
{
    int contador = 0;
    Nodo *listaCopia = *listaPend;

    printf("\n/- -- - Tareas Pendientes: - -- -/\n");
    while (listaCopia != NULL)
    {
        if (strstr(listaCopia->datos.descripcion, palabra) != NULL)
        {
            printf("\nID: #%d", listaCopia->datos.tareaID);
            printf("\nDescripcion: %s.", listaCopia->datos.descripcion);
            printf("\nDuracion: %d Dias.\n", listaCopia->datos.duracion);
            contador += 1;
        }
        listaCopia = listaCopia->siguiente;
    }
    if (contador == 0)
    {
        printf("\nNo se encontraron tareas pendientes cuya descripcion tenga esa palabra.\n");
    }

    contador = 0;
    listaCopia = *listaComp;
    printf("\n/- -- - Tareas Completadas: - -- -/\n");
    while (listaCopia != NULL)
    {
        if (strstr(listaCopia->datos.descripcion, palabra) != NULL)
        {
            printf("\nID: #%d", listaCopia->datos.tareaID);
            printf("\nDescripcion: %s.", listaCopia->datos.descripcion);
            printf("\nDuracion: %d Dias.\n", listaCopia->datos.duracion);
            contador += 1;
        }
        listaCopia = listaCopia->siguiente;
    }
    if (contador == 0)
    {
        printf("\nNo se encontraron tareas completadas cuya descripcion tenga esa palabra.\n");
    }
}


void liberarNodos(Nodo **lista)
{
    Nodo *temp;
    while (*lista != NULL)
    {
        temp = *lista;
        *lista = temp->siguiente;
        free(temp->datos.descripcion);
        free(temp);
    }
}