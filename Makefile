#Makefile para compilar

all: compila ejecuta

compila:
	gcc regresion_lineal.c -o regresion -lm

#Modifique el .txt al conjunto_de_datos de su preferencia
ejecuta:
	./regresion colesterol_y_triglicéridos.txt

clean:
	rm -f grafica.png recta.dat puntos_dispercion.dat regresion
