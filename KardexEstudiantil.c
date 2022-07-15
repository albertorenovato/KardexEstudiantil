#include<stdio.h>
#include<conio.h>
#include <stdbool.h>
typedef struct fecha{
    int anio;
    int mes;
    int dia;
}fecha;
typedef struct UDA{
    char clave[10];
    char nombre[50];
    int creditos;
    float calf;
    struct UDA *atras;
	struct UDA *siguiente;
}UDA;
UDA* primerou=NULL;
UDA* ultimou=NULL;
typedef UDA *pUDA;
typedef struct periodo{
    int Id;
    pUDA UDA;
	float Promedio;
    struct periodo *atras;
	struct periodo *siguiente;
}periodo;
periodo* primerop=NULL;
periodo* ultimop=NULL;
typedef periodo *pperiodo;

typedef struct nodo{
	char AP[20];
    char AM[20];
    char nom[40];
    char clave[10];
    fecha FI;
    fecha FEE;
    pperiodo Periodo;
    int NUA;
    float calf;
	int Edad;
	float promedio;
    int MR;
	float promed;
	struct nodo* siguiente;
	struct nodo* atras;
}nodo;
nodo* primero=NULL;
nodo* ultimo=NULL;
void insertarnodo();
void buscarnodo();
void modificarnodo();
void eliminarnodo();
void desplegarLista();

