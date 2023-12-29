#include <stdio.h>
#include <windows.h>
#include <time.h>



#define edge '|'
#define space ' '
#define wall '#'
#define Player1 'A'
#define Player2 'B'


char board[100][100];


void clearScrean(){
	system("cls");
}


void setTextColor(int textColor, int backColor) {
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	int colorAttribute = backColor << 4 | textColor;
	SetConsoleTextAttribute(consoleHandle, colorAttribute);
}


void sleep(unsigned int mseconds) {
	clock_t goal = mseconds + clock();
	while (goal > clock());
}






void Board(char walls[][100],int n,int x,int y,int a,int b){ // board preparation
	int i,j;
	for(i=0 ; i<n ; i++){
		for(j=0 ; j<n ; j++){
			if (i==x && j==y) board[i][j]=Player1;
			else if(i==a && j==b) board[i][j]=Player2;
			else if(walls[i][j]==wall) board[i][j]=wall;
			else if(i==0 || i==n-1 || j==0 || j==n-1) board[i][j]=edge;
			else if(i%2==0) board[i][j]=edge;
			else if(j%2==0) board[i][j]=edge;
			else board[i][j]=space;
		}
	}
}


char BoardPrint(int k){
	int i,j;
		for(i=0 ; i<k ; i++){
			for(j=0 ; j<k ; j++){
				printf("%c",board[i][j]);
			}
			printf("\n");
		}
}


