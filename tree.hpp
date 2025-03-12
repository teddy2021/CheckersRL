#pragma once
#include <vector>
using std::vector;

#include <string>
using std::string;


template <typename t>
class dNode{
	private:
		t* value;
		int height;
	public:

		dNode<t>* left;
		dNode<t>* right;
		
		dNode(): value(nullptr), left(nullptr), right(nullptr), height(1){};
		dNode(t val): value(new t(val)), left(nullptr), right(nullptr), height(1){};
		dNode(const dNode<t> &other): height(1){
			*value = *other->value;
		}
		~dNode(){return;};

		t *getValue(){
			return value;
		};

		auto primarySortVal();
		auto secondarySortVal();

		void updateHeight();
		int getHeight(){ return height;  };

		string to_string();

		bool operator==(const dNode<t> &other);
		void operator=(const dNode<t> &other);
		
};

template <typename t>
class dTree{

	private:
		int sz;
		dNode<t>* root;

		dNode<t>* insert(t val, dNode<t>* cur);
		dNode<t>* insert(dNode<t> *val, dNode<t>* cur);
		dNode<t>* remove(t val, dNode<t>* cur);
		template<typename n>
		dNode<t>* getItem(n primary, n secondary, dNode<t>* cur);


		vector<dNode<t>> preorder(dNode<t> *cur);
		vector<dNode<t>> inorder(dNode<t> *cur);
		vector<dNode<t>> postorder(dNode<t> *cur);

		string treeRep(dNode<t> * cur, int depth);

		int getBalance(dNode<t> * cur);

		dNode<t> * balance(dNode<t> * cur);
		void balance();

		dNode<t> * lRotation(dNode<t> *cur);
		dNode<t> * rRotation(dNode<t> *cur);
		dNode<t> * lrRotation(dNode<t> *cur);
		dNode<t> * rlRotation(dNode<t> *cur);

	public:
		dTree():sz(0), root(){};
		dTree(t val): sz(1), root(val){};
		dTree(const dTree<t> &other):sz(other->sz){
			vector<dNode<t>> values = other->inorder();
			for(int i = 0; i < values.size(); i += 1){
				insert(values[i].getValue());
			}
		};
		~dTree(){
			delete root;
		};

		int size(){return sz;};
		void insert(t val);
		void remove(t val);
		dNode<t> *getItem(auto primary, auto secondary);

		vector<dNode<t>> preorder();
		vector<dNode<t>> inorder();
		vector<dNode<t>> postorder();

		string treeRep();
};

template <typename t>
auto dNode<t>::primarySortVal(){
	return value->primary();
};

template <typename t>
auto dNode<t>::secondarySortVal(){
	return value->secondary();
}


template <typename t>
string dNode<t>::to_string(){
	string res = std::to_string(height);
	return "[" + res + " " + value->to_string() + "]";
}

template <typename t>
bool dNode<t>::operator==(const dNode<t> &other){
	return *value == *other->value;
}

template <typename t>
void dNode<t>::operator=(const dNode<t> &other){
	*value = *other->value;
}

template <typename t>
void dTree<t>::insert(t val){
	root = insert(val, root);
	sz += 1;
	balance();
}


template <typename t>
void dTree<t>::remove(t val){
	root = remove(val, root);
	sz -= 1;
	balance();
}

template <typename t>
dNode<t> * dTree<t>::getItem(auto primary, auto secondary){
	return getItem(primary, secondary, root);
}

template <typename t>
template <typename n>
dNode<t> * dTree<t>::getItem(n primary, n secondary, dNode<t> *cur){
	if(cur == nullptr){
		return nullptr;
	}

	if(primary < cur->primarySortVal()){
		return getItem(primary, secondary, cur->left);
	}
	else if(primary == cur->primarySortVal()){
		if(secondary == cur->secondarySortVal()){
			return cur;
		}
		else if(secondary < cur->secondarySortVal()){
			return getItem(primary, secondary, cur->left);
		}
		else{
			return getItem(primary, secondary, cur->right);
		}
	}
	else{
		return getItem(primary, secondary, cur->right);
	}
}


template <typename t>
dNode<t> * dTree<t>::insert(t val, dNode<t>* cur){
	if(cur == nullptr){
		cur = new dNode<t>(val);
		return cur;
	}
	else if(val.primary() < cur->primarySortVal()){
		if(cur->left == nullptr){
			cur->left = new dNode<t>(val);
		}
		else{
			insert(val, cur->left);
		}
	}
	else if(val.primary() == cur->primarySortVal()){
		if(val.secondary() <= cur->secondarySortVal()){
			if(cur->left == nullptr){
				cur->left = new dNode<t>(val);
			}
			else {
				insert(val, cur->left);
			}
		}
		else{
			if(cur->right == nullptr){
				cur->right = new dNode<t>(val);
			}
			else{
				insert(val, cur->right);
			}
		}
	}
	else if(val.primary() > cur->primarySortVal()){
		if(cur->right == nullptr){
			cur->right = new dNode<t>(val);
		}
		else{
			insert(val, cur->right);
		}
	}
	cur->updateHeight();
	return cur;
}

