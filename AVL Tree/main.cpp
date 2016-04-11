#include "stdafx.h"
#include "avltree.h"
#include <iostream>
#include <string>
using namespace std;

template<typename ElementType>
 Position<ElementType> RotationWith_L(Position<ElementType> K2){


		    Position<ElementType>	 K1 = K2->Left;
			K2->Left = K1->Right;
			if(K1->Right!=nullptr)K1->Right->Parent = K2;
			K1->Right = K2;

			K1->Parent = K2->Parent;
			K2->Parent = K1;

			K2->High = Max(Height<ElementType>(K2->Left), Height<ElementType>(K2->Right)) + 1;
			K1->High = Max(Height<ElementType>(K1->Left), K2->High) + 1;
			if (K1->Parent != nullptr) {
				if (K1->Element < K1->Parent->Element)K1->Parent->Left = K1;
				else K1->Parent->Right = K1;
			}
			return K1;
}
template<typename ElementType>
Position<ElementType> RotationWith_R(Position<ElementType> K2) {


	Position<ElementType> K1 = K2->Right;
	K2->Right = K1->Left;
	if(K1->Left!=nullptr)K1->Left->Parent = K2;
	K1->Left = K2;

	K1->Parent = K2->Parent;
	K2->Parent = K1;

	K2->High = Max(Height<ElementType>(K2->Left), Height<ElementType>(K2->Right)) + 1;
	K1->High = Max(Height<ElementType>(K1->Right), K2->High) + 1;
	if (K1->Parent != nullptr) {
				if (K1->Element < K1->Parent->Element)K1->Parent->Left = K1;
				else K1->Parent->Right = K1;
			}
			return K1;
}
template<typename ElementType>
 Position<ElementType> RotationWith_LR(Position<ElementType> K3){
	K3->Left = RotationWith_R(K3->Left);


	return RotationWith_L(K3);


}
template<typename ElementType>
 Position<ElementType> RotationWith_RL(Position<ElementType> K3){
	K3->Right = RotationWith_L(K3->Right);


	return RotationWith_R(K3);


}
template<typename ElementType>
AvlNode<ElementType> * avl_tree<ElementType>::Insert(ElementType X,AvlNode<ElementType> * T) {
	if (X == T->Element)return T;
	AvlTree<ElementType> Next = T;
	AvlTree<ElementType> Parent =nullptr;

	while (Next!=nullptr)
	{
		Parent = Next;

		if (X > Next->Element) {
			
			Next = Next->Right;

}
		else if (X < Next->Element) {

			Next = Next->Left;

		}
		else if (X == Next->Element)return T;
	};

if(Next==nullptr)
{
	Next= new AvlNode<ElementType>;
	if (Next == nullptr)return nullptr;
	else {
		if (X > Parent->Element)Parent->Right = Next;
		else if (X < Parent->Element)Parent->Left = Next;
		Next->Parent = Parent;
		Next->Element = X;
		Next->High = 0;
		Next->Left = Next->Right = nullptr;
	}
};

//save height before instert node

intptr_t oriHeight = Height<ElementType>(Parent);


//add height after insert node
if(oriHeight!=-1)
Parent->High=Max(Height<ElementType>(Parent->Left), Height<ElementType>(Parent->Right)) + 1;

// to balance
Position<ElementType> tmp=nullptr;
if (oriHeight==0) {

	Position<ElementType> K2 = Parent->Parent;
	if(K2!=nullptr)K2->High=Max(Height<ElementType>(K2->Left), Height<ElementType>(K2->Right)) + 1;

	while ( K2!=nullptr)
	{


		if (
			Height<ElementType>(K2->Left) - Height<ElementType>(K2->Right) == 2)
		{
			if (X < K2->Left->Element) {

				K2 = RotationWith_L<ElementType>(K2);

			}
			else {

				K2 = RotationWith_LR<ElementType>(K2);


			}
		}
		else if (Height<ElementType>(K2 -> Right) - Height<ElementType>(K2 -> Left) == 2) {

			if (X > K2->Right->Element) {


				K2 = RotationWith_R<ElementType>(K2);


			}
			else {
				K2 = RotationWith_RL<ElementType>(K2);

			}


		}
		K2->High = Max(Height<ElementType>(K2->Left), Height<ElementType>(K2->Right)) + 1;
	if(K2->Parent!=nullptr)K2->Parent->High=	Max(Height<ElementType>(K2->Parent->Left), Height<ElementType>(K2->Parent->Right)) + 1;
		tmp = K2;
		K2=K2->Parent;

	}


}
if(tmp!=nullptr)
	T = tmp;

	T->High = Max(Height<ElementType>(T->Left), Height<ElementType>(T->Right)) + 1;
	return T;
}

template<typename ElementType>
intptr_t Height(AvlNode<ElementType> * Tree)
{
	return (Tree == nullptr )? (-1) :(Tree->High);
}




static intptr_t Max(intptr_t a, intptr_t b)
{
	return a > b ? a : b;
}





template<typename E>
void display(AvlNode<E> * ptr, int level)
{
	int i;
	if (ptr != nullptr)
	{
		display(ptr->Right, level + 1);
		printf("\n");
		for (i = 0; i < level ; i++)
			cout << "        ";
		cout << ptr->Element;
		display(ptr->Left, level + 1);
	}
}




int main()
{
	AvlNode<int> * root =new AvlNode<int>();
	root->Element = 1;

	avl_tree<int> han;
    int choice, item;
	for (int i = 1; i <= 7; i++) {
		root=han.Insert(i, root);
	}

    while (1)
    {
        cout<<"\n---------------------"<<endl;
        cout<<"AVL Tree Implementation"<<endl;
        cout<<"\n---------------------"<<endl;
        cout<<"1.Insert Element into the tree"<<endl;
        cout<<"2.Display Balanced AVL Tree"<<endl;
        cout<<"3.InOrder traversal"<<endl;
        cout<<"4.PreOrder traversal"<<endl;
        cout<<"5.PostOrder traversal"<<endl;
        cout<<"6.Exit"<<endl;
        cout<<"Enter your Choice: ";

		cin>>choice;
        switch(choice)
        {
        case 1:
            cout<<"Enter value to be inserted: ";
            cin>>item;
			root=han.Insert(item,root);   display(root, 1);
            break;
        case 2:
            if (root == nullptr)
            {
                cout<<"Tree is Empty"<<endl;
                continue;
            }
            cout<<"Balanced AVL Tree:"<<endl;
            display(root, 1);
            break;
        case 6:
            exit(1);    
            break;
        default:
            cout<<"Default Insert"<<endl;
			root=han.Insert(choice,root);   display(root, 1);
        }
    }
    return 0;
}
