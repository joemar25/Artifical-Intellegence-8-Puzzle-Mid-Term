
// Name: Muhammad Fawad Jawaid Malik
// Roll No. 11k - 2116
// Submitted To: Sir Rafi

#include <iostream>
#include <vector>
#include <string>
#include <math.h>
#include <sstream>
#include <fstream>

// Informed- A* Search
using namespace std;

// Statespace
class Statespace_Tree
{
private:
    struct Node
    {
        Node *parent;

        Node *anode;
        Node *bnode;
        Node *cnode;
        Node *dnode;

        vector<int> state;

        int idx;
        int dist;
        int cost;
    };

    vector<Node *> S;

    vector<int> initial;
    vector<int> goal;

    Node *r;

    int h;
    bool got;

public:
    Statespace_Tree()
    {
        r = NULL;
    }

    // Functions Prototypes
    void generate_root(vector<int>);
    void generate();
    void insert(Node *);
    void input_state();
    void print_state(Node *);
    void Move(Node *, Node *, char);
    void check_goal(Node *);
    void sorting();
    int s1(Node *);

    bool isEmpty() const
    {
        return r == NULL;
    }
};

// Functions Definitions
void Statespace_Tree::generate_root(vector<int> state)
{
    Node *n1 = new Node;

    for (int i = 0; i < (signed)state.size(); i++)
    {
        n1->state.push_back(state[i]);
    }

    n1->cost = s1(n1);
    n1->dist = 1;

    n1->parent = NULL;
    n1->anode = NULL;
    n1->bnode = NULL;
    n1->cnode = NULL;
    n1->dnode = NULL;

    for (int i = 0; i < (signed)state.size(); i++)
    {
        if (state[i] == 0)
        {
            n1->idx = i;
        }
    }

    if (isEmpty())
    {
        r = n1;
        S.push_back(r);
    }
}

// Generating tree
void Statespace_Tree::generate()
{
    input_state();
    generate_root(initial);
    got = false;

    Node *curr;
    h = 1;

    int t = 0;

    while (S.size() > 0)
    {
        curr = S.front();
        S.erase(S.begin());
        insert(curr);

        if (curr->dist > t)
        {
            t = curr->dist;
        }
    }
}

void Statespace_Tree::insert(Node *curr)
{
    Node *n1 = new Node;
    Move(curr, n1, 'u');
    n1->dist = curr->dist + 1;
    n1->cost = s1(n1) + n1->dist;
    n1->parent = curr;
    n1->anode = NULL;
    n1->bnode = NULL;
    n1->cnode = NULL;
    n1->dnode = NULL;

    Node *n2 = new Node;
    Move(curr, n2, 'r');
    n2->dist = curr->dist + 1;
    n2->cost = s1(n2) + n2->dist;
    n2->parent = curr;
    n2->anode = NULL;
    n2->bnode = NULL;
    n2->cnode = NULL;
    n2->dnode = NULL;

    Node *n3 = new Node;
    Move(curr, n3, 'd');
    n3->dist = curr->dist + 1;
    n3->cost = s1(n3) + n3->dist;
    n3->parent = curr;
    n3->anode = NULL;
    n3->bnode = NULL;
    n3->cnode = NULL;
    n3->dnode = NULL;

    Node *n4 = new Node;
    Move(curr, n4, 'l');
    n4->dist = curr->dist + 1;
    n4->cost = s1(n4) + n4->dist;
    n4->parent = curr;
    n4->anode = NULL;
    n4->bnode = NULL;
    n4->cnode = NULL;
    n4->dnode = NULL;

    if ((curr->anode == NULL) && (n1->state.size() > 0))
    {
        curr->anode = n1;
        if (!got)
            S.push_back(curr->anode);
    }
    else
        delete n1;

    if ((curr->bnode == NULL) && (n2->state.size() > 0))
    {
        curr->bnode = n2;
        if (!got)
            S.push_back(curr->bnode);
    }
    else
        delete n2;

    if ((curr->cnode == NULL) && (n3->state.size() > 0))
    {
        curr->cnode = n3;
        if (!got)
            S.push_back(curr->cnode);
    }
    else
        delete n3;

    if ((curr->dnode == NULL) && (n4->state.size() > 0))
    {
        curr->dnode = n4;
        if (!got)
            S.push_back(curr->dnode);
    }
    else
        delete n4;

    sorting();
    check_goal(curr);
}

