#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <graphics.h>
#include <conio.h>
#include <math.h>

struct Punto{
    int x;
    int y;
};

struct Punto puntos[5000]; 

struct Punto rotar_punto(int px, int py, int cx, int cy, double angulo){
    double s = sin(angulo);
    double c = cos(angulo);

    double x_rel = (double)(px - cx);
    double y_rel = (double)(py - cy);
    double x_rotado = x_rel * c - y_rel * s;
    double y_rotado = x_rel * s + y_rel * c;

    struct Punto p_nuevo;
    p_nuevo.x = (int)(x_rotado + cx);
    p_nuevo.y = (int)(y_rotado + cy);
    return p_nuevo;
}

void traslacionmapa();
void rotacionmapa();
void escalarmapa();
void reflejarmapa();

void traslacionfondo();
void rotacionfondo();
void escalarfondo();
void reflejarfondo();

int main(){
	int op; 
	printf("\n¡Bienvenido al programa de transformaciones!\n");
	do{
		printf("\nEscribe \n1 Para realizar la traslación del mapa de Mexico\n2 Para rotar el mapa de Mexico\n3 Para escalar el mapa de Mexico\n4 Para reflejar el mapa de Mexico");
		printf("\n5 Para trasladar el fondo \n6 Para rotar el fondo \n7 Para escalar el fondo\n8 Para reflejar el fondo\n9 Para salir del programa");
		scanf("%d",&op);
		switch(op){
			case 1:{
				traslacionmapa();
				break;
			}
			case 2:{
				rotacionmapa();
				break;
			}
			case 3:{
				escalarmapa();
				break;
			}
			case 4:{
				reflejarmapa();
				break;
			}
			case 5:{
				traslacionfondo();
				break;
			}
			case 6:{
				rotacionfondo();
				break;
			}
			case 7:{
				escalarfondo();
				break;
			}
			case 8:{
				reflejarfondo();
				break;
			}
			case 9:{
				printf("\nSalida exitosa");
				break;
			}
			default:
				printf("Intente otra opcion");
		}
	
	}while(op!=9);
	getch();
	closegraph();
	return 0;
}

void traslacionmapa(){
	printf("\nPRIMER PROGRAMA: Transladando el mapa de Mexico\n");
	printf("El mapa de Mexico se mueve de izquierda a derecha con sus respectivas flechas. Presiona esc para salir del programa\n");
    FILE *archivo;
    char cadena[100];
    int i = 0;
    int num_puntos = 0; 
    
    archivo = fopen("C:\\CarpetaGraphics\\GraficacionPuntos\\coordenadas.txt", "r");
    
    while(fgets(cadena, 100, archivo) != NULL){
        if (strlen(cadena) > 2) { 
            puntos[i].x = atoi(strtok(cadena, ","));
            puntos[i].y = atoi(strtok(NULL, ","));
            i++;
        }
    }
    num_puntos = i;
    fclose(archivo); 

    int gd = DETECT, gm;
    initgraph(&gd, &gm, (char*)""); 
    
    int centrox = getmaxx() / 2;
    int centroy = getmaxy() / 2;

    int tx = 0; 
    int ty = 0; 
    
    int tecla = 0;
    
    while(1) { 
        
        cleardevice(); 
        for(i = 0; i < num_puntos; i++){
            int plot_x = centrox + puntos[i].x + tx; 
            int plot_y = centroy + puntos[i].y + ty; 
            
            putpixel(plot_x, plot_y, GREEN); 
        }

        tecla = getch();

        if (tecla == 27) { 
            break; 
        }
        
        if (tecla == 0 || tecla == 227 || tecla ) {
            tecla = getch(); 
            switch(tecla) {
                case 75: 
                    tx -= 10; 
                    break;
                case 77: 
                    tx += 10; 
                    break;
                case 72:
                	ty-=10;
                	break;
                case 80:
                	ty+=10;
                	break;
            }
        }
    
    }
    cleardevice(); 
}

