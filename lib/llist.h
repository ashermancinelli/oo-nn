

class LList {
private:
	struct Node {
		Node *next, *prev;
		Base_Link *element;
	};
	Node *head, *tail, *curr;
	int count;

public:	
	LList(void);
	~LList(void);
	int Add_To_Tail
}
