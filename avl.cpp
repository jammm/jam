//for understanding how rotations work, http://pages.cs.wisc.edu/~paton/readings/liblitVersion/AVL-Tree-Rotations.pdf :)



#include<iostream>
#include<stack>

using namespace std;

class node
{
	int ele;				//value
	node *left,*right;		//left and right links
	int height;				//height of each node

	node(int a):ele(a),left(NULL),right(NULL),height(0)		//default constructor
	{}
	friend class tree;
};

class tree
{

	node *root;


	//calculate height of node
	//height of a NULL node is set to -1
	//height is calculated by using the formula for node x:-
	//height(x) = (	max(height(x->left),height(x->right)) + 1 )
	int height(node *x)
	{
		if(x==NULL)
			return -1;
		else return x->height;
	}

	//Insert method is extended from the recursive insert method of BST
	//check balance factor after each insertion
	//rotations depend on which side of parent it's being inserted (left or right)
	//after insertion, when unwinding, update the left and right links of each node to reflect changes.

	node *insert(node *x,int a)
	{
		//if node is empty
		if(x==NULL)
		{
			return new node(a);
		}

		if(a>=x->ele)
		{
			x->right = insert(x->right,a);
			
			//calculate balance factor, formula is difference(left child, right child)
			if(height(x->right) - height(x->left) == 2)
			{
				//if balance factor of x's right child is 1, then perform RL rotation
				if(height(x->right->left) - height(x->right->right) == 1)
					x = RL(x);
				else
					x = RR(x);
			}
			
			
		}
		else
		{
			x->left = insert(x->left,a);
			if(height(x->left) - height(x->right) ==2)
			{
				//if balance factor of x's left child is -1, then perform LR rotation
				if(height(x->left->left) - height(x->left->right) == -1)
					x = LR(x);
				else
					x = LL(x);
			}
			
		}
		//adjust height
		x->height = max(height(x->right),height(x->left)) + 1;
		return x;
	}

	//Rotations start here

	node *RR(node *x)	//RR rotation
	{
		node *y = x->right;
		x->right = y->left;
		y->left = x;
		
		//adjust heights
		x->height = max(height(x->right),height(x->left)) + 1;
		y->height = max(height(y->right),height(y->left)) + 1;
		return y;
	}

	node *LL(node *x)	//LL rotation
	{
		node *y = x->left;
		x->left = y->right;
		y->right = x;

		//adjust heights
		x->height = max(height(x->right),height(x->left)) + 1;
		y->height = max(height(y->right),height(y->left)) + 1;
		return y;
	}

	node *LR(node *x)	//LR rotation
	{
		x->left = RR(x->left);		//perform RR on x's left child
		return LL(x);				//then perform LL on x and return result
	}

	node *RL(node *x)	//RL rotation
	{
		x->right = LL(x->right);	//perform LL on x's right child
		return RR(x);				//then perform RR on x and return
	}

	void inorder(node *x)								 //Inorder traversal (ascending order), format of output:-
	{													 //		(node1) (height1)
		if(x)											 //		(node2) (height2)
		{												 //		(node3) (height3) .. etc
			inorder(x->left);
			cout<<x->ele<<" "<<x->height<<"\n";
			inorder(x->right);
		}
	}


public:



	

	tree()		//Default constructor, root of AVL tree is set to NULL initially
	{
		root = NULL;
	}

	//below functions act as an interface to access class functions.

	void insert(int a)
	{
		root = insert(root,a);
	}
	
	void inorder()
	{
		inorder(root);
	}

			
		
};

int main()
{
	tree a;
	int x;
	while(cin>>x)			//keep inserting until cin returns false
	{
		a.insert(x);
	}
	
	a.inorder();
}