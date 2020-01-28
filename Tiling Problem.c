#include <stdio.h>

#define side 16 //Square side is always 2 to the nth power.

typedef struct
{
 	int i;
 	int j;
 } PositionsT;

void PlaceTile(int tilecounts[][side], int posi, int posj, PositionsT square, int tilecount);
void DivideFloor(int Floor[][side], int step, PositionsT square, int tilecount, int begin_i, int begin_j);
PositionsT FindSquare(int Floor[][side], int begin_i, int begin_j, int searchlen);

int main()
{
	int Floor[side][side] = {0};
	PositionsT square;
	int tilecount = 0;
	int i, j, step;

    printf("Please enter the position of the special square in a %dx%d floor.\n",side,side);
	do {
    printf("Row: ");
	scanf("%d", &square.i);
	if (square.i < 0 || square.i >= side){
        printf("Error! Must be a number between 0 and %d!\n\n", side - 1);
	}
	} while(square.i < 0 || square.i >= side);

	do {
    printf("Column: ");
	scanf("%d", &square.j);
	if (square.j < 0 || square.j >= side){
        printf("Error! Must be a number between 0 and %d!\n\n", side - 1);
	}
	} while(square.j < 0 || square.j >= side);

	Floor[square.i][square.j] = -1; //The special square is symbolized with -1.
	step = side/2;

	if (step != 0) {
		DivideFloor(Floor, step, square, tilecount, 0, 0);
		tilecount = side * side / 3;
	}

	printf("\nThis is the floor:\n\n");
	for(i = 0; i < side; i++)
	{
		for(j = 0; j < side; j++)
		{
		   printf("%4.d", Floor[i][j]);
		}
		printf("\n");
	}
	printf("\nPlaced tiles: %d.\n", tilecount);

	return 0;
}

//Divides the floor into 4 parts each time, moving from part to part and repeating the procedure.
void DivideFloor(int Floor[][side], int step, PositionsT square, int tilecount, int begin_i, int begin_j)
{
	int i, j;
	PositionsT divide;

	divide.i = begin_i + step;
	divide.j = begin_j + step;


    tilecount++;
	PlaceTile(Floor, divide.i, divide.j, square,  tilecount);

	if (step > 1) {
		for(i = begin_i; i < begin_i + step * 2; i += step)
		{
			for(j = begin_j; j < begin_j + step * 2; j += step)
			{
				if(step > 2)
				{
					square = FindSquare(Floor, i, j, step);
					DivideFloor(Floor, step/2, square, tilecount, i, j);
					tilecount += (step * step) / 3;
				}
				else
				{
					square = FindSquare(Floor, i, j, 2);
					tilecount++;
					PlaceTile(Floor, i+1, j+1, square,  tilecount);
				}
			}
		}
	}
}

//Uses the special square as a reference and places a tile to the 3 parts of the given floor that it isn't in.
void PlaceTile(int Floor[][side], int posi, int posj, PositionsT square, int tilecount)
{
	if (square.i < posi)
    {
		if (square.j < posj) {
			Floor[posi-1][posj] = Floor[posi][posj-1] = Floor[posi][posj] = tilecount;
		}
		else {
			Floor[posi][posj] = Floor[posi][posj-1] = Floor[posi-1][posj-1] = tilecount;
		}
	}
	else
	{
		if (square.j < posj) {
			Floor[posi-1][posj] = Floor[posi-1][posj-1] = Floor[posi][posj] = tilecount;
		}
		else {
			Floor[posi-1][posj] = Floor[posi][posj-1] = Floor[posi-1][posj-1] = tilecount;
		}
	}
}

//Scans the given floor, finds the position of the tile's part that has been placed in it and makes it the next special square.
PositionsT FindSquare(int Floor[][side], int begin_i, int begin_j, int searchlen)
{
	PositionsT square;
	int i, j, found = 0;

    i = begin_i;
	while((found == 0) && (i < begin_i + searchlen)){
	    j = begin_j;
		while((found == 0) && (j < begin_j + searchlen)){
			if (Floor[i][j] != 0){
				square.i = i;
				square.j = j;
				found = 1;
			}
			j++;
		}
		i++;
	}
	return square;
}