void rotacionmapa(){
	printf("\nSEGUNDO PROGRAMA: Rotando el mapa de Mexico\n");
	printf("\nEl mapa rota con las flechas. Presiona esc para salir del programa\n");
    FILE *archivo;
    char cadena[100];
    int i = 0;
    int num_puntos = 0;

    archivo = fopen("C:\\CarpetaGraphics\\GraficacionPuntos\\coordenadas.txt", "r");


    while (fgets(cadena, 100, archivo) != NULL) {
        if (strlen(cadena) > 2) {
            puntos[i].x = atoi(strtok(cadena, ","));
            puntos[i].y = atoi(strtok(NULL, ","));
            i++;
        }
    }
    num_puntos = i;
    fclose(archivo);
    int gd = DETECT, gm;
    initgraph(&gd, &gm, (char*)"");

    int centrox = getmaxx() / 2;
    int centroy = getmaxy() / 2;

    int tx = 0; 
    int ty = 0; 
    double theta_deg = 0.0; 
    int tecla = 0;
    char buffer_texto[100];
    while (1) {
        
        double theta_rad = theta_deg * M_PI / 180.0; 
        double cos_t = cos(theta_rad);
        double sin_t = sin(theta_rad);
        cleardevice();
        sprintf(buffer_texto, "Angulo: %.1f grados | Traslacion (tx: %d, ty: %d)", theta_deg, tx, ty);
        outtextxy(10, 30, buffer_texto);

        for(i = 0; i < num_puntos; i++){
            
            int x_orig = puntos[i].x;
            int y_orig = puntos[i].y;

            int x_rot = (int)(x_orig * cos_t - y_orig * sin_t);
            int y_rot = (int)(x_orig * sin_t + y_orig * cos_t);

            int plot_x = centrox + x_rot + tx;
            int plot_y = centroy + y_rot + ty;

            putpixel(plot_x, plot_y, GREEN);
        }

        tecla = getch();

        if (tecla==27) { 
            break;
        }

        if(tecla == 0 || tecla == 224){ 
            tecla = getch(); 
            switch (tecla) {
                case 75: 
                    theta_deg -= 5.0; 
                    break;
                case 77: 
                    theta_deg += 5.0; 
                    break;
                case 72: 
                    ty -= 10; 
                    break;
                case 80: 
                    ty += 10; 
                    break;
            }
        }
    }
    cleardevice();
    //printf("Segundo");
}
void escalarmapa(){
	printf("\nTERCER PROGRAMA: Puestas a escala de la FIGURA\n"); 
	printf("Escalar con el signo de '+' y de '-'. Presiona ESC para salir");
    FILE *archivo;
    char cadena[100];
    int i = 0;
    int num_puntos = 0;

    archivo = fopen("C:\\CarpetaGraphics\\GraficacionPuntos\\coordenadas.txt", "r");

    while (fgets(cadena, 100, archivo) != NULL) {
        if (strlen(cadena) > 2) {
            puntos[i].x = atoi(strtok(cadena, ","));
            puntos[i].y = atoi(strtok(NULL, ","));
            i++;
        }
    }
    num_puntos = i;
    fclose(archivo);

    int gd = DETECT, gm;
    initgraph(&gd, &gm, (char*)"");

    int centrox = getmaxx() / 2;
    int centroy = getmaxy() / 2;
    int max_x = getmaxx();
    int max_y = getmaxy();

    double sx = 1.0; 
    double sy = 1.0; 

    int tecla = 0;
    char buffer_texto[100]; 

    while (1) {
        
        cleardevice();
        setcolor(DARKGRAY);
        int grid_spacing = 50; 
        
        for(int c = 1; ; c++) {
            int offset = c * grid_spacing;
            
            int plot_x_pos = centrox + offset;
            int plot_x_neg = centrox - offset;
            int plot_y_pos = centroy + offset;
            int plot_y_neg = centroy - offset;
            
            int lineas_visibles = 0;
            
            if(plot_x_pos < max_x){ 
				line(plot_x_pos, 0, plot_x_pos, max_y); 
				lineas_visibles++; 
			}
            if(plot_x_neg >= 0){ 
				line(plot_x_neg, 0, plot_x_neg, max_y); 
				lineas_visibles++; 
			}
            if(plot_y_pos < max_y){ 
				line(0, plot_y_pos, max_x, plot_y_pos); 
				lineas_visibles++; 
			}
            if(plot_y_neg >= 0){ 
				line(0, plot_y_neg, max_x, plot_y_neg); 
				lineas_visibles++; 
			}
            if(lineas_visibles == 0 && c > 10){
				break; 
			}
        }

        setcolor(LIGHTGRAY); 
        setlinestyle(SOLID_LINE, 0, 3); 
        line(centrox, 0, centrox, max_y);
        line(0, centroy, max_x, centroy);
        setlinestyle(SOLID_LINE, 0, 1); 

        for(i = 0; i < num_puntos; i++){
            int x_orig = puntos[i].x;
            int y_orig = puntos[i].y;

            int x_scaled = (int)(x_orig * sx);
            int y_scaled = (int)(y_orig * sy);
            int plot_x = centrox + x_scaled;
            int plot_y = centroy + y_scaled;

            putpixel(plot_x, plot_y, GREEN);
        }
        setcolor(WHITE);
        sprintf(buffer_texto, "Escala Figura (Sx: %.1f, Sy: %.1f)", sx, sy); 
        outtextxy(10, 30, buffer_texto);

        tecla = getch();

        if(tecla == 27){ 
            break;
        }

        switch(tecla){
            case '+': 
                sx += 0.1;
                sy += 0.1;
                break;
            case '-': 
                if (sx > 0.1 && sy > 0.1) {
                    sx -= 0.1;
                    sy -= 0.1;
                }
                break;
        }
    }

    cleardevice();
    //printf("\ntercero");
}
void reflejarmapa(){
	printf("\nCUARTO PROGRAMA: Reflejo y Traslacion del mapa\n");
	printf("\nMover el reflejo con las flecha de arriba y abajo. Presionar esc para salir.");
    FILE *archivo;
    char cadena[100];
    int i = 0;
    int num_puntos = 0;
    archivo = fopen("C:\\CarpetaGraphics\\GraficacionPuntos\\coordenadas.txt", "r");

    while(fgets(cadena, 100, archivo) != NULL){
        if (strlen(cadena) > 2) {
            puntos[i].x = atoi(strtok(cadena, ","));
            puntos[i].y = atoi(strtok(NULL, ","));
            i++;
        }
    }
    num_puntos = i;
    fclose(archivo);

    int gd = DETECT, gm;
    initgraph(&gd, &gm, (char*)"");

    int centrox = getmaxx() / 2;
    int centroy = getmaxy() / 2;
    int max_x = getmaxx();
    int max_y = getmaxy();

    int tx = 0; 
    int ty = 0; 
    double sx = 1; 
    double sy = 1; 

    int tecla = 0;
    char buffer_texto[100];

    while(1){
        cleardevice();

        setcolor(WHITE);
        sprintf(buffer_texto, "Reflejo (Sx: %.0f, Sy: %.0f) | Traslacion (tx: %d, ty: %d)", sx, sy, tx, ty);
        outtextxy(10, 30, buffer_texto);
        setcolor(DARKGRAY);
        line(centrox + tx, 0, centrox + tx, max_y); 
        line(0, centroy + ty, max_x, centroy + ty); 

        for(i = 0; i < num_puntos; i++){
            
            int x_orig = puntos[i].x;
            int y_orig = puntos[i].y;

            int x_reflejado = (int)(x_orig * sx);
            int y_reflejado = (int)(y_orig * sy);
            int plot_x = centrox + x_reflejado + tx;
            int plot_y = centroy + y_reflejado + ty;
            putpixel(plot_x, plot_y, GREEN);
        }
        tecla = getch();

        if(tecla == 27){ 
            break;
        }

        if(tecla == 0 || tecla == 224){ 
            tecla = getch();
            switch (tecla) {
                case 72:
                    sy = sy * -1; 
                    break;
                case 80:
                    sx = sx * -1;
                    break;
            }
        }
    }
    cleardevice();
}

