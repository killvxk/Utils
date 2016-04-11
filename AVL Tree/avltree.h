
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

//AvlNode <ElementType>* Find(ElementType X, AvlNode<ElementType> * T);

//AvlNode <ElementType>* FindMin(AvlNode<ElementType> * T);

//AvlNode <ElementType>* FindMax(AvlNode<ElementType> * T);

AvlNode <ElementType> * Insert(ElementType X, AvlNode<ElementType> * T);

//AvlNode <ElementType>* Delete(ElementType X, AvlNode<ElementType> * T);


ElementType Retrieve(AvlNode<ElementType> * P);
	
};