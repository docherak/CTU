class Node
{
	int data;
	Node* left;
	Node* right;
public:
	Node();
	Node(int);
	~Node() = default;
	int GetData() const;
	void SetData(int);
	friend class BinaryTree;
};

class BinaryTree
{
	Node* root;
private:
	bool Search(Node*, int);
	void Insert(Node*, int);
	void Delete(Node*&, int);
	void Print(Node*, int);
	Node* FindMin(Node*&);
public:
	BinaryTree();
	~BinaryTree() = default;
	bool Search(int);
	bool Contains(int);
	void Insert(int);
	void Delete(int);
	void Print();
};
