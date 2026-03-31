#include <iostream>
#include <string>
#include <algorithm>
#include <cstdlib>
#include <ctime>
using namespace std;

static int PriorityUp = 0;

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
		priority = PriorityUp;
		PriorityUp--;
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

template <class T>
class HashTable //Universal Hash Class with double Hashing
{
private:
	class HashItem //Class to hold hash table data
	{
	public:
		int val; // key of type ID
		T ptr;
		int status; // 11 for deleted 2 for occupied 0 for empty

		HashItem(int k = 0, T p = nullptr, int s = 0)
		{
			val = k;
			ptr = nullptr;
			status = s;
		}
	};
	HashItem* table;
	int tableSize;
	int a;
	int b;
	int p; // a , b , p used for universal hashing
	int size;

	int Hash1(int k)
	{
		return ((a * k + b) % p) % tableSize; //basic universal hash function
	}

	int Hash2(int k, int i)
	{
		int h1 = Hash1(k);
		int h2 = p - (k % p);
		return (h1 + (h2 * i)) % tableSize; //double hashing 
	}

	int findPrime(int num) //find a prime number larger than tableSize
	{
		for (int i = num - 1; i >= 2; --i)
		{
			if (isPrime(i))
			{
				return i;
			}
		}
		return 2;
	}

	bool isPrime(int num) // check if number is prime
	{
		if (num < 2)
		{
			return false;
		}
		for (int i = 2; i * i <= num; ++i)
		{
			if (num % i == 0) {
				return false;
			}
		}
		return true;
	}

public:
	HashTable(int c) //base constructor
	{
		tableSize = c;
		size = 0;
		table = new HashItem[tableSize];
		for (int i = 0; i < tableSize; i++)
		{
			table[i] = HashItem();
		}
		srand(time(0)); // set on random time 
		a = rand() % (tableSize - 1) + 1;
		b = rand() % tableSize;
		p = findPrime(tableSize);
	}

	void InsertUser(int key, T ptr) // Insert User into hash table of type ID
	{
		if (size < tableSize)
		{
			int index = Hash1(key);
			int j = 0;
			for (int i = 0;(table[index].status == 2) && (table[index].val != key); i++) // check if cell is not occupied
			{
				j++;
				index = Hash2(key, j);
			}
			table[index].val = key; // set values of cell to given items
			table[index].status = 2;
			table[index].ptr = ptr;
			size++;
		}
		else
		{
			return;
		}
	}

	T SearchUser(int key) // search a user of a given ID
	{
		int index = Hash1(key);
		int j = 0;

		for (int i = 0; table[index].status != 0; i++)
		{
			if ((table[index].status == 2) && (table[index].ptr.getIteID() == key)) /// if key found
			{
				return table[index].ptr;
			}
			else
			{
				j++;
				index = Hash2(key, j); // if not found do double Hashing
			}
		}
		return nullptr;
	}

	void RemoveInHashID(int key) // remove a givne USer ID user from hash Table
	{
		int index = Hash1(key);
		int j = 0;
		bool del = false;

		for (int i = 0; table[index].status != 0 && del == false; i++)
		{
			if ((table[index].status == 2) && (table[index].val == key))
			{
				table[index].status = 1;
				del = true;
			}
			else
			{
				j++;
				index = Hash2(key, j);
			}
		}

	}

