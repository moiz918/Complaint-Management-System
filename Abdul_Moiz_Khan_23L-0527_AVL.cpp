#include <iostream>
#include <string>
#include <algorithm>
using namespace std;


//User class which holds data of the users
class User
{
private:
	int UserID;
	string UserName;
	string Email;
	string Country;
	string Type;
public:
	User(int UID = 0, string UN = "", string E = "", string C = "", string T = "")
	{
		UserID = UID;
		UserName = UN;
		Email = E;
		Country = C;
		Type = T;
	}

	//getters to access the data of the users in other classes
	int getID()
	{
		return UserID;
	}

	string getName()
	{
		return UserName;
	}

	string getEmail()
	{
		return Email;
	}

	string getCountry()
	{
		return Country;
	}

	string getType()
	{
		return Type;
	}

	//printing user data through a function
	void printUser()
	{
		cout << "User ID " << UserID << endl;
		cout << "User Name " << UserName << endl;
		cout << "Email " << Email << endl;
		cout << "Country " << Country << endl;
		cout << "Type " << Type << endl;
		cout << "------------------------------------" << endl << endl;
	}

	~User()
	{

	}
};

//class to hold complaint data
class Complaint
{
private:
	int UID;
	int CID;
	string COMP;
	string Country;
	string Type;
	int priority; //priority setting of complaint in order of a min heap

	friend ostream& operator << (ostream& out, const Complaint& rhs) //to display complaint data through iterator
	{
		out << "User ID " << rhs.UID << endl;
		out << "Complaint ID " << rhs.CID << endl;
		out << "Complaint " << rhs.COMP << endl;
		out << "Country " << rhs.Country << endl;
		out << "Type " << rhs.Type << endl;
		out << "------------------------------------" << endl << endl;
		return out;
	}
public:
	Complaint(int U = 0, int C = 0, string c = "", string CN = "", string t = "")
	{
		UID = U;
		CID = C;
		COMP = c;
		Country = CN;
		Type = t;
		if (Type == "platinum") //setting priority based on complaint type
		{
			priority = 1;
		}
		else if (Type == "gold")
		{
			priority = 2;
		}
		else if (Type == "silver")
		{
			priority = 3;
		}
		else if (Type == "new")
		{
			priority = 4;
		}
		else
		{
			priority = 5;
		}
	}

	//all getters
	int getUserID()
	{
		return UID;
	}

	int getComplaintID()
	{
		return CID;
	}

	string getCOMP()
	{
		return COMP;
	}

	string getCountry()
	{
		return Country;
	}

	string getType()
	{
		return Type;
	}

	int getPriority()
	{
		return priority;
	}

	void IncreasePriority() //to increase a complaints priority to the highest priority
	{
		priority = 0;
	}

	bool operator<(const Complaint& rhs)
	{
		if (priority != rhs.priority)
		{
			return priority < rhs.priority;
		}
		else
		{
			return CID < rhs.CID;
		}
	}

	~Complaint()
	{

	}
};

//class to hold individual indexes like ID , Name , Email
template <class T, class U>
class AVLTree
{
private:

	class AVLNode
	{
	public:
		T data;
		U ptr; //U is type List Iterator to hold the pointer to the data in User List
		int height;
		AVLNode* left;
		AVLNode* right;

		AVLNode(T d, U p, AVLNode* l = nullptr, AVLNode* r = nullptr) : data(d), ptr(p), left(l), right(r), height(0)
		{

		}

		~AVLNode()
		{

		}
	};

	AVLNode* root; //Root of tree

	//Function used to get the height of a node in the tree
	int Height(AVLNode* node)
	{
		if (node == nullptr)
		{
			return -1;
		}
		int Left = -1;
		int Right = -1;
		if (node->left)
		{
			Left = node->left->height;
		}
		if (node->right)
		{
			Right = node->right->height;
		}
		return max(Left, Right) + 1;
	}

	//Right imbalance correction
	void LeftRotate(AVLNode*& x)
	{
		AVLNode* orphan = x->right->left;
		AVLNode* y = x->right;

		y->left = x;
		x->right = orphan;

		x->height = Height(x);
		y->height = Height(y);

		x = y;
	}

	//Left Imbalance Correction
	void RightRotate(AVLNode*& x)
	{
		AVLNode* orphan = x->left->right;
		AVLNode* y = x->left;

		y->right = x;
		x->left = orphan;

		x->height = Height(x);
		y->height = Height(y);

		x = y;
	}

	//these funcions are for double imbalances
	void doubleLeftRightRotation(AVLNode*& x)
	{
		LeftRotate(x->left);
		RightRotate(x);
	}

	void doubleRightLeftRotation(AVLNode*& x)
	{
		RightRotate(x->right);
		LeftRotate(x);
	}

	//to balance an AVL tree after removing or inserting a node
	void balance(AVLNode*& node)
	{
		if (node == nullptr)
		{
			return;
		}

		if (Height(node->left) - Height(node->right) > 1)
		{
			if (Height(node->left->left) >= Height(node->left->right))
			{
				RightRotate(node);
			}
			else
			{
				doubleLeftRightRotation(node);
			}
		}
		else if (Height(node->right) - Height(node->left) > 1)
		{
			if (Height(node->right->right) >= Height(node->right->left))
			{
				LeftRotate(node);
			}
			else {
				doubleRightLeftRotation(node);
			}
		}
		node->height = max(Height(node->left), Height(node->right)) + 1;
	}

	//Find the closest node to the inserted index in order to make an insertion before or after it in DLL
	U findClosest(AVLNode* node, T target)
	{
		// base case
		if (node == nullptr)
		{
			return nullptr;
		}


		AVLNode* closestNode = node;
		int closestDiff = abs(target - node->data); // to gwt the absolute difference in between nodes to check closeness

		while (node)
		{
			int currentDiff = abs(target - node->data);
			if (currentDiff < closestDiff) //to get the minimum dfference in between inserted index and tree of nodes
			{
				closestDiff = currentDiff;
				closestNode = node;
			}

			if (target < node->data)
			{
				node = node->left;
			}
			else if (target > node->data)
			{
				node = node->right;
			}
			else
			{
				return node->ptr;
			}
		}

		return closestNode->ptr;
	}

	//Search the pointer to user list in AVL tree
	U SearchPtr(T d, AVLNode* node)
	{
		if (node != nullptr)
		{
			if (d < node->data)
			{
				return SearchPtr(d, node->left);
			}
			else if (d > node->data)
			{
				return SearchPtr(d, node->right);
			}
			else
			{
				return node->ptr; // if node is found return its iterator
			}
		}
		else
		{
			return nullptr;
		}
	}

	// this function is used to dislay the node index in Q2
	T SearchNodeData(T d, AVLNode* node)
	{
		if (node != nullptr)
		{
			if (d < node->data)
			{
				return SearchNodeData(d, node->left);
			}
			else if (d > node->data)
			{
				return SearchNodeData(d, node->right);
			}
			else
			{
				return node->data; // if node is found return its index
			}
		}
	}

