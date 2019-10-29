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
void insertarProductoDesdeArchivos(int id, char nombre[500], float precio);
void altaProductos();
void bajaProductos(char mensaje[50]);
void actualizarArchivo();

struct producto *raiz = NULL;
struct producto *fondo = NULL;

main()
{
	inicializarAlmacen();
	inicioSesion("");
	printf("almacen");
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
		printf("No hay ningun producto en el almacen. Creando nuevo archivo \n");
		archivoProductos = fopen("./productos.txt", "w+");
	}
}

void leerProductos(FILE *archivo)
{
	printf("\nEl contenido del archivo de prueba es \n\n");
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
					printf("id: %d\n", id);
					break;
				case 2: //nombre
					strcpy(nombre, token);
					printf("nombre: %s\n", nombre);
					break;
				case 3: //precio
					sscanf(token, "%f", &precio);
					printf("precio: %s\n", token);
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
	printf("Almacen: Iniciar Sesion\n");
	printf("1. Administrador\n");
	printf("2. Vendedor\n");
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
		inicioSesion("Selecciona una opcion del menu");
		break;
	}
}

void menuAdministrador()
{
	int opA = 0;
	system("cls");
	printf("***************************************************************\n");
	printf("***********************ALMACEN DE PRODUCTOS********************\n");
	printf("*************************              ************************\n");
	printf("*************************  BIENVENIDO  ************************\n");
	printf("************************* Administrador ***********************\n");
	printf("***************************************************************\n\n\n\n");

	printf("Selecciona la opcion que desees\n\n");
	printf("\n\t\t\t\t1.Agregar Producto\n");
	printf("\n\t\t\t\t2.Quitar producto\n");
	printf("\n\t\t\t\t3.Modificar Producto\n");
	printf("\n\t\t\t\t4.Volver a menu\n");
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
		break;
	}
	case 4:
	{
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
	printf("Iniciar Sesion: Administrador\n");
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

void iniciarSesionVendedor(char mensaje[50])
{
	int op;
	int opc;
	system("color 09");
	printf("***************************************************************\n");
	printf("*************************Tienda El Caly************************\n");
	printf("*************************              ************************\n");
	printf("*************************  BIENVENIDO  ************************\n");
	printf("******************** A LA VENTA DE PRODUCTOS *****************\n");
	printf("***************************************************************\n\n\n\n");
	printf("\t1.Producto 1                         Productos seleccionados:\n\n");
	printf("\t2.Producto 2\n\n");
	printf("\t3.Producto 3\n\n");
	printf("\t4.Producto n                         TOTAL: \n\n\n");
	printf("Selecciona el producto que desees:\t");
	scanf("%d", &op);
	printf("\n\nSelecciona la cantidad:\t");
	scanf("%d", &opc);
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
	struct producto *recorrido = raiz;
	printf("Lista completa.\n");
	while (recorrido != NULL)
	{
		printf("%i,%s,%.2f \n", recorrido->id, recorrido->nombre, recorrido->precio);
		recorrido = recorrido->siguiente;
	}
	printf("\n");
}

void altaProductos()
{
	char nombre[500] = "";
	float precio = 0;
	system("cls");
	printf("Escribe el nombre del producto\n");
	scanf("%s", &nombre);
	printf("Escribe el precio del producto\n");
	scanf("%f", &precio);
	insertarProducto(nombre, precio);
	imprimirproductosConsola();
}

void bajaProductos(char mensaje[50])
{
	system("cls");
	printf("%s\n", mensaje);
	imprimirproductosConsola();
	int idEscogido = 0;
	printf("Escribe el id del producto que deseas borrar\n");
	scanf("%d", &idEscogido);
	struct producto *recorrido = raiz;
	struct producto *anterior = raiz;
	while (recorrido != NULL)
	{
		if (recorrido->id == idEscogido)
		{
			char opc;
			printf("Estas seguro de que deseas borrar el siguiente producto?  s: si, n: no\n");
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

					if (recorrido != NULL)
					{
						struct producto *sig = recorrido->siguiente;
						if (recorrido == raiz)
						{
							raiz = sig;
						}
						else
						{
							anterior->siguiente = sig;
						}
					}
					else
					{
						anterior->siguiente = NULL;
						fondo = anterior;
					}
				}
				free(recorrido);
				actualizarArchivo();
				imprimirproductosConsola();
				bajaProductos("");
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

void actualizarArchivo()
{
	char buffer[1000] = "";
	FILE *archivoProductos;
	archivoProductos = fopen("./productos.txt", "w+");

	struct producto *recorrido = raiz;
	if(recorrido != NULL){
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
