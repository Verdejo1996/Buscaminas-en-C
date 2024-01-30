#include <stdio.h>
#include <stdlib.h>
#define BOMBAS 10	//numero de bombas totales
#define TAMANIO 10	//tamanio elevado al cuadrado es igual al numero de casillas totales(el "+1" es la fila y columna reservada para el indice)

void mostrartablero(char tablero[TAMANIO][TAMANIO]);
void cargarbomba(char (*tablero)[TAMANIO][TAMANIO]);
void elegircasilla(int *y, int *x);
int checkearbomba(int y, int x, char tablero[TAMANIO][TAMANIO]);
void checkalrededor(int y, int x,char (*tablero)[TAMANIO][TAMANIO]);
int checkwin(char tablero[TAMANIO][TAMANIO]);
void actualizartabla(char tablero[TAMANIO][TAMANIO], char (*tabla)[TAMANIO][TAMANIO]);
void limpiartabla(char (*tabla)[TAMANIO][TAMANIO], char (*tablero)[TAMANIO][TAMANIO]);

/* Con respecto a lo mostrado en el tablero:-El numero X/9 representa las Bombas
.											-El numero 0 representa las casillas vacias sin bombas al rededor
.											-Los numeros del 1 al 8 Representan la cantidad de bombas que hax en las proyimidades
.											-El numero . representa las casillas que todavia no fueron seleccionadas 
*/	
int main(int argc, char *argv[]) {

	char tablero[TAMANIO][TAMANIO], tabla[TAMANIO][TAMANIO]; 		//generacion del tablero de tamaño determianado por la constante
	int yp, xp, contwin = 0, bomba=0;		
	int *pyp = &yp, *pxp = &xp;
	
	limpiartabla(&tabla, &tablero);
	cargarbomba(&tablero);
	
	while(contwin != (TAMANIO*TAMANIO)){ 							//LOOP principal del juego hasta ganar o perder
	
		mostrartablero(tabla);
		//mostrartablero(tablero);									//tablero con los valores reales
		elegircasilla(pyp, pxp);
		bomba = checkearbomba(yp, xp, tablero);
		
		if(bomba == 1){ 											//checkea la condicion de derrota x sale con "return" si se cumple
			printf("se selecciono una bomba\n");
			tabla[yp][xp] = 'X';
			mostrartablero(tabla);	
			return 0;	
		}
		
		if(bomba == 0){
			checkalrededor(yp, xp, &tablero);
		}
		
		//contwin = checkwin(tablero);
		
		actualizartabla(tablero, &tabla);
		
		printf("%d %d %d %d \n", yp, xp, bomba, contwin);			//testeo de que los valores sean correctos
	}
	
	printf("GANASTE EL JUEGO!!!\n");
	mostrartablero(tabla);
	
	return 0;
}

void limpiartabla(char (*tabla)[TAMANIO][TAMANIO], char (*tablero)[TAMANIO][TAMANIO]){
	
	int i;
	for(i=0; i < TAMANIO; i++){	
		(*tablero)[0][i] = '0'+i;
		(*tabla)[0][i] = '0'+i;
	}
	
	for(i=0; i < TAMANIO; i++){	
		(*tablero)[i][0] = '0'+i;
		(*tabla)[i][0] = '0'+i;
	}
	
	int y;
	int x;
	for(y=1; y < TAMANIO; y++){									//limpiar matriz para que todos los valores inicien en 0
		for(x=1; x < TAMANIO; x++){
			(*tablero)[y][x] = '.';
			(*tabla)[y][x] = '.';
		}
	}
	
}

void actualizartabla(char tablero[TAMANIO][TAMANIO], char (*tabla)[TAMANIO][TAMANIO]){
	
	int y;
	int x;
	
	for(y=1; y < TAMANIO; y++){									//limpiar matriz para que todos los valores inicien en 0
		for(x=1; x < TAMANIO; x++){
			if(tablero[y][x] != '9')
				(*tabla)[y][x] =  tablero[y][x];
		}
	}
	
	
	
}

int checkwin(char tablero[TAMANIO][TAMANIO]){
	
	int cont=TAMANIO*2-1;
	int y;
	int x;
	
	for(y=1; y < TAMANIO; y++){									//conteo de casillas que fuero seleccionadas
		for(x=1; x < TAMANIO; x++){
			
			if(tablero[y][x] == '.')
				return cont;
				
			cont++;
		}
	}	
	
	return cont;
}

void checkalrededor(int y, int x,char (*tablero)[TAMANIO][TAMANIO]){
	
	int cont = 0;
	int a;
	int b;

	for(a=y-1; a <= y+1; a++){ 									//recorre todas las ubicaciones aledañas a la seleccionada x contabiliza la cantidad de bombas
		for(b=x-1; b <= x+1; b++){
			
			if(a >= 1 && a < TAMANIO && b >= 1 && b < TAMANIO){
			
				if((*tablero)[a][b] == '9')
					cont++;
				
				//printf("%d %d \n %d \n", a, b, cont);				//testeo de que los valores sean correctos
				
			}			
				
		}
	}
	
	(*tablero)[y][x] = '0'+cont; 										//asigna la cantidad de bombas aledañas como valor a mostrar, al igual que en el juego
	
	if(cont == 0){													//si no tiene bombas al rededor se eypande a las ubicaciones continuas
		
		(*tablero)[y][x] = '0';
		
		int c;
		int d;
		
		for(c=y-1; c <= y+1; c++){								//busca si las ubicaiones continuas fuero abiertas,  
			for(d=x-1; d <= x+1; d++){
				
				if(c >= 1 && c < TAMANIO && d >= 1 && d < TAMANIO){
					if((*tablero)[c][d] == '.')
						checkalrededor(c, d, tablero);	
				}
				
				//printf("%d %d \n %d \n", c, d, cont);			
			}
		}
	
	}
	
}

int checkearbomba(int y, int x, char tablero[TAMANIO][TAMANIO]){
	
	system("cls");
	
	if(tablero[y][x] == '9'){ 										//checkeo de bomba en la casilla
		
		return 1;												 	//devuelve 1 indicando el fin del juego
		
	}else if(tablero[y][x] != '.'){ 								//determina si la casilla xa fue seleccionada de antemano, para que no influxa en el caculo final
		
		printf("la casilla ya fue seleccionada\n");
		return 2;
		
	}
	
	return 0;
	
}

void elegircasilla(int *y, int *x){
	
		printf("ingrese las cordenadas de la casilla: \n Y=");		//Valores de la posicion seleccionada por el Plaxer
		scanf("%d",y);
		printf(" X=");
		scanf("%d",x);				
	
	//printf("%d %d ", *y, *x); 									//testeo de que los valores sean correctos
	
}

void cargarbomba(char (*tablero)[TAMANIO][TAMANIO]){
	
	int yb, xb, cont = 0;
	srand(time(NULL));
	
	while(cont != BOMBAS){											//cantidad de bombas determinada por la constante
	

		yb = rand()%TAMANIO; 										//generacion aleatoria de las posiciones
		xb = rand()%TAMANIO;
	
		if((*tablero)[yb][xb] == '.'){ 								//condicional para que las bombas no se superpongan 	
			cont++;
			(*tablero)[yb][xb] = '9'; 								//carga de bomba(representada con el 10)
		}
	
	}
}

void mostrartablero(char tablero[TAMANIO][TAMANIO]){
	
	//mostrar matriz en forma de tabla 
	int y;
	int x;
	
	for(y=0; y < TAMANIO; y++){
		for(x=0; x < TAMANIO; x++){
			printf("| %c |", tablero[y][x]);
		}
		
		printf("\n");
	}
	
}
