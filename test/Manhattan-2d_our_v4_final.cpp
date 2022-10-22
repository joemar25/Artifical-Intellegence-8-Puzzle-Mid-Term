#include <iostream>

int *misplacement(int row, int col, int _state[], int _goal[])
{
	static int location[2];
	int state[3][3];
	int goal[3][3];

	for (int index = 0, i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			state[i][j] = _state[index];
			index++;
		}
	}

	for (int index = 0, i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			goal[i][j] = _goal[index];
			index++;
		}
	}

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

int h(int state[])
{
	int goal[9] = {1, 2, 3, 8, 0, 4, 7, 6, 5};
	unsigned int total = 0, index = 0;
	unsigned int x = 0, y = 0;
	int *loc = new int;

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (state[index] != 0)
			{
				loc = misplacement(i, j, state, goal);
				x = (i > loc[0]) ? i - loc[0] : loc[0] - i;
				y = (j > loc[1]) ? j - loc[1] : loc[1] - j;
				total += x + y;
			}
			index++;
		}
	}

	// free memory
	loc = NULL;
	delete loc;
	loc = NULL;

	return total;
}

int main()
{
	int state[9] = {1, 3, 4, 8, 6, 2, 7, 5, 0};
	std::cout << h(state);
	return 0;
}