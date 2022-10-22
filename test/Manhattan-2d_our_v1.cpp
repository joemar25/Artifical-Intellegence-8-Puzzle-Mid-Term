#include <iostream>

int *findLoc(int row, int col, int old_array[][3], int new_array[][3])
{
	static int location[2];
	int temp = 0;
	int goal = 0;

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			temp = new_array[i][j];
			goal = old_array[row][col];
			if (goal == temp)
			{
				location[0] = i;
				location[1] = j;
			}
		}
	}
	return location;
}

int main()
{
	// int old_array[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 0}};
	int old_array[3][3] = {{1, 3, 4}, {8, 6, 2}, {7, 5, 0}};
	int new_array[3][3] = {{1, 2, 3}, {8, 0, 4}, {7, 6, 5}};

	int sum = 0;
	int *loc = new int;

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			// comment to include 0
			if (old_array[i][j] != 0)
			{
				int col_diff, row_diff;
				loc = findLoc(i, j, old_array, new_array);
				//				row_diff = (i > loc[0]) ? i - loc[0] : loc[0] - i;
				if (i > loc[0])
					row_diff = i - loc[0];
				else
					row_diff = loc[0] - i;
				//				col_diff = (j > loc[1]) ? j - loc[1] : loc[1] - j;
				if (j > loc[1])
					col_diff = j - loc[1];
				else
					col_diff = loc[1] - j;

				sum += col_diff + row_diff;
			}
		}
	}

	std::cout << sum;

	delete loc; // freed memory
	loc = NULL; // pointed dangling ptr to NULL

	return 0;
}