	// function used to insert new nodes in a tree
	void Insert(T d, U p, AVLNode*& node)
	{
		if (node == nullptr)
		{
			node = new AVLNode(d, p); // if end of a branch is reached insert the new nodes data and pointer to respective user in userlist
		}
		else if (d < node->data)
		{
			Insert(d, p, node->left);
		}
		else if (d > node->data)
		{
			Insert(d, p, node->right);
		}
		balance(node); // call balance to balance node tree after insertion
	}

	//find successor
	AVLNode* findMin(AVLNode* node)
	{
		while (node->left != nullptr)
		{
			node = node->left;
		}
		return node;
	}

	//delete a certain node in the tree
	void deleteNode(AVLNode*& node, T key)
	{
		if (node == nullptr)
		{
			return;
		}
		// Traverse the tree
		if (key < node->data)
		{
			deleteNode(node->left, key);
		}
		else if (key > node->data)
		{
			deleteNode(node->right, key);
		}
		else
		{
			// Found the node to delete
			if (node->left == nullptr)
			{
				AVLNode* temp = node->right;
				delete node;
				node = temp;
			}
			else if (node->right == nullptr)
			{
				AVLNode* temp = node->left;
				delete node;
				node = temp;
			}
			else
			{
				// Case 3: Two children
				AVLNode* temp = findMin(node->right);  // Find inorder successor
				node->data = temp->data;
				node->ptr = temp->ptr;  // Copy successor's data to current node
				deleteNode(node->right, temp->data);  // Delete the inorder successor
			}
		}
		balance(node); // balance after deletion
	}

	//destructor recurive call fucntion
	void AVLDeletion(AVLNode*& t)
	{
		if (t)
		{
			AVLDeletion(t->left);
			AVLDeletion(t->right);
			delete t;
		}
	}
public:
	AVLTree() :root(nullptr) //constructor which sets root to nullptr
	{

	}

	void InsertInTree(T d, U p)
	{
		if (!root) //if tree is emoty
		{
			root = new AVLNode(d, p);

		}
		else
		{
			Insert(d, p, root);
		}
	}

	// remove node from tree
	void RemoveInTree(T d)
	{
		deleteNode(root, d);
	}

	U findClosestNode(T d)
	{
		return findClosest(root, d);
	}

	// returns iterator of type pointer to user
	U Search(T d)
	{
		U ret = SearchPtr(d, root);
		return ret;
	}

	// get the closest node for insertion in dll in log(n) time
	U InsertInTreeAndList(T d, U p)
	{
		U inNode = findClosestNode(d);
		return inNode;
	}

	U RemoveFromTreeAndList(T d)
	{
		U delNode = Search(d);
		return delNode;
	}

	T SearchDisplay(T d)
	{
		return SearchNodeData(d, root);
	}

	// display the index of the certain ID , Name , Email and also return its pointer
	void DisplayData(T d)
	{
		if (Search(d) != nullptr)
		{
			cout << "Index of AVL is ";
			cout << SearchDisplay(d) << endl;
		}
	}

	~AVLTree()
	{
		AVLDeletion(root);
	}
};

//SLL class used for group of indexes in group avl tree
template <class U>
class SLL
{
private:
	class SLLNode
	{
	public:
		U ptr; //pointer to user list
		SLLNode* next;
		SLLNode(U p, SLLNode* n = nullptr) : ptr(p), next(n)
		{

		}
		~SLLNode()
		{
			next = 0;
		}
	};

	SLLNode* head;
	SLLNode* tail;

public:
	// uses ummy nodes
	SLL()
	{
		head = new SLLNode(0);
		tail = new SLLNode(0);
		head->next = tail;
	}

	SLL(const SLL& rhs)  //copy constructor
	{

		head = new SLLNode(0, nullptr);  // Dummy head node
		tail = new SLLNode(0, nullptr);  // Dummy tail node
		head->next = tail;

		SLLNode* curr = rhs.head->next;
		SLLNode* end = head;

		while (curr != nullptr && curr != rhs.tail)
		{
			SLLNode* newNode = new SLLNode(curr->ptr);
			end->next = newNode;
			end = newNode;
			curr = curr->next;
		}

		end->next = tail;
	}

	//basic insert at start function used for a standard SLL
	void insertAtStart(U ptr)
	{
		if (head->next == tail)
		{
			SLLNode* temp = new SLLNode(ptr, tail);
			head->next = temp;
		}
		else
		{
			SLLNode* temp = new SLLNode(ptr, head->next);
			head->next = temp;
		}
	}

	// delete SLL completely when index is being deleted
	void deleteSLL()
	{
		while (head->next != nullptr)
		{
			SLLNode* temp = head->next;
			SLLNode* temp2 = temp->next;
			head->next = temp2;
			delete temp;
		}
	}

	// display all users of a certain country or type
	void DisplayList()
	{
		if (head->next != nullptr)
		{
			for (SLLNode* temp = head->next; temp != tail; temp = temp->next)
			{
				DisplayIte(temp->ptr);
			}
		}
	}

	//accesses the display users through class List Iterator
	void DisplayIte(U ptr)
	{
		ptr.DisplayUserIte();
	}

	// delete a certain node from sll
	bool deleteSLLNode(int ID)
	{
		// if sll is empty
		if (head->next == tail)
		{
			return false;
		}
		else
		{
			SLLNode* del = nullptr;
			SLLNode* store = nullptr;
			bool flag = false;
			for (SLLNode* temp = head; temp->next != tail && flag == false; temp = temp->next)
			{
				SearchSLLNode(temp->next, del, ID); // find the node in the sll with given id
				if (del != nullptr && flag == false) // if found delete it
				{
					flag = true;
					store = temp;
				}
			}

			if (flag == true) // deletion done through gwtting previous node and setting it to nodes next node and deleting the node so no extra processing time is required
			{
				SLLNode* temp2 = store->next;
				SLLNode* change = del->next;
				store->next = change;
				delete temp2;
			}
		}
	}

	// helper fuction for the previous function
	void SearchSLLNode(SLLNode* temp, SLLNode*& ret, int ID)
	{
		if (temp->ptr.getIteID() == ID) // compares node id with give id
		{
			ret = temp;
		}
	}

	// checks if sll is empty 
	bool isEmpty()
	{
		if (head->next == tail)
		{
			return false;
		}
		else
		{
			return true;
		}
	}

	//destructor
	~SLL()
	{
		while (head->next != nullptr)
		{
			SLLNode* temp = head->next;
			SLLNode* temp2 = temp->next;
			head->next = temp2;
			delete temp;
		}
	}
};

//AVL Tree class with group indexes like country and type
template <class T, class U>
class GroupAVLTree
{
private:
	class GroupNode //node class to hod the data of the tree
	{
	public:
		T data;
		typename SLL<U>* userListHead; //singlylink list to hold gorup of pointers to users
		int height;
		GroupNode* left;
		GroupNode* right;

		GroupNode(T d) :height(0), left(nullptr), right(nullptr)
		{
			data = d;
			userListHead = new SLL<U>; //initialising SLL as it is a pointer
		}

