/*---------------------------------------------------------------------------------

	$Id: puzstar1.h $

	Basic external definitions to use the supporting routines and data

---------------------------------------------------------------------------------*/

extern char matrix[10][8];

extern void initialize_matrix(int num_colors);

extern unsigned char select_blocks();
extern unsigned char select_columns();
extern void move_blocks();
extern void move_columns();

extern int recursive_markup(int row, int column, unsigned char value);
extern void remove_marks(int unmark);

