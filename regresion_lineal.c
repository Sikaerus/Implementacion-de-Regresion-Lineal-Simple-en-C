//Sikaerus, GNU: México
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//NUMERO DE PUNTOS PARA LA RECTA
#define NPR 100
//NUMERO DE COMANDOS DE GRAFICACIÓN
#define NCG 8

double sumatoria(double vector[],  int numero_variables);
double media_aritmetica(double vector[], int numero_variables);
double mediana(double vector[], int numero_variables);
void quicksort(double vector[], int primero, int ultimo);
double varianza(double vector[], int numero_variables);
double covarianza(double vector_x[], double vector_y[], int numero_variables);
double coeficiente_de_pearson(double vector_x[], double vector_y[], int numero_variables);
double * funcion_de_la_recta(double vector_x[], double vector_y[], int numero_variables);
void graficar(double vector_x[], double vector_y[], int numero_variables, double vector_recta[]);

int main(int argc, char const *argv[]) {

	FILE *archivo;
	archivo = fopen( argv[1], "r" );
	if( archivo == NULL ){
		fputs("Error al abrir \n", stderr);
		exit(1);
	}

	int linea, numero_variables = 0;
	while((linea = fgetc(archivo)) != EOF){
		if(linea == '\n'){
			numero_variables++;
		}
	}
	printf("Número de variables independientes y dependientes, por grupo %d \n", numero_variables);

	double x, y;
	register int i = 0;
	double X[numero_variables]; double Y[numero_variables];
	archivo = fopen( argv[1], "r" );
  while(fscanf(archivo, "%lf,%lf", &x, &y) == 2){
    printf("Valor de x: %lf, Valor de y: %lf\n", x, y);
		X[i] = x; Y[i] = y; i++;
  }

	//Sumatoria
	double sumatoria_x = sumatoria(X, numero_variables);
	double sumatoria_y = sumatoria(Y, numero_variables);
	printf("Sumatoria de x: %lf, Sumatoria de y: %lf\n", sumatoria_x, sumatoria_y);
	//Media, media aritmetica, promedio
	double media_x = media_aritmetica(X, numero_variables);
	double media_y = media_aritmetica(Y, numero_variables);
	printf("Media aritmetica de x: %lf, Media aritmetica de y: %lf\n", media_x, media_y);
	//Media muestral, valor intermedio de una muestra ordenada
	double mediana_x = mediana(X, numero_variables);
	double mediana_y = mediana(Y, numero_variables);
	printf("Mediana de x: %lf, Mediana de y: %lf\n", mediana_x, mediana_y);
	//Varianza
	double varianza_x = varianza(X, numero_variables);
	double varianza_y = varianza(Y, numero_variables);
	printf("Varianza de x: %lf, Varianza de y: %lf\n", varianza_x, varianza_y);
	//Dirección de realacion que se da entre variables
	double covarianza_x_y = covarianza(X, Y, numero_variables);
	printf("Covarianza Sxy: %lf\n", covarianza_x_y);
	//Coeficiente de Pearson r
	double r = coeficiente_de_pearson(X, Y, numero_variables);
	printf("Coeficiente de Pearson r: %lf\n", r);
	if(r == -1 ){ printf("Relación perfecta negativa\n"); }
	if(r == 0 ){ printf("No hay relación \n"); }
	if(r == 1 ){ printf("Relación perfecta positiva\n"); }
	if(r >= 0.80 ){ printf("Relación buena o muy aceptable\n"); }
	if(r < 0.80 ){ printf("Relación poco o nada aceptable\n"); }
	//Función de la recta
	double * vector_recta = malloc(NPR * sizeof(double));
	vector_recta = funcion_de_la_recta(X, Y, numero_variables);
	for( i = 0; i < NPR ; i++){
		printf("2 Dado el valor independiente: %d se obtiene el valor dependiente y: %lf\n", i, vector_recta[i]);
	}

	graficar(X, Y, numero_variables, vector_recta);

	fclose(archivo);
	return 0;
}
double sumatoria(double vector[],  int numero_variables){
	register int i;
	double sumatoria = 0;
	for(i = 0; i < numero_variables; i++){
		sumatoria += vector[i];
	}
	return sumatoria;
}
double media_aritmetica(double vector[], int numero_variables){
	return sumatoria(vector, numero_variables) / numero_variables;
}
double mediana(double vector[], int numero_variables){
	register int i;
	double mediana;
	quicksort(vector, 0, numero_variables-1);
	/*
	for(i = 0; i < numero_variables; i++){
		//Imprime el vector ordenado
		printf("\n %lf \n",vector[i]);
	}
	*/

	if( numero_variables%2 == 0 ){
		//Toma los valores intermedios, los suma y divide entre dos
		mediana = (vector[(numero_variables/2)-1]+vector[(numero_variables/2)+1-1]) / 2;
	}else{
		//Toma el valor exacto de la mitad
		mediana = vector[numero_variables/2];
	}

	return mediana;
}
void quicksort(double vector[], int primero, int ultimo){
   int i, j, pivote;
	 double temporal;
   if( primero < ultimo ){
      pivote = primero;
      i = primero;
      j = ultimo;
      while( i <  j){
         while( vector[i] <= vector[pivote] && i < ultimo)
            i++;
         while( vector[j] > vector[pivote] )
            j--;
         if( i < j ){
            temporal = vector[i];
            vector[i] = vector[j];
            vector[j] = temporal;
         }
      }
      temporal = vector[pivote];
      vector[pivote] = vector[j];
      vector[j] = temporal;
      quicksort(vector, primero, j-1);
      quicksort(vector, j+1, ultimo);
   }
}
double varianza(double vector[], int numero_variables){
	register int i;
	double varianza;
	double sumatoria_pre_varianza = 0;
	for(i = 0; i < numero_variables; i++){
		sumatoria_pre_varianza += pow( vector[i] - media_aritmetica(vector, numero_variables), 2);
	}
	varianza = sumatoria_pre_varianza/numero_variables;
	return varianza;
}
double covarianza(double vector_x[], double vector_y[], int numero_variables){
	register int i;
	double covarianza;
	double sumatoria_pre_covarianza = 0;
	for(i = 0; i < numero_variables;i++){
		sumatoria_pre_covarianza += (vector_x[i] - media_aritmetica(vector_x, numero_variables)) *
																(vector_y[i] - media_aritmetica(vector_y, numero_variables));
	}
	covarianza = sumatoria_pre_covarianza/numero_variables;
	return covarianza;
}
double coeficiente_de_pearson(double vector_x[], double vector_y[], int numero_variables){
	double r;
	double Sx = sqrt( varianza(vector_x, numero_variables) );
	double Sy = sqrt( varianza(vector_y, numero_variables) );
	double Sxy = covarianza(vector_x, vector_y, numero_variables);
	r = Sxy/( Sx * Sy );
	return r;
}
double * funcion_de_la_recta(double vector_x[], double vector_y[], int numero_variables){
	register int x;
	//Vector de la recta
	double * vector_de_la_recta = malloc(NPR * sizeof(double));
	double b = covarianza(vector_x, vector_y, numero_variables)/varianza(vector_x, numero_variables);
	printf("b --- > %lf\n", b);
	if( b > 0 ){ printf("b > 0: Relacion positiva\n"); }
	if( b == 0 ){ printf("b == 0: No hay relacion\n"); }
	if( b < 0 ){ printf("b > 0: Relacion negativa\n"); }
	double a = media_aritmetica(vector_y, numero_variables) - b * media_aritmetica(vector_x, numero_variables);
	printf("a ---- > %lf\n", a);
	for( x = 0; x < NPR ; x++){
		//A partir de x valor independiente se obtiene y valor dependiente
		double y = a + b*x;
		vector_de_la_recta[x] = y;
		//printf("1 Dado el valor independiente: %d se obtiene el valor dependiente y: %lf\n", x, y);
	}
	return vector_de_la_recta;
}
void graficar(double vector_x[], double vector_y[], int numero_variables, double vector_recta[]){
	register int i;

	FILE * puntos_dispercion = fopen("puntos_dispercion.dat", "w");
	for(i = 0; i < numero_variables; i++){
		//Escribe sobre el archivo puntos_dispercion.dat los puntos dispersos de la grafica
		fprintf(puntos_dispercion, "%lf %lf \n", vector_x[i], vector_y[i]);
	}

	FILE * recta = fopen("recta.dat", "w");
	for (i = 0; i < NPR; i++ ){
		//Escribe sobre el archivo recta.dat los puntos que graficarán la recta
		fprintf(recta, "%d %lf \n", i, vector_recta[i]);
	}

	char * config_gnuplot[] = {"set title \"Regresión lineal\"",
														"set xlabel \"x - Colesterol\"","set ylabel \"y - Triglicéridos\"",
														"set xrange [-1:16]",
														"set yrange [-1:16]",
														"set zeroaxis",
														"plot \"puntos_dispercion.dat\" title \"Relación Colesterol-Triglicéridos\" pt 7 lt rgb \"red\" ",
														"replot \"recta.dat\" using 1:2 with lines title \"Recta y = a + b*x_{i} \" lt rgb \"blue\"",
														"pause 1"};

	FILE * ventana_gnuplot = popen("gnuplot -persist", "w");

	for( i = 0; i < NCG; i++ ){
		fprintf(ventana_gnuplot, "%s \n", config_gnuplot[i]);
	}

	fclose(puntos_dispercion);
	fclose(recta);
	fclose(ventana_gnuplot);
}