		~GroupNode()
		{
			left = nullptr;
			right = nullptr;
		}
	};

	GroupNode* root;

	int Height(GroupNode* node)
	{
		if (node == nullptr)
		{
			return -1;
		}
		int Left = -1;
		int Right = -1;
		if (node->left)
		{
			Left = node->left->height;
		}
		if (node->right)
		{
			Right = node->right->height;
		}
		return max(Left, Right) + 1;
	}

	void LeftRotate(GroupNode*& x)
	{
		GroupNode* orphan = x->right->left;
		GroupNode* y = x->right;

		y->left = x;
		x->right = orphan;

		x->height = Height(x);
		y->height = Height(y);

		x = y;
	}

	void RightRotate(GroupNode*& x)
	{
		GroupNode* orphan = x->left->right;
		GroupNode* y = x->left;

		y->right = x;
		x->left = orphan;

		x->height = Height(x);
		y->height = Height(y);

		x = y;
	}

	void doubleLeftRightRotation(GroupNode*& x)
	{
		LeftRotate(x->left);
		RightRotate(x);
	}

	void doubleRightLeftRotation(GroupNode*& x)
	{
		RightRotate(x->right);
		LeftRotate(x);
	}

	void balance(GroupNode*& node)
	{
		if (node == nullptr)
		{
			return;
		}

		if (Height(node->left) - Height(node->right) > 1)
		{
			if (Height(node->left->left) >= Height(node->left->right))
			{
				RightRotate(node);
			}
			else
			{
				doubleLeftRightRotation(node);
			}
		}
		else if (Height(node->right) - Height(node->left) > 1)
		{
			if (Height(node->right->right) >= Height(node->right->left))
			{
				LeftRotate(node);
			}
			else {
				doubleRightLeftRotation(node);
			}
		}
		node->height = max(Height(node->left), Height(node->right)) + 1;
	}

	//insert a node in group avl and see if it creates a new node or is sent to a sll
	void insertNode(T key, U ptr, GroupNode*& node)
	{
		if (node == nullptr)
		{
			node = new GroupNode(key);
			InsertInSLL(node->userListHead, ptr); //initial insertion of a new countr or type
		}
		else if (key < node->data)
		{
			insertNode(key, ptr, node->left);
		}
		else if (key > node->data)
		{
			insertNode(key, ptr, node->right);
		}
		else
		{
			InsertInSLL(node->userListHead, ptr); // if same country or type is made insert the new pointer in the SLL
		}
		balance(node);
	}

	void InsertInSLL(SLL<U>* ptr, U in)
	{
		ptr->insertAtStart(in); // function in sll class to insert a new pointer in the sll
	}

	//search the avl to find a group index which matches the given type or country in log(n) time
	bool SearchPtr(T d, GroupNode* node)
	{
		if (node != nullptr)
		{
			if (d < node->data)
			{
				return SearchPtr(d, node->left);
			}
			else if (d > node->data)
			{
				return SearchPtr(d, node->right);
			}
			else
			{
				return true;
			}
		}
		else
		{
			return false;
		}
	}


	// this function is used to dislay the node index in Q3
	T SearchNodeData(T d, GroupNode* node)
	{
		if (node != nullptr)
		{
			if (d < node->data)
			{
				return SearchNodeData(d, node->left);
			}
			else if (d > node->data)
			{
				return SearchNodeData(d, node->right);
			}
			else
			{
				return node->data;
			}
		}
	}

	// search the node which holds the specific group index and return it
	GroupNode* SearchByNode(GroupNode* node, T d)
	{
		if (node != nullptr)
		{
			if (d < node->data)
			{
				return SearchByNode(node->left, d);
			}
			else if (d > node->data)
			{
				return SearchByNode(node->right, d);
			}
			else
			{
				return node;
			}
		}
		else
		{
			return nullptr; // if node not found return nullptr
		}
	}

	// find sucessor of node
	GroupNode* findMin(GroupNode* node)
	{
		while (node->left != nullptr)
		{
			node = node->left;
		}
		return node;
	}

	void deleteGroupNodes(T key, GroupNode*& node)
	{
		if (node == nullptr)
			return;

		if (key < node->data)
		{
			deleteGroupNodes(key, node->left);
		}
		else if (key > node->data)
		{
			deleteGroupNodes(key, node->right);
		}
		else
		{
			deleteSLL(node->userListHead);
			if (node->left == nullptr)
			{
				GroupNode* temp = node->right;
				delete node;
				node = temp;
			}
			else if (node->right == nullptr)
			{
				GroupNode* temp = node->left;
				delete node;
				node = temp;
			}
			else
			{
				GroupNode* minRight = findMin(node->right);
				node->data = minRight->data;
				if (minRight->userListHead != nullptr) // copy the list of sucessor node in the parent list
				{
					node->userListHead = new SLL<U>(*minRight->userListHead);
				}
				else
				{
					node->userListHead = nullptr;
				}
				deleteGroupNodes(node->data, node->right);
			}
		}
		balance(node);
	}

	// delete the entire sll in instance of group deletion
	void deleteSLL(SLL<U>* ptr)
	{
		ptr->deleteSLL();
	}

	// destructor
	void GroupAVLDeletion(GroupNode*& t)
	{
		if (t)
		{
			GroupAVLDeletion(t->left);
			GroupAVLDeletion(t->right);
			delete t;
		}
	}

public:

	GroupAVLTree()
	{
		root = nullptr;
	}

	void insert(T key, U userIterator)
	{
		insertNode(key, userIterator, root);
	}

	bool Search(T d)
	{
		return SearchSLLPtr(d, root);
	}

	// check if group index exists and if sll is empty or not
	bool SearchSLLPtr(T d, GroupNode* node)
	{
		if (SearchPtr(d, root) == true)
		{
			GroupNode* node = SearchN(d);
			if (node != nullptr)
			{
				return SLLEmpty(node->userListHead);
			}
		}
		else
		{
			return false;
		}
	}

	bool SLLEmpty(SLL<U>* ptr)
	{
		return ptr->isEmpty();
	}

	T SearchDisplay(T d)
	{
		return SearchNodeData(d, root);
	}

	GroupNode* SearchN(T d)
	{
		return SearchByNode(root, d);
	}

	void DisplayData(T d)
	{
		if (Search(d))
		{
			cout << "Index of AVL is "; // display the group index of the type or country
			cout << SearchDisplay(d) << endl;
			GroupNode* node = SearchN(d);
			DisplayList(node->userListHead);
		}
	}

	void DisplayList(SLL<U>* ptr)
	{
		ptr->DisplayList(); //display the list stored in group index
	}

	void deleteGroup(T key)
	{
		if (Search(key) == true)
		{
			deleteGroupNodes(key, root);
		}
	}

	void deleteGroupSLL(T key, int ID)
	{
		GroupNode* node = SearchN(key);
		if (node)
		{
			deleteSLLNode(node->userListHead, key, ID);
		}
	}

	void deleteSLLNode(SLL<U>* ptr, T key, int ID) // delete a certain node from ID and thus also in the avl without deleting the group index
	{
		ptr->deleteSLLNode(ID);
	}

