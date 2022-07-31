#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <windows.h>

#define RED "\x1B[31m"
#define RESET "\x1B[0m"
#define GRN "\x1B[32m"
#define CYN "\x1B[36m"

int largura = 40, altura = 20;
int x, y, gameOver, pointX, pointY, flag, countTail, vel = 250, pointX2, pointY2, k;
int tailX[50], tailY[50];

void update();
void draw();
void setup();
void input();

int main() {
	setup();

	while(gameOver == 0)
	{
        Sleep(vel);
		draw();
		input();
		update(); 
		if((x == 0) || (x == altura - 1) || (y == 0) || (y == largura -1))
		{
        	gameOver = 1;
        	printf("Game Over");
    	}
	}

getch();
}
//---------------------------------------------------------------------------------------
void draw() {
	system("cls");
	printf("Pontuacao: %d\n", countTail);
	int i, j;
	for (i = 0; i < altura; i++)  {
		for(j = 0; j < largura; j++) {

			if(i == 0 || i == altura -1 || j == 0 || j == largura -1) {
				printf("%c", 176); // Paredes
			}
			else {
				if(pointX == i && pointY == j)	{
					printf(GRN "%c" RESET,162); // Fruta -> Aumentar
				}
				else if(x == i && y == j) {
					printf(CYN "%c" RESET, 219); // Snake
				}
				else if(pointX2 == i && pointY2 == j && countTail > 0) {
					printf(RED "%c" RESET, 162); // Fruta -> diminuir
				}
				else {
                    int ch = 0;
                    int k;
                    for(k = 0; k < countTail; k++) {
                        if(i == tailX [k] && j == tailY[k]) {
                            printf(CYN "%c" RESET, 219); // Cauda
                            ch =1;
                   		}                 
                    }
                    if(ch == 0)
                    {
                    	printf(" "); //area do jogo
					}   
                }
			}
		}
		printf("\n");
	}

	if(x == pointX && y == pointY)
    {
    	label3:
        pointX = rand() % altura;
        if(pointX == 0)
        {
            goto label3;
		}
        
    	label4:
        pointY = rand() % largura;
        if(pointY == 0)
        {
            goto label4;
    	}
        countTail++;
        if(countTail %3 == 0 && vel > 100)
        {
            vel = vel - 50;
        }
        if(countTail %3 == 0 && vel == 100)
        {
            vel = 25;
        }
    }
    if(x == pointX2 && y == pointY2)
    {
    	label5:
    	pointX2 = rand() % altura;
    	if(pointX2 == 0)
    	{
    		goto label5;
		}
		label6:
		pointY2 = rand () % largura;
		if(pointY2 == 0)
		{
			goto label6;
		}
		countTail--;
	}
	if(pointX == pointX2 && pointY == pointY2)
	{
		label9:
    	pointX = rand() % altura;
    	pointX2 = rand() % altura;
    	if(pointX == 0 || pointX2 == 0)
    	{
    		goto label9;
		}
		label10:
		pointY = rand () % largura;
		pointY2 = rand () % largura;
		if(pointY == 0 || pointY2 == 0)
		{
			goto label10;
		}
	}
}
//---------------------------------------------------------------------------------------
void setup() {
	gameOver = 0;
	x = altura /2; 
	y = largura /2;

label1:
	pointX = rand() % altura;
	if(pointX == 0)
	{
		goto label1;
	}
	
label2:
	pointY = rand() % largura;
	if(pointY == 0)
	{
		goto label2;
	}
	
label7:
	pointX2 = rand() % altura;
	if(pointX == 0)
	{
		goto label7;
	}
	
label8:
	pointY2 = rand() % largura;
	if(pointY2 == 0)
	{
		goto label8;
	}
}
//---------------------------------------------------------------------------------------
void update() {
    int vetPrevX = tailX[0];
    int vetPrevY = tailY[0];
    
    int vet2PrevX, vet2PrevY;
    
    tailX[0] = x;
    tailY[0] = y;
    
    int k;
    for(k = 1; k < countTail; k++)
    {
        vet2PrevX = tailX[k];
        vet2PrevY = tailY[k];
        tailX[k] = vetPrevX;
        tailY[k] = vetPrevY;
        vetPrevX = vet2PrevX;
        vetPrevY = vet2PrevY;
    }
    
    if(x == pointX2 && y == pointY2)
	{
		int j;
		for(j=0;j<50;j++)
		{
			tailX[j] = tailX[j+1];
		}
	}
	if(x == pointX2 && y == pointY2)
	{
		int j;
		for(j=0;j<50;j++)
		{
			tailY[j] = tailY[j+1];
		}
	}
    
	switch(flag)
	{
		case 1:
			x--;
			break;

		case 2:
			x++;
			break;

		case 3:
			y--;
			break;

		case 4:
			y++;
			break;
	}
	
	
}
//---------------------------------------------------------------------------------------
void input() {
	if(kbhit())
	{
		switch (getch())
		{
			case 'w': // Cima
				flag = 1;
			break;

			case 's':
				flag = 2; // Esquerda
			break;

			case 'a':
				flag = 3; 	// Baixo
			break;

			case 'd':
				flag = 4; // Direita
			break;

			case 'x':
				flag = 5; 	// sair
				gameOver = 1;
			break;
		}
	}
}
