#include <graphics.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <dos.h>

struct producto
{
	int id;
	char nombre[500];
	float precio;
	struct producto *siguiente;
};

void inicioSesion(char mensaje[50]);
void iniciarSesionAdministrador(char mensaje[50]);
void iniciarSesionVendedor(char mensaje[50]);
void menuAdministrador();
void inicializarAlmacen();
void obtenerProductosAlmacen();
void leerProductos(FILE *archivo);
void insertarProducto(char nombre[500], float precio);
void imprimirproductosConsola();
void imprimirproductosConsolaV();
void insertarProductoDesdeArchivos(int id, char nombre[500], float precio);
void altaProductos();
void bajaProductos(char mensaje[50]);
void actualizarArchivo();
void editarProducto(char mensaje[50]);
void calcularTotalCompra();
void agregarCarrito(char nombre[500], float precio);

struct producto *raiz = NULL;
struct producto *fondo = NULL;

struct producto *compraRaiz = NULL;
struct producto *compraFondo = NULL;

main()
{
	inicializarAlmacen();
	inicioSesion("");
	return 0;
}

void inicializarAlmacen()
{
	FILE *archivoProductos;
	archivoProductos = fopen("./productos.txt", "r+");
	if (archivoProductos != NULL)
	{
		leerProductos(archivoProductos);
	}
	else
	{
		printf("\nNo hay ningun producto en el almacen. Creando nuevo archivo \n");
		archivoProductos = fopen("./productos.txt", "w+");
	}
}

void leerProductos(FILE *archivo)
{
	//printf("\nEl contenido del archivo de prueba es \n\n");
	char caracteres[1000] = "";
	while (feof(archivo) == 0)
	{ //salto de linea
		fgets(caracteres, 100, archivo);
		char delimitador[] = ",";
		char *token = strtok(caracteres, delimitador);
		if (token != NULL)
		{
			int i = 1;
			int id = 0;
			char nombre[500] = "";
			float precio = 0;
			while (token != NULL)
			{ //cada coma que hay entre la info de los productos
				switch (i)
				{
				case 1: //id
					sscanf(token, "%d", &id);
					//printf("id: %d\n", id);
					break;
				case 2: //nombre
					strcpy(nombre, token);
					//printf("nombre: %s\n", nombre);
					break;
				case 3: //precio
					sscanf(token, "%f", &precio);
					//printf("precio: %s\n", token);
					break;
				default:
					break;
				}
				token = strtok(NULL, delimitador);
				i++;
			}
			insertarProductoDesdeArchivos(id, nombre, precio);
		}
	}
	fclose(archivo);
}

void obtenerProductosAlmacen()
{
}
/**
 * Menu de inicio de sesion, se puede elegir entre administrador o vendedor
**/
void inicioSesion(char mensaje[50])
{
	printf("%s\n", mensaje);
	int opc = 0;
	printf("Almacen: Iniciar Sesion\n\n\n");
	printf("1. Administrador\n");
	printf("2. Vendedor\n\n");
	printf("Elige una opcion\n");
	printf("\n");
	scanf("%i", &opc);
	system("cls");
	switch (opc)
	{
	case 1:
		iniciarSesionAdministrador("");
		break;
	case 2:
		iniciarSesionVendedor("");
		break;
	default:
		inicioSesion("Selecciona una opcion del menu\n\n");
		break;
	}
}

void menuAdministrador()
{
	int opA = 0;
	system("cls");
	system("color 04");
	printf("***************************************************************\n");
	printf("***********************ALMACEN DE PRODUCTOS********************\n");
	printf("*************************              ************************\n");
	printf("*************************  BIENVENIDO  ************************\n");
	printf("************************* Administrador ***********************\n");
	printf("***************************************************************\n\n\n\n");

	printf("Selecciona la opcion que desees\n\n");
	printf("\n\t\t\t\t1.Agregar Producto\n");
	printf("\n\t\t\t\t2.Borrar Producto\n");
	printf("\n\t\t\t\t3.Editar Producto\n");
	printf("\n\t\t\t\t4.Cerrar Sesion\n");
	printf("\n\t\t\t\t5.Salir\n");
	printf("\n\nOpcion seleccionada:\t\t");
	scanf("%d", &opA);

	switch (opA)
	{
	case 1:
	{
		altaProductos();
		break;
	}
	case 2:
	{
		bajaProductos("");
		break;
	}
	case 3:
	{
		editarProducto("");
		break;
	}
	case 4:
	{
		system("cls");
		inicioSesion("Sesion cerrada");
		break;
	}
	case 5:
	{
		exit(0);
	}
	default:
	{
		printf("\n\nOpcion equiovacada, intentalo de nuevo\n");
	}
	}
}

