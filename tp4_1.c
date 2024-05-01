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
void buscarTareaPorID(Nodo **listaPend, Nodo **listaComp, int idABuscar);
void buscarTareaPorPalabra(Nodo **listaPend, Nodo **listaComp, char palabra[]);  // acordate que en C, string es un arreglo de char
void liberarMemorias(Nodo **lista);



int main(int argv, char *argc[])
{
    /* Variables */
    int auxID = 999, opcion, completadoID, IDBuscado;
    char continuar = 'S', otraTareaNueva = 'N', completarOtraTarea = 'S', opcionBusqueda, palabraBuscada[20];

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
                    printf("\nIngrese el ID de la tarea completada: ");
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

                printf("\n/---- Tareas Pendientes ----/");
                if (StPendientes == NULL)
                {
                    printf("\nAun no se registraron tareas nuevas.\n");
                }
                else
                {
                    mostrarUnaSolaLista(StPendientes);    
                }

                printf("\n/---- Tareas Completadas ----/");
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
                    printf("\nQuiere buscar por ID o por palabra? (I/P) ");
                    fflush(stdin);
                    scanf("%c", &opcionBusqueda);
                } while (opcionBusqueda != 'I' && opcionBusqueda != 'P');       // acá tenes una forma mas obvia de acegurar que ingresen letras

                if (opcionBusqueda == 'I')
                {
                    printf("\nIngrese el ID de que busca: ");
                    fflush(stdin);
                    while ( (scanf("%d", &IDBuscado) == 0) || IDBuscado <= 999)     // esta es otra forma: si no ingresas lo que pide scanf devuelve 0
                    {
                        fflush(stdin);
                        printf("Utilice valores mayores a 999.   ");                // o podras usar algo como isalnum de ctype.h
                    }
                    buscarTareaPorID(&StPendientes, &StCompletadas, IDBuscado);
                }
                else
                {
                    printf("\nIngrese una palabra para iniciar la busqueda: ");
                    fflush(stdin);
                    gets(palabraBuscada);
                    buscarTareaPorPalabra(&StPendientes, &StCompletadas, palabraBuscada);
                }

                break;
        }

        do
        {
            printf("\nDesea continuar con otra opcion? (S/N): ");
            fflush(stdin);
            scanf("%c", &continuar);
            continuar = toupper(continuar);
        } while (continuar != 'S' && continuar != 'N');
    }

    /* liberas la memoria de las listas */
    liberarMemorias(&StPendientes);
    liberarMemorias(&StCompletadas);

    /* liberas las cabeceras */
    free(StPendientes);
    free(StCompletadas);

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
    // quiza tendrias que pensar esto con malloc
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
        printf("\nEl ID ingresado no corresponde a una tarea en la lista de pendientes.\n");
    }
}

/* CONTROLAR ESTA FUNCION */
void buscarTareaPorID(Nodo **listaPend, Nodo **listaComp, int idABuscar)
{
    Nodo *copia = *listaPend;
    while (copia != NULL && copia->datos.tareaID != idABuscar)
    {
        copia = copia->siguiente;
    }

    if (copia != NULL)              // si encuentra el nodo lo imprime
    {
        printf("\n/---- Tarea Pendiente ----/");
        printf("\nTarea #%d\n", copia->datos.tareaID);
        printf("%s\n", copia->datos.descripcion);
        printf("Duracion: %dhs\n", copia->datos.duracion);
    }

    else                            // si llega al final de la lista no encuentra la tarea
    {
        copia = *listaComp;         // aqui habia un error si ponias un * en copia, ya está declarado como puntero
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


void buscarTareaPorPalabra(Nodo **listaPend, Nodo **listaComp, char palabra[])
{
    int contador = 0;
    char *bufferTemp;
    Nodo *copia = *listaPend;

    printf("\n/---- Tareas Pendientes ----/\n");
    while (copia != NULL)
    {
        // strstr esta funcion devuelve un puntero, si encuentra la palabra
        // bufferTemp no va a estar vacio, si no la encuentra queda en NULL
        bufferTemp = strstr(copia->datos.descripcion, palabra);
        if (bufferTemp != NULL)
        {
            printf("\nTarea #%d\n", copia->datos.tareaID);
            printf("%s\n", copia->datos.descripcion);
            printf("Duracion: %dhs\n", copia->datos.duracion);
            contador += 1;
        }
        copia = copia->siguiente;
    }
    if (contador == 0)
    {
        printf("\nNo hay coincidencias entre las tareas pendientes.\n");
    }

    printf("\n/---- Tareas Completadas ----/\n");
    contador = 0;
    copia = *listaComp;
    while (copia != NULL)
    {
        bufferTemp = strstr(copia->datos.descripcion, palabra);
        if (bufferTemp != NULL)
        {
            printf("\nID: #%d\n", copia->datos.tareaID);
            printf("Descripcion: %s\n", copia->datos.descripcion);
            printf("Durachion %dhs\n", copia->datos.duracion);
            contador += 1;
        }
        copia = copia->siguiente;
    }
    if (contador == 0)
    {
        printf("\nNo hay coincidencias en la lista de tareas completadas.\n");
    }
}


void liberarMemorias(Nodo **lista)
{
    // esta funcion la haces igual que si borrars un nodo
    // para pasarlo a otra lista solo que bue... no lo pasas a ningun lado
    Nodo *temp;
    while (*lista != NULL)
    {
        temp = *lista;                      // guardas el nodo
        *lista = (*lista)->siguiente;       // asignas el sigueinte nodo a la cabecera
        free(temp->datos.descripcion);      // asignaste memoria para la descripcion, se libera tambien
        free(temp);                         // al final liberas el nodo
    }
}