	~GroupAVLTree()
	{
		GroupAVLDeletion(root);
	}
};

//class which holds list of all users as well as index pointers of all types of AVL Trees
class UserList
{
private:
	class Node // Node class of dll
	{
	public:

		User* data; // holds the data of a user in the dll
		Node* next;
		Node* prev;

		Node()
		{
			data = 0;
			next = 0;
			prev = 0;
		}

		Node(User* U = 0, Node* N = nullptr, Node* P = nullptr)
		{
			data = U;
			next = N;
			prev = P;
		}

		~Node()
		{
			next = 0;
			prev = 0;
			delete data;
		}
	};
	//list iterator class to put pointers in all AVL's
	class ListIterator
	{
	private:
		Node* current;
	public:

		ListIterator(Node* curr = 0)
		{
			current = curr;
		}

		ListIterator& operator++()  //Post-fix increment
		{
			if (current)
			{
				current = current->next;
			}
			return *this;
		}

		ListIterator operator++(int)   //Pre-fix increment
		{
			ListIterator old(current);
			if (current)
			{
				current = current->next;
			}
			return old;
		}

		ListIterator& operator--()   //Post-fix decrement
		{
			if (current)
			{
				current = current->prev;
			}
			return *this;
		}

		ListIterator operator--(int)   //Pre-fix decrement
		{
			ListIterator old(current);
			if (current)
			{
				current = current->prev;
			}
			return old;;
		}

		User*& operator*() // return the data of users 
		{

			return current->data;

		}

		bool operator==(const ListIterator& l) const
		{

			return current == l.current;

		}

		bool operator!=(const ListIterator& l) const
		{

			return !(current == l.current);

		}

		Node* getCurrent()
		{
			return current;
		}

		void DisplayUserIte() // display the current user data in the list iterator
		{
			current->data->printUser();
		}

		int getIteID() // get the id of the current user in the list iterator
		{
			return current->data->getID();
		}
	};

	Node* head;
	Node* tail;
	AVLTree<int, ListIterator> UserIDIndex; //Tree class with ID Index
	AVLTree<string, ListIterator> UserNameIndex; //Tree class with Name Index
	AVLTree<string, ListIterator> EmailIndex; //Tree class with Email Index
	GroupAVLTree<string, ListIterator> CountryIndex;//Group Tree class with Country Group Index
	GroupAVLTree<string, ListIterator> TypeIndex; //Group Tree class with Type Group Index


public:

	typedef ListIterator Iterator; //Define iterator to be used elsewhere in program

	//base constructor
	UserList()
	{
		head = new Node(0);
		tail = new Node(0);
		head->next = tail;
		tail->prev = head;
	}

	//Inserting a new user in dll
	void Insert(int ID, string Name, string email, string country, string type)
	{
		User* rhs = new User(ID, Name, email, country, type); // make a new user
		Node* in = new Node(rhs);
		if (head->next == tail) // if dll is empty perform insert at start
		{
			head->next = tail->prev = in;
			in->prev = head;
			in->next = tail;
			Iterator i(in);
			UserIDIndex.InsertInTree(rhs->getID(), i); // insert the dll's pointer with respective index in all trees
			UserNameIndex.InsertInTree(rhs->getName(), i);
			EmailIndex.InsertInTree(rhs->getEmail(), i);
			CountryIndex.insert(rhs->getCountry(), i);
			TypeIndex.insert(rhs->getType(), i);
		}
		else
		{
			Iterator i(in);
			Iterator insert = UserIDIndex.InsertInTreeAndList(rhs->getID(), i); // if dll not empty search for its closest node through ID Index tree in O log(n)
			Node* current = insert.getCurrent();
			if (current->data->getID() > in->data->getID()) // if closest node is greater than ID value insert before closest node
			{
				InsertBefore(current, in);
				UserIDIndex.InsertInTree(rhs->getID(), i);
				UserNameIndex.InsertInTree(rhs->getName(), i);
				EmailIndex.InsertInTree(rhs->getEmail(), i);
				CountryIndex.insert(rhs->getCountry(), i);
				TypeIndex.insert(rhs->getType(), i);
			}
			else
			{
				InsertAfter(current, in); // if closest node is lessser than ID value insert after closest node
				UserIDIndex.InsertInTree(rhs->getID(), i);
				UserNameIndex.InsertInTree(rhs->getName(), i);
				EmailIndex.InsertInTree(rhs->getEmail(), i);
				CountryIndex.insert(rhs->getCountry(), i);
				TypeIndex.insert(rhs->getType(), i);
			}
		}
	}

	//standard insert before function for a dll
	void InsertBefore(Node* current, Node* insert)
	{
		current->prev->next = insert;
		insert->prev = current->prev;
		insert->next = current;
		current->prev = insert;
	}

	//standard insert after function for a dll
	void InsertAfter(Node* current, Node* insert)
	{
		current->next->prev = insert;
		insert->next = current->next;
		insert->prev = current;
		current->next = insert;
	}

	//search a user using ID Index and dispkay it
	void SearchUsingID(int ID)
	{
		Iterator curr = UserIDIndex.Search(ID); //search in ID AVL Tree in O log(n) time and display its data
		if (curr != nullptr)
		{
			Node* display = curr.getCurrent();
			display->data->printUser();
		}
		else
		{
			cout << "User Not Found in List" << endl << endl;
		}
	}