void traslacionfondo(){
	printf("\nQUINTO PROGRAMA: Trasladando el fondo\n");
	printf("\nMover con flechas. Salir con ESC");
    FILE *archivo;
    char cadena[100];
    int i = 0;
    int num_puntos = 0;
    
    archivo = fopen("C:\\CarpetaGraphics\\GraficacionPuntos\\coordenadas.txt", "r");

    while (fgets(cadena, 100, archivo) != NULL) {
        if (strlen(cadena) > 2) {
            puntos[i].x = atoi(strtok(cadena, ","));
            puntos[i].y = atoi(strtok(NULL, ","));
            i++;
        }
    }
    num_puntos = i;
    fclose(archivo);

    int gd = DETECT, gm;
    initgraph(&gd, &gm, (char*)"");

    int centrox = getmaxx() / 2;
    int centroy = getmaxy() / 2;
    int max_x = getmaxx();
    int max_y = getmaxy();
    int tx = 0;
    int ty = 0;
    double sx = 1;
    double sy = 1;

    int tecla = 0;
    char buffer_texto[100];

    while(1){
        
        cleardevice();

        setcolor(DARKGRAY); 
        int grid_spacing = 50; 
        for(int x = -max_x; x < (max_x * 2); x += grid_spacing){
            line(x + tx, 0, x + tx, max_y);
        }
        for(int y = -max_y; y < (max_y * 2); y += grid_spacing){
            line(0, y + ty, max_x, y + ty);
        }
        setcolor(WHITE);
        sprintf(buffer_texto, "Reflejo (Sx: %.0f, Sy: %.0f) | Desplazamiento Fondo (tx: %d, ty: %d)", sx, sy, tx, ty);
        outtextxy(10, 30, buffer_texto);
        setcolor(LIGHTGRAY); 
        setlinestyle(SOLID_LINE, 0, 3); 
        line(centrox + tx, 0, centrox + tx, max_y);
        line(0, centroy + ty, max_x, centroy + ty); 
        
        setlinestyle(SOLID_LINE, 0, 1); 
        for(i = 0; i < num_puntos; i++){
            
            int x_orig = puntos[i].x;
            int y_orig = puntos[i].y;

            int x_reflejado = (int)(x_orig * sx);
            int y_reflejado = (int)(y_orig * sy);
            int plot_x = centrox + x_reflejado;
            int plot_y = centroy + y_reflejado;

            putpixel(plot_x, plot_y, GREEN);
        }

        tecla = getch();

        if(tecla == 27){
            break;
        }

        if(tecla == 0 || tecla == 224) {
            tecla = getch();
            switch (tecla) {
                case 72: ty -= 10; break;
                case 80: ty += 10; break;
                case 75: tx -= 10; break;
                case 77: tx += 10; break;
            }
        }
    }

    cleardevice();
}
void rotacionfondo(){
	printf("\nSEXTO PROGRAMA: Rotando el fondo\n");
	printf("Rotar con flechs izq y der, salir con ESC");
    FILE *archivo;
    char cadena[100];
    int i = 0;
    int num_puntos = 0;
    
    archivo = fopen("C:\\CarpetaGraphics\\GraficacionPuntos\\coordenadas.txt", "r");

    while(fgets(cadena, 100, archivo) != NULL){
        if (strlen(cadena) > 2) {
            puntos[i].x = atoi(strtok(cadena, ","));
            puntos[i].y = atoi(strtok(NULL, ","));
            i++;
        }
    }
    num_puntos = i;
    fclose(archivo);

    int gd = DETECT, gm;
    initgraph(&gd, &gm, (char*)"");

    int centrox = getmaxx() / 2;
    int centroy = getmaxy() / 2;
    int max_x = getmaxx();
    int max_y = getmaxy();
    
    double angulo = 0.0; 
    double sx = 1;
    double sy = 1;

    int tecla = 0;
    char buffer_texto[100];
    struct Punto p1, p2; 

    while(1){
        
        cleardevice();

        setcolor(DARKGRAY); 
        int grid_spacing = 50;
        
        for(int x = -max_x; x < (max_x * 2); x += grid_spacing){
            p1 = rotar_punto(x, 0, centrox, centroy, angulo);
            p2 = rotar_punto(x, max_y, centrox, centroy, angulo);
            line(p1.x, p1.y, p2.x, p2.y);
        }
        for(int y = -max_y; y < (max_y * 2); y += grid_spacing){
            p1 = rotar_punto(0, y, centrox, centroy, angulo);
            p2 = rotar_punto(max_x, y, centrox, centroy, angulo);
            line(p1.x, p1.y, p2.x, p2.y);
        }
        
        setcolor(WHITE);
        
        double angulo_grados = angulo * 180.0 / 3.14159265; 
        sprintf(buffer_texto, "Reflejo (Sx: %.0f, Sy: %.0f) | Angulo Fondo: %.1f grados", sx, sy, angulo_grados);
        outtextxy(10, 30, buffer_texto);
        
        setcolor(LIGHTGRAY); 
        setlinestyle(SOLID_LINE, 0, 3); 
        p1 = rotar_punto(centrox, 0, centrox, centroy, angulo);
        p2 = rotar_punto(centrox, max_y, centrox, centroy, angulo);
        line(p1.x, p1.y, p2.x, p2.y);
        p1 = rotar_punto(0, centroy, centrox, centroy, angulo);
        p2 = rotar_punto(max_x, centroy, centrox, centroy, angulo);
        line(p1.x, p1.y, p2.x, p2.y); 
        setlinestyle(SOLID_LINE, 0, 1); 
        for(i = 0; i < num_puntos; i++){
            
            int x_orig = puntos[i].x;
            int y_orig = puntos[i].y;

            int x_reflejado = (int)(x_orig * sx);
            int y_reflejado = (int)(y_orig * sy);
            int plot_x = centrox + x_reflejado;
            int plot_y = centroy + y_reflejado;

            putpixel(plot_x, plot_y, GREEN);
        }

        tecla = getch();

        if(tecla == 27){
            break;
        }

        if(tecla == 0 || tecla == 224){ 
            tecla = getch();
            switch(tecla){
                case 75: angulo -= 0.05; break;
                case 77: angulo += 0.05; break;
            }
        }
    }
    cleardevice();
}
void escalarfondo(){
	printf("\nSEPTIMO PROGRAMA: Puestas a escala del FONDO\n");
	printf("\nEscalar fondo con '+' y '-'. Presionar ESC para salir");
    FILE *archivo;
    char cadena[100];
    int i = 0;
    int num_puntos = 0;

    archivo = fopen("C:\\CarpetaGraphics\\GraficacionPuntos\\coordenadas.txt", "r");

    while (fgets(cadena, 100, archivo) != NULL) {
        if (strlen(cadena) > 2) {
            puntos[i].x = atoi(strtok(cadena, ","));
            puntos[i].y = atoi(strtok(NULL, ","));
            i++;
        }
    }
    num_puntos = i;
    fclose(archivo);

    int gd = DETECT, gm;
    initgraph(&gd, &gm, (char*)"");

    int centrox = getmaxx() / 2;
    int centroy = getmaxy() / 2;
    int max_x = getmaxx();
    int max_y = getmaxy();

    double sx = 1.0; 
    double sy = 1.0; 

    int tecla = 0;
    char buffer_texto[100]; 

    while (1) {
        
        cleardevice();
        
        setcolor(DARKGRAY);
        int grid_spacing = 50; 
        
        for(int c = 1; ; c++) {
            int offset = c * grid_spacing;
            
            int plot_x_pos = centrox + (int)(offset * sx);
            int plot_x_neg = centrox - (int)(offset * sx);
            int plot_y_pos = centroy + (int)(offset * sy);
            int plot_y_neg = centroy - (int)(offset * sy);
            
            int lineas_visibles = 0;
            
            if(plot_x_pos < max_x){ 
				line(plot_x_pos, 0, plot_x_pos, max_y); lineas_visibles++; 
			}
            if(plot_x_neg >= 0){ 
				line(plot_x_neg, 0, plot_x_neg, max_y); lineas_visibles++; 
			}
            if(plot_y_pos < max_y){ 
				line(0, plot_y_pos, max_x, plot_y_pos); lineas_visibles++; 
			
			}
            if(plot_y_neg >= 0){ 
				line(0, plot_y_neg, max_x, plot_y_neg); lineas_visibles++; 
			}
            
            if(lineas_visibles == 0 && c > 10) 
				break; 
        }

        setcolor(LIGHTGRAY); 
        setlinestyle(SOLID_LINE, 0, 3); 
        line(centrox, 0, centrox, max_y);
        line(0, centroy, max_x, centroy);
        setlinestyle(SOLID_LINE, 0, 1); 

        for(i = 0; i < num_puntos; i++){
            int x_orig = puntos[i].x;
            int y_orig = puntos[i].y;

            int plot_x = centrox + x_orig;
            int plot_y = centroy + y_orig;

            putpixel(plot_x, plot_y, GREEN);
        }

        setcolor(WHITE);
        sprintf(buffer_texto, "Escala Fondo (Sx: %.1f, Sy: %.1f)", sx, sy);
        outtextxy(10, 30, buffer_texto);

        tecla = getch();

        if(tecla == 27){
            break;
        }

        switch(tecla){
            case '+': 
                sx += 0.1;
                sy += 0.1;
                break;
            case '-': 
                if (sx > 0.1 && sy > 0.1) {
                    sx -= 0.1;
                    sy -= 0.1;
                }
                break;
        }
    }

    cleardevice();
}
void reflejarfondo(){
	printf("\nOCTAVO PROGRAMA: Reflejo del fondo\n");
	printf("\nMover el fondo con flechas. Presionar ESC para salir");
    FILE *archivo;
    char cadena[100];
    int i = 0;
    int num_puntos = 0;
    archivo = fopen("C:\\CarpetaGraphics\\GraficacionPuntos\\coordenadas.txt", "r");

    while(fgets(cadena, 100, archivo) != NULL){
        if (strlen(cadena) > 2) {
            puntos[i].x = atoi(strtok(cadena, ","));
            puntos[i].y = atoi(strtok(NULL, ","));
            i++;
        }
    }
    num_puntos = i;
    fclose(archivo);

    int gd = DETECT, gm;
    initgraph(&gd, &gm, (char*)"");

    int centrox = getmaxx() / 2;
    int centroy = getmaxy() / 2;
    int max_x = getmaxx();
    int max_y = getmaxy();

    int tx = 0; 
    int ty = 0; 
    double sx = 1; 
    double sy = 1; 

    int tecla = 0;
    char buffer_texto[100];

    while(1){
        cleardevice();

        setcolor(DARKGRAY); 
        int grid_spacing = 50; 
        
        for(int x = -max_x; x < (max_x * 2); x += grid_spacing){
            int plot_x = centrox + (int)((x - centrox) * sx) + tx;
            line(plot_x, 0, plot_x, max_y);
        }
        for(int y = -max_y; y < (max_y * 2); y += grid_spacing){
            int plot_y = centroy + (int)((y - centroy) * sy) + ty;
            line(0, plot_y, max_x, plot_y);
        }
        
        setcolor(LIGHTGRAY); 
        setlinestyle(SOLID_LINE, 0, 3); 
        line(centrox + tx, 0, centrox + tx, max_y); 
        line(0, centroy + ty, max_x, centroy + ty); 
        setlinestyle(SOLID_LINE, 0, 1); 

        for(i = 0; i < num_puntos; i++){
            
            int x_orig = puntos[i].x;
            int y_orig = puntos[i].y;
            
            int plot_x = centrox + x_orig;
            int plot_y = centroy + y_orig;
            putpixel(plot_x, plot_y, GREEN);
        }

        setcolor(WHITE);
        sprintf(buffer_texto, "Fondo (Sx: %.0f, Sy: %.0f) | Fondo (tx: %d, ty: %d)", sx, sy, tx, ty);
        outtextxy(10, 30, buffer_texto);

        tecla = getch();

        if(tecla == 27){ 
            break;
        }
        if(tecla == 0 || tecla == 224){ 
            tecla = getch();
            switch(tecla) {
                case 72:
                case 80:
                    sy = sy * -1; 
                    break;
                case 75:
                case 77:
                    sx = sx * -1; 
                    break;
            }
        }
    }
    cleardevice();
}