void main ()
{
	int n,k;
	int i,j;
	int h,v,p;
	int ascii,sw=0;
	int x,y,a,b;// Variables that  show coordinates of player1 and player2's character
	int xx,yy,aa,bb;//copy of original variables
	int wallCount,wallCount1,wallCount2;//count of the walls for each player
	char player1[20],player2[20];//each player's nickname
	char walls[100][100];// an array to put # as wall and match it with board
	char wallDirection;// vertical or horizontal

	do{//receive 'n' as dimention of the board which will be n*n
		sleep(500);
		printf("Please enter dimension of the board : ");
		scanf("%d",&n);
		clearScrean();
	}while(n<=3);
	k=2*n+1;

	if(n%2==0){x=1 , y=n-1;}// determining where should player 1&2's characters locate
	else { x=1 , y=n;}
	if(n%2==0){	a=k-2 , b=n-1;}
	else { a=k-2 , b=n;}

//when player1 should enter sth , Board's color will be yellow
//when player2 should enter sth , Board's color will be blue

	//scanning the nickname of player1
	sleep(400);
	setTextColor(6,0);
	printf("<< player1 >> \n");// board's printing
	printf("Remained walls: \n");
	Board(walls,k,x,y,a,b);
	BoardPrint(k);
	printf("Remained walls: \n");
	printf("<< player2 >> \n");// end of board's printing
	printf("\nPlayer1...! enter a nickname for yourself : ");
	scanf("%s",player1);
	clearScrean();

	//scanning the nickname of player2
	sleep(400);
	setTextColor(11,0);
	printf("<< %s >>\n",player1);// board's printing
	printf("Remained walls: \n");
	Board(walls,k,x,y,a,b);
	BoardPrint(k);
	printf("Remained walls: \n");
	printf("<< player2 >> \n");// end of board's printing
	printf("\nPlayer2...! enter a nickname for yourself : ");
	scanf("%s",player2);
	clearScrean();


	do{//scanning the number of their walls
		clearScrean();
		sleep(400);
		setTextColor(15,0);
		printf("<< %s >>\n",player1);// board's printing
		printf("Remained walls: \n");
		Board(walls,k,x,y,a,b);
		BoardPrint(k);
		printf("Remained walls: \n");
		printf("<< %s >>\n",player2);// end of board's printing
		printf("\nHow many walls would you like to have? ");
		scanf("%d",&wallCount);
		wallCount1=wallCount;
		wallCount2=wallCount;
		clearScrean();
	}while(wallCount>=n*n/4);// we use do...while because wallCount for each player shouldn't be more than n*n/4


	do{//game started , Until someone reaches the other side, this loop will repeat
		do{//player1's next move...
			xx=x , yy=y;
			clearScrean();
			sleep(400);
			setTextColor(6,0);
			printf("<< %s >>\n",player1);// board's printing
			printf("Remained walls: %d\n",wallCount1);
			Board(walls,k,x,y,a,b);
			BoardPrint(k);
			printf("Remained walls: %d\n",wallCount2);
			printf("<< %s >>\n",player2);// end of board's printing
			printf("\n %s  if you want to build a wall enter any button\n else move 'A' character...! ",player1);//asking the player1's next move...
			printf("%c",getch());//scanning the player1's next move...
			ascii=getch();
			if(ascii==80 && a==xx+2 && yy==b) xx+=4;// ASCII code of up & down & left & right button
			else if(ascii==80) xx+=2;
			else if(ascii==75 && b==yy-2 && xx==a) yy-=4;
			else if(ascii==75) yy-=2;
			else if(ascii==77 && b==yy+2 && xx==a) yy+=4;
			else if(ascii==77) yy+=2;
			else if(ascii==72 && a==xx-2 && yy==b) xx-=4;
			else if(ascii==72) xx-=2;
			else{//player chose to build a wall
				if(wallCount1>0){
					do{
    					sw=1;
						clearScrean();
						sleep(400);
						setTextColor(6,0);
						printf("<< %s >>\n",player1);// board's printing
						printf("Remained walls: %d\n",wallCount1);
						Board(walls,k,x,y,a,b);
						BoardPrint(k);
						printf("Remained walls: %d\n",wallCount2);
						printf("<< %s >>\n",player2);// end of board's printing
						printf("\nIf the wall is vertical enter 'V' else enter 'H' : ");
						scanf("%c",&wallDirection);
						clearScrean();
					}while(wallDirection!='H' && wallDirection!='V' && wallDirection!='v' && wallDirection!='h');// we use do...while because wallDirection should be just one of these characters

					if(wallDirection=='v' || wallDirection=='V'){
						do{
							setTextColor(6,0);
							sleep(400);
							printf("<< %s >>\n",player1);// board's printing
							printf("Remained walls: %d\n",wallCount1);
							Board(walls,k,x,y,a,b);
							BoardPrint(k);
							printf("Remained walls: %d\n",wallCount2);
							printf("<< %s >>\n",player2);// end of board's printing
							printf("\nEnter the wall's coordinates : ");
							scanf("%d %d",&h,&v);
							clearScrean();
						}while(h>=n || v>=n || board[2*h-1][2*v-1]!=space || board[2*h+1][2*v-1]!=space);// we use do...while because wall's coordinates should be in the board and should be in the free places
						h=2*h-1;
						v=2*v-1;
						walls[h][v]=wall;
						walls[h+2][v]=wall;
						wallCount1--;
					}

					if(wallDirection=='h' || wallDirection=='H'){
						do{
							setTextColor(6,0);
							sleep(400);
							printf("<< %s >>\n",player1);// board's printing
							printf("Remained walls: %d\n",wallCount1);
							Board(walls,k,x,y,a,b);
							BoardPrint(k);
							printf("Remained walls: %d\n",wallCount2);
							printf("<< %s >>\n",player2);// end of board's printing
							printf("\nEnter the wall's coordinates : ");
							scanf("%d %d",&h,&v);
							clearScrean();
						}while(h>=n || v>=n || board[2*h-1][2*v-1]!=space || board[2*h-1][2*v+1]!=space);// we use do...while because wall's coordinates should be in the board and should be in the free places
						h=2*h-1;
						v=2*v-1;
						walls[h][v]=wall;
						walls[h][v+2]=wall;
						wallCount1--;
					}

					sleep(400);
					printf("<< %s >>\n",player1);// board's printing
					printf("Remained walls: %d\n",wallCount1);
					Board(walls,k,x,y,a,b);
					BoardPrint(k);
					printf("Remained walls: %d\n",wallCount2);
					printf("<< %s >>\n",player2);// end of board's printing
				}
				else{
					clearScrean();
					sleep(400);
					printf("<< %s >>\n",player1);// board's printing
					printf("Remained walls: %d\n",wallCount1);
					Board(walls,k,x,y,a,b);
					BoardPrint(k);
					printf("Remained walls: %d\n",wallCount2);
					printf("<< %s >>\n",player2);// end of board's printing
					printf("\nNo wall has remained for you!\nEnter 'B' to get back... ");
					scanf("%d",&p);
				}
			}
		}while(board[xx][yy]!=' '&& sw==0);
		sw=0;
		x=xx , y=yy;
		if(x==k-2) break;

		do{//player2's next move...
			aa=a , bb=b;
			clearScrean();
			sleep(400);
			setTextColor(11,0);
			printf("<< %s >>\n",player1);// board's printing
			printf("Remained walls: %d\n",wallCount1);
			Board(walls,k,x,y,a,b);
			BoardPrint(k);
			printf("Remained walls: %d\n",wallCount2);
			printf("<< %s >>\n",player2);// end of board's printing
			printf("\n %s if you want to build a wall enter any button\n else move 'B' character...! ",player2);//asking the player1's next move...
			printf("%c",getch());
			ascii=getch();//scanning the player1's next move...
			if(ascii==80 && x==aa+2 && bb==y) aa+=4;// ASCII code of up & down & left & right button
			else if(ascii==80) aa+=2;
			else if(ascii==75 && bb==y-2 && aa==x) bb-=4;
			else if(ascii==75) bb-=2;
			else if(ascii==77 && y==bb+2 && x==aa) bb+=4;
			else if(ascii==77) bb+=2;
			else if(ascii==72 && x==aa-2 && y==bb) aa-=4;
			else if(ascii==72) aa-=2;
			else{//player chose to build a wall
				if(wallCount2>0){
					do{
    					sw=1;
						clearScrean();
						setTextColor(11,0);
						sleep(400);
						printf("<< %s >>\n",player1);// board's printing
						printf("Remained walls: %d\n",wallCount1);
						Board(walls,k,x,y,a,b);
						BoardPrint(k);
						printf("Remained walls: %d\n",wallCount2);
						printf("<< %s >>\n",player2);// end of board's printing
						printf("\nIf the wall is vertical enter 'V' else enter 'H' : ");
						scanf("%c",&wallDirection);
						clearScrean();
					}while(wallDirection!='H' && wallDirection!='V' && wallDirection!='v' && wallDirection!='h');// we use do...while because wallDirection should be just one of these characters

					if(wallDirection=='v' || wallDirection=='V'){
						do{
							setTextColor(11,0);
							sleep(400);
							printf("<< %s >>\n",player1);// board's printing
							printf("Remained walls: %d\n",wallCount1);
							Board(walls,k,x,y,a,b);
							BoardPrint(k);
							printf("Remained walls: %d\n",wallCount2);
							printf("<< %s >>\n",player2);// end of board's printing
							printf("\nEnter the wall's coordinates : ");
							scanf("%d %d",&h,&v);
							clearScrean();
						}while(h>=n || v>=n || board[2*h-1][2*v-1]!=space || board[2*h+1][2*v-1]!=space);// we use do...while because wall's coordinates should be in the board and should be in the free places
						h=2*h-1;
						v=2*v-1;
						walls[h][v]=wall;
						walls[h+2][v]=wall;
						wallCount2--;
					}

					if(wallDirection=='h' || wallDirection=='H'){
						do{
							setTextColor(11,0);
							sleep(400);
							printf("<< %s >>\n",player1);// board's printing
							printf("Remained walls: %d\n",wallCount1);
							Board(walls,k,x,y,a,b);
							BoardPrint(k);
							printf("Remained walls: %d\n",wallCount2);
							printf("<< %s >>\n",player2);// end of board's printing
							printf("\nEnter the wall's coordinates : ");
							scanf("%d %d",&h,&v);
							clearScrean();
						}while(h>=n || v>=n || board[2*h-1][2*v-1]!=space || board[2*h-1][2*v+1]!=space);// we use do...while because wall's coordinates should be in the board and should be in the free places
						h=2*h-1;
						v=2*v-1;
						walls[h][v]=wall;
						walls[h][v+2]=wall;
						wallCount2--;
					}

					sleep(400);
					printf("<< %s >>\n",player1);// board's printing
					printf("Remained walls: %d\n",wallCount1);
					Board(walls,k,x,y,a,b);
					BoardPrint(k);
					printf("Remained walls: %d\n",wallCount2);
					printf("<< %s >>\n",player2);// end of board's printing
				}
				else {
					clearScrean();
					sleep(400);
					printf("<< %s >>\n",player1);// board's printing
					printf("Remained walls: %d\n",wallCount1);
					Board(walls,k,x,y,a,b);
					BoardPrint(k);
					printf("Remained walls: %d\n",wallCount2);
					printf("<< %s >>\n",player2);// end of board's printing
					printf("\nNo wall has remained for you!\nEnter 'B' to get back... ");
					scanf("%d",&p);
				}
			}
		}while(board[aa][bb]!=' ' && sw==0);
		sw=0;
		a=aa , b=bb;

	}while(a!=1 && x!=k-2);

	clearScrean();
	sleep(500);
	setTextColor(15,0);
	printf("<< %s >>\n",player1);// board's printing
	printf("Remained walls: %d\n",wallCount1);
	Board(walls,k,x,y,a,b);
	BoardPrint(k);
	printf("Remained walls: %d\n",wallCount2);
	printf("<< %s >>\n",player2);// end of board's printing
	//determining winner
	if(x==k-2) printf("\nThe winner is << %s >>...!",player1);
	else if(a==1) printf("\nThe winner is << %s >>...!",player2);
}