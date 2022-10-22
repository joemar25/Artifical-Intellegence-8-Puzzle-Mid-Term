#include <iostream>

int *h(int row, int col, int _state[], int _goal[])
{
	int index = 0;
	int state[3][3];
	int goal[3][3];

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			state[i][j] = _state[index];
			index++;
		}
	}

	index = 0;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			goal[i][j] = _goal[index];
			index++;
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
	int state[9] = {1, 2, 3, 4, 5, 6, 7, 8, 0};
	// int state[9] = {1, 3, 4, 8, 6, 2, 7, 5, 0};
	int goal[9] = {1, 2, 3, 8, 0, 4, 7, 6, 5};

	unsigned int sum = 0, index = 0;
	unsigned int row_diff = 0, col_diff = 0;
	int *loc = new int;

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (state[index] != 0)
			{
				loc = h(i, j, state, goal);
				row_diff = (i > loc[0]) ? i - loc[0] : loc[0] - i;
				col_diff = (j > loc[1]) ? j - loc[1] : loc[1] - j;
				sum += col_diff + row_diff;
			}
			index++;
		}
	}

	std::cout << sum;
	loc = NULL;
	delete loc;
	loc = NULL;

	return 0;
}