void iniciarSesionAdministrador(char mensaje[50])
{
	char contrasena[50] = "";
	printf("%s\n", mensaje);
	printf("Iniciar Sesion: Administrador\n\n");
	printf("Escribe la contrasena\n");
	scanf("%s", &contrasena);

	if (strcmp(contrasena, "ok") == 0)
	{
		menuAdministrador();
	}
	else
	{
		char opc;
		printf("contrasena incorrecta\n");
		printf("Desea regresar al menu principal? s: si, n: no\n");
		scanf("%s", &opc);
		system("cls");
		if (opc == 's')
		{
			inicioSesion("");
		}
		else
		{
			iniciarSesionAdministrador("contrasena incorrecta");
			return;
		}
	}
}

void insertarProductoDesdeArchivos(int id, char nombre[500], float precio)
{
	struct producto *nuevo;
	nuevo = (struct producto *)malloc(sizeof(struct producto));
	strcpy(nuevo->nombre, nombre);
	nuevo->precio = precio;
	nuevo->id = id;
	nuevo->siguiente = NULL;
	if (raiz == NULL)
	{
		raiz = nuevo;
		fondo = nuevo;
		nuevo->siguiente = NULL;
	}
	else
	{
		fondo->siguiente = nuevo;
		fondo = nuevo;
	}
}

void insertarProducto(char nombre[500], float precio)
{
	char buffer[1000] = "";
	struct producto *nuevo;
	int id = 0;
	nuevo = (struct producto *)malloc(sizeof(struct producto));
	strcpy(nuevo->nombre, nombre);
	nuevo->precio = precio;
	nuevo->siguiente = NULL;
	if (raiz == NULL)
	{
		raiz = nuevo;
		fondo = nuevo;
		nuevo->siguiente = NULL;
		nuevo->id = 0;
		sprintf(buffer, "%d, %s, %f", nuevo->id, nuevo->nombre, nuevo->precio);
	}
	else
	{
		id = fondo->id + 1;
		nuevo->id = id;
		fondo->siguiente = nuevo;
		fondo = nuevo;
		sprintf(buffer, "\n%d, %s, %f", nuevo->id, nuevo->nombre, nuevo->precio);
	}

	FILE *archivoProductos;
	archivoProductos = fopen("./productos.txt", "a+");
	if (archivoProductos != NULL)
	{
		fputs(buffer, archivoProductos);
	}
	fclose(archivoProductos);
}

void imprimirproductosConsola()
{
	system("cls");
	struct producto *recorrido = raiz;
	printf("\nLista completa.\n\n");
	while (recorrido != NULL)
	{
		printf("%i,%s,%.2f \n\n", recorrido->id, recorrido->nombre, recorrido->precio);
		recorrido = recorrido->siguiente;
	}
	printf("\n");
}

void imprimirproductosConsolaV()
{
   struct producto *recorrido = raiz;
   while (recorrido != NULL)
	{
		printf("%i,%s,%.2f \n\n", recorrido->id, recorrido->nombre, recorrido->precio);
		recorrido = recorrido->siguiente;
	}
	printf("\n");
}

void altaProductos()
{
	char nombre[500] = "";
	float precio = 0;
	system("cls");
	system("color 04");
	printf("Escribe el nombre del producto\n\n");
	scanf("%s", &nombre);
	printf("\nEscribe el precio del producto\n\n");
	scanf("%f", &precio);
	insertarProducto(nombre, precio);
	imprimirproductosConsola();
	system("PAUSE");
	menuAdministrador();

}

void bajaProductos(char mensaje[50])
{
	system("cls");
	system("color 04");
	printf("%s\n", mensaje);
	imprimirproductosConsola();
	int idEscogido = 0;
	printf("\nEscribe el id del producto que deseas borrar\n\n");
	scanf("%d", &idEscogido);
	struct producto *recorrido = raiz;
	struct producto *anterior = raiz;
	while (recorrido != NULL)
	{
		if (recorrido->id == idEscogido)
		{
			char opc;
			printf("\n\nEstas seguro de que deseas borrar el siguiente producto?  s: si, n: no\n");
			printf("%i,%s,%.2f \n", recorrido->id, recorrido->nombre, recorrido->precio);
			scanf("%s", &opc);
			if (opc == 's')
			{
				if (raiz == fondo)
				{
					raiz = NULL;
					fondo = NULL;
				}
				else
				{
						struct producto *sig = recorrido->siguiente;
						if (recorrido == raiz)
						{
							raiz = sig;
						}
						else
						{
							if (sig != NULL){
								anterior->siguiente = sig;
							}
							else{
								anterior->siguiente = NULL;
								fondo = anterior;
							}
							

						}
					
				}
				free(recorrido);
				actualizarArchivo();
				imprimirproductosConsola();
				system("PAUSE");
				menuAdministrador();
				return;
			}
			else
			{
				menuAdministrador();
			}
			return;
		}
		anterior = recorrido;
		recorrido = recorrido->siguiente;
	}
	bajaProductos("Digite un id de la lista");
}

