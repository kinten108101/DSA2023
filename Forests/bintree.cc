#include <functional>
#include <queue>

#include "../Utils/utils.h"
#include <iostream>
#include <iomanip>

template <class T>
class BinTree {
protected:	
struct Node {
	T data;
	Node *left;
	Node *right;

	Node(const T& data, Node *left = nullptr, Node *right = nullptr): data(data), left(left), right(right) {}
	Node(const T&& data, Node *left = nullptr, Node *right = nullptr): data(data), left(left), right(right) {}
};

	void clear(Node *target) {
		if (target) {
			this->clear(target->left);
			this->clear(target->right);
		}
	}

	void traverse_nlr_recursive(Node *node, std::function<void (T&)> execute) {
		if (node) {
			execute(node->data);
			traverse_nlr_recursive(node->left, execute);
			traverse_nlr_recursive(node->right, execute);
		}
	}

	void traverse_nrl_recursive(Node *node, std::function<void (T&)> execute) {
		if (node) {
			execute(node->data);
			traverse_nrl_recursive(node->right, execute);
			traverse_nrl_recursive(node->left, execute);
		}
	}

	void traverse_lnr_recursive(Node *node, std::function<void (T&)> execute) {
		if (node) {
			traverse_lnr_recursive(node->left, execute);
			execute(node->data);
			traverse_lnr_recursive(node->right, execute);
		}
	}

	void traverse_rnl_recursive(Node *node, std::function<void (T&)> execute) {
		if (node) {
			traverse_rnl_recursive(node->right, execute);
			execute(node->data);
			traverse_rnl_recursive(node->left, execute);
		}
	}

	void traverse_lrn_recursive(Node *node, std::function<void (T&)> execute) {
		if (node) {
			traverse_lrn_recursive(node->left, execute);
			traverse_lrn_recursive(node->right, execute);
			execute(node->data);
		}
	}

	void traverse_rln_recursive(Node *node, std::function<void (T&)> execute) {
		if (node) {
			traverse_rln_recursive(node->right, execute);
			traverse_rln_recursive(node->left, execute);
			execute(node->data);
		}
	}

	void traverse_bf(Node *node, std::function<void (T&)> execute) {
		std::queue<Node *> queue;
		if (node) queue.push(node);
		while (!queue.empty()) {
			Node *head = queue.front();
			if (head->left)
				queue.push(head->left);
			if (head->right)
				queue.push(head->right);
			execute(head->data);
			queue.pop();
			
		}
	}

public:
	enum TraversalOrder {
		DF_NLR,
		DF_NRL,
		DF_LNR,
		DF_RNL,
		DF_LRN,
		DF_RLN,
		BF,
	};

	Node *root;

	BinTree(): root() {}
	BinTree(Node* root): root(root) {}
	~BinTree() {
		this->clear(this->root);
	}	

	static Node* build_node(const T& data, Node *left = nullptr, Node *right = nullptr) {
		return new Node(data, left, right);
	}

	void clear() {
		this->clear(this->root);
	}

	void traverse(std::function<void (T&)> execute, TraversalOrder order = TraversalOrder::DF_NLR) {
		switch (order) {
		case DF_NLR:
			this->traverse_nlr_recursive(this->root, execute);
			break;
		case DF_NRL:
			this->traverse_nrl_recursive(this->root, execute);
			break;
		case DF_LNR:
			this->traverse_lnr_recursive(this->root, execute);
			break;
		case DF_RNL:
			this->traverse_rnl_recursive(this->root, execute);
			break;
		case DF_LRN:
			this->traverse_lrn_recursive(this->root, execute);
			break;
		case DF_RLN:
			this->traverse_rln_recursive(this->root, execute);
			break;
		case BF:
			this->traverse_bf(this->root, execute);
			break;
		default:
			throw utils::NotImplementedException("travsere");
		}
	}
};

template <class T>
class BSTree : public BinTree<T> {
protected:
	typedef typename BinTree<T>::Node Node;
	void remove(Node * &p, const T& key) {
		if (!p) return;
		if (p->data == key) {
			if (p->left && p->right) {
				Node *tmp = p->right;
				while (tmp->left) {
					tmp = tmp->left;
				}
				p->data = tmp->data;
				this->remove(p->right, p->data);
			} else if (p->left) {
				Node *tmp = p;
				p = p->left;
				delete tmp;
			} else if (p->right) {
				Node *tmp = p;
				p = p->right;
				delete tmp;
			} else {
				delete p;
				p = nullptr;
			}
		} else if (p->data > key) {
			this->remove(p->left, key);
		} else {
			this->remove(p->right, key);
		}
	}

	T& find(Node *p, const T& key) {
		if (p) {
			if (p->data == key) return (p->data);
			if (p->data > key) return find(p->left, key);
			else return find(p->right, key);
		} else throw std::logic_error("");
	}

	void insert(Node * &p, const T& key) {
		if (p) {
			if (p->data > key) insert(p->left, key);
			else insert(p->right, key);
		} else {
			p = new Node(key);
		}
	}
public:
	void remove(const T& item) {
		this->remove(this->root, item);
	}

	T& find(const T& item) {
		return this->find(this->root, item);
	}

	T& find_iterative(const T& key) {

		Node *p = this->root;
		while (p) {
			if (p->data == key) return p->data;
			else if (p->data > key) p = p->left;
			else p = p->right;
		}
		throw std::logic_error("");

	}

	void insert(const T& item) {
		this->insert(this->root, item);
	}

	void insert_iterative(const T& key) {
		Node **pp = &this->root;
		while (*pp) {
			if ((*pp)->data > key) pp = &((*pp)->left);
			else pp = &((*pp)->right);
		}
		*pp = new Node(key);
	}
};

int main() {
	BinTree<char> tree(
		BinTree<char>::build_node('a',
			BinTree<char>::build_node('b',
				BinTree<char>::build_node('e'),
				BinTree<char>::build_node('c',
					BinTree<char>::build_node('f'),
					nullptr
				)
			),
			BinTree<char>::build_node('d',
				nullptr,
				BinTree<char>::build_node('g',
					BinTree<char>::build_node('h'),
					nullptr
				)
			)
		)
	);

	tree.traverse(
		[](char name) {
			std::cout << std::setw(5) << name;
		},
		BinTree<char>::TraversalOrder::BF);
	std::cout << std::endl;

	BSTree<int> bst;
	for (int i = 0, val; i < 10; i++) {
		bst.insert(val = rand() % 100);
	}

	bst.remove(15);

	bst.traverse(
		[](int num) {
			std::cout << std::setw(5) << num;
		},
		BSTree<int>::TraversalOrder::DF_LNR);
	std::cout << std::endl;
	return 0;
}

// reinterpret_cast