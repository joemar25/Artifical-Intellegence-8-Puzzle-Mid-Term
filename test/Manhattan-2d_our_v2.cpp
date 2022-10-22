#include <iostream>

int *findLoc(int row, int col, int _state[][3], int _goal[][3])
{
	int counter = 0;

	int state[3][3];
	int goal[3][3];
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			state[i][j] = _state[i][j];
			counter++;
		}
	}

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			goal[i][j] = _goal[i][j];
			counter++;
		}
	}

	static int location[2];

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (goal[i][j] == state[row][col])
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
	int state[3][3] = {{1, 3, 4}, {8, 6, 2}, {7, 5, 0}};
	int goal[3][3] = {{1, 2, 3}, {8, 0, 4}, {7, 6, 5}};

	int sum = 0;
	int *loc = new int;

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (state[i][j] != 0)
			{
				int col_diff, row_diff;
				loc = findLoc(i, j, state, goal);

				if (i > loc[0])
					row_diff = i - loc[0];
				else
					row_diff = loc[0] - i;

				if (j > loc[1])
					col_diff = j - loc[1];
				else
					col_diff = loc[1] - j;

				sum += col_diff + row_diff;
			}
		}
	}

	std::cout << sum;
	loc = NULL;
	delete loc;
	loc = NULL;

	return 0;
}
