#include <iostream>

using namespace std;

int *findLoc(int row, int col, int old_array[][3], int new_array[][3])
{

	static int location[2];

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (new_array[i][j] == old_array[row][col])
			{

				location[0] = i;
				location[1] = j;
			}
		}
	}

	return location;
}

main()
{

	int old_array[3][3] = {{3, 2, 4}, {0, 5, 8}, {7, 6, 1}};
	int new_array[3][3] = {{2, 0, 4}, {8, 1, 6}, {3, 7, 5}};

	int sum = 0;

	int *loc;

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{

			if (old_array[i][j] != 0)
			{ // comment to include 0

				int col_diff;
				int row_diff;

				loc = findLoc(i, j, old_array, new_array);

				//				row_diff = (i > loc[0]) ? i - loc[0] : loc[0] - i;

				if (i > loc[0])
				{
					row_diff = i - loc[0];
				}
				else
				{
					row_diff = loc[0] - i;
				}

				//				col_diff = (j > loc[1]) ? j - loc[1] : loc[1] - j;

				if (j > loc[1])
				{
					col_diff = j - loc[1];
				}
				else
				{

					col_diff = loc[1] - j;
				}

				sum += col_diff + row_diff;

			} // end if
		}
	}

	cout << sum;
}