// Move Function, To move blocks
void Statespace_Tree::Move(Node *curr, Node *n, char move)
{
    int a, idx;
    bool Notcorrect = false;

    for (int i = 0; i < (signed)curr->state.size(); i++)
    {
        if (curr->state[i] == 0)
        {
            idx = i;
        }
        n->state.push_back(curr->state[i]);
    }

    n->idx = idx;

    if (curr->dist > 2)
    {
        if (idx == curr->parent->idx)
        {
            Notcorrect = true;
        }
    }

    switch (move)
    {
    case 'r':
        if ((idx % 3 != 2) && (!Notcorrect))
        {
            a = n->state[idx];
            n->state[idx] = n->state[idx + 1];
            n->state[idx + 1] = a;
        }
        else
            n->state.erase(n->state.begin(), n->state.end());
        break;
    case 'l':
        if ((idx % 3 != 0) && (!Notcorrect))
        {
            a = n->state[idx];
            n->state[idx] = n->state[idx - 1];
            n->state[idx - 1] = a;
        }
        else
            n->state.erase(n->state.begin(), n->state.end());
        break;
    case 'u':
        if ((idx > 2) && (!Notcorrect))
        {
            a = n->state[idx];
            n->state[idx] = n->state[idx - 3];
            n->state[idx - 3] = a;
        }
        else
            n->state.erase(n->state.begin(), n->state.end());
        break;
    case 'd':
        if ((idx < 6) && (!Notcorrect))
        {
            a = n->state[idx];
            n->state[idx] = n->state[idx + 3];
            n->state[idx + 3] = a;
        }
        else
            n->state.erase(n->state.begin(), n->state.end());
        break;
    }
}

// Inputting Initial and final states from Input File
void Statespace_Tree::input_state()
{
    ifstream in("A2in1.txt");

    string p, q;
    int n = 0;

    while (getline(in, p))
    {
        istringstream linestream(p);

        while (getline(linestream, q, ' '))
        {
            n++;

            if (n <= 9)
            {
                initial.push_back(atoi(q.c_str()));
            }
            else
            {
                goal.push_back(atoi(q.c_str()));
            }
        }
    }
}

