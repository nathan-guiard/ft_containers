// Implementing Red-Black Tree in C++

#include <iostream>
#include <iomanip>
using namespace std;

struct Node
{
	int value;
	Node *parent;
	Node *left;
	Node *right;
	int color;
};

typedef Node *NodePtr;

class RedBlackTree
{
	 private:
	NodePtr root;
	NodePtr TNULL;

	void initializeNULLNode(NodePtr node, NodePtr parent)
	{
		node->value = 0;
		node->parent = parent;
		node->left = 0;
		node->right = 0;
		node->color = 0;
	}

	// Preorder
	void preOrderHelper(NodePtr node)
	{
		if (node != TNULL)
		{
			cout << node->value << " ";
			preOrderHelper(node->left);
			preOrderHelper(node->right);
		}
	}

	// Inorder
	void inOrderHelper(NodePtr node)
	{
		if (node != TNULL)
		{
			inOrderHelper(node->left);
			cout << node->value << " ";
			inOrderHelper(node->right);
		}
	}

	// Post order
	void postOrderHelper(NodePtr node)
	{
		if (node != TNULL)
		{
			postOrderHelper(node->left);
			postOrderHelper(node->right);
			cout << node->value << " ";
		}
	}

	NodePtr searchTreeHelper(NodePtr node, int key)
	{
		if (node == TNULL || key == node->value)
		{
			return node;
		}

		if (key < node->value)
		{
			return searchTreeHelper(node->left, key);
		}
		return searchTreeHelper(node->right, key);
	}

	// For balancing the tree after deletion
	void deleteFix(NodePtr x)
	{
		NodePtr s;
		while (x != root && x->color == 0)
		{
			if (x == x->parent->left)
			{
				s = x->parent->right;
				if (s->color == 1)
				{
					s->color = 0;
					x->parent->color = 1;
					leftRotate(x->parent);
					s = x->parent->right;
				}

				if (s->left->color == 0 && s->right->color == 0)
				{
					s->color = 1;
					x = x->parent;
				}
				else
				{
					if (s->right->color == 0)
					{
						s->left->color = 0;
						s->color = 1;
						rightRotate(s);
						s = x->parent->right;
					}

					s->color = x->parent->color;
					x->parent->color = 0;
					s->right->color = 0;
					leftRotate(x->parent);
					x = root;
				}
			}
			else
			{
				s = x->parent->left;
				if (s->color == 1)
				{
					s->color = 0;
					x->parent->color = 1;
					rightRotate(x->parent);
					s = x->parent->left;
				}

				if (s->right->color == 0 && s->right->color == 0)
				{
					s->color = 1;
					x = x->parent;
				}
				else
				{
					if (s->left->color == 0)
					{
						s->right->color = 0;
						s->color = 1;
						leftRotate(s);
						s = x->parent->left;
					}

					s->color = x->parent->color;
					x->parent->color = 0;
					s->left->color = 0;
					rightRotate(x->parent);
					x = root;
				}
			}
		}
		x->color = 0;
	}

	void replace(NodePtr u, NodePtr v)
	{
		if (u->parent == 0)
		{
			root = v;
		}
		else if (u == u->parent->left)
		{
			u->parent->left = v;
		}
		else
		{
			u->parent->right = v;
		}
		v->parent = u->parent;
	}

	void deleteNodeHelper(NodePtr node, int key)
	{
		NodePtr to_del = TNULL;
		NodePtr x, y;
		while (node != TNULL)
		{
			if (node->value == key)
			{
				to_del = node;
			}

			if (node->value <= key)
			{
				node = node->right;
			}
			else
			{
				node = node->left;
			}
		}

		if (to_del == TNULL)
		{
			cout << "Key not found in the tree" << endl;
			return;
		}

		y = to_del;
		int y_original_color = y->color;
		if (to_del->left == TNULL)
		{
			x = to_del->right;
			replace(to_del, to_del->right);
		}
		else if (to_del->right == TNULL)
		{
			x = to_del->left;
			replace(to_del, to_del->left);
		}
		else
		{
			y = minimum(to_del->right);
			y_original_color = y->color;
			x = y->right;
			if (y->parent == to_del)
			{
				x->parent = y;
			}
			else
			{
				replace(y, y->right);
				y->right = to_del->right;
				y->right->parent = y;
			}

			replace(to_del, y);
			y->left = to_del->left;
			y->left->parent = y;
			y->color = to_del->color;
		}
		delete to_del;
		if (y_original_color == 0)
		{
			deleteFix(x);
		}
	}

