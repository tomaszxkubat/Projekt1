//////// DRZEWO AVL ///////////
///// TOMASZ KUBAT 2018 //////

#include "stdafx.h"
#include <iostream>

using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	return 0;
}


struct node
{
	node *up;       //wsaŸnik na ojca
	node *left;		//wsaŸnik na lewego syna
	node *right;	//wsaŸnik na prawego syna
	int key;		//wartoœæ(klucz)
	int bf;			//wspó³czynnik równowagi
	int level;		//poziom
	node();
};

node::node()
{
	up = 0;
	left = 0;
	right = 0;
	bf = 0;
	level = 0;
}

struct tree
{
	int maxlevel;						//maksymalny poziom
	node *root;							//wskŸnik na korzeñ
	void add(int key);					//dodawanie elementu(pod jaki element , wartoœæ)
	void viewroot();					//wyswietl korzen
	void viewheight(node *temp);		//wyswietl wysokosc
	void preorder(node *temp);			//przejscie pre-order
	void postorder(node *temp);			//przejscie post-order
	void inorder(node *temp);			//przejscie in-order
	node *AVRrotationLR(node *&root, node * A);		//rotacja LR
	node *AVRrotationLL(node *&root, node *A);		//rotacja LL
	node *AVRrotationRL(node *&root, node *A);		//rotacja RL
	node *AVRrotationRR(node *&root, node *A);		//rotacja RR
	node *pre(node *p);								//znajdŸ poprzednika(pomocnicza f. remove)
	void del(int k);								//usuñ element
	node *remove(node * &root, node * x);			//funkcja usuwaj¹ca 
	tree();							
};

tree::tree()
{
	root = 0;
	maxlevel=0;
}

node *tree::AVRrotationLR(node *&root, node *A)
{

	node * B = A->left, *C = B->right, *P = A->up;

	B->right = C->left;
	if (B->right) B->right->up = B;
	A->left = C->right;
	if (A->left) A->left->up = A;
	C->right = A;
	C->left = B;
	A->up = B->up = C;
	C->up = P;
	if (P)
	{
		if (P->left == A) P->left = C; else P->right = C;
	}
	else root = C;

	A->bf = (C->bf == 1) ? -1 : 0;
	B->bf = (C->bf == -1) ? 1 : 0;
	C->bf = 0;

	return C;
}

node *tree::AVRrotationLL(node *&root, node *A)
{
	node *B = A->left, *P = A->up;

	A->left = B->right;
	if (A->left) A->left->up = A;
	B->right = A;
	B->up = P;
	A->up = B;
	if (P)
	{
		if (P->left == A) P->left = B; else P->right = B;
	}
	else root = B;

	if (B->bf == 1)
	{
		A->bf = B->bf = 0;
	}
	else
	{
		A->bf = 1; B->bf = -1;
	}

	return B;
}
node *tree::AVRrotationRL(node *&root, node *A)
{
	node *B = A->right, *C = B->left, *P = A->up;

	B->left = C->right;
	if (B->left) B->left->up = B;
	A->right = C->left;
	if (A->right) A->right->up = A;
	C->left = A;
	C->right = B;
	A->up = B->up = C;
	C->up = P;
	if (P)
	{
		if (P->left == A) P->left = C; else P->right = C;
	}
	else root = C;

	A->bf = (C->bf == -1) ? 1 : 0;
	B->bf = (C->bf == 1) ? -1 : 0;
	C->bf = 0;

	return C;
}

node *tree::AVRrotationRR(node *&root, node *A)
{
	node *B = A->right, *P = A->up;

	A->right = B->left;
	if (A->right) A->right->up = A;
	B->left = A;
	B->up = P;
	A->up = B;
	if (P)
	{
		if (P->left == A) P->left = B; else P->right = B;
	}
	else root = B;

	if (B->bf == -1)
	{
		A->bf = B->bf = 0;
	}
	else
	{
		A->bf = -1; B->bf = 1;
	}
	return B;
}

node *tree::pre(node *p)
{
	node *r;

	if (p)
	{
		if (p->left)
		{
			p = p->left;
			while (p->right) p = p->right;
		}
		else
			do
			{
				r = p;
				p = p->up;
			} while (p && p->right != r);
	}
	return p;
}

void tree::del(int k)
{
	node *p = root;
	while (p && p->key != k)
		p = (k < p->key) ? p->left : p->right;

	remove(root, p);
}


