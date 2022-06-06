#include <iostream>

const int MAX = 4;

struct Node
{
    int cnt; 
    int key[MAX + 1];
    Node* ref[MAX + 2];
    Node() : cnt(0)
    {
        for (int i = 0; i < MAX + 1; i++)
            key[i] = -1;
        for (int i = 0; i < MAX + 2; i++)
            ref[i] = nullptr;
    }
};

void insert0(Node* p, int val) // everything except the root
{
    // 1 3 5 7
    // add 4: fails at 5
    int i = 0;
    while (i < p->cnt && p->key[i] < val)
        i++;
    if (i < p->cnt && p->key[i] == val) {}
    else
    {
        Node* t = p->ref[i];
        // if deep down the list:
        if (!t) // t == nullptr
        {
            for (int k = p->cnt - 1; k >= i; k--)
                p->key[k + 1] = p->key[k];
            for (int k = p->cnt; k >= i; k--)
                p->ref[k + 1] = p->ref[k];
            p->key[i] = val;
            p->ref[i] = nullptr;
            p->cnt++;
        }
        else // if not:
        {
            insert0(t, val); // insert in that subtree
            // case when too much data
            if (t->cnt > MAX)
            {
                int a = MAX / 2; // amount of elems in the first node
                int b = MAX - 1 - a; // how many elems to another node
                int d = t->key[a];

                // create new node
                Node* n = new Node();
                n->cnt = b;
                for (int k = a + 1; k < t->cnt; k++)
                    n->key[k - (a + 1)] = t->key[k];
                for (int k = a + 1; k < t->cnt + 1; k++)
                    n->ref[k - (a + 1)] = t->ref[k];

                // clean original field
                for (int k = a; k < t->cnt; k++)
                    t->key[k] = -1;
                for (int k = a; k < t->cnt + 1; k++)
                    t->ref[k] = nullptr;
            
                for (int k = p->cnt-1; k >= i; k--)
                    p->key[k + 1] = p->key[k];
                for (int k = p->cnt; k >= i; k--)
                    p->ref[k + 1] = p->ref[k];
                p->key[i] = d;
                p->ref[i + 1] = n;
                p->cnt++;
            }
        }
    }
}

void insert(Node*& p, int val)
{
    if (!p)
    {
        p = new Node();
        p->cnt = 1;
        p->key[0] = val;
        p->ref[0] = nullptr;
        p->ref[1] = nullptr;
    }
    else
    {
        insert0(p, val);
        Node* t = p;
        if (t->cnt > MAX)
        {
            int a = MAX / 2;
	    int b = MAX - 1 - a;
            int d = t->key[a];

            Node* n = new Node();
            n->cnt = b;
            for (int k = a + 1; k < t->cnt; k++)
                n->key[k - (a + 1)] = t->key[k];
            for (int k = a + 1; k < t->cnt + 1; k++)
                n->ref[k - (a + 1)] = t->ref[k];

            for (int k = a; k < t->cnt; k++)
                t->key[k] = -1;
            for (int k = a; k < t->cnt + 1; k++)
                t->ref[k] = nullptr;
            t->cnt = a;
            
            // new node, save to root pointer

            p = new Node;
            p->cnt = 1;
            p->key[0] = d;
            p->ref[0] = t;
            p->ref[1] = n;
        }
    }
}

int main()
{
    Node* strom = nullptr;
    insert(strom, 14);
    insert(strom, 12);
    insert(strom, 7);
    insert(strom, 5);
    insert(strom, 1);
    insert(strom, 6);
    insert(strom, 2);
    insert(strom, 3);
}

// note: graphviz - dreampuf/github
