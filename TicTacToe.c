#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

// indexed to zero
#define ROW 2
#define COL 2
#define WIN 2

void set(char **board);
void print(char **board);
void move(char **board, char *player, int *total_moves);
void check (char **board, int *total_moves, char *player, bool *game_over);
void find_line (char **board, int row_loop, int col_loop, char *player, bool *game_over, int line_length, int row_change, int col_change);



int main(void)
{
	// define variables to be used throughout game
	char **board;
	board = malloc(sizeof(char*) * (ROW+1));
	for (int row_loop = 0; row_loop <= ROW; row_loop++)
	{
		board[row_loop] = malloc(sizeof(char*)*(COL+1));
	};
	
		
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
	
	while (*game_over == false)
	{						
		// player selects move
		move(board, player, total_moves);
		
		//print board
		print(board);	
		
		// check for win or draw
		check(board, total_moves, player, game_over);
		
		// switch players
		if (*player == 'X') {
			*player = 'O';
		}
		else {
			*player = 'X';
		};
	}
   
	// unload variables
	free(board);
	free(game_over);
	free(total_moves);
	free(player);
	
}

// sets board
void set(char **board)
{
   for (int row_loop = 0; row_loop <= ROW; row_loop++)
   {	   
	   for (int col_loop = 0; col_loop <= COL; col_loop++)
	   {
			board[row_loop][col_loop] = ' ';
	   };
   };
}

// prints board
void print(char **board)
{
	// add space from previous turn
	printf("\n\n\n\n");
	
	// print each row
	for (int row_loop = 0; row_loop <= ROW; row_loop++)
	{	   
	   // print each column in each row
		for (int col_loop = 0; col_loop <= COL; col_loop++)
	   {
	   
		   // print value
			printf(" %c ", board[row_loop][col_loop]);		   
			
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
		   for (int col_loop = 0; col_loop < COL; col_loop++)
			{
				printf("----");
			}
			printf("---\n");
	   }
	};
}


void move(char **board, char *player, int *total_moves)
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
		
		// index to zero
		row_selection--;
		
			
		// check row input TODO validate input is int
		while (row_selection < 0 || row_selection > ROW)
		{
			printf("Invalid row. Please enter a value between 1 and %i:\n", ROW+1);
			scanf("%i", &row_selection);
			row_selection--;
		};
	
		// prompt user for column
		printf("\nEnter column:\n");
		scanf("%i", &col_selection);
		
		//index to zero
		col_selection--;
	
		// check column input TODO validate input is int
		while (col_selection < 0 || col_selection > COL)
		{
			printf("Invalid col. Please enter a value between 1 and %i:\n", COL+1);
			scanf("%i", &col_selection);
			col_selection--;
		};
	
		// check if space is taken on board
		if (board[row_selection][col_selection] == ' ')
		{
			board[row_selection][col_selection] = *player;
			valid_input = true;
		}	
		else
		{
			printf("\nThis space is already taken. Please try again.\n");
			valid_input = false;
		};				
	} while (valid_input == false);
	
	// increase number of moves
	*total_moves = *total_moves + 1;
			
}

void check (char **board, int *total_moves, char *player, bool *game_over)
{	
	// save some time avoiding checks before game can be won
	if (*total_moves <= WIN*2){	
		return;
	}
	// check board for winning line
	else
	{
		for (int row_loop = 0; row_loop <= ROW; row_loop++)
		{
			for(int col_loop = 0; col_loop <= COL; col_loop++)
			{
				if (board[row_loop][col_loop] == *player)
				{
					
					// check for four possible winning line directions
					if ((ROW - row_loop) >= WIN)
					{
						find_line(board, row_loop, col_loop, player, game_over, 0, 1, 0);
					}
					if ((COL - col_loop) >= WIN)
					{
						find_line(board, row_loop, col_loop, player, game_over, 0, 0, 1);
					}
					if ((ROW - row_loop) >= WIN && (COL - col_loop) >= WIN)
					{
						find_line(board, row_loop, col_loop, player, game_over, 0, 1, 1);
					}
					if (col_loop >= WIN && (ROW - row_loop) >= WIN)
					{
						find_line(board, row_loop, col_loop, player, game_over, 0, 1, -1);
					}		
				}	
			}
		}
	};
		
	// check for draw
	if (*total_moves == (ROW+1) * (COL+1))
	{
		printf("\nGAME OVER: PLAYER %c HAS FORCED A DRAW\n\n", *player);
		*game_over = true;
	};
}

void find_line (char **board, int row_loop, int col_loop, char *player, bool *game_over, int line_length, int row_change, int col_change)
{
	row_loop = row_loop + row_change;
	col_loop = col_loop + col_change;
	
	if (board[row_loop][col_loop] == *player)
	{
		line_length++;
		
		if (line_length == WIN)
		{
			printf("\nGAME OVER: PLAYER %c WINS!!!\n", *player);
			*game_over = true;
		}
		else
		{
			printf("%i", line_length);
			find_line(board, row_loop, col_loop, player, game_over, line_length, row_change, col_change);
		}
	}	
}