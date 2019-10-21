#include <graphics.h>
#include <stdio.h>
#include <dos.h>

struct producto{
    int id;
	char nombre[500];
	float precio;
    struct producto *siguiente;
};


void inicioSesion(char mensaje[50]);
void iniciarSesionAdministrador(char mensaje[50]);
void iniciarSesionVendedor(char mensaje[50]);

main()
{
	inicioSesion("");
	printf("almacen");
	return 0;
}

/**
 * Menu de inicio de sesion, se puede elegir entre administrador o vendedor
**/
void inicioSesion(char mensaje[50]){
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

void iniciarSesionAdministrador(char mensaje[50]){
	char contrasena[50] = "";
	printf("%s\n", mensaje);
	printf("Iniciar Sesion: Administrador\n");
	printf("Escribe la contrasena\n");
	printf("Para regresar al menu principal pulse la tecla ESC\n");
	scanf("%s", &contrasena);
	if(strcmp(contrasena, "ok") == 0){
		printf("ok\n");
	}
	else{
		iniciarSesionAdministrador("contrasena incorrecta");
		return;
	}
}

void iniciarSesionVendedor(char mensaje[50]){
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
	scanf("%d",&op);
	printf("\n\nSelecciona la cantidad:\t");
	scanf("%d",&opc);
}