	// For balancing the tree after insertion
	void insertFix(NodePtr child)
	{
		NodePtr u;
		while (child->parent->color == 1)
		{
			if (child->parent == child->parent->parent->right)
			{
				u = child->parent->parent->left;
				if (u->color == 1)
				{
					u->color = 0;
					child->parent->color = 0;
					child->parent->parent->color = 1;
					child = child->parent->parent;
				}
				else
				{
					if (child == child->parent->left)
					{
						child = child->parent;
						rightRotate(child);
					}
					child->parent->color = 0;
					child->parent->parent->color = 1;
					leftRotate(child->parent->parent);
				}
			}
			else
			{
				u = child->parent->parent->right;

				if (u->color == 1)
				{
					u->color = 0;
					child->parent->color = 0;
					child->parent->parent->color = 1;
					child = child->parent->parent;
				}
				else
				{
					if (child == child->parent->right)
					{
						child = child->parent;
						leftRotate(child);
					}
					child->parent->color = 0;
					child->parent->parent->color = 1;
					rightRotate(child->parent->parent);
				}
			}
			if (child == root)
			{
				break;
			}
		}
		root->color = 0;
	}

	void printHelper(NodePtr root, int indent)
	{
		if (!root || root->value == 0)
			return;
		indent += 4;
		printHelper(root->right, indent);
		for (int i = 4; i < indent; i++)
			std::cout << " ";
		std::cout << (root->color == 0 ? "\033[90m" : "\033[31m") << std::setw(4) << root->value << "\033[0m" << std::endl;
		printHelper(root->left, indent);
	}

	 public:
	RedBlackTree()
	{
		TNULL = new Node;
		TNULL->color = 0;
		TNULL->left = 0;
		TNULL->right = 0;
		root = TNULL;
	}

	void preorder()
	{
		preOrderHelper(this->root);
	}

	void inorder()
	{
		inOrderHelper(this->root);
	}

	void postorder()
	{
		postOrderHelper(this->root);
	}

	NodePtr searchTree(int k)
	{
		return searchTreeHelper(this->root, k);
	}

	NodePtr minimum(NodePtr node)
	{
		while (node->left != TNULL)
		{
			node = node->left;
		}
		return node;
	}

	NodePtr maximum(NodePtr node)
	{
		while (node->right != TNULL)
		{
			node = node->right;
		}
		return node;
	}

	NodePtr successor(NodePtr x)
	{
		if (x->right != TNULL)
		{
			return minimum(x->right);
		}

		NodePtr y = x->parent;
		while (y != TNULL && x == y->right)
		{
			x = y;
			y = y->parent;
		}
		return y;
	}

	NodePtr predecessor(NodePtr x)
	{
		if (x->left != TNULL)
		{
			return maximum(x->left);
		}

		NodePtr y = x->parent;
		while (y != TNULL && x == y->left)
		{
			x = y;
			y = y->parent;
		}

		return y;
	}

	void leftRotate(NodePtr x)
	{
		NodePtr y = x->right;
		x->right = y->left;
		if (y->left != TNULL)
		{
			y->left->parent = x;
		}
		y->parent = x->parent;
		if (x->parent == 0)
		{
			this->root = y;
		}
		else if (x == x->parent->left)
		{
			x->parent->left = y;
		}
		else
		{
			x->parent->right = y;
		}
		y->left = x;
		x->parent = y;
	}

	void rightRotate(NodePtr x)
	{
		NodePtr y = x->left;
		x->left = y->right;
		if (y->right != TNULL)
		{
			y->right->parent = x;
		}
		y->parent = x->parent;
		if (x->parent == 0)
		{
			this->root = y;
		}
		else if (x == x->parent->right)
		{
			x->parent->right = y;
		}
		else
		{
			x->parent->left = y;
		}
		y->right = x;
		x->parent = y;
	}

	// Inserting a node
	void insert(int key)
	{
		NodePtr child = new Node;
		child->parent = 0;
		child->value = key;
		child->left = TNULL;
		child->right = TNULL;
		child->color = 1;

		NodePtr parent = 0;
		NodePtr x = this->root;

		while (x != TNULL)
		{
			parent = x;
			if (child->value < x->value)
			{
				x = x->left;
			}
			else
			{
				x = x->right;
			}
		}

		child->parent = parent;
		if (parent == 0)
		{
			root = child;
		}
		else if (child->value < parent->value)
		{
			parent->left = child;
		}
		else
		{
			parent->right = child;
		}

		if (child->parent == 0)
		{
			child->color = 0;
			return;
		}

		if (child->parent->parent == 0)
		{
			return;
		}

		insertFix(child);
	}

	NodePtr getRoot()
	{
		return this->root;
	}

	void deleteNode(int value)
	{
		deleteNodeHelper(this->root, value);
	}

	void printTree()
	{
		if (root)
		{
			printHelper(this->root, 0);
		}
	}
};

int main()
{
	RedBlackTree bst;
	bst.insert(10);
	bst.insert(25);
	bst.insert(50);
	bst.insert(6);
	bst.insert(7);
	bst.insert(78);
	bst.insert(42);
	bst.insert(100);
	bst.insert(12);
	bst.insert(20);
	bst.insert(24);
	bst.insert(88);
	bst.insert(26);

	bst.printTree();
	cout << endl
		 << "After deleting" << endl;
	bst.deleteNode(12);
	bst.printTree();
}