#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

#define ROW 3
#define COL 3
#define WIN 3

void set(char *board);
void print(char *board);
void move(void);
void check (void);


int main(void)
{
	// define variables to be used throughout game
	char *board[ROW][COL];
	board = malloc(sizeof(*board));
	
	bool *game_over;
	game_over = malloc(sizeof(bool));
	*game_over = false;
	
	int *total_moves;
	total_moves = malloc(sizeof(int));
	*total_moves = 0;
	
	char *player;
	player = malloc(sizeof(char));
	*player = 'X';
	
	//set board
   set(board);

	//print board
	print(board);			
	
	while (game_over == false)
	{						
		// player selects move
		move(board, player, total_moves);
		
		//print board
		print(board);	
		
		// check for win or draw
		check(board, game_over, total_moves);

		// switch players
		if (player == 'X') {
			player = 'O';
		}
		else {
			player = 'X';
		};
	}
   
	// unload variables
	free(board);
	free(game_over);
	free(total_moves);
	free(player);
	
}

// sets board
void set(char *board)
{
   for (int row_loop = 0; row_loop < ROW; row_loop++)
   {	   
	   for (int col_loop = 0; col_loop < COL; col_loop++)
	   {
			*board[row_loop][col_loop] = ' ';
	   };
   };
}

// prints board
void print(char *board)
{
	// add space from previous turn
	printf("\n\n\n\n");
	
	// print each row
	for (int row_loop = 0; row_loop < ROW; row_loop++)
	{	   
	   // print each column in each row
		for (int col_loop = 0; col_loop < COL; col_loop++)
	   {
	   
		   printf(" %c ", *board[row_loop][col_loop]);		   
			// add bar between columns and return for each row
			if (col_loop != COL)
		   {
			   printf("|");
		   }
			else
			{
				printf("\n");
			}
	   };
	   // add bar between rows
		if (row_loop != ROW)
	   {
		   for (int col_loop = 1; col_loop < COL; col_loop++)
			{
				printf("----");
			}
			printf("---\n");
	   }
	};
}


void move(char *board, *player, int *total_moves)
{
	printf("\nPLAYER %c's TURN\n", *player);
	
	int row_selection;
	int col_selection;
	bool valid_input = true;
	
	do
	{
		// prompt user for row
		printf("\nEnter row:\n");
		scanf("%i", &row_selection);
	
		// check row input TODO validate input is int
		while (row_selection < 1 || row_selection > ROW)
		{
			printf("Invalid row. Please enter a value between 1 and %i:\n", ROW);
			scanf("%i", &row_selection);
		};
	
		// prompt user for column
		printf("\nEnter column:\n");
		int col_scan_check = scanf("%i", &col_selection);
	
		// check column input TODO validate input is int
		while (col_selection < 1 || col_selection > COL)
		{
			printf("Invalid col. Please enter a value between 1 and %i:\n", COL);
			scanf("%i", &col_selection);
		};
	
		// check if space is taken on board
		if (board[row_selection][col_selection] == ' ')
		{
			*board[row_selection][col_selection] = *player;
			valid_input = true;
		}	
		else
		{
			printf("This space is already taken. Please try again.");
			valid_input = false;
		};				
	} while (valid_input == false);
	
	// increase number of moves
	*total_moves++;
			
}

void check (int *total_moves, char *player)
{
	// save some time avoiding checks before game can be won
	if (*total_moves < WIN*2){	
		return;
	};
	
	
	// check for draw
	if (*total_moves == ROW * COL)
	{
		printf("\nGAME OVER: PLAYER %c HAS FORCED A DRAW\n\n", *player);
		*game_over = true;
	};
}
