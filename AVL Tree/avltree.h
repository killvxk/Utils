
#pragma once
#include "stdafx.h"



template <typename T> struct    AvlNode {
	T Element;
	AvlNode<T> * Parent;
	AvlNode<T> * Left;
	AvlNode<T> * Right;
	intptr_t High;
};

template<typename T>
using AvlTree = AvlNode <T> *;
template<typename T>
using Position = AvlNode <T> *;

template <typename ElementType>
class avl_tree {
public:


	//AvlNode <ElementType>* MakeEmpty(AvlNode<ElementType> * T);

	AvlNode <ElementType>* Find(const ElementType X, AvlNode<ElementType> * T);

	AvlNode <ElementType>* FindMin(AvlNode<ElementType> * T);

	AvlNode <ElementType>* FindMax(AvlNode<ElementType> * T);

	AvlNode <ElementType> * Insert(const ElementType X, AvlNode<ElementType> * T);

	AvlNode <ElementType>* Delete(const ElementType X, AvlNode<ElementType> * T);


	ElementType Retrieve(AvlNode<ElementType> * P);

};


template<typename ElementType>
static AvlTree<ElementType> Balance(Position<ElementType> Node, AvlTree<ElementType> Tree)
{
	//K2 point to grandparent of node that insert
	Position<ElementType> tmp = nullptr;
	Position<ElementType> K2 = Node;

	if (K2 != nullptr)updateHeight(K2);
	while (K2 != nullptr&&tmp != Tree)
	{


		if (
			Height<ElementType>(K2->Left) - Height<ElementType>(K2->Right) == 2)
		{
			if (Height<ElementType>(K2->Left->Left) > Height<ElementType>(K2->Left->Right)) {

				K2 = RotationWith_L<ElementType>(K2);

			}
			else {

				K2 = RotationWith_LR<ElementType>(K2);


			}
		}
		else if (Height<ElementType>(K2->Right) - Height<ElementType>(K2->Left) == 2) {

			if (Height<ElementType>(K2->Right->Left) < Height<ElementType>(K2->Right->Right)) {


				K2 = RotationWith_R<ElementType>(K2);


			}
			else {
				K2 = RotationWith_RL<ElementType>(K2);

			}


		}
		K2->High = Max(Height<ElementType>(K2->Left), Height<ElementType>(K2->Right)) + 1;
		tmp = K2;
		K2 = K2->Parent;

	}
	return tmp;
}