	bool SearchExistence(int ID)
	{
		Iterator curr = UserIDIndex.Search(ID);
		if (curr != nullptr)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	string retCountry(int ID)
	{
		Iterator curr = UserIDIndex.Search(ID);
		Node* temp = curr.getCurrent();
		return temp->data->getCountry();
	}

	string retType(int ID)
	{
		Iterator curr = UserIDIndex.Search(ID);
		Node* temp = curr.getCurrent();
		return temp->data->getType();
	}


	//search a user using Name Index and dispkay it
	void SearchUsingName(string Name)
	{
		Iterator curr = UserNameIndex.Search(Name);
		if (curr != nullptr)
		{
			UserNameIndex.DisplayData(Name);
			Node* displayName = curr.getCurrent();
			displayName->data->printUser();
		}
		else // if Index not found then find it in dll in O (n) time and display its data
		{
			Node* check = nullptr;
			for (Node* temp = head->next; temp != tail; temp = temp->next)
			{
				if (temp->data->getName() == Name)
				{
					check = temp;
				}
			}

			if (check == nullptr)
			{
				cout << "User Not Found in List" << endl << endl;
			}
			else
			{
				cout << "Index of AVL was not found" << endl << endl;
				check->data->printUser();
			}
		}
	}

	void SearchUsingEmail(string Email)
	{
		Iterator curr = EmailIndex.Search(Email);
		if (curr != nullptr)
		{
			EmailIndex.DisplayData(Email);
			Node* displayName = curr.getCurrent();
			displayName->data->printUser();
		}
		else
		{
			Node* check = nullptr;
			for (Node* temp = head->next; temp != tail; temp = temp->next)
			{
				if (temp->data->getEmail() == Email)
				{
					check = temp;
				}
			}

			if (check == nullptr)
			{
				cout << "User Not Found in List" << endl << endl;
			}
			else
			{
				cout << "Index of AVL was not found" << endl << endl;
				check->data->printUser();
			}
		}
	}

	//function used to display a group of users belongig to a certain country
	void SearchUsingCountry(string Country)
	{
		bool ite = CountryIndex.Search(Country);
		if (ite != false)
		{
			CountryIndex.DisplayData(Country); // if group index found disolay alll of its sll nodes
		}
		else
		{
			Node* check = nullptr;
			bool found = false;
			int count = 0;
			for (Node* temp = head->next; temp != tail; temp = temp->next)
			{
				if (temp->data->getCountry() == Country) // if not found display each node in dll by searching it
				{
					if (found == false && count == 0)
					{
						found = true;
						cout << "Index of AVL was not found" << endl << endl;
						count++;
					}
					check = temp;
					check->data->printUser();
				}
			}

			if (check == nullptr)
			{
				cout << "User Not Found in List" << endl << endl;
			}
		}
	}

	void SearchUsingType(string Type)
	{
		bool ite = TypeIndex.Search(Type);
		if (ite != false)
		{
			TypeIndex.DisplayData(Type);
		}
		else
		{
			Node* check = nullptr;
			bool found = false;
			int count = 0;
			for (Node* temp = head->next; temp != tail; temp = temp->next)
			{
				if (temp->data->getType() == Type)
				{
					if (found == false && count == 0)
					{
						found = true;
						cout << "Index of AVL was not found" << endl << endl;
						count++;
					}
					check = temp;
					check->data->printUser();
				}
			}

			if (check == nullptr)
			{
				cout << "User Not Found in List" << endl << endl;
			}
		}
	}

	//delete a user from all trees and avl
	void DeleteUsingID(int ID)
	{

		Iterator del = UserIDIndex.RemoveFromTreeAndList(ID); //find the index by searching it in ID tree
		if (del != nullptr)
		{
			Node* current = del.getCurrent();
			if (current->next == tail && current->prev == head) // if one node exiss in dll
			{
				UserIDIndex.RemoveInTree(current->data->getID()); // delete all of its indexes fom every tree
				UserNameIndex.RemoveInTree(current->data->getName());
				EmailIndex.RemoveInTree(current->data->getEmail());
				CountryIndex.deleteGroupSLL(current->data->getCountry(), current->data->getID());
				TypeIndex.deleteGroupSLL(current->data->getType(), current->data->getID());
				head->next = tail;
				tail->prev = head;
				delete current;
			}
			else
			{
				UserIDIndex.RemoveInTree(current->data->getID());
				UserNameIndex.RemoveInTree(current->data->getName());
				EmailIndex.RemoveInTree(current->data->getEmail());
				CountryIndex.deleteGroupSLL(current->data->getCountry(), current->data->getID());
				TypeIndex.deleteGroupSLL(current->data->getType(), current->data->getID());
				current->next->prev = current->prev;
				current->prev->next = current->next;
				delete current;
			}
		}
		else
		{
			cout << "User to be Deleted is not found " << endl << endl;
		}
	}

	// delete user Name index from name avl
	void DeleteUsingName(string Name)
	{

		Iterator del = UserNameIndex.RemoveFromTreeAndList(Name);
		if (del != nullptr)
		{
			UserNameIndex.RemoveInTree(Name);
		}
		else
		{
			cout << "User to be Deleted is not found " << endl << endl;
		}
	}

	void DeleteUsingEmail(string Email)
	{

		Iterator del = EmailIndex.RemoveFromTreeAndList(Email);
		if (del != nullptr)
		{
			EmailIndex.RemoveInTree(Email);
		}
		else
		{
			cout << "User to be Deleted is not found " << endl << endl;
		}
	}

	//delete group index in group avl tree
	void DeleteUsingCountry(string Country)
	{
		bool ite = CountryIndex.Search(Country);
		if (ite != false)
		{
			CountryIndex.deleteGroup(Country);
		}
		else
		{
			cout << "User to be Deleted is not found " << endl << endl;
		}
	}

	void DeleteUsingType(string Type)
	{
		bool ite = TypeIndex.Search(Type);
		if (ite != false)
		{
			TypeIndex.deleteGroup(Type);
		}
		else
		{
			cout << "User to be Deleted is not found " << endl << endl;
		}
	}


	// print all users in the dll
	void printlist()
	{
		if (head->next != tail)
		{
			for (Node* temp = head->next; temp != tail; temp = temp->next)
			{
				temp->data->printUser();
			}
		}
		else
		{
			cout << "There are no Users in UserList " << endl << endl;
		}
	}

	//destructor
	~UserList()
	{
		Node* temp = nullptr;
		while (head->next != nullptr)
		{
			temp = head;
			head = head->next;
			delete temp;
		}
	}

};

template <class U>
class SLLComplaint
{
private:
	class SLLNode
	{
	public:
		U ptr;
		SLLNode* next;
		SLLNode(U p, SLLNode* n = nullptr) : ptr(p), next(n)
		{

		}
		~SLLNode()
		{
			next = 0;
		}
	};

	SLLNode* head;
	SLLNode* tail;
public:
	// uses dummy nodes
	SLLComplaint()
	{
		head = new SLLNode(0);
		tail = new SLLNode(0);
		head->next = tail;
	}

	SLLComplaint(const SLLComplaint& rhs)  //copy constructor
	{

		head = new SLLNode(0, nullptr);  // Dummy head node
		tail = new SLLNode(0, nullptr);  // Dummy tail node
		head->next = tail;

		SLLNode* curr = rhs.head->next;
		SLLNode* end = head;

		while (curr != nullptr && curr != rhs.tail)
		{
			SLLNode* newNode = new SLLNode(curr->ptr);
			end->next = newNode;
			end = newNode;
			curr = curr->next;
		}

		end->next = tail;
	}

	//basic insert at start function used for a standard SLL
	void insertAtStart(U ptr)
	{
		if (head->next == tail)
		{
			SLLNode* temp = new SLLNode(ptr, tail);
			head->next = temp;
		}
		else
		{
			SLLNode* temp = new SLLNode(ptr, head->next);
			head->next = temp;
		}
	}

	// display all users of a certain country or type
	void DisplayList()
	{
		if (head->next != nullptr)
		{
			for (SLLNode* temp = head->next; temp != tail; temp = temp->next)
			{
				DisplayIte(temp->ptr);
			}
		}
	}

	//accesses the display users through class List Iterator
	void DisplayIte(U ptr)
	{
		cout << ptr;
	}

	// delete SLL completely when index is being deleted
	void deleteSLL()
	{
		while (head->next != nullptr)
		{
			SLLNode* temp = head->next;
			SLLNode* temp2 = temp->next;
			head->next = temp2;
			delete temp;
		}
	}

