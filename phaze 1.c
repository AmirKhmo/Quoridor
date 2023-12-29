# include <stdio.h>


#define edge '|'
#define space ' '
#define wall '#'
#define Player1 '1'
#define Player2 '2'


char board[100][100];


void clearScrean(){
	system("cls");
}


void Board(char walls[][100],int n,int x,int y,int a,int b){
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


void main ()
{
	int n,k;
	int i,j,z;
	int wall1,wall2;
	int x=-1,y=-1,a=-1,b=-1;
	int o,p,u;
	char walls[100][100];
	char wallDirection;

	do{
		printf("Please enter dimension : ");
		scanf("%d",&n);
		clearScrean();
	}while(n<=3);
	k=2*n-1;


	do{
		x=-1 , y=-1;
		Board(walls,k,x,y,a,b);
		for(i=0 ; i<k ; i++){
			for(j=0 ; j<k ; j++){
				printf("%c",board[i][j]);
			}
			printf("\n");
		}
		printf("Please enter Player1's coordinates : ");
		scanf("%d %d",&x,&y);
		clearScrean();
	}while(x>=n || y>=n);
	x=2*x-1;
	y=2*y-1;
	clearScrean();


	do{
		a=-1 , b=-1;
		Board(walls,k,x,y,a,b);
		for(i=0 ; i<k ; i++){
			for(j=0 ; j<k ; j++){
				printf("%c",board[i][j]);
			}
			printf("\n");
		}
		printf("Please enter Player2's coordinates : ");
		scanf("%d %d",&a,&b);
		clearScrean();
	}while(a>=n || b>=n);
	a=2*a-1;
	b=2*b-1;
	clearScrean();


	do{
		clearScrean();
		Board(walls,k,x,y,a,b);
		for(i=0 ; i<k ; i++){
			for(j=0 ; j<k ; j++){
				printf("%c",board[i][j]);
			}
			printf("\n");
		}
		printf("How many walls does player1 have? ");
		scanf("%d",&wall1);
		clearScrean();
	}while(wall1>=n*n/2);

	for(z=1;z<=wall1;z++){
		do{
			clearScrean();
			Board(walls,k,x,y,a,b);
			for(i=0 ; i<k ; i++){
				for(j=0 ; j<k ; j++){
					printf("%c",board[i][j]);
				}
				printf("\n");
			}
			printf("If %d th wall is vertical enter 'V' else enter 'H' : ",z);
			scanf("%c",&wallDirection);
			clearScrean();
		}while(wallDirection!='H' && wallDirection!='V' && wallDirection!='v' && wallDirection!='h');

		if(wallDirection=='v' || wallDirection=='V'){
			do{
				Board(walls,k,x,y,a,b);
				for(i=0 ; i<k ; i++){
					for(j=0 ; j<k ; j++){
					printf("%c",board[i][j]);
					}
					printf("\n");
				}
				printf("Enter %d th wall's coordinates : ",z);
				scanf("%d %d %d",&o,&p,&u);
				clearScrean();
			}while(o>=n || p>=n || u>=n);
			o=2*o-1;
			u=2*u-1;
			p=2*p-1;
			walls[p][o]=wall;
			walls[u][o]=wall;
		}

		if(wallDirection=='h' || wallDirection=='H'){
			do{
				Board(walls,k,x,y,a,b);
				for(i=0 ; i<k ; i++){
					for(j=0 ; j<k ; j++){
					printf("%c",board[i][j]);
					}
					printf("\n");
				}
				printf("Enter %d th wall's coordinates : ",z);
				scanf("%d %d %d",&o,&p,&u);
				clearScrean();
			}while(o>=n || p>=n || u>=n);
			o=2*o-1;
			u=2*u-1;
			p=2*p-1;
			walls[o][p]=wall;
			walls[o][u]=wall;
		}

		Board(walls,k,x,y,a,b);
			for(i=0 ; i<k ; i++){
				for(j=0 ; j<k ; j++){
					printf("%c",board[i][j]);
				}
				printf("\n");
			}
	}


	do{
		clearScrean();
		Board(walls,k,x,y,a,b);
		for(i=0 ; i<k ; i++){
			for(j=0 ; j<k ; j++){
				printf("%c",board[i][j]);
			}
			printf("\n");
		}
		printf("How many walls does player2 have? ");
		scanf("%d",&wall2);
		clearScrean();
	}while(wall2>=n*n/2);

	for(z=1;z<=wall2;z++){
		do{
			clearScrean();
			Board(walls,k,x,y,a,b);
			for(i=0 ; i<k ; i++){
				for(j=0 ; j<k ; j++){
					printf("%c",board[i][j]);
				}
				printf("\n");
			}
			printf("If %dth wall is vertical enter 'V' else enter 'H' : ",z);
			scanf(" %c",&wallDirection);
			clearScrean();
		}while(wallDirection=='H' && wallDirection!='V' && wallDirection!='v' && wallDirection!='h');

		if(wallDirection=='v' || wallDirection=='V'){
			do{
				Board(walls,k,x,y,a,b);
				for(i=0 ; i<k ; i++){
					for(j=0 ; j<k ; j++){
					printf("%c",board[i][j]);
					}
					printf("\n");
				}
				printf("Enter %d th wall's coordinates : ",z);
				scanf("%d %d %d",&o,&p,&u);
				clearScrean();
			}while(o>=n || p>=n || u>=n);
			o=2*o-1;
			u=2*u-1;
			p=2*p-1;
			walls[p][o]=wall;
			walls[u][o]=wall;
		}

		if(wallDirection=='h' || wallDirection=='H'){
			do{
				Board(walls,k,x,y,a,b);
				for(i=0 ; i<k ; i++){
					for(j=0 ; j<k ; j++){
					printf("%c",board[i][j]);
					}
					printf("\n");
				}
				printf("Enter %d th wall's coordinates : ",z);
				scanf("%d %d %d",&o,&p,&u);
				clearScrean();
			}while(o>=n || p>=n || u>=n);
			o=2*o-1;
			u=2*u-1;
			p=2*p-1;
			walls[o][p]=wall;
			walls[o][u]=wall;
		}

		Board(walls,k,x,y,a,b);
			for(i=0 ; i<k ; i++){
				for(j=0 ; j<k ; j++){
					printf("%c",board[i][j]);
				}
				printf("\n");
			}
	}

}