int main(){
	int opcionmenu=0;
	do
	{
		system ("color 75" );
		printf( "\n|------------------------------------------------------------|");
		printf( "\n|                       °  KARDEX  °                         |");
		printf( "\n|---------------------------|--------------------------------|");
		printf( "\n| 1. Anadir Kardex          | 5. Desplegar y Guardar .dat    |");
	    printf( "\n| 2. Buscar Alumno          | 6. Salir                       |");
		printf( "\n| 3. Modificar NUA de Alumno|                                |");
		printf( "\n| 4. Eliminar Alumno        |                                |");
		printf( "\n|-------------------- ------|--------------------------------|");
		printf(  "\n\n Eliga una Opcion: ");
		scanf("%d",&opcionmenu);
		switch(opcionmenu){
			case 1:
			printf("\n\n Añadir Nuevo Kardex de Alumnos");
			insertarnodo();
			break;
			case 2:
			printf("\n\n Buscar Alumno");
			buscarnodo();
			break;
			case 3:
			printf("\n\n Modificar datos de Alumno");
			modificarnodo();
			break;
			case 4:
			printf("\n\n Eliminar Alumno");
			eliminarnodo();
			break;
			case 5:
			printf("\n\n Desplegar Alumnos de base de datos");
			desplegarLista();
			break;
			case 6:
			printf("\n\n Programa Finalizado");
			break;
			default:
			printf("\n\n Opcion no valida");	
		}
		}while(opcionmenu!=6);
	return 0;
}
void insertarnodo(){
	int n,i,op,nm,nmp;
	printf("\n\n Ingrese el numero de alumnos a calcular:");
	scanf("%d",&n);
	
	for(i=0;i<n;i++)
	{
	nodo* nuevo=(nodo*)malloc(sizeof(nodo));
	printf("Ingrese el nombre del alumno %d:", i+1);
	scanf("%s",&nuevo->nom);
	fflush( stdin );
	printf("Ingrese el apellido paterno:");
	scanf("%s",&nuevo->AP);
	printf("Ingrese el apellido materno:");
	scanf("%s",&nuevo->AM);
	printf("Ingrese el NUA del alumno:");
	scanf("%i",&nuevo->NUA);
	printf("Ingrese su fecha de ingreso (DD MM AAAA): ");
    scanf("%d %d %d", &(nuevo->FI.dia), &(nuevo->FI.mes), &(nuevo->FI.anio));
    nuevo->promedio=0;
    nuevo->MR=0;
    
    if(nuevo->FI.mes<6)
    {
        nuevo->FEE.anio=nuevo->FI.anio+4;
        nuevo->FEE.mes=nuevo->FI.mes+6;
    }
    else
    {
        nuevo->FEE.anio=nuevo->FI.anio+5;
        nuevo->FEE.mes=1;
    }
    nuevo->FEE.dia=nuevo->FI.dia;
    nuevo->Periodo = NULL;
    nm=0;
    
	do{
	if(nuevo->Periodo==NULL)
        {
            nuevo->Periodo=(pperiodo)malloc(sizeof(periodo));
            if(nuevo->Periodo==NULL)
            {
                //liberar(atras);
                nuevo->atras=NULL;
                nuevo->siguiente=NULL;
                //liberar(nv);
                return NULL;
            }
            nuevo->Periodo->atras=NULL;
            nuevo->Periodo->siguiente=NULL;
		}
        else
        {
            nuevo->Periodo->siguiente = (pperiodo)malloc(sizeof(periodo));
            if (nuevo->Periodo->siguiente == NULL)
            {
                //liberar(a);
                nuevo->atras = NULL;
                nuevo->siguiente = NULL;
                //liberar(nv);
                return NULL;
            }
            nuevo->Periodo->siguiente->atras=nuevo->Periodo;
            nuevo->Periodo=nuevo->Periodo->siguiente;
            nuevo->Periodo->siguiente=NULL;
        }
        nuevo->Periodo->Promedio=0;
        nuevo->Periodo->UDA=NULL;
        nmp=0;
        do{
            if(nuevo->Periodo->UDA==NULL)
            {
                nuevo->Periodo->UDA=(pUDA)malloc(sizeof(UDA));
                if(nuevo->Periodo->UDA==NULL)
                {
                    //liberar(a);
                    nuevo->atras = NULL;
                    nuevo->siguiente = NULL;
                    //liberar(nv);
                    return NULL;
                }
                nuevo->Periodo->UDA->atras=NULL;
                nuevo->Periodo->UDA->siguiente=NULL;
            }
            else
            {
                nuevo->Periodo->UDA->siguiente = (pUDA)malloc(sizeof(UDA));
                if (nuevo->Periodo->UDA->siguiente == NULL)
                {
                    //liberar(a);
                    nuevo->atras = NULL;
                    nuevo->siguiente = NULL;
                    //liberar(nv);
                    return NULL;
                }
                nuevo->Periodo->UDA->siguiente->atras = nuevo->Periodo->UDA;
                nuevo->Periodo->UDA = nuevo->Periodo->UDA->siguiente;
                nuevo->Periodo->UDA->siguiente = NULL;
            }
            printf("Ingrese la clave de la UDA: ");
            scanf("%s", &(nuevo->Periodo->UDA->clave));
            printf("Ingrese el nombre de la UDA: ");
            scanf("%s", &(nuevo->Periodo->UDA->nombre));
            fflush( stdin );
            nuevo->Periodo->UDA->creditos= (int)(10*(nuevo->Periodo->UDA->clave[5]-48)+(nuevo->Periodo->UDA->clave[6]-48)); // creditos de materia;
            printf("Ingrese la calificacion: ");
            scanf("%f", &(nuevo->Periodo->UDA->calf));
            
			if (nuevo->Periodo->UDA->calf<7)
                nuevo->MR++; //materias reprobadas
                
            else 
			{
			
			nm++;
            //nuevo->promed += nuevo->Periodo->UDA->calf;
			//nuevo->CT += nuevo->Periodo ->UDA->creditos; // ct creditos totales 
				
            }    
            
			nuevo->Periodo->Promedio += nuevo->Periodo->UDA->calf;
			nmp++;
			printf("Desea agregar otro UDA: ");
            scanf("%d", &op);

        }while(op);
        printf("\nLas materias reprobadas son: %d",nuevo->MR);//Numero de materias reprobadas
        printf("\nEl promedio del periodo es: %f",nuevo->Periodo->Promedio /= nmp ); // no. materias del periodo, promedio del periodo
        printf("\n La fecha estimada de egreso es: %d %d %d",nuevo->FEE.dia,nuevo->FEE.mes,nuevo->FEE.anio);
		printf("\nDesea agregar otro periodo: ");
        scanf("%d", &op);
        //printf("\nEl promedio general es: %f",nuevo ->promed/=nm);//promedio general
        //printf("\nLas materias reprobadas son: %d",nv->MR);
	}while(op); 
	//printf("\nEl promedio general es: %f",nuevo ->promed/=nm);//promedio general
	if(primero==NULL){
		primero=nuevo;
		primero->siguiente=NULL;
		primero->atras=NULL;
		ultimo=primero;
	}else{
		ultimo->siguiente=nuevo;
		nuevo->siguiente=NULL;
		nuevo->atras=ultimo;	
		ultimo=nuevo;
	}
	printf("\n Alumno agregado con exito\n");

        }while(op);

	
}
void buscarnodo(){
	
nodo* actual=(nodo*)malloc(sizeof(nodo));
actual=primero;
int nodobuscado=0, encontrado=0;
printf("\n\nIngrese el NUA buscado");
scanf("%d",&nodobuscado);

if(primero!=NULL){
	while(actual!=NULL&& encontrado!=1){
	if(actual->NUA==nodobuscado){
		printf("\n El alumno con el nua (%d) fue encontrado\n",nodobuscado);
		printf("\n%s",actual->nom);
	printf("\n%s",actual->AP);
	printf("\n%i",actual->NUA);
	printf("\n%s",actual->clave);
	printf("\n%s",actual->Periodo->UDA->nombre);
		encontrado=1;
	}
	
		actual=actual->siguiente;
	}
	if(encontrado==0){
		printf("\n Almuno no encontrado\n");
	}
}	else{
	printf("\n No existe ningun alumno registrado");
}
}
void modificarnodo(){

			nodo* actual=(nodo*)malloc(sizeof(nodo));
            actual=primero;
            bool encontrado=false;
            int nodobuscado=0;
            printf("\n\n Escriba el NUA del Alumno que desea modificar");
            scanf("%d",&nodobuscado);

            if(primero!=NULL){
	        while(actual!=NULL){
	        if(actual->NUA==nodobuscado){
		    printf("\n El alumno con el nombre  fue encontrado\n",nodobuscado);
		    printf("Ingrese el nuevo nua del alumno:");
		    scanf("%d",&actual->NUA);
		    printf("El nuevo nua se ha guardado");
		    encontrado=true;
	}
	
		actual=actual->siguiente;
	}
	if(encontrado==true){
		printf("\n Almuno no encontrado\n");
	}
}	else{
	printf("\n La lista esta vacia");
}
}
void eliminarnodo(){
nodo* actual=(nodo*)malloc(sizeof(nodo));
actual=primero;
nodo* anterior=(nodo*)malloc(sizeof(nodo));
anterior=NULL;
int nodobuscado=0, encontrado=0;
printf("\n\n Ingrese el Nua del alumno que desea eliminar:");
scanf("%d",&nodobuscado);

if(primero!=NULL){
	while(actual!=NULL && encontrado!=1){
	if(actual->NUA==nodobuscado){
		
		if(actual==primero){
			primero=primero->siguiente;
			primero->atras=NULL;
		}else if(actual==ultimo){
			anterior->siguiente=NULL;
			ultimo=anterior;
		}else{
			anterior->siguiente=actual->siguiente;
			actual->siguiente->atras=anterior;
		}
		printf("\n Alumno Eliminado con exito");
		encontrado=1;
	}
	anterior=actual;
	actual=actual->siguiente;
	}
	if(encontrado==0){
		printf("\n Almuno no encontrado\n");
	}else{
	free(anterior);	
	}
    }else{
	printf("\n No existe ningun alumno");
  }	
}
void desplegarLista(){

FILE *archivo = fopen ("datos.dat", "a+");
nodo* actual=(nodo*)malloc(sizeof(nodo));


actual=primero;

if(primero!=NULL){
	
	
	while(actual!=NULL){
	printf("\n%s",actual->nom);
	fprintf(archivo,"\n%s",actual->nom);
	
	printf("\n%s",actual->AP);
	fprintf(archivo,"\n%s",actual->AP);
	
	printf("\n%i",actual->NUA);
	fprintf(archivo,"\n%i",actual->NUA);
	
	printf("\n%s",actual->Periodo->UDA->clave);
	fprintf(archivo,"\n%s",actual->Periodo->UDA->clave);
	
	printf("\n%s",actual->Periodo->UDA->nombre);
	fprintf(archivo,"\n%s",actual->Periodo->UDA->nombre);
	
	printf("\n%d",actual->Periodo->UDA->calf);
	fprintf(archivo,"\n%d",actual->Periodo->UDA->calf);
	
		actual=actual->siguiente;
	
	}
	
	}	else{
	printf("\n\n No exite ningun alumno ");
}

fclose (archivo);
}
