
#include <vector>
using std::vector;

#include <algorithm>

#pragma once
template <typename t>
class mNode{
	private:
		t * value;
		float sort_val;
	public:
		mNode(): value(nullptr), sort_val(0){};
		mNode(t val): value(val), sort_val(0){};
		mNode(t val, float sort): value(val), sort_val(sort){};
		mNode(const mNode<t> & other): value(*other->value), sort_val(other->sort_val){};

		t * val();
		float sort();
};

template <typename t>
class mTree{
	private:
		mNode<t> * value;
		int max_branches;
		vector<mTree *> branches;
	public:
		mTree():value(nullptr), max_branches(2), branches(2){};
		mTree(t val): value(val), max_branches(2), branches(2){};
		mTree(t val, int branch): value(val), max_branches(branch), branches(branch){};
		mTree(vector<mNode<t>> nodes, int branch): branches(branch){
			value = new mNode(nodes[0].val(), nodes[0].sort());

			for(int i = 0; i < nodes.size(); i += 1){
				branches.push_back(new mTree(nodes[i], branch));
			}

			max_branches = branch;
		};
		mTree(const mTree<t> & other): value(other->value), max_branches(other->max_branches), branches(other->max_branches){
			for(int i = 0; i < other->branches.size(); i += 1){
				branches[i] = new mTree(other->branches[i]);
			}
		};

		mTree<t> * branch(int branch_no);
		float sort();
		t * val();

		vector<mTree *> ascending();
		vector<mTree *> descending();
};

template <typename t>
t * mNode<t>::val(){
	return value;
}

template<typename t>
float mNode<t>::sort(){
	return sort_val;
}


template<typename t>
mTree<t> * mTree<t>::branch(int branch_no){
	if(branch_no < 0 || branch_no >= max_branches){
		return nullptr;
	}
	return branches[branch_no];
}

template <typename t>
float mTree<t>::sort(){
	return value->sort();
}

template <typename t>
t * mTree<t>::val(){
	if(value == nullptr){
		return t();
	}
	return value->val();
}

template <typename t>
vector<mTree<t> *> mTree<t>::ascending(){
	vector<mTree<t> *> out(branches.size() + 1);
	out[0] = this;
	out.insert(branches.begin(), branches.end());
	std::sort(out.begin(), out.end(), [](mTree<t> * a, mTree<t> *b){return a->sort() < b->sort();});
	return out;
}

template <typename t>
vector<mTree<t> *> mTree<t>::descending(){
	vector<mTree<t> *> out(branches.size() + 1);
	out[0] = this;
	out.insert(branches.begin(), branches.end());
	std::sort(out.begin(), out.end(), [](mTree<t> * a, mTree<t> *b){return a->sort() > b->sort();});
	return out;
}


