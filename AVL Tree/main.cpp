#include "stdafx.h"
#include "avltree.h"
#include <iostream>
#include <string>
using namespace std;





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
	AvlNode<int> * root =new AvlNode<int>(),*tmp;
	root->Element = 1;

	avl_tree<int> han;
    int choice, item;
	for (int i = 1; i <= 10; i++) {
		root=han.Insert(i, root);
	}

    while (1)
    {
        cout<<"\n---------------------"<<endl;
        cout<<"AVL Tree Implementation"<<endl;
        cout<<"\n---------------------"<<endl;
        cout<<"1.Insert Element into the tree"<<endl;
        cout<<"2.Display Balanced AVL Tree"<<endl;
		cout<<"3.Delete Element in AVL Tree" << endl;
		cout<<"4.Find Element in AVL Tree" << endl;
		cout<<"5.Exit"<<endl;

        cout<<"Enter your Choice: ";

		cin>>choice;
        switch(choice)
        {
        case 1:
            cout<<"Enter value to be inserted: ";
            cin>>item;
			root=han.Insert(item,root);   
			goto dis;
            break;
        case 2:
   dis:         if (root == nullptr)
            {
                cout<<"Tree is Empty"<<endl;
                continue;
            }
            cout<<"Balanced AVL Tree:"<<endl;
            display(root, 1);
            break;
		case 3:
            cout<<"Enter value to delete: ";
            cin>>item;
			root=han.Delete(item,root);   
			goto dis;
            break;

		case 4:

			cout <<"Enter value that want to be found: ";
			cin >> item;
			tmp = han.Find(item, root);
			if (tmp == nullptr) {
				cout << "Can not be found" << endl;
				continue;//to next loop
			}
			else display(tmp, 1);
			break;
        case 5:
            exit(1);    
            break;
        default:
            cout<<"Default Insert"<<endl;
			root = han.Insert(choice, root);  goto dis;
        }
    }
    return 0;
}