// To print each state and moves
void Statespace_Tree::print_state(Node *n)
{
    vector<Node *> v;
    ofstream fout("out.txt");

    while (n != NULL)
    {
        v.push_back(n);
        n = n->parent;
    }
    for (int b = v.size() - 1; b >= 0; b--)
    {
        for (int a = 0; a < (signed)v[b]->state.size(); a++)
        {
            fout << v[b]->state[a] << " ";
            cout << v[b]->state[a] << " ";

            if (a % 3 == 2)
            {
                fout << endl;
                cout << endl;
            }
        }
        fout << endl;
        cout << endl;
    }
    cout << "Goal state found." << endl;

    ifstream infile("out.txt");
    ofstream ofile("A2P4out1.txt");

    int arr[10], arr1[10], arr2[10], arr3[10], arr4[10];
    int l = 0, m = 0, g = 0, p = 0, q = 0;

    for (int i = 0; i < 9; i++)
    {
        infile >> arr[i];

        if (arr[i] == 0)
        {
            l = i;
        }
    }

    for (int i = 0; i < 9; i++)
    {
        infile >> arr1[i];

        if (arr1[i] == 0)
        {
            m = i;
        }
    }

    for (int i = 0; i < 9; i++)
    {
        infile >> arr2[i];

        if (arr2[i] == 0)
        {
            g = i;
        }
    }

    for (int i = 0; i < 9; i++)
    {
        infile >> arr3[i];

        if (arr3[i] == 0)
        {
            p = i;
        }
    }

    for (int i = 0; i < 9; i++)
    {
        infile >> arr4[i];

        if (arr4[i] == 0)
        {
            q = i;
        }
    }

    if (m == l + 1)
    {
        ofile << arr[m] << " left" << endl;
    }
    else if (m == l + 3)
    {
        ofile << arr[m] << " up" << endl;
    }

    if (g == m + 1)
    {
        ofile << arr1[g] << " left" << endl;
    }
    else if (g == m + 3)
    {
        ofile << arr1[g] << " up" << endl;
    }
    else if (g == m - 3)
    {
        ofile << arr1[g] << " down" << endl;
    }
    else if (g == m - 1)
    {
        ofile << arr1[g] << " right" << endl;
    }

    if (p == g + 1)
    {
        ofile << arr2[p] << " left" << endl;
    }
    else if (p == g + 3)
    {
        ofile << arr2[p] << " up" << endl;
    }
    else if (p == g - 3)
    {
        ofile << arr2[p] << " down" << endl;
    }
    else if (p == g - 1)
    {
        ofile << arr2[p] << " right" << endl;
    }

    if (q == p + 1)
    {
        ofile << arr3[q] << " left" << endl;
    }
    else if (q == p + 3)
    {
        ofile << arr3[q] << " up" << endl;
    }
    else if (q == p - 3)
    {
        ofile << arr3[q] << " down" << endl;
    }
    else if (q == p - 1)
    {
        ofile << arr3[q] << " right" << endl;
    }

    ofile << "Goal state found." << endl;

    fout.close();
}

int Statespace_Tree::s1(Node *n)
{
    int q = 0;

    for (int a = 0; a < (signed)n->state.size(); a++)
    {
        if (n->state[a] != goal[a])
        {
            q++;
        }
    }

    return q;
}

void Statespace_Tree::sorting()
{
    Node *n;

    for (int i = 0; i < (signed)S.size() - 1; i++)
    {
        for (int j = 0; j < (signed)S.size() - 1; j++)
        {
            if (S[j]->cost > S[j + 1]->cost)
            {
                n = S[j];
                S[j] = S[j + 1];
                S[j + 1] = n;
            }
        }
    }
}

// To check whether we reach the goal or not.
void Statespace_Tree::check_goal(Node *curr)
{
    bool check1 = true, check2 = true, check3 = true, check4 = true;

    for (int a = 0; a < (signed)goal.size(); a++)
    {
        if (curr->anode != NULL)
        {
            if (curr->anode->state[a] != goal[a])
                check1 = false;
        }
        else
            check1 = false;

        if (curr->bnode != NULL)
        {
            if (curr->bnode->state[a] != goal[a])
                check2 = false;
        }
        else
            check2 = false;

        if (curr->cnode != NULL)
        {
            if (curr->cnode->state[a] != goal[a])
                check3 = false;
        }
        else
            check3 = false;

        if (curr->dnode != NULL)
        {
            if (curr->dnode->state[a] != goal[a])
                check4 = false;
        }
        else
            check4 = false;
    }

    if (check1)
    {
        got = true;
        print_state(curr->anode);
    }
    else if (check2)
    {
        got = true;
        print_state(curr->bnode);
    }
    else if (check3)
    {
        got = true;
        print_state(curr->cnode);
    }
    else if (check4)
    {
        got = true;
        print_state(curr->dnode);
    }

    if (got)
    {
        while (!S.empty())
        {
            S.erase(S.begin());
        }
    }
}

int main()
{
    Statespace_Tree t;
    t.generate();

    system("pause");
    return 0;
}