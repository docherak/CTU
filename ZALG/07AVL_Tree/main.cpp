// 1 -> 2 -> 3 - lisi se o dve
// rebalanc:
// 1 <- 2 -> 3

#include <iostream>

using namespace std;

struct Item
{
    int key;    // stored value
    int height; // subtree height
    Item* left;
    Item* right;
    Item() : key(0), height(1), left(nullptr), right(nullptr)
    {
//        key = 0;
//        height = 1;
//        left = right = nullptr
    }
};

inline int h(Item* p)
{
    if (!p)     // p == nullptr
        return 0;
    else
        return p->height;
}

void update(Item* p)
{
    int L = h(p->left);
    int R = h(p->right);
    if (L > R)
        p->height = L + 1;
    else
        p->height = R + 1;
}

void insert(Item*& root, int val)
{
    if (!root)
    {
        root = new Item();
        root->key = val;
    }
    else if (val < root->key)  // go left?
        insert(root->left, val);
    else if (val > root->key)  // go right?
        insert(root->right, val);

    update(root);
    int L = h(root->left);  // height of the left subtree
    int R = h(root->right); // height of the right subtree
    Item* a = root;

    if (L > R + 1)   // left subtree is too high
    {
        Item* b = a->left;
        //          a
        //      b
        //  c       d
        int LL = h(b->left);
        int LR = h(b->right);
        if (LL > LR) // left-left case
        {
            Item* c = b->left;
            //          a
            //      b
            //  c       t
            Item* t = b->right;
            root = b;
            //      b
            //  c       a
            b->right = a;
            a->left = t;

            update(a);
            update(b);
        }
        else // Left Right case
        {
            Item* c = b->right;
            //          a
            //      b
            //          c
            //         t u
            Item* t = c->left;
            Item* u = c->right;
            //      c
            //  b       a
            root = c;
            c->left = b;
            c->right = a;

            b->right = t;
            a->left = u;
            //      c
            //  b       a
            //   t     u
            update(a);
            update(b);
            update(c);
        }
    }
    else if (R > L + 1)   // right subtree is too high
    {
        Item* b = a->right;
        int RL = h(b->left);
        int RR = h(b->right);

        if (RR > RL)
        {
            Item* c = b->right;
            //  a
            //      b
            //          c
            Item* t = b->left;
            root = b;
            b->left = a;
            a->right = t;
            update(a);
            update(b);
        }
        else
        {
            Item* c = b->left;
            //  a
            //      b
            //  c       t
            Item* t = c->left;
            Item* u = c->right;
            root = c;
            c->right = b;
            c->left = a;
            b->left = t;
            b->right = u;
            update(a);
            update(b);
            update(c);
        }
        
    }
    // else
}

void print(Item* branch, int level = 0)
{
    if (branch) // branch != nullptr
    {
        for (int i = 0; i < level; i++)
            cout << '-';
        cout << branch->key << " (" << branch->height << ")" << endl;

        print(branch->left, level + 1);
        print(branch->right, level + 1);
    }
}

bool ok, first;
int last_value;

void checkBranch(Item* branch)
{
    if (branch)
    {
        checkBranch(branch->left);
        if (!first)
            if (last_value >= branch->key)
            {
                cout << "ERROR..." << endl;
                ok = false;
            }
        last_value = branch->key;
        first = false;
        checkBranch(branch->right);
    }
}

void check(Item* root)
{
    ok = true;
    first = true;
    checkBranch(root);
    if (ok) cout << "WORKING FINE" << endl;
}

int main()
{
    // Item* strom; // not guaranteed nullptr
    Item* tree = nullptr;
    
    // int const N = 1024; // 2^10 -> 10 levels
    int const N = 16;

    for (int i = 0; i < N; i++)
    {
        insert(tree, i);
        print(tree);
        getchar();
    }
    print(tree);
    check(tree);
}
