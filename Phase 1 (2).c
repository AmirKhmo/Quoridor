# include <stdio.h>
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
	int i,j,z;
	int wall1,wall2; // count of each player's walls
	int x=-1,y=-1,a=-1,b=-1;// coordinates of player1 and player2's character which will be scanned in next lines
	int v,h;
	char walls[100][100];// an array to put # as wall and match it with board
	char wallDirection;// vertical or horizontal

	do{//receive 'n' as dimention of the board which will be n*n
		sleep(600);
		printf("Please enter dimension : ");
		scanf("%d",&n);
		clearScrean();
	}while(n<=3);
	k=2*n+1;

//when player1 should enter sth , Board's color will be yellow
//when player2 should enter sth , Board's color will be blue

	do{
		x=-1 , y=-1;
		sleep(400);
		setTextColor(6,0);
		Board(walls,k,x,y,a,b);// board's printing
		BoardPrint(k);
		printf("Please enter Player1's coordinates : ");
		scanf("%d %d",&x,&y);
		clearScrean();
	}while(x>n || y>n);// we use do...while because x,y shouldn't be more than n
	x=2*x-1;
	y=2*y-1;
	clearScrean();


	do{
		a=-1 , b=-1;
		sleep(400);
		setTextColor(11,0);
		Board(walls,k,x,y,a,b);// board's printing
		BoardPrint(k);
		printf("Please enter Player2's coordinates : ");
		scanf("%d %d",&a,&b);
		clearScrean();
	}while(a>n || b>n);// we use do...while because a,b shouldn't be more than n
	a=2*a-1;
	b=2*b-1;
	clearScrean();


	do{
		clearScrean();
		sleep(400);
		setTextColor(6,0);
		Board(walls,k,x,y,a,b);// board's printing
		BoardPrint(k);
		printf("How many walls does player1 have? ");
		scanf("%d",&wall1);
		clearScrean();
	}while(wall1>=n*n/2);// we use do...while because wall1 shouldn't be more than n*n/2

	for(z=1;z<=wall1;z++){
		do{
			clearScrean();
			setTextColor(6,0);
			Board(walls,k,x,y,a,b);// board's printing
			BoardPrint(k);
			printf("If %d th wall is vertical enter 'V' else enter 'H' : ",z);
			scanf("%c",&wallDirection);
			clearScrean();
		}while(wallDirection!='H' && wallDirection!='V' && wallDirection!='v' && wallDirection!='h');// we use do...while because wallDirection should be just one of these characters

		if(wallDirection=='v' || wallDirection=='V'){
			do{
				setTextColor(6,0);
				Board(walls,k,x,y,a,b);// board's printing
				BoardPrint(k);
				printf("Enter %d th wall's coordinates : ",z);
				scanf("%d %d",&h,&v);
				clearScrean();
			}while(h>=n || v>=n || board[2*h-1][2*v-1]!=space || board[2*h+1][2*v-1]!=space);// we use do...while because wall's coordinates should be in the board and should be in the free places
			h=2*h-1;
			v=2*v-1;
			walls[h][v]=wall;
			walls[h+2][v]=wall;
		}

		if(wallDirection=='h' || wallDirection=='H'){
			do{
				setTextColor(6,0);
				Board(walls,k,x,y,a,b);// board's printing
				BoardPrint(k);
				printf("Enter %d th wall's coordinates : ",z);
				scanf("%d %d",&h,&v);
				clearScrean();
			}while(h>=n || v>=n || board[2*h-1][2*v-1]!=space || board[2*h-1][2*v+1]!=space);// we use do...while because wall's coordinates should be in the board and should be in the free places
			h=2*h-1;
			v=2*v-1;
			walls[h][v]=wall;
			walls[h][v+2]=wall;
		}

		Board(walls,k,x,y,a,b);// board's printing
		BoardPrint(k);
	}


	do{
		clearScrean();
		sleep(400);
		setTextColor(12,0);
		Board(walls,k,x,y,a,b);// board's printing
		BoardPrint(k);
		printf("How many walls does player2 have? ");
		scanf("%d",&wall2);
		clearScrean();
	}while(wall2>=n*n/2);// we use do...while because wall2 shouldn't be more than n*n/2

	for(z=1;z<=wall2;z++){
		do{
			clearScrean();
			setTextColor(12,0);
			Board(walls,k,x,y,a,b);// board's printing
			BoardPrint(k);
			printf("If %dth wall is vertical enter 'V' else enter 'H' : ",z);
			scanf(" %c",&wallDirection);
			clearScrean();
		}while(wallDirection=='H' && wallDirection!='V' && wallDirection!='v' && wallDirection!='h');// we use do...while because wallDirection should be just one of these characters

		if(wallDirection=='v' || wallDirection=='V'){
			do{
				setTextColor(12,0);
				Board(walls,k,x,y,a,b);// board's printing
				BoardPrint(k);
				printf("Enter %d th wall's coordinates : ",z);
				scanf("%d %d",&h,&v);
				clearScrean();
			}while(h>=n || v>=n || board[2*h-1][2*v-1]!=space || board[2*h+1][2*v-1]!=space);// we use do...while because wall's coordinates should be in the board and should be in the free places
			h=2*h-1;
			v=2*v-1;
			walls[h][v]=wall;
			walls[h+2][v]=wall;
		}

		if(wallDirection=='h' || wallDirection=='H'){
			do{
				setTextColor(12,0);
				Board(walls,k,x,y,a,b);// board's printing
				BoardPrint(k);
				printf("Enter %d th wall's coordinates : ",z);
				scanf("%d %d",&h,&v);
				clearScrean();
			}while(h>=n || v>=n || board[2*h-1][2*v-1]!=space || board[2*h-1][2*v+1]!=space);// we use do...while because wall's coordinates should be in the board and should be in the free places
			h=2*h-1;
			v=2*v-1;
			walls[h][v]=wall;
			walls[h][v+2]=wall;
		}

		sleep(500);
		setTextColor(15,0);
		Board(walls,k,x,y,a,b);// board's printing
    	BoardPrint(k);
	}
}