/*
 * TicTacToe game. Uses variable board and win settings, so similar games such as Connect Four are possible.
 *
 * Some questions:
 * — How to validate scanf input is an int? There seem to be a few theories online, but nearly all looked very messy
 *   and a lot of posts acknowledged that they were imperfect solutions so I'm probably overlooking a clearer solution.
 * — Did it make sense to use pointers? I know global variables are bad form, but the code would have looked considerably
 *   cleaner without pointers.
 * — Is there a better way to check for a win besides recurive equations? It seems overly complicated (TicTacToe only has 8)
 *   possible win formations), but I'm not sure it's avoidable if larger boards / longer winning lines are specified.
 */


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

// indexed to zero
#define ROW 2
#define COL 2
#define WIN 2

// declaring functions to use within main
void set(char **board);
void print(char **board);
void move(char **board, char *player, int *total_moves);
void check (char **board, int *total_moves, char *player, bool *game_over);
void find_line (char **board, int line_row, int line_col, char *player, bool *game_over, int line_length, int row_change, int col_change);


int main(void)
{	
	
	// define variables to be used throughout game
	// board pointer
	char **board;
	board = malloc(sizeof(char*) * (ROW+1));
	for (int malloc_row_loop = 0; malloc_row_loop <= ROW; malloc_row_loop++)
	{
		board[malloc_row_loop] = malloc(sizeof(char*)*(COL+1));
	};
	
	// true if someone has won or no more open spots remain	
	bool *game_over;
	game_over = malloc(sizeof(bool));
	*game_over = false;
	
	// keeps track of number of moves in order to know if no more open spots remain
	int *total_moves;
	total_moves = malloc(sizeof(int));
	*total_moves = 0;
	
	// switches between X and O
	char *player;
	player = malloc(sizeof(char));
	*player = 'X';
	
	//sets board to have all blank spaces
   set(board);

	//print board
	print(board);			
	
	// gameplay. ends when *game_over == true
	while (*game_over == false)
	{						
		// player selects move
		move(board, player, total_moves);
		
		//print board with new move included
		print(board);	
		
		// check for win or draw. prints result if win or draw.
		check(board, total_moves, player, game_over);
		
		// switches players at end of turn
		if (*player == 'X') {
			*player = 'O';
		}
		else {
			*player = 'X';
		};
	};
   
	// unload variables
	free(board);
	free(game_over);
	free(total_moves);
	free(player);
	
};

// sets board to be filled with spaces
void set(char **board)
{
   for (int set_row_loop = 0; set_row_loop <= ROW; set_row_loop++)
   {	   
	   for (int set_col_loop = 0; set_col_loop <= COL; set_col_loop++)
	   {
			board[set_row_loop][set_col_loop] = ' ';
	   };
   };
};

// prints board
void print(char **board)
{
	// add a few spaces to separate turns
	printf("\n\n\n\n");
	
	// print each row
	for (int print_row_loop = 0; print_row_loop <= ROW; print_row_loop++)
	{	   
	   // print each column in each row
		for (int print_col_loop = 0; print_col_loop <= COL; print_col_loop++)
	   {
	   
		   // print value in space
			printf(" %c ", board[print_row_loop][print_col_loop]);		   
			
			// add bar between columns and new line for each row
			if (print_col_loop != COL)
		   {
			   printf("|");
		   }
			else
			{
				printf("\n");
			};
	   };
		
	   // add bar between rows
		if (print_row_loop != ROW)
	   {
		   for (int print_col_loop = 0; print_col_loop < COL; print_col_loop++)
			{
				printf("----");
			}
			printf("---\n");
	   };
	};
};


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
		
			
		// check row input TODO WARNING: THIS ASSUMES INPUT IS AN INT
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
	
		// check column input TODO WARNING: THIS ASSUMES INPUT IS AN INT
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
		for (int check_row_loop = 0; check_row_loop <= ROW; check_row_loop++)
		{
			for(int check_col_loop = 0; check_col_loop <= COL; check_col_loop++)
			{
				// only check spaces used by the current player
				if (board[check_row_loop][check_col_loop] == *player)
				{				
					/* checks for four possible winning line directions. 
					 * if-statements check if there is enough room between given space
					 * and the edge of the board for the type of line specified. 
					 */
					
					if ((ROW - check_row_loop) >= WIN)
					{
						// check for vertical line (movng down)
						find_line(board, check_row_loop, check_col_loop, player, game_over, 0, 1, 0);
					};
					if ((COL - check_col_loop) >= WIN)
					{
						// check for horizontal line (moving right)
						find_line(board, check_row_loop, check_col_loop, player, game_over, 0, 0, 1);
					};
					if ((ROW - check_row_loop) >= WIN && (COL - check_col_loop) >= WIN)
					{
						// check for diagonal line (moving down and right)
						find_line(board, check_row_loop, check_col_loop, player, game_over, 0, 1, 1);
					};
					if (check_col_loop >= WIN && (ROW - check_row_loop) >= WIN)
					{
						// check for diagonal line (moving down and left)
						find_line(board, check_row_loop, check_col_loop, player, game_over, 0, 1, -1);
					};		
				};	
			};
		};
	};
		
	// check for draw
	if (*total_moves == (ROW+1) * (COL+1))
	{
		printf("\nGAME OVER: PLAYER %c HAS FORCED A DRAW\n\n", *player);
		*game_over = true;
	};
};

void find_line (char **board, int line_row, int line_col, char *player, bool *game_over, int line_length, int row_change, int col_change)
{
	// updates space to check depending on if line is expected to be horitzontal, vertical, or diagonal
	line_row = line_row + row_change;
	line_col = line_col + col_change;
	
	// only continue process if new space belongs to current player
	if (board[line_row][line_col] == *player)
	{
		// update length of current line
		line_length++;
		
		// if new line length is equal to the WIN amount, declare a winner and end the game
		if (line_length == WIN)
		{
			printf("\nGAME OVER: PLAYER %c WINS!!!\n", *player);
			*game_over = true;
		}
		// if new space is taken by current player but line isn't long enough yet, check the next space in the line
		else
		{
			find_line(board, line_row, line_col, player, game_over, line_length, row_change, col_change);
		};
	};	
};