	// destructor
	~HashTable()
	{
		if (table)
		{
			delete[] table;
		}
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
		string val;
		U ptr; //pointer to user list
		SLLNode* next;
		SLLNode(U p, SLLNode* n = nullptr, string v = "0") : ptr(p), next(n)
		{
			val = v;
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
	void insertAtStart(U ptr, string s)
	{
		if (head->next == tail)
		{
			SLLNode* temp = new SLLNode(ptr, tail, s);
			head->next = temp;
		}
		else
		{
			SLLNode* temp = new SLLNode(ptr, head->next, s);
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
	bool deleteSLLNodeName(string Name)
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
				SearchSLLNodeName(temp->next, del, Name); // find the node in the sll with given id
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
				return true;
			}
			else
			{
				return false;
			}
		}
	}

	// helper fuction for the previous function
	void SearchSLLNodeName(SLLNode* temp, SLLNode*& ret, string s)
	{
		if (temp->ptr != nullptr)
		{
			string c = temp->ptr.getIteName();
			if (c == s) // compares node id with give id
			{
				ret = temp;
			}
		}
	}

	// delete a certain node from sll
	bool deleteSLLNodeEmail(string Email)
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
				SearchSLLNodeEmail(temp->next, del, Email); // find the node in the sll with given id
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
				return true;
			}
			else
			{
				return false;
			}
		}
	}

	// helper fuction for the previous function
	void SearchSLLNodeEmail(SLLNode* temp, SLLNode*& ret, string s)
	{
		if (temp->ptr != nullptr)
		{
			string c = temp->ptr.getIteEmail();
			if (c == s) // compares node id with give id
			{
				ret = temp;
			}
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

	U SearchSLLName(string Name) // search for a node in SLL on the base of email
	{
		if (head->next == tail)
		{
			return nullptr;
		}
		SLLNode* ret = nullptr;
		bool flag = false;
		for (SLLNode* temp = head->next; temp != tail && flag == false; temp = temp->next)
		{
			SearchSLLNodeName(temp, ret, Name); // find the node in the sll with given id
			if (ret != nullptr && flag == false) // if found delete it
			{
				flag = true;
			}
		}
		if (flag == true)
		{
			return ret->ptr;
		}
		else
		{
			return nullptr;
		}
	}

	U SearchSLLEmail(string Email)
	{
		if (head->next == tail)
		{
			return nullptr;
		}
		SLLNode* ret = nullptr;
		bool flag = false;
		for (SLLNode* temp = head->next; temp != tail && flag == false; temp = temp->next)
		{
			SearchSLLNodeEmail(temp, ret, Email); // find the node in the sll with given id
			if (ret != nullptr && flag == false) // if found delete it
			{
				flag = true;
			}
		}
		if (flag == true)
		{
			return ret->ptr;
		}
		else
		{
			return nullptr;
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

template <class T>
class ChainHash // Hash Tbale Made for Name and Email on the base of Name And Email
{
private:
	class HashItemC
	{
	public:
		typename SLL<T>* ptr;
		int status;

		HashItemC(T p = nullptr, int s = 0)
		{
			ptr = new SLL<T>;
			status = s;
		}

		~HashItemC()
		{

		}
	};
	HashItemC* table;
	int tableSize;
	int size;

	unsigned int ChainHashVal(const string& key, int size) //Hashing a string 
	{
		unsigned int index = 0;
		for (char ch : key)
		{
			index = (37 * index) + ch;
		}
		return index % size;
	}

public:
	ChainHash(int c) //base constructor
	{
		tableSize = c;
		size = 0;
		table = new HashItemC[tableSize];
		for (int i = 0; i < tableSize; i++)
		{
			table[i] = HashItemC();
		}
	}

	void InsertChain(string s, T ptr)
	{
		if (size < tableSize)
		{
			int index = 0;
			index = ChainHashVal(s, tableSize); // Insert Direct in hash Value as it is chaining so collision does not matter
			InsertInTable(s, table[index], ptr);
			if (table[index].status == 0)
			{
				size++;
			}
			table[index].status = 2;
		}
		else
		{
			return;
		}
	}

	void InsertInTable(string s, HashItemC in, T ptr) // Insert in SLL
	{
		in.ptr->insertAtStart(ptr, s);
	}

	T SearchChainName(string s)
	{
		int index = 0;
		index = ChainHashVal(s, tableSize); // Search At given Index
		if (table[index].status == 2)
		{
			return SearchInTableName(table[index], s);
		}
		else
		{
			return nullptr;
		}
	}

	T SearchInTableName(HashItemC in, string s) // Search In Table
	{
		return in.ptr->SearchSLLName(s);
	}

	bool DeleteChainStringName(string s)
	{
		int index = 0;
		index = ChainHashVal(s, tableSize);
		return DeleteInTableName(table[index], s);
	}

	bool DeleteInTableName(HashItemC in, string s)
	{
		return in.ptr->deleteSLLNodeName(s);
	}

	T SearchChainEmail(string s)
	{
		int index = 0;
		index = ChainHashVal(s, tableSize);
		if (table[index].status == 2)
		{
			return SearchInTableEmail(table[index], s);
		}
		else
		{
			return nullptr;
		}
	}

	T SearchInTableEmail(HashItemC in, string s)
	{
		return in.ptr->SearchSLLEmail(s);
	}

	bool DeleteChainStringEmail(string s)
	{
		int index = 0;
		index = ChainHashVal(s, tableSize);
		return DeleteInTableEmail(table[index], s);
	}

	bool DeleteInTableEmail(HashItemC in, string s)
	{
		return in.ptr->deleteSLLNodeEmail(s);
	}

	~ChainHash()
	{
		if (table)
		{
			delete[] table;
		}
	}

};

//SLL class used for group of indexes in group avl tree
template <class U>
class GroupSLL
{
private:
	class GroupSLLNode
	{
	public:
		U ptr; //pointer to user list
		GroupSLLNode* next;
		GroupSLLNode(U p, GroupSLLNode* n = nullptr) : ptr(p), next(n)
		{

		}
		~GroupSLLNode()
		{
			next = 0;
		}
	};

	GroupSLLNode* head;
	GroupSLLNode* tail;

public:
	// uses dummy nodes
	GroupSLL()
	{
		head = new GroupSLLNode(0);
		tail = new GroupSLLNode(0);
		head->next = tail;
	}

	GroupSLL(const GroupSLL& rhs)  //copy constructor
	{

		head = new GroupSLLNode(0, nullptr);  // Dummy head node
		tail = new GroupSLLNode(0, nullptr);  // Dummy tail node
		head->next = tail;

		GroupSLLNode* curr = rhs.head->next;
		GroupSLLNode* end = head;

		while (curr != nullptr && curr != rhs.tail)
		{
			GroupSLLNode* newNode = new GroupSLLNode(curr->ptr);
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
			GroupSLLNode* temp = new GroupSLLNode(ptr, tail);
			head->next = temp;
		}
		else
		{
			GroupSLLNode* temp = new GroupSLLNode(ptr, head->next);
			head->next = temp;
		}
	}

	// delete SLL completely when index is being deleted
	void deleteSLL()
	{
		while (head->next != nullptr)
		{
			GroupSLLNode* temp = head->next;
			GroupSLLNode* temp2 = temp->next;
			head->next = temp2;
			delete temp;
		}
		head->next = tail;
	}

	// display all users of a certain country or type
	void DisplayList()
	{
		if (head->next != nullptr)
		{
			for (GroupSLLNode* temp = head->next; temp != tail; temp = temp->next)
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
			GroupSLLNode* del = nullptr;
			GroupSLLNode* store = nullptr;
			bool flag = false;
			for (GroupSLLNode* temp = head; temp->next != tail && flag == false; temp = temp->next)
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
				GroupSLLNode* temp2 = store->next;
				GroupSLLNode* change = del->next;
				store->next = change;
				delete temp2;
			}
		}
	}

	// helper fuction for the previous function
	void SearchSLLNode(GroupSLLNode* temp, GroupSLLNode*& ret, int ID)
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
	~GroupSLL()
	{
		if (head->next != tail)
		{
			while (head->next != nullptr)
			{
				GroupSLLNode* temp = head->next;
				GroupSLLNode* temp2 = temp->next;
				head->next = temp2;
				delete temp;
			}
		}
	}
};

template <class T>
class GroupHash // Hash Table Made on the base of group hashing through chaining users with common countries or types
{
private:
	class HashItemG
	{
	public:
		string val;
		typename GroupSLL<T>* ptr;
		int status;

		HashItemG(string str = "0", T p = nullptr, int s = 0)
		{
			val = str;
			ptr = new GroupSLL<T>;
			status = s;
		}

		~HashItemG()
		{

		}
	};
	HashItemG* table;
	int tableSize;
	int size;

	unsigned int GroupHashVal(const string& key, int size)
	{
		unsigned int index = 0;
		for (char ch : key)
		{
			index = (37 * index) + ch;
		}
		return index % size;
	}

	int linearProbing(int index, int i) //Linear Probing for country
	{
		return (index + i) % tableSize;
	}

	int quadraticProbing(int index, int i) //Quadraic Probing for type
	{
		return (index + i * i) % tableSize;
	}

public:
	GroupHash(int c)
	{
		tableSize = c;
		size = 0;
		table = new HashItemG[tableSize];
		for (int i = 0; i < tableSize; i++)
		{
			table[i] = HashItemG();
			table[i].status = 0;
		}
	}

	void InsertUsingCountry(string c, T ptr)
	{
		int index = GroupHashVal(c, tableSize);
		int j = 0;

		for (int i = 0; table[index].val != c && table[index].status == 2; i++) //keep on getting new indexes until u find an empty cell or val matches 
		{
			j++;
			index = linearProbing(index, j); //use linear probing for country
		}

		if (table[index].status != 2)
		{
			table[index].val = c;
			table[index].status = 2;

		}

		InsertInGroupSLL(table[index], ptr);
	}

	void InsertUsingType(string c, T ptr)
	{
		int index = GroupHashVal(c, tableSize);
		int j = 0;

		for (int i = 0; table[index].val != c && table[index].status == 2; i++)
		{
			j++;
			index = quadraticProbing(index, j); // use quadratic probing for type
		}

		if (table[index].status != 2)
		{
			table[index].val = c;
			table[index].status = 2;

		}

		InsertInGroupSLL(table[index], ptr);
	}

	void InsertInGroupSLL(HashItemG in, T ptr)
	{
		in.ptr->insertAtStart(ptr);
	}

	bool SearchGroupCountry(string s)
	{
		int index = GroupHashVal(s, tableSize);
		int j = 0;

		for (int i = 0; table[index].status != 0; i++)
		{
			if (table[index].val == s && table[index].status == 2) // if cell is occupied and its val matches given country
			{
				return DisplayGroupListCountry(table[index]);
			}
			j++;
			index = linearProbing(index, j);
		}
		return false;
	}

	bool SearchGroupType(string s)
	{
		int index = GroupHashVal(s, tableSize);
		int j = 0;

		for (int i = 0; table[index].status != 0; i++)
		{
			if (table[index].val == s && table[index].status == 2)
			{
				return DisplayGroupListType(table[index]);
			}
			j++;
			index = quadraticProbing(index, j); // quadratic probing for type searching
		}
		return false;
	}

	bool DisplayGroupListCountry(HashItemG in) // display a group of countries
	{
		if (in.ptr->isEmpty() == false) // if the SLL is empty search Doubly list instead
		{
			return false;
		}
		else
		{
			cout << "Index of Group Hash is " << in.val << endl << endl; // else output the group
			in.ptr->DisplayList();
			return true;
		}
	}

	bool DisplayGroupListType(HashItemG in)
	{
		if (in.ptr->isEmpty() == false)
		{
			return false;
		}
		else
		{
			cout << "Index of Group Hash is " << in.val << endl << endl;
			in.ptr->DisplayList();
			return true;
		}
	}

	bool DeleteNodeUsingCountry(string s, int ID) // delete a specific user from the Hash Table
	{
		int index = GroupHashVal(s, tableSize);
		int j = 0;

		for (int i = 0; table[index].status != 0; i++)
		{
			if (table[index].val == s && table[index].status == 2)
			{
				return DeleteGroupListCountry(table[index], ID); // if index and val matches delete it from the SLL
			}
			j++;
			index = linearProbing(index, j);
		}
		return false;
	}

	bool DeleteNodeUsingType(string s, int ID)
	{
		int index = GroupHashVal(s, tableSize);
		int j = 0;

		for (int i = 0; table[index].status != 0; i++)
		{
			if (table[index].val == s && table[index].status == 2)
			{
				return DeleteGroupListType(table[index], ID);
			}
			j++;
			index = quadraticProbing(index, j);
		}
		return false;
	}

	bool DeleteGroupListCountry(HashItemG in, int ID)
	{
		return in.ptr->deleteSLLNode(ID);
	}


	bool DeleteGroupListType(HashItemG in, int ID)
	{
		return in.ptr->deleteSLLNode(ID);
	}

	bool DeleteGroupUsingCountry(string s) // Delete a group index from the Hash Table
	{
		int index = GroupHashVal(s, tableSize);
		int j = 0;

		for (int i = 0; table[index].status != 0; i++)
		{
			if (table[index].val == s && table[index].status == 2)
			{
				if (table[index].ptr->isEmpty() == false)
				{
					return false;
				}
				else
				{
					table[index].ptr->deleteSLL();
					return true;
				}
			}
			j++;
			index = linearProbing(index, j);
		}
		return false;
	}

	bool DeleteGroupUsingType(string s)
	{
		int index = GroupHashVal(s, tableSize);
		int j = 0;

		for (int i = 0; table[index].status != 0; i++)
		{
			if (table[index].val == s && table[index].status == 2)
			{
				if (table[index].ptr->isEmpty() == false)
				{
					return false;
				}
				else
				{
					table[index].ptr->deleteSLL();
					return true;
				}
			}
			j++;
			index = quadraticProbing(index, j);
		}
		return false;
	}

	~GroupHash()
	{
		if (table)
		{
			delete[] table;
		}
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

		string getIteName()
		{
			return current->data->getName();
		}

		string getIteEmail()
		{
			return current->data->getEmail();
		}

	};

	Node* head;
	Node* tail;
	HashTable<ListIterator> UserIDIndex; // HashTable Made on type user using universal and double hashing
	ChainHash<ListIterator> UserNameIndex; // HashTable Made on Name using Chain Hashing
	ChainHash<ListIterator> EmailIndex; // Hash Table Made on Email using Chain Hashing
	GroupHash<ListIterator> CountryIndex; // Hash Table made on Country using Group Linear Probing and chaining
	GroupHash<ListIterator> TypeIndex; // Hash Table made on Type using Group Quadratic probing and chaining


public:

	typedef ListIterator Iterator; //Define iterator to be used elsewhere in program

	//base constructor
	UserList(int cap) : UserIDIndex(cap), UserNameIndex(cap), EmailIndex(cap), CountryIndex(cap), TypeIndex(cap)
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
			Iterator ite(in);
			UserIDIndex.InsertUser(rhs->getID(), ite); // Insert in all Hash Tables
			UserNameIndex.InsertChain(rhs->getName(), in);
			EmailIndex.InsertChain(rhs->getEmail(), in);
			CountryIndex.InsertUsingCountry(rhs->getCountry(), in);
			TypeIndex.InsertUsingType(rhs->getType(), in);
		}
		else
		{
			in->next = head->next;
			in->prev = head;
			head->next->prev = in;
			head->next = in;
			Iterator ite(in);
			UserIDIndex.InsertUser(rhs->getID(), ite);
			UserNameIndex.InsertChain(rhs->getName(), in);
			EmailIndex.InsertChain(rhs->getEmail(), in);
			CountryIndex.InsertUsingCountry(rhs->getCountry(), in);
			TypeIndex.InsertUsingType(rhs->getType(), in);
		}
	}

	//search a user using ID Index and dispkay it
	void SearchUsingID(int ID)
	{
		Iterator curr = UserIDIndex.SearchUser(ID); //search in ID AVL Tree in O log(n) time and display its data
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

	//search a user using Name Index and display it
	void SearchUsingName(string Name)
	{
		Iterator curr = UserNameIndex.SearchChainName(Name);
		if (curr != nullptr)
		{
			cout << "Index is " << curr.getIteName() << endl << endl;
			Node* displayName = curr.getCurrent();
			displayName->data->printUser();
		}
		else // if Index not found then find it in dll in O (n) time and display its data
		{
			cout << "User Index on Name Does Not Exist " << endl << endl;
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
				check->data->printUser();
			}
		}
	}

	//Searcha user based on Email Index
	void SearchUsingEmail(string Email)
	{
		Iterator curr = EmailIndex.SearchChainEmail(Email);
		if (curr != nullptr)
		{
			cout << "Index is " << curr.getIteEmail() << endl << endl;
			Node* displayName = curr.getCurrent();
			displayName->data->printUser();
		}
		else
		{
			cout << "User Index on Email Does Not Exist " << endl << endl;
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
				check->data->printUser();
			}
		}
	}

	//Search a group of users on the base of country
	void SearchUsingCountry(string Country)
	{
		bool ite = CountryIndex.SearchGroupCountry(Country);
		if (ite == false)
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
						cout << "Index of Group Hash was not found" << endl << endl;
						count++;
					}
					check = temp;
					check->data->printUser();
				}
			}

			if (check == nullptr)
			{
				cout << "Index of Group Hash was not found" << endl << endl;
				cout << "User Not Found in List" << endl << endl;
			}
		}
	}

	//Search a group of users on the base of Type
	void SearchUsingType(string Type)
	{
		bool ite = TypeIndex.SearchGroupType(Type);
		if (ite == false)
		{
			Node* check = nullptr;
			bool found = false;
			int count = 0;
			for (Node* temp = head->next; temp != tail; temp = temp->next)
			{
				if (temp->data->getType() == Type) // if not found display each node in dll by searching it
				{
					if (found == false && count == 0)
					{
						found = true;
						cout << "Index of Group Hash was not found" << endl << endl;
						count++;
					}
					check = temp;
					check->data->printUser();
				}
			}

			if (check == nullptr)
			{
				cout << "Index of Group Hash was not found" << endl << endl;
				cout << "User Not Found in List" << endl << endl;
			}
		}
	}

	//delete a user from all trees and avl
	void DeleteUsingID(int ID)
	{

		Iterator del = UserIDIndex.SearchUser(ID); //find the index by searching it in ID tree

		if (del != nullptr)
		{
			Node* current = del.getCurrent();
			if (current->next == tail && current->prev == head) // if one node exists in dll
			{
				UserIDIndex.RemoveInHashID(current->data->getID()); // delete all of its indexes fom every Hash Table
				UserNameIndex.DeleteChainStringName(current->data->getName());
				EmailIndex.DeleteChainStringEmail(current->data->getEmail());
				CountryIndex.DeleteNodeUsingCountry(current->data->getCountry(), current->data->getID());
				TypeIndex.DeleteNodeUsingType(current->data->getType(), current->data->getID());
				head->next = tail;
				tail->prev = head;
				delete current;
			}
			else
			{
				UserIDIndex.RemoveInHashID(current->data->getID());
				UserNameIndex.DeleteChainStringName(current->data->getName());
				EmailIndex.DeleteChainStringEmail(current->data->getEmail());
				CountryIndex.DeleteNodeUsingCountry(current->data->getCountry(), current->data->getID());
				TypeIndex.DeleteNodeUsingType(current->data->getType(), current->data->getID());
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

	void DeleteUsingName(string Name)
	{

		bool del = UserNameIndex.DeleteChainStringName(Name);
		if (del == false)
		{
			cout << "User to be Deleted is not found " << endl << endl;
		}
	}

	void DeleteUsingEmail(string Email)
	{

		bool del = EmailIndex.DeleteChainStringEmail(Email);
		if (del == false)
		{
			cout << "User to be Deleted is not found " << endl << endl;
		}
	}

	void DeleteUsingCountry(string Country)
	{
		bool del = CountryIndex.DeleteGroupUsingCountry(Country);
		if (del == false)
		{
			cout << "Group to be Deleted is not found " << endl << endl;
		}
	}

	void DeleteUsingType(string Type)
	{
		bool del = TypeIndex.DeleteGroupUsingType(Type);
		if (del == false)
		{
			cout << "Group to be Deleted is not found " << endl << endl;
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

	//Check if User exists
	bool SearchExistence(int ID)
	{
		Iterator curr = UserIDIndex.SearchUser(ID);
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
		Iterator curr = UserIDIndex.SearchUser(ID);
		Node* temp = curr.getCurrent();
		return temp->data->getCountry();
	}

	string retType(int ID)
	{
		Iterator curr = UserIDIndex.SearchUser(ID);
		Node* temp = curr.getCurrent();
		return temp->data->getType();
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

template <class U>
class SLLComplaint
{
private:
	class SLLNode
	{
	public:
		U ptr;
		SLLNode* next;
		SLLNode(U p = 0, SLLNode* n = nullptr) : ptr(p), next(n)
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

// Group Hashing of Complaints on the base of user ID
template <class T, class U>
class ComplaintHash
{
private:
	class HashItemComp
	{
	public:
		int val;
		typename SLLComplaint<U>* ptr;
		int status;

		HashItemComp(int d = 0, int s = 0)
		{
			val = d;
			ptr = new SLLComplaint<U>;
			status = s;
		}

		~HashItemComp()
		{

		}
	};
	int tableSize;
	int a;
	int b;
	int p;
	int size;
	HashItemComp* table;

	int Hash1(int k)
	{
		return ((a * k + b) % p) % tableSize;
	}

	int Hash2(int k, int i)
	{
		int h1 = Hash1(k);
		int h2 = p - (k % p);
		return (h1 + (h2 * i)) % tableSize;
	}

	int findPrime(int num)
	{
		for (int i = num - 1; i >= 2; --i)
		{
			if (isPrime(i))
			{
				return i;
			}
		}
		return 2;
	}

	bool isPrime(int num)
	{
		if (num < 2)
		{
			return false;
		}
		for (int i = 2; i * i <= num; ++i)
		{
			if (num % i == 0) {
				return false;
			}
		}
		return true;
	}

public:
	ComplaintHash(int c)
	{
		tableSize = c;
		size = 0;
		srand(time(0));
		a = rand() % (tableSize - 1) + 1;
		b = rand() % tableSize;
		p = findPrime(tableSize);
		table = new HashItemComp[tableSize];
		for (int i = 0; i < tableSize; i++)
		{
			table[i] = HashItemComp();
		}
	}

	void InsertComplaintUsingID(int c, U ptr)
	{
		int index = Hash1(c);
		int j = 0;
		for (int i = 0; table[index].val != c && table[index].status == 2; i++) // if val is equal to inputted ID to empty cell is found
		{
			j++;
			index = Hash2(c, j);
		}

		if (table[index].status != 2)
		{
			table[index].status = 2;
			table[index].val = c;
		}
		table[index].ptr->insertAtStart(ptr);
	}

	void SearchComplaintUsingID(int UID)
	{
		int index = Hash1(UID);
		int j = 0;
		bool flag = false;

		for (int i = 0;table[index].status != 0 && flag == false; i++)
		{
			if (table[index].val == UID && table[index].status == 2)
			{
				flag = DisplayGroupComplaintListID(table[index]);
			}
			j++;
			index = Hash2(UID, j);
		}

		if (flag == false)
		{
			cout << "Index not Found " << endl << endl;
		}

	}

	bool DisplayGroupComplaintListID(HashItemComp in)
	{
		if (in.ptr->isEmpty() == false)
		{
			return false;
		}
		else
		{
			cout << "Index of Complaint is " << in.val << endl << endl;
			in.ptr->DisplayList();
			return true;
		}
	}

	void DeleteSLLComplaintID(int UID, int CID)
	{
		int index = Hash1(UID);
		int j = 0;
		bool flag = false;

		for (int i = 0;table[index].status != 0 && flag == false; i++)
		{
			if (table[index].val == UID && table[index].status == 2)
			{
				table[index].ptr->deleteSLLNode(CID);
				flag = true;
			}
			j++;
			index = Hash2(UID, j);
		}
	}

	~ComplaintHash()
	{
		if (table)
		{
			delete[] table;
		}
	}
};

// Group hash Table Made on Compliants with Country
template <class T, class U>
class ComplaintHash2
{
private:
	class HashItemComp2
	{
	public:
		string val;
		typename SLLComplaint<U>* ptr;
		int status;

		HashItemComp2(string d = "0", int s = 0)
		{
			val = d;
			ptr = new SLLComplaint<U>;
			status = s;
		}

		~HashItemComp2()
		{

		}
	};
	int tableSize;
	int size;
	HashItemComp2* table;

	unsigned int ComplaintHashVal(const string& key, int size)
	{
		unsigned int index = 0;
		for (char ch : key)
		{
			index = (37 * index) + ch;
		}
		return index % size;
	}

	int linearProbing(int index, int i)
	{
		return (index + i) % tableSize;
	}
public:
	ComplaintHash2(int c)
	{
		tableSize = c;
		size = 0;
		table = new HashItemComp2[tableSize];
		for (int i = 0; i < tableSize; i++)
		{
			table[i] = HashItemComp2();
		}
	}

	void InsertComplaintUsingCountry(string c, U ptr)
	{
		int index = ComplaintHashVal(c, tableSize);
		int j = 0;

		for (int i = 0; table[index].val != c && table[index].status == 2; i++)
		{
			j++;
			index = linearProbing(index, j);
		}

		if (table[index].status != 2)
		{
			table[index].status = 2;
			table[index].val = c;
		}

		table[index].ptr->insertAtStart(ptr);
	}

	void SearchComplaintUsingCountry(string s)
	{
		int index = ComplaintHashVal(s, tableSize);
		int j = 0;
		bool flag = false;

		for (int i = 0;table[index].status != 0 && flag == false; i++)
		{
			if (table[index].val == s && table[index].status == 2)
			{
				flag = DisplayGroupComplaintListCountry(table[index]);
			}
			j++;
			index = linearProbing(index, j);
		}

		if (flag == false)
		{
			cout << "Index not Found " << endl << endl;
		}
	}

	bool DisplayGroupComplaintListCountry(HashItemComp2 in)
	{
		if (in.ptr->isEmpty() == false)
		{
			return false;
		}
		else
		{
			cout << "Index of Complaint is " << in.val << endl << endl;
			in.ptr->DisplayList();
			return true;
		}
	}

	void DeleteSLLComplaintCountry(string s, int CID)
	{
		int index = ComplaintHashVal(s, tableSize);
		int j = 0;
		bool flag = false;

		for (int i = 0;table[index].status != 0 && flag == false; i++)
		{
			if (table[index].val == s && table[index].status == 2)
			{
				table[index].ptr->deleteSLLNode(CID);
				flag = true;
			}
			j++;
			index = linearProbing(index, j);
		}
	}

	~ComplaintHash2()
	{
		if (table)
		{
			delete[] table;
		}
	}
};

//Main class which holds the data of all users and complaints
class CustomerModel
{
private:
	UserList* Users; //list of users
	PriorityQueue<Complaint>* ComplaintList; //queue of complaints
	ComplaintHash<int, Complaint> UserComplaint; // Group Hash Table Made on the Base of User ID Complaint using universal and double hashing
	ComplaintHash2<string, Complaint> CountryComplaint; // Group Hash Table made on the base of Country using linear probing

public:

	CustomerModel(int cap) : UserComplaint(cap), CountryComplaint(cap)//base constructor
	{
		Users = new UserList(cap);
		ComplaintList = new PriorityQueue<Complaint>;
	}

	//wrapper functions for all userlist users
	void insert(int ID, string Name, string Email, string Country, string Type)
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

	string getUserCountry(int ID)
	{
		return Users->retCountry(ID);
	}

	string getUserType(int ID)
	{
		return Users->retType(ID);
	}

	//check if user exists in user list
	bool CheckUserinUserList(int ID)
	{
		return Users->SearchExistence(ID);
	}

	void InsertComplaint(int UID, int CID, string comp)
	{
		bool check = CheckUserinUserList(UID); //check if user is registered so we can register their complaint
		if (check)
		{
			Complaint temp = Complaint(UID, CID, comp, getUserCountry(UID), getUserType(UID));
			ComplaintList->Insert(temp);
			UserComplaint.InsertComplaintUsingID(UID, temp);
			CountryComplaint.InsertComplaintUsingCountry(temp.getCountry(), temp);
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
			UserComplaint.DeleteSLLComplaintID(temp.getUserID(), temp.getComplaintID());
			CountryComplaint.DeleteSLLComplaintCountry(temp.getCountry(), temp.getComplaintID());
			ComplaintList->deleteMin();
		}
		else
		{
			cout << "There are no complaints, hence Complaint Servicing cannot be done" << endl << endl;
		}

	}

	//wrapper functions for ComplaintList priority queue
	void IncreasePriority(int ID)
	{
		ComplaintList->PriorityUp(ID);
	}

	void SearchUsingComplaintUserID(int ID)
	{
		UserComplaint.SearchComplaintUsingID(ID);
	}

	void SearchUsingComplaintCountry(string country)
	{
		CountryComplaint.SearchComplaintUsingCountry(country);
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
	int size = 0;
	cout << "Enter Size of All Hash Tables ( Size Must be Greater than 17 and Preferrably Prime ) " << endl << endl;
	while (size <= 17)
	{
		cin >> size;
		if (size <= 17)
		{
			cout << "Size of Hash Table is too small " << endl << endl;
		}
	}
	system("cls");


	cout << "\t\t\t\t\tWelcome to Customer Service Model " << endl << endl;
	CustomerModel CSM(size);
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
	cout << "All Users in Customer Model " << endl << endl;
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

	cout << "Deleting User in Name Hash using User Name : Moiz" << endl << endl;
	CSM.DeleteName("Moiz");

	cout << "Searching User in List using User Name: Moiz after Deletion from Name Hash Index" << endl << endl;
	CSM.SearchName("Moiz");

	cout << "Searching User index in List using Email: moiz6299@gmail.com" << endl << endl;
	CSM.SearchEmail("moiz6299@gmail.com");

	cout << "Deleting User index in Email Hash using Email: moiz6299@gmail.com" << endl << endl;
	CSM.DeleteEmail("moiz6299@gmail.com");

	cout << "Searching User index in List using Email: moiz6299@gmail.com after Deletion from Email Hash Index" << endl << endl;
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