	// delete a certain node from sll
	bool deleteSLLNode(int ID)
	{
		// if sll is empty
		if (head->next == tail)
		{
			return false;
		}
		else
		{
			SLLNode* del = nullptr;
			SLLNode* store = nullptr;
			bool flag = false;
			for (SLLNode* temp = head; temp->next != tail && flag == false; temp = temp->next)
			{
				SearchSLLNode(temp->next, del, ID); // find the node in the sll with given id
				if (del != nullptr && flag == false) // if found delete it
				{
					flag = true;
					store = temp;
				}
			}

			if (flag == true) // deletion done through gwtting previous node and setting it to nodes next node and deleting the node so no extra processing time is required
			{
				SLLNode* temp2 = store->next;
				SLLNode* change = del->next;
				store->next = change;
				delete temp2;
			}
		}
	}

	// helper fuction for the previous function
	void SearchSLLNode(SLLNode* temp, SLLNode*& ret, int ID)
	{
		if (temp->ptr.getComplaintID() == ID) // compares node id with give id
		{
			ret = temp;
		}
	}

	// checks if sll is empty 
	bool isEmpty()
	{
		if (head->next == tail)
		{
			return false;
		}
		else
		{
			return true;
		}
	}

};

template <class T>
class GroupAVLTreeComplaints
{
private:
	class GroupNode //node class to hod the data of the tree
	{
	public:
		T data;
		typename SLLComplaint<Complaint>* userListHead; //singlylink list to hold gorup of pointers to users
		int height;
		GroupNode* left;
		GroupNode* right;

		GroupNode(T d) :height(0), left(nullptr), right(nullptr)
		{
			data = d;
			userListHead = new SLLComplaint<Complaint>; //initialising SLL as it is a pointer
		}

		~GroupNode()
		{
			left = nullptr;
			right = nullptr;
		}
	};

	GroupNode* root;

	int Height(GroupNode* node)
	{
		if (node == nullptr)
		{
			return -1;
		}
		int Left = -1;
		int Right = -1;
		if (node->left)
		{
			Left = node->left->height;
		}
		if (node->right)
		{
			Right = node->right->height;
		}
		return max(Left, Right) + 1;
	}

	void LeftRotate(GroupNode*& x)
	{
		GroupNode* orphan = x->right->left;
		GroupNode* y = x->right;

		y->left = x;
		x->right = orphan;

		x->height = Height(x);
		y->height = Height(y);

		x = y;
	}

	void RightRotate(GroupNode*& x)
	{
		GroupNode* orphan = x->left->right;
		GroupNode* y = x->left;

		y->right = x;
		x->left = orphan;

		x->height = Height(x);
		y->height = Height(y);

		x = y;
	}

	void doubleLeftRightRotation(GroupNode*& x)
	{
		LeftRotate(x->left);
		RightRotate(x);
	}

	void doubleRightLeftRotation(GroupNode*& x)
	{
		RightRotate(x->right);
		LeftRotate(x);
	}

	void balance(GroupNode*& node)
	{
		if (node == nullptr)
		{
			return;
		}

		if (Height(node->left) - Height(node->right) > 1)
		{
			if (Height(node->left->left) >= Height(node->left->right))
			{
				RightRotate(node);
			}
			else
			{
				doubleLeftRightRotation(node);
			}
		}
		else if (Height(node->right) - Height(node->left) > 1)
		{
			if (Height(node->right->right) >= Height(node->right->left))
			{
				LeftRotate(node);
			}
			else {
				doubleRightLeftRotation(node);
			}
		}
		node->height = max(Height(node->left), Height(node->right)) + 1;
	}

	//insert a node in group avl and see if it creates a new node or is sent to a sll
	void insertNode(T key, Complaint ptr, GroupNode*& node)
	{
		if (node == nullptr)
		{
			node = new GroupNode(key);
			InsertInSLL(node->userListHead, ptr); //initial insertion of a new countr or type
		}
		else if (key < node->data)
		{
			insertNode(key, ptr, node->left);
		}
		else if (key > node->data)
		{
			insertNode(key, ptr, node->right);
		}
		else
		{
			InsertInSLL(node->userListHead, ptr); // if same country or type is made insert the new pointer in the SLL
		}
		balance(node);
	}

	void InsertInSLL(SLLComplaint<Complaint>* ptr, Complaint in)
	{
		ptr->insertAtStart(in); // function in sll class to insert a new pointer in the sll
	}

	//search the avl to find a group index which matches the given type or country in log(n) time
	bool SearchPtr(T d, GroupNode* node)
	{
		if (node != nullptr)
		{
			if (d < node->data)
			{
				return SearchPtr(d, node->left);
			}
			else if (d > node->data)
			{
				return SearchPtr(d, node->right);
			}
			else
			{
				return true;
			}
		}
		else
		{
			return false;
		}
	}


	// this function is used to dislay the node index in Q3
	T SearchNodeData(T d, GroupNode* node)
	{
		if (node != nullptr)
		{
			if (d < node->data)
			{
				return SearchNodeData(d, node->left);
			}
			else if (d > node->data)
			{
				return SearchNodeData(d, node->right);
			}
			else
			{
				return node->data;
			}
		}
	}

	// search the node which holds the specific group index and return it
	GroupNode* SearchByNode(GroupNode* node, T d)
	{
		if (node != nullptr)
		{
			if (d < node->data)
			{
				return SearchByNode(node->left, d);
			}
			else if (d > node->data)
			{
				return SearchByNode(node->right, d);
			}
			else
			{
				return node;
			}
		}
		else
		{
			return nullptr; // if node not found return nullptr
		}
	}

	// find sucessor of node
	GroupNode* findMin(GroupNode* node)
	{
		while (node->left != nullptr)
		{
			node = node->left;
		}
		return node;
	}

	void deleteGroupNodes(T key, GroupNode*& node)
	{
		if (node == nullptr)
			return;

		if (key < node->data)
		{
			deleteGroupNodes(key, node->left);
		}
		else if (key > node->data)
		{
			deleteGroupNodes(key, node->right);
		}
		else
		{
			deleteSLL(node->userListHead);
			if (node->left == nullptr)
			{
				GroupNode* temp = node->right;
				delete node;
				node = temp;
			}
			else if (node->right == nullptr)
			{
				GroupNode* temp = node->left;
				delete node;
				node = temp;
			}
			else
			{
				GroupNode* minRight = findMin(node->right);
				node->data = minRight->data;
				if (minRight->userListHead != nullptr) // copy the list of sucessor node in the parent list
				{
					node->userListHead = new SLL<Complaint>(*minRight->userListHead);
				}
				else
				{
					node->userListHead = nullptr;
				}
				deleteGroupNodes(node->data, node->right);
			}
		}
		balance(node);
	}

	// delete the entire sll in instance of group deletion
	void deleteSLL(SLLComplaint<Complaint>* ptr)
	{
		ptr->deleteSLL();
	}

	// destructor
	void GroupAVLDeletion(GroupNode*& t)
	{
		if (t)
		{
			GroupAVLDeletion(t->left);
			GroupAVLDeletion(t->right);
			delete t;
		}
	}

public:

	GroupAVLTreeComplaints()
	{
		root = nullptr;
	}

	void insert(T key, Complaint userIterator)
	{
		insertNode(key, userIterator, root);
	}

