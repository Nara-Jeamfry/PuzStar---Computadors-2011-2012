/*---------------------------------------------------------------------------------

	$Id: main1.c,v 1.0 2011-09-06 Santiago Romani $

	Main program skeleton for milestone 1 of the PuzzStar project

---------------------------------------------------------------------------------*/
#include <nds.h>
#include <stdio.h>
#include <puzstar1.h>

	/* print at using ansi escape sequence \x1b[line;columnH  */
void print_matrix()
{	
	int i, j, value, color;
	
	for (i = 0; i < 10; i++)		/* for all rows */
	{
		for (j = 0; j < 8; j++)		/* for all columns */
		{
			color = value = matrix[i][j];	/* obtain the value of the element */
			if (value > 127)
			{								/* for negative char values */
				color = 256 - value;		/* obtain the color absolute value */
				value = value-256; 			/* get the negative int value */
			}
			printf("\x1b[%dm", 30+color);
			printf("\x1b[%d;%dH %d", (i*2+2), (j*2), value);
		}
		printf("\x1b[%d;%dH ", (i*2+2), (j*2));	/* erase the last column */
	}
	printf("\x1b[0m");
}

void my_delay(int dsecs)
{	
	int i, j;
	
	for (i = 0; i < dsecs; i++)		/* for each tenth second */
		for (j = 0; j < 6; j++)		/* wait for 6 vertical blanks */
			swiWaitForVBlank();
}

void move_elements()
{
	while(select_blocks()==1)
	{
		my_delay(4);
		move_blocks();
	}
	while(select_columns()==1)
	{
		my_delay(6);
		move_columns();
	}
	
	/* move blocks and columns until no more movements */

}


int main(void) {

	touchPosition	thisXY;
	int dx, dy;
	int block;
	int num_marks = 0;

	initialize_matrix(3);	/* init for 3 block types */

	consoleDemoInit();

	printf("PuzzStar1 (master branch)\n");
	print_matrix();
	
	do
	{
		move_elements();
		swiWaitForVBlank();
		scanKeys();
		if (keysHeld() & KEY_TOUCH)
		{
			touchRead(&thisXY);
			
			dx=thisXY.px;
			dy=thisXY.py;
			
			block=matrix[dx, dy]; /* we read the color of the block */
			
			
			
			if(num_marks==0)					/* if we have 0 marked blocks */
				num_marks=recursive_markup(dx,dy, block);		/* we mark the ones we just clicked */
			else
				if(matrix[dx, dy] < 0)				/* if not, we see the position */
				{
					remove_marks(0);				/* if we clicked the same blocks marked, we remove them */
				}
				else
					remove_marks(1);				/* if we clicked anywere else, we unmark them */
			
			/* process touched positions */
			
		}
		while (keysHeld() & KEY_TOUCH)
		{
			scanKeys();
			swiWaitForVBlank();
		}
	} while (1);		/* infinite loop */

	return 0;		/* it will never return */
}

