#include <iostream>
#include <stack>

using namespace std;

class Graph
{

public:
    void IDS(int, int);
    bool IDS_util(int, int, int);
};

void Graph::IDS(int x, int required)
{
    if (x == required)
        return;

    cout << "Iterated Deepening Search for " << required << ", starting from vertex " << x << " : " << endl;

    for (int d = 0; d <= n; d++)
        if (IDS_util(x, required, d))
            return;

    cout << required << " was unable to be located via " << x << endl;
}

bool Graph::IDS_util(int x, int required, int depth)
{

    if (x == required)
        return true;

    stack s, x_child;
    bool *visited = new bool[n + 1];
    int i, k, d, sub_k;

    for (i = 0; i <= n; i++)
        visited[i] = false;

    visited[x] = true;

    for (i = n; i >= 0; --i)
        if (isConnected(x, i))
            x_child.push(i);

    cout << '[' << x << "] ";

    while (!x_child.isEmpty())
    {
        k = x_child.pop();
        s.push(k);

        for (d = 0; d < depth; d++)
        {
            sub_k = s.pop();
            if (sub_k == required)
                return true;

            cout << '[' << sub_k << "] ";

            for (i = 0; i <= n; i++)
            {
                if (isConnected(sub_k, i) && !visited[i])
                {
                    if (i == required)
                    {
                        cout << "\n\n"
                             << required << " is a child of " << sub_k << endl;
                        return true;
                    }

                    s.push(i);
                    visited[i] = true;
                }
            }
        }
    }
    cout << endl;
    delete[] visited;

    return false;
}

int main()
{
    return 0;
}