template<typename ElementType>
static Position<ElementType> RotationWith_L(Position<ElementType> K2) {


	Position<ElementType>	 K1 = K2->Left;
	K2->Left = K1->Right;
	if (K1->Right != nullptr)K1->Right->Parent = K2;
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
static Position<ElementType> RotationWith_R(Position<ElementType> K2) {


	Position<ElementType> K1 = K2->Right;
	K2->Right = K1->Left;
	if (K1->Left != nullptr)K1->Left->Parent = K2;
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
static Position<ElementType> RotationWith_LR(Position<ElementType> K3) {
	K3->Left = RotationWith_R(K3->Left);


	return RotationWith_L(K3);


}
template<typename ElementType>
static Position<ElementType> RotationWith_RL(Position<ElementType> K3) {
	K3->Right = RotationWith_L(K3->Right);


	return RotationWith_R(K3);


}
template<typename ElementType>
AvlTree<ElementType> avl_tree<ElementType>::Insert(const ElementType X, AvlNode<ElementType> * T) {
	//if X already in tree ,just return
	if (X == T->Element)return T;

	AvlTree<ElementType> Parent = nullptr;


	//if tree is null , create root
	if (T == nullptr) {
		T = new AvlNode<ElementType>;
		if (T == nullptr)return nullptr;
		else {
			if (X > Parent->Element)Parent->Right = T;
			else if (X < Parent->Element)Parent->Left = T;
			T->Parent = Parent;
			T->Element = X;
			T->High = 0;
			T->Left = T->Right = nullptr;
		}
		return T;
	}

	AvlTree<ElementType> Next = T;

	//to find where should insert
	while (Next != nullptr)
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

	//insert node
	if (Next == nullptr)
	{
		Next = new AvlNode<ElementType>;
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


	//update height after insert node
	if (oriHeight != -1)
		Parent->High = Max(Height<ElementType>(Parent->Left), Height<ElementType>(Parent->Right)) + 1;

	// to balance,use parent ptr for temp
	Parent = nullptr;
	if (oriHeight == 0)Parent = Balance<ElementType>(Next->Parent->Parent, T);
	if (Parent != nullptr)
		T = Parent;

	updateHeight<ElementType>(T);
	return T;
}

template<typename ElementType>
intptr_t static Height(AvlNode<ElementType> * Tree)
{
	return (Tree == nullptr) ? (-1) : (Tree->High);
}
template<typename ElementType>
void static updateHeight(AvlNode<ElementType> * T)
{
	T->High = Max(Height<ElementType>(T->Left), Height<ElementType>(T->Right)) + 1;
}



static inline intptr_t Max(intptr_t a, intptr_t b)
{
	return a > b ? a : b;
}






template<typename ElementType>
AvlTree <ElementType> avl_tree<ElementType>::Delete(const ElementType X, AvlTree<ElementType>  T) {
	if (T == nullptr)return T;
	AvlTree<ElementType> root = T;
	Position<ElementType> node = avl_tree<ElementType>::Find(X, root);
	if (node == nullptr)return root;

	Position<ElementType> tmp;
	if (node->High == 0) {
		tmp = node->Parent;
		if (tmp != nullptr) {
			if (tmp->Element > X)tmp->Left = nullptr;
			else {
				node->Parent->Right = nullptr;
			}
			if (tmp->Left == nullptr&&tmp->Right == nullptr)updateHeight<ElementType>(node->Parent);

			root = Balance<ElementType>(tmp, root);
		};

		delete node;
		return root;
	};

	if (node->Left == nullptr) {
		tmp = node->Parent;
		if (tmp != nullptr) {
			if (X < tmp->Element)tmp->Left = node->Right;
			else tmp->Right = node->Right;
			node->Right->Parent = tmp;
			updateHeight<ElementType>(tmp);
			root = Balance<ElementType>(tmp, root);
		}
		else {
			root = node->Right;
			root->Parent = nullptr;
		}
		delete node;
		return root;
	}
	if (node->Right == nullptr) {
		tmp = node->Parent;
		if (tmp != nullptr) {
			if (X < tmp->Element)tmp->Left = node->Left;
			else tmp->Right = node->Left;
			node->Right->Parent = tmp;
			updateHeight<ElementType>(tmp);
			root = Balance<ElementType>(tmp, root);
		}
		else {
			root = node->Left;
			root->Parent = nullptr;
		}

		delete			node;
		return root;
	}
	if (node->Right != nullptr&&node->Left != nullptr)
	{
		tmp = node->Parent;
		if (tmp != nullptr) {
			if (X < tmp->Element) {
				tmp = avl_tree<ElementType>::FindMax(node);
				node->Element = tmp->Element;
				if (tmp->High != 0) {


					tmp->Left->Parent = tmp->Parent;





					tmp->Parent->Right = tmp->Left;

					node = tmp->Parent;
					delete tmp;
					updateHeight<ElementType>(node);
					root = Balance<ElementType>(node, root);


				}
				else {
					tmp = tmp->Parent;
					delete tmp->Right;
					tmp->Right = nullptr;
					updateHeight<ElementType>(tmp);
					root = Balance<ElementType>(tmp, root);
				}
			}


			else {

				tmp = avl_tree<ElementType>::FindMin(node);
				node->Element = tmp->Element;
				if (tmp->High != 0) {


					tmp->Right->Parent = tmp->Parent;





					tmp->Parent->Left = tmp->Right;

					node = tmp->Parent;
					delete tmp;
					updateHeight<ElementType>(node);
					root = Balance<ElementType>(node, root);


				}
				else {
					tmp = tmp->Parent;
					delete tmp->Left;
					tmp->Left = nullptr;
					updateHeight<ElementType>(tmp);
					root = Balance<ElementType>(tmp, root);
				};
				return root;
			}
		}
		else {
			tmp
				= avl_tree<ElementType>::FindMin(node->Right);
			if (root->High == 1) {
				delete root->Right; root->Right = nullptr; return root;
			}

				if ( tmp->Parent == root)
				{
					tmp->Left = root->Left;
					root->Left->Parent = tmp;
					tmp->Parent = nullptr;
					updateHeight<ElementType>(tmp);
					delete root;
					root = tmp;
					root = Balance<ElementType>(root->Left, root);
				}

				else					if (tmp->High != 0 && tmp->Parent != root) {

			node->Element = tmp->Element;
					tmp->Right->Parent = tmp->Parent;





					tmp->Parent->Left = tmp->Right;

					node = tmp->Parent;
					delete tmp;
					updateHeight<ElementType>(node);
					root = Balance<ElementType>(node, root);

				}
				else 
				{
			node->Element = tmp->Element;
					tmp = tmp->Parent;
					delete tmp->Left;
					tmp->Left = nullptr;
					updateHeight<ElementType>(tmp);
					root = Balance<ElementType>(tmp, root);
				}
				
		}
		return root;



	};
	if (root->High == 0) {
		delete root;
		return nullptr;
	}
	return root;

}

template<typename ElementType>
AvlTree <ElementType> avl_tree<ElementType>::Find(const ElementType X, AvlTree<ElementType>  T) {
	while (T != nullptr)
	{

		if (X > T->Element) {

			T = T->Right;

		}
		else if (X < T->Element) {

			T = T->Left;

		}
		else if (X == T->Element)return T;
	};
	return T;
}
template<typename ElementType>
Position<ElementType> avl_tree<ElementType>::FindMax(AvlTree<ElementType> T)
{
	while (T->Right != nullptr)
	{

		T = T->Right;
	}
	return T;

}




template<typename ElementType>
Position<ElementType> avl_tree<ElementType>::FindMin(AvlTree<ElementType> T)
{
	while (T->Left != nullptr)
	{

		T = T->Left;
	}
	return T;

}