	bool Search(T d)
	{
		return SearchSLLPtr(d, root);
	}

	// check if group index exists and if sll is empty or not
	bool SearchSLLPtr(T d, GroupNode* node)
	{
		if (SearchPtr(d, root) == true)
		{
			GroupNode* node = SearchN(d);
			if (node != nullptr)
			{
				return SLLEmpty(node->userListHead);
			}
		}
		else
		{
			return false;
		}
	}

	bool SLLEmpty(SLLComplaint<Complaint>* ptr)
	{
		return ptr->isEmpty();
	}

	T SearchDisplay(T d)
	{
		return SearchNodeData(d, root);
	}

	GroupNode* SearchN(T d)
	{
		return SearchByNode(root, d);
	}

	void DisplayData(T d)
	{
		if (Search(d))
		{
			cout << "Index of AVL is "; // display the group index of the type or country
			cout << SearchDisplay(d) << endl;
			GroupNode* node = SearchN(d);
			DisplayList(node->userListHead);
		}
		else
		{
			cout << "Index not Found " << endl << endl;
		}
	}

	void DisplayList(SLLComplaint<Complaint>* ptr)
	{
		ptr->DisplayList(); //display the list stored in group index
	}

	void deleteGroup(T key)
	{
		if (Search(key) == true)
		{
			deleteGroupNodes(key, root);
		}
	}

	void deleteGroupSLL(T key, int ID)
	{
		GroupNode* node = SearchN(key);
		if (node)
		{
			deleteSLLNode(node->userListHead, key, ID);
		}
	}

	void deleteSLLNode(SLLComplaint<Complaint>* ptr, T key, int ID) // delete a certain node from ID and thus also in the avl without deleting the group index
	{
		ptr->deleteSLLNode(ID);
	}

	~GroupAVLTreeComplaints()
	{
		GroupAVLDeletion(root);
	}
};

//class to sort complaints into a min heap
template <class T>
class PriorityQueue
{
private:
	T* data;
	int currentsize;
	int max;

	//basic reheapUp and reheapDown functions
	void ReheapDown(int cnode, int last)
	{
		int minChild, leftChild, rightChild;
		leftChild = 2 * cnode + 1;
		rightChild = 2 * cnode + 2;

		if (leftChild <= last)
		{
			if (leftChild == last)
			{
				minChild = leftChild;
			}
			else
			{
				if (data[leftChild] < data[rightChild])
					minChild = leftChild;
				else
					minChild = rightChild;
			}


			if (data[minChild] < data[cnode])
			{
				swap(data[cnode], data[minChild]);
				ReheapDown(minChild, last);
			}
		}
	}

	void ReheapUp(int root, int last)
	{
		int parent;
		if (last > root)
		{
			parent = (last - 1) / 2;
			if (data[last] < data[parent])
			{
				T temp = data[parent];
				data[parent] = data[last];
				data[last] = temp;
				ReheapUp(root, parent);
			}
		}
	}
public:
	PriorityQueue()
	{
		data = new T[100];
		currentsize = 0;
		max = 100;
	}

	//insert a complaint in priority queue and then sort the entire queue again
	void Insert(const T& x)
	{
		if (currentsize < max)
		{
			currentsize++;
			data[currentsize - 1] = x;
			ReheapUp(0, currentsize - 1);
		}
	}

	//check if queue is empty
	bool isEmpty() const
	{
		return currentsize == 0;
	}

	//get top of queue as it is a min heap
	const T& getMin() const
	{
		if (currentsize != 0)
		{
			return data[0];
		}
		else
		{
			return -1;
		}
	}

	int getMinUID()
	{
		if (currentsize != 0)
		{
			return data[0].getUserID();
		}
	}

	int getMinCID()
	{
		if (currentsize != 0)
		{
			return data[0].getComplaintID();
		}
	}

	int getMinCountry()
	{
		if (currentsize != 0)
		{
			return data[0].getCountry();
		}
	}

	void retMin()
	{
		if (currentsize != 0)
		{
			cout << data[0];
		}
		else
		{
			cout << "List is Empty so No Complaint can be processed" << endl << endl;
		}
	}

	//delete the top of queue or service it
	void deleteMin()
	{
		if (currentsize != 0)
		{
			data[0] = data[currentsize - 1];
			currentsize = currentsize - 1;
			ReheapDown(0, currentsize - 1);
		}
	}

	bool deleteAll(T key)
	{
		bool ret = false;
		int i = 0;
		while (i < currentsize)
		{
			if (data[i] == key)
			{
				data[i] = data[currentsize - 1];
				currentsize--;
				ReheapDown(i, currentsize - 1);
				ReheapUp(i, currentsize - 1);
				ret = true;
			}
			else
			{
				i++;
			}
		}
		return ret;
	}

	void printHeap()
	{
		if (currentsize != 0)
		{
			int current = currentsize;
			for (int i = 0; i < current; i++)
			{
				cout << data[i];
		/*		cout << getMin();
				deleteMin();*/
			}
		}
		else
		{
			cout << "Priority Complaint List is Empty " << endl;
		}
		cout << endl << endl;
	}

	//increase the priority of a certain complaint
	void PriorityUp(int ID)
	{
		bool flag = false;
		for (int i = 0; i < currentsize && flag == false; i++)
		{
			if (data[i].getComplaintID() == ID)
			{
				data[i].IncreasePriority();
				ReheapUp(0, i);
				flag = true;
			}
		}

		if (flag == false)
		{
			cout << "Complaint not Found " << endl << endl;
		}
	}

	~PriorityQueue()
	{
		if (data)
		{
			delete[] data;
		}
	}
};

//Main class which holds the data of all users and complaints
class CustomerModel
{
private:
	UserList* Users; //list of users
	PriorityQueue<Complaint>* ComplaintList; //queue of complaints
	GroupAVLTreeComplaints<int>UserComplaints; //group of users with common complaints
	GroupAVLTreeComplaints<string>CountryComplaints; //group of countries with common complaints

public:

	CustomerModel() //base constructor
	{
		Users = new UserList;
		ComplaintList = new PriorityQueue<Complaint>;
	}

	//wrapper functions for all userlist users
	void insert(int ID , string Name , string Email , string Country , string Type)
	{
		Users->Insert(ID, Name, Email, Country, Type);
	}

	void print()
	{
		Users->printlist();
	}

	void SearchID(int ID)
	{
		Users->SearchUsingID(ID);
	}

	void SearchEmail(string Email)
	{
		Users->SearchUsingEmail(Email);
	}

	void SearchName(string Name)
	{
		Users->SearchUsingName(Name);
	}

	void SearchCountry(string Country)
	{
		Users->SearchUsingCountry(Country);
	}

	void SearchType(string Type)
	{
		Users->SearchUsingType(Type);
	}

	void DeleteID(int ID)
	{
		Users->DeleteUsingID(ID);
	}

	void DeleteName(string Name) 
	{
		Users->DeleteUsingName(Name);
	}

	void DeleteEmail(string Email)
	{
		Users->DeleteUsingEmail(Email);
	}