node *tree::remove(node * &root, node * x)
{
	node  *t, *y, *z;
	bool nest;

	if (x->left && x->right)
	{
		y = remove(root, pre(x));
		nest = false;
	}
	else
	{
		if (x->left)
		{
			y = x->left; x->left = NULL;
		}
		else
		{
			y = x->right; x->right = NULL;
		}
		x->bf = 0;
		nest = true;
	}

	if (y)
	{
		y->up = x->up;
		y->left = x->left;  if (y->left)  y->left->up = y;
		y->right = x->right; if (y->right)  y->right->up = y;
		y->bf = x->bf;
	}

	if (x->up)
	{
		if (x->up->left == x) x->up->left = y; else x->up->right = y;
	}
	else root = y;

	if (nest)
	{
		z = y;
		y = x->up;
		while (y)
		{
			if (!y->bf)
			{              
				if (y->left == z)  y->bf = -1; else y->bf = 1;
				break;
			}
			else
			{
				if (((y->bf == 1) && (y->left == z)) || ((y->bf == -1) && (y->right == z)))
				{           
					y->bf = 0;
					z = y; y = y->up;
				}
				else
				{
					if (y->left == z)  t = y->right; else t = y->left;
					if (!t->bf)
					{         
						if (y->bf == 1) AVRrotationLL(root, y); else AVRrotationRR(root, y);
						break;
					}
					else if (y->bf == t->bf)
					{         
						if (y->bf == 1) AVRrotationLL(root, y); else AVRrotationRR(root, y);
						z = t; y = t->up;
					}
					else
					{         
						if (y->bf == 1) AVRrotationLR(root, y); else AVRrotationRL(root, y);
						z = y->up; y = z->up;
					}
				}
			}
		}
	}
	return x;
}

void tree::add(int key)
{
	node *nev = new node;			  // dodawnay wezel
	nev->key = key;					  // podstaw wartosc

	node *temp = root;				  
	node *x;
	bool t;

	if (temp == 0)                     
		root = nev;						
	else
	{
		while (1)						
			if (key < temp->key)         
			{                      
				if (temp->left == 0)        
				{
					temp->left = nev;       
					break;             
				}
				else temp = temp->left;
			}
			else
			{
				if (temp->right == 0)        
				{
					temp->right = nev;      
					break;             
				}
				else temp = temp->right;
			}

		nev->up = temp;					


		if (temp->bf)
			temp->bf = 0; 
		else
		{
			if (temp->left == nev)   
				temp->bf = 1;
			else
				temp->bf = -1;

			x = temp->up;        
			t = false;			
			while (x)
			{
				if (x->bf)
				{
					t = true;     
					break;        
				};
				if (x->left == temp) x->bf = 1;
				else             x->bf = -1;

				temp = x;          
				x = x->up;
			}

			if (t)             
			{                 
				if (x->bf == 1)
				{
					if (x->right == temp) x->bf = 0;  
					else if (temp->bf == -1) AVRrotationLR(root, x);
					else                 AVRrotationLL(root, x);
				}
				else
				{             
					if (x->left == temp) x->bf = 0;  
					else if (x->bf == 1) AVRrotationRL(root, x);
					else                AVRrotationRR(root, x);
				}
			}
		}
	}
}

void tree::viewroot()
{
	cout << "KORZENIEM DRZEWA JEST LICZBA: " << root->key << endl;
}
void tree::viewheight(node *temp)
{
	if (temp)
	{
		if (temp->left != 0)
		{
			temp->left->level = (temp->level + 1);
			if (maxlevel < temp->left->level)
				maxlevel = temp->left->level;
		}
		if (temp->right != 0)
		{
			temp->right->level = (temp->level + 1);
			if (maxlevel < temp->right->level)
				maxlevel = temp->right->level;
		}
		viewheight(temp->left);
		
		viewheight(temp->right);
	}

}

void tree::preorder(node *temp)
{
	if (temp)
	{
		cout << temp->key << " ";
		preorder(temp->left);
		preorder(temp->right);
	}
}

void tree::postorder(node *temp)
{
	if (temp)
	{
		postorder(temp->left);     
		postorder(temp->right);    
		cout << temp->key << " "; 
	}
}

void tree::inorder(node *temp)
{
	if (temp)
	{
		inorder(temp->left);       
		cout << temp->key << " "; 
		inorder(temp->right);      
	}

}

// Program wykonywalny
/////////////////////////////////////////
int main()
{
	tree *drzewo = new tree;

	int choice;

	do
	{
		cout << "##################" << endl;
		cout << "# WYBIERZ OPCJE: #" << endl;
		cout << "##################" << endl;
		cout << "# 1.ADD          #" << endl;
		cout << "# 2.REMOVE       #" << endl;
		cout << "# 3.ROOT         #" << endl;
		cout << "# 4.HEIGHT       #" << endl;
		cout << "# 5.PREORDER     #" << endl;
		cout << "# 6.POSTORDER    #" << endl;
		cout << "# 7.INORDER      #" << endl;
		cout << "# 8.END          #" << endl;
		cout << "##################" << endl;
		cout << "#===============> ";
		cin >> choice;

		switch (choice)
		{
		case 1:
			int value1;
			cout << "Podaj liczbe: ";
			cin >> value1;
			cout << endl;
			drzewo->add(value1);
			break;

		case 2:
			int value2;
			cout << "Podaj liczbe: ";
			cin >> value2;
			cout << endl;
			drzewo->del(value2);
			break;

		case 3:
			drzewo->viewroot();
			break;

		case 4:
			drzewo->maxlevel = 0;
			drzewo->root->level = 0;
			drzewo->viewheight(drzewo->root);
			cout << "WYSOKOSC DRZEWA TO: " << drzewo->maxlevel+1 << endl;
			break;

		case 5:
			drzewo->preorder(drzewo->root);
			cout << endl;
			break;

		case 6:
			drzewo->postorder(drzewo->root);
			cout << endl;
			break;

		case 7:
			drzewo->inorder(drzewo->root);
			cout << endl;
			break;

		}

	} while (choice != 8);

	return 0;
}