void editarProducto(char mensaje[50])
{
	system("cls");
	system("color 04");
	printf("%s\n", mensaje);
	imprimirproductosConsola();
	int idEscogido = 0;
	printf("Escribe el id del producto al que deseas hacer modificaciones\n");
	scanf("%d", &idEscogido);
	struct producto *recorrido = raiz;
	while (recorrido != NULL)
	{
		if (recorrido->id == idEscogido)
		{
			int opcionesEdicion = 0;
			printf("%i,%s,%.2f \n", recorrido->id, recorrido->nombre, recorrido->precio);
			printf("\nElige una opcion:\n\n");
			printf("1. Editar nombre\n");
			printf("2. Editar precio\n");
			printf("3. Cancelar\n");
			scanf("%d", &opcionesEdicion);

			switch (opcionesEdicion)
			{
				case 1:
				{
					char nombre[500] = "";
					printf("Escribe el nuevo nombre del producto\n");
					scanf("%s", &nombre);
					strcpy(recorrido->nombre, nombre);
					imprimirproductosConsola();
					system("PAUSE");
					actualizarArchivo();
					menuAdministrador();	
					return;
					break;
				}
				case 2:
				{
					float precio = 0;
					printf("Escribe el nuevo precio del producto\n");
					scanf("%f", &precio);
					recorrido->precio = precio;
					imprimirproductosConsola();
					system("PAUSE");
					actualizarArchivo();
					menuAdministrador();	
					return;
					break;
				}
				case 3:
				{
					menuAdministrador();
					return;
					break;
				}
				default:
				{
					editarProducto("Selecciona una opcion del menu");
					return;
					break;
				}
			}
		}
		recorrido = recorrido->siguiente;
	}
	editarProducto("Digite un id de la lista");
}

void actualizarArchivo()
{
	char buffer[1000] = "";
	FILE *archivoProductos;
	archivoProductos = fopen("./productos.txt", "w+");

	struct producto *recorrido = raiz;
	if (recorrido != NULL)
	{
		sprintf(buffer, "%d, %s, %f", recorrido->id, recorrido->nombre, recorrido->precio);
		fputs(buffer, archivoProductos);
		recorrido = recorrido->siguiente;
	}
	while (recorrido != NULL)
	{
		sprintf(buffer, "\n%d, %s, %f", recorrido->id, recorrido->nombre, recorrido->precio);
		fputs(buffer, archivoProductos);
		recorrido = recorrido->siguiente;
	}
	fclose(archivoProductos);
}

void iniciarSesionVendedor(char mensaje[50])
{
    float p=0;
    int e=0;
    
	system("color 06");
	printf("***************************************************************\n");
	printf("*************************Tienda El Caly************************\n");
	printf("*************************              ************************\n");
	printf("*************************  BIENVENIDO  ************************\n");
	printf("******************** A LA VENTA DE PRODUCTOS *****************\n");
	printf("***************************************************************\n\n\n\n");
	printf("Productos disponibles:\n\n");
    imprimirproductosConsolaV();
    int idEscogido = 0;
	printf("\n\nEscribe el id del producto que deseas\n");
	scanf("%d", &idEscogido);
	struct producto *recorrido = raiz;
	while(recorrido != NULL)
	{
	   if(recorrido->id == idEscogido)
		{
			system("cls");
			printf("\n\n%i,%s,%.2f \n", recorrido->id, recorrido->nombre, recorrido->precio);
			printf("\nDigite la cantidad que va a llevar de ese producto\n");
			scanf("%f",&p);
			printf("\n\n%i,%s,%.2f,%.2f \n", recorrido->id, recorrido->nombre, recorrido->precio, p*recorrido->precio);
			agregarCarrito(recorrido->nombre, p*recorrido->precio);
			printf("Desea continuar con la compra: s:si, n:no\n");
			char opc;
			scanf("%s", &opc);
			if (opc == 's'){
				iniciarSesionVendedor("");
				return;
			}
			else{
				calcularTotalCompra();
				return;	
			}
			system("cls");
			inicioSesion("");	
		    return;
	    } 
	      recorrido = recorrido->siguiente; 
    }
    iniciarSesionVendedor("Elije una opcion");
}

void agregarCarrito(char nombre[500], float precio)
{
	char buffer[1000] = "";
	struct producto *nuevo;
	int id = 0;
	nuevo = (struct producto *)malloc(sizeof(struct producto));
	strcpy(nuevo->nombre, nombre);
	nuevo->precio = precio;
	nuevo->siguiente = NULL;
	if (compraRaiz == NULL)
	{
		compraRaiz = nuevo;
		compraFondo = nuevo;
		nuevo->siguiente = NULL;
		nuevo->id = 0;
	}
	else
	{
		id = compraFondo->id + 1;
		nuevo->id = id;
		compraFondo->siguiente = nuevo;
		compraFondo = nuevo;
	}
}

void calcularTotalCompra(){
	struct producto *recorrido = compraRaiz;
	float total = 0;
	int i = 1;
	   while (recorrido != NULL)
		{
			printf("%i,%s,%.2f \n\n", i, recorrido->nombre, recorrido->precio);
			total += recorrido->precio;
			i++;
			recorrido = recorrido->siguiente;
		}
		printf("%.2f", total);
}
