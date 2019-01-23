#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <list>

using namespace std;

int nRet;
int nFiled[11][11];
int nFiled_vita[11][11];
int nN, nM, nK;

typedef struct Tree_Inf
{
	int nX, nY, nAge;
};

list <Tree_Inf> tree_list;
list <Tree_Inf> tree_list_x5;
list <Tree_Inf> tree_death_list;
list <Tree_Inf>::iterator tree_list_index;

const int dirx[] = { -1, 0, 1, 1, 1, 0, -1, -1 };
const int diry[] = { 1, 1, 1, 0, -1, -1, -1, 0 };

void fnSolution()
{
	for (int t = 0; t < nK; t++)
	{
		tree_death_list.clear();
		tree_list_x5.clear();
		for (tree_list_index = tree_list.begin(); tree_list_index != tree_list.end();)
		{
			if (nFiled[tree_list_index->nX][tree_list_index->nY] >= tree_list_index->nAge)
			{
				nFiled[tree_list_index->nX][tree_list_index->nY] -= tree_list_index->nAge;
				tree_list_index->nAge += 1;
				if (tree_list_index->nAge % 5 == 0)
					tree_list_x5.push_back(*tree_list_index);

				tree_list_index++;
			}
			else
			{
				tree_death_list.push_back(*tree_list_index);
				tree_list.erase(tree_list_index++);
			}
		}

		for (tree_list_index = tree_death_list.begin(); tree_list_index != tree_death_list.end(); tree_list_index++)
		{
			nFiled[tree_list_index->nX][tree_list_index->nY] += (tree_list_index->nAge) / 2;
		}

		int nextx = 0;
		int nexty = 0;

		for (tree_list_index = tree_list_x5.begin(); tree_list_index != tree_list_x5.end(); tree_list_index++)
		{
			for (int j = 0; j < 8; j++)
			{
				nextx = tree_list_index->nX + dirx[j];
				nexty = tree_list_index->nY + diry[j];

				if (nextx >= 0 && nextx < nN && nexty >= 0 && nexty < nN)
				{
					tree_list.push_front({ nextx, nexty, 1 });
				}

			}
		}

		for (int i = 0; i < nN; i++)
		{
			for (int j = 0; j < nN; j++)
			{
				nFiled[i][j] += nFiled_vita[i][j];
			}
		}

	}
}


int main()
{
	Tree_Inf tmp = { 0, 0, 0 };
	scanf("%d%d%d", &nN, &nM, &nK);

	for (int i = 0; i < nN; i++)
	{
		for (int j = 0; j < nN; j++)
		{
			scanf("%d", &nFiled_vita[i][j]);
			nFiled[i][j] = 5;
		}
	}
	tree_list.clear();
	for (int i = 0; i < nM; i++)
	{
		scanf("%d%d%d", &tmp.nX, &tmp.nY, &tmp.nAge);
		tmp.nX = tmp.nX - 1;
		tmp.nY = tmp.nY - 1;
		tree_list.push_back(tmp);
	}

	fnSolution();
	nRet = tree_list.size();

	printf("%d", nRet);
	return 0;

}