	void DeleteCountry(string Country)
	{
		Users->DeleteUsingCountry(Country);
	}

	void DeleteType(string Type)
	{
		Users->DeleteUsingType(Type);
	}

	//check if user exists in user list
	bool CheckUserinUserList(int ID)
	{
		return Users->SearchExistence(ID);
	}

	void InsertComplaint(int UID , int CID , string comp)
	{
		bool check = CheckUserinUserList(UID); //check if user is registered so we can register their complaint
		if (check)
		{
			Complaint temp = Complaint (UID, CID, comp, getUserCountry(UID), getUserType(UID));
			ComplaintList->Insert(temp);
			UserComplaints.insert(temp.getUserID(), temp);
			CountryComplaints.insert(temp.getCountry(), temp);
		}
		else
		{
			cout << "Complaint with User ID " << UID << " cannot be registered as User does not exist " << endl << endl;
		}
	}

	void DisplayComplaint()
	{
		ComplaintList->printHeap(); //display complaint
	}

	void ProcessComplaint() //process the complaint or remove it from the top of complaint queue
	{
		bool checkEmpty = ComplaintList->isEmpty();
		if (checkEmpty == false)
		{
			cout << "Servicing Complaint: " << endl;
			Complaint temp = ComplaintList->getMin();
			ComplaintList->retMin();
			UserComplaints.deleteGroupSLL(temp.getUserID(), temp.getComplaintID());
			CountryComplaints.deleteGroupSLL(temp.getCountry(), temp.getComplaintID());
			ComplaintList->deleteMin();
		}
		else
		{
			cout << "There are no complaints, hence Complaint Servicing cannot be done" << endl << endl;
		}

	}

	string getUserCountry(int ID)
	{
		return Users->retCountry(ID);
	}

	string getUserType(int ID)
	{
		return Users->retType(ID);
	}

	//wrapper functions for ComplaintList priority queue
	void IncreasePriority(int ID)
	{
		ComplaintList->PriorityUp(ID);
	}

	void SearchUsingComplaintUserID(int ID)
	{
		UserComplaints.DisplayData(ID);
	}

	void SearchUsingComplaintCountry(string country)
	{
		CountryComplaints.DisplayData(country);
	}

	//destructor
	~CustomerModel()
	{
		delete Users;
		delete ComplaintList;
	}
};


int main()
{
	CustomerModel CSM;
	CSM.insert(1, "Moiz", "moiz6299@gmail.com", "Sweden", "gold");
	CSM.insert(77, "Ghayas", "gassu@gmail.com", "Pakistan", "silver");
	CSM.insert(93, "Nihaal", "nihaaldurrani@gmail.com", "Pakistan", "gold");
	CSM.insert(32, "Burhan", "burhan6969@gmail.com", "India", "gold");
	CSM.insert(23, "Saif", "saifi@gmail.com", "Pakistan", "platinum");
	CSM.insert(15, "Saad", "SaadDelulu@gmail.com", "Sweden", "silver");
	CSM.insert(55, "Shahzaib", "shazu@gmail.com", "Pakistan", "gold");
	CSM.insert(100, "KelaShahid", "Kela@gmail.com", "India", "platinum");
	CSM.insert(18, "Manzer", "Manzer@gmail.com", "Pakistan", "gold");
	CSM.insert(42, "Ali", "ali@gmail.com", "India", "gold");
	CSM.insert(25, "Ahmad", "ayk@gmail.com", "Pakistan", "platinum");
	CSM.insert(2, "Soban", "Soban@gmail.com", "America", "regular");
	CSM.insert(51, "Ammar", "chappalChor@gmail.com", "America", "regular");
	CSM.insert(101, "Uneeb", "SadUneeb@gmail.com", "Pakistan", "new");
	CSM.print();

	cout << "Deleting User using ID 42 , 93 , 25 , 55" << endl << endl;
	CSM.DeleteID(42);
	CSM.DeleteID(93);
	CSM.DeleteID(25);
	CSM.DeleteID(55);
	CSM.print();

	cout << "Searching User 77 in List using User ID" << endl << endl;

	CSM.SearchID(77);

	cout << "Searching User in List using User Name: Moiz" << endl << endl;
	CSM.SearchName("Moiz");

	cout << "Deleting User in Name AVL using User Name : Moiz" << endl << endl;
	CSM.DeleteName("Moiz");

	cout << "Searching User in List using User Name: Moiz after Deletion from Name AVL Tree" << endl << endl;
	CSM.SearchName("Moiz");

	cout << "Searching User index in List using Email: moiz6299@gmail.com" << endl << endl;
	CSM.SearchEmail("moiz6299@gmail.com");

	cout << "Deleting User index in Email AVL using Email: moiz6299@gmail.com" << endl << endl;
	CSM.DeleteEmail("moiz6299@gmail.com");

	cout << "Searching User index in List using Email: moiz6299@gmail.com after Deletion from Email AVL Tree" << endl << endl;
	CSM.SearchEmail("moiz6299@gmail.com");

	cout << "Searching User group index in List using User Country: Pakistan" << endl << endl;
	CSM.SearchCountry("Pakistan");

	cout << "Deleting group index and Searching User in List using User Country: Pakistan" << endl << endl;
	CSM.DeleteCountry("Pakistan");
	CSM.SearchCountry("Pakistan");

	cout << "Searching User index in List using User Type: platinum" << endl << endl;
	CSM.SearchType("platinum");

	cout << "Deleting group index and Searching User in List using User Type: platinum" << endl << endl;
	CSM.DeleteType("platinum");
	CSM.SearchType("platinum");

	cout << "Registering Complaints of Multiple Users " << endl << endl;
	CSM.InsertComplaint(23, 100, "VolleyBall Khelni Hai");
	CSM.InsertComplaint(1, 10, "Libero nhi ban sakta");
	CSM.InsertComplaint(23, 99, "Setting is off");
	CSM.InsertComplaint(19, 17, "Armi Cutie");
	CSM.InsertComplaint(23, 12, "FAST NUCES :( ");
	CSM.InsertComplaint(1, 56, "Smog");
	CSM.InsertComplaint(1, 24, "Projects Overload");
	CSM.InsertComplaint(77, 111, "Fortnite not Updating");
	CSM.InsertComplaint(51, 72, "Online Classes");
	CSM.InsertComplaint(101, 66, "Faulty Internet");
	CSM.DisplayComplaint();

	cout << "Servicing Highest Priority Complaint " << endl << endl;
	CSM.ProcessComplaint();
	cout << "Displaying new Complaint Priority List " << endl << endl;
	CSM.DisplayComplaint();

	cout << "Increasing Priority of Complaint with ID 56" << endl << endl;
	CSM.IncreasePriority(56);
	CSM.DisplayComplaint();

	cout << "Searching Priority Complaints using User ID 1" << endl << endl;
	CSM.SearchUsingComplaintUserID(1);

	cout << "Searching Priority Complaints using Country Pakistan" << endl << endl;
	CSM.SearchUsingComplaintCountry("Pakistan");


	system("pause");
	return 0;
}