template <typename t>
dNode<t> * dTree<t>::insert(dNode<t> *val, dNode<t> * cur){
	if(cur == nullptr){
		return val;
	}
	if(val == nullptr){
		return cur;
	}
	if(val->primarySortVal() < cur->primarySortVal()){
		cur->left = insert(val, cur->left);
	}
	else if(val->primarySortVal() == cur->primarySortVal()){
		if(val->secondarySortVal() <= cur->secondarySortVal()){
			cur->left = insert(val, cur->left);
		}
		else{
			cur->right = insert(val, cur->right);
		}
	}
	else{
		cur->right = insert(val, cur->right);
	}
	cur->updateHeight();
	return cur;
}


template <typename t>
dNode<t>* dTree<t>::remove(t val, dNode<t>* cur){
	if(cur == nullptr){
		return nullptr;
	}
	if(val.primary() < cur->primarySortVal()){
		cur->left = remove(val, cur->left);
	}
	else if(val.primary() == cur->primarySortVal()){
		if(val.secondary() < cur->secondarySortVal()){
			cur->left = remove(val, cur->left);
		}
		else if(val.secondary() == cur->secondarySortVal()){
			dNode<t> * l = remove(val, cur->left);
			dNode<t> * r = cur->right;
			r = insert(l, r);
			cur = r;
		}
		else{
			cur->right = remove(val, cur->right);
		}
	}
	else{
		cur->right = remove(val, cur->right);
	}
	return cur;
}


template <typename t>
vector<dNode<t>> dTree<t>::preorder(){
	return preorder(root);
}

template <typename t>
vector<dNode<t>> dTree<t>::preorder(dNode<t> *cur){
	if(cur == nullptr){
		return vector<dNode<t>>();
	}
	dNode<t> * left = cur->left;
	dNode<t> * right = cur->right;
	vector<dNode<t>> leftRes = preorder(left);
	vector<dNode<t>> rightRes = preorder(right);

	leftRes.insert(leftRes.begin(), *cur->getValue());
	leftRes.insert(leftRes.end(), rightRes.begin(), rightRes.end());
	return leftRes;
}

template <typename t>
vector<dNode<t>> dTree<t>::inorder(){
	return inorder(root);
}


template <typename t>
vector<dNode<t>> dTree<t>::inorder(dNode<t> *cur){
	if(cur == nullptr){
		return vector<dNode<t>>();
	}
	dNode<t> * left = cur->left;
	dNode<t> * right = cur->right;
	vector<dNode<t>> leftRes = inorder(left);
	vector<dNode<t>> rightRes = inorder(right);

	leftRes.push_back(*cur->getValue());
	leftRes.insert(leftRes.end(), rightRes.begin(), rightRes.end());

	return leftRes;
}



template <typename t>
vector<dNode<t>> dTree<t>::postorder(){
	return postorder(root);
}


template <typename t>
vector<dNode<t>> dTree<t>::postorder(dNode<t> *cur){
	if(cur == nullptr){
		return vector<dNode<t>>();
	}
	dNode<t> * left = cur->left;
	dNode<t> * right = cur->right;
	vector<dNode<t>> leftRes = postorder(left);
	vector<dNode<t>> rightRes = postorder(right);

	leftRes.insert(leftRes.end(), rightRes.begin(), rightRes.end());
	leftRes.push_back(*cur->getValue());

	return leftRes;
}

template <typename t>
string dTree<t>::treeRep(){
	return treeRep(root, 0);
}


template <typename t>
string dTree<t>::treeRep(dNode<t> *cur, int depth){
	if(cur == nullptr){
		return "";
	}
	string res;
	res += treeRep(cur->right, depth + 1);
	res += "\n";
	int padding = cur->to_string().size();
	for(int i = 0; i < depth; i += 1 ){
		res += "--";
	}
	res += ">>";
	res += cur->to_string();
	res += treeRep(cur->left, depth + 1);
	return res;
}


template <typename t>
void dNode<t>::updateHeight(){
	if(this == nullptr){
		return;
	}
	int lefth = 0;
	if(left != nullptr){
		lefth = left->height;
	}
	int righth;
	if(right != nullptr){
		righth = right->height;
	}
	height = 1 + std::max(lefth, righth);
}


template <typename t>
int dTree<t>::getBalance(dNode<t> * cur){
	if(cur == nullptr){
		return 0;
	}
	int balance = 0;
	if(cur->left != nullptr){
		balance += cur->left->getHeight();
	}
	if(cur->right != nullptr){
		balance -= cur->right->getHeight();
	}
	return balance;
}


template <typename t>
void dTree<t>::balance(){
	root = balance(root);
	if(root != nullptr){  
		root->updateHeight();
	}
}


template <typename t>
dNode<t> * dTree<t>::balance(dNode<t> *cur){
	if(cur == nullptr){
		return nullptr;
	}
	cur->right = balance(cur->right);
	cur->left = balance(cur->left);
	if(cur != nullptr){  
		cur->updateHeight();
	}
	int bal = getBalance(cur);
	if(-2 < bal && bal < 2){
		return cur;
	}
	if(bal <= -2){
		dNode<t> * right = cur->right;
		dNode<t> * left = nullptr;
		if(cur->right != nullptr){  
			left = cur->right->left;
		}
		cur->right = left;
		right->left = cur;
		cur->updateHeight();
		return right;
	}
	if(2 <= bal){
		dNode<t> * left = cur->left;
		dNode<t> * right = nullptr;
		if(cur->left != nullptr){  
			right = cur->left->right;
		}
		cur->left = right;
		left->right = cur;
		if(cur != nullptr){  
			cur->updateHeight(); 
		}
		return left;
	}
	if(cur != nullptr){  
		cur->updateHeight();
	}
	return cur;
}


