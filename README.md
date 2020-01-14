# DataStructure
## Singly Linked List
Singly linked list contains address of first node. Each node contains its data and address of next node. Data can be any type. This has following functions.
* push_back(Data) : void
* push_front(Data) : void
* pop_back() : void
* pop_front() : void
* clear() : void
* empty() : void
* insert(const iterator, Data) : iterator
* insert(const iterator, const iterator, const iterator) : iterator
* remove(const iterator) : iterator
* remove(const iterator, const iterator) : iterator
### push_back()
This function takes an argument and creates a node and attaches it at the end of the chain of nodes. It takes O(n) time.
### push_front()
This function takes an argument and creates a node and attaches it to head of the chain of nodes. Any nodes that already exist will be pushed back. It takes O(1) time.
### pop_back()
This function removes a node located at the end of the chain of nodes. It takes O(n) time.
### pop_front()
This function removes a node located at the head of the chain of nodes. Any nodes that already exist will be pushed to head. It takes O(1) time.
### clear()
This function removes all nodes. It takes O(n) time.
### empty()
This function distinguishes whether the list is empty. It takes O(1) time.
### insert(const iterator, Data) : iterator
This function inserts a node in front of a node which the iterator points. Any nodes from iterator points will be pushed back. This will return iterator pointing newly inserted node. It takes O(n) time.
### insert(const iterator, const iterator, const iterator) : iterator
This function inserts number of nodes in front of a node which first iterator points. Number of nodes are added which between second and third iterator pointing at. This function returns iterator pointing last inserted node. It takes O(n) time.
### remove(const iterator) : iterator
This function removes a node where iterator pointing at. Any nodes after the iterator pointing at will be pushed front. This will return iterator pointing next node of deleted node. It takes O(n) time.
### remove(const iterator, const iterator) : iterator
This function removes number of nodes between first iterator and second iterator pointing at. This returns iterator pointing next node of deleted node. It takes O(n) time.

