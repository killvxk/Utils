
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
using AvlTree = AvlNode <T> * ;
template<typename T>
using Position = AvlNode <T> * ;

template <typename ElementType>
class avl_tree {
public:


//AvlNode <ElementType>* MakeEmpty(AvlNode<ElementType> * T);

AvlNode <ElementType>* Find(const ElementType X, AvlNode<ElementType> * T);

//AvlNode <ElementType>* FindMin(AvlNode<ElementType> * T);

//AvlNode <ElementType>* FindMax(AvlNode<ElementType> * T);

AvlNode <ElementType> * Insert(const ElementType X, AvlNode<ElementType> * T);

AvlNode <ElementType>* Delete(const ElementType X, AvlNode<ElementType> * T);


ElementType Retrieve(AvlNode<ElementType> * P);
	
};






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
AvlNode<ElementType> * avl_tree<ElementType>::Insert(const ElementType X,AvlNode<ElementType> * T) {
	//if X already in tree ,just return
	if (X == T->Element)return T;
	
	AvlTree<ElementType> Parent =nullptr;


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

//insert node
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


//update height after insert node
if(oriHeight!=-1)
Parent->High=Max(Height<ElementType>(Parent->Left), Height<ElementType>(Parent->Right)) + 1;

// to balance,use parent ptr for temp
Parent=nullptr;
if (oriHeight==0) {
	//K2 point to grandparent of node that insert
	Position<ElementType> K2 = Next->Parent->Parent;
	if(K2!=nullptr)K2->High=Max(Height<ElementType>(K2->Left), Height<ElementType>(K2->Right)) + 1;

	while ( K2!=nullptr&&Parent!=T)
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
		Parent= K2;
		K2=K2->Parent;

	}


}
if(Parent!=nullptr)
	T = Parent;

	T->High = Max(Height<ElementType>(T->Left), Height<ElementType>(T->Right)) + 1;
	return T;
}

template<typename ElementType>
intptr_t static Height(AvlNode<ElementType> * Tree)
{
	return (Tree == nullptr )? (-1) :(Tree->High);
}




static intptr_t Max(intptr_t a, intptr_t b)
{
	return a > b ? a : b;
}






template<typename ElementType>
AvlNode <ElementType>* avl_tree<ElementType>::Delete(const ElementType X, AvlNode<ElementType> * T) {




};


template<typename ElementType>
AvlNode <ElementType>* avl_tree<ElementType>::Find(const ElementType X, AvlNode<ElementType> * T) {
	while (T != nullptr)
	{

		if (X > T->Element) {

			T = T->Right;

		}
		else if (X <T->Element) {

			T = T->Left;

		}
		else if (X == T->Element)return T;
	};
	return T;
}














