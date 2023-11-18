#include <functional>
#include <queue>

#include "../Utils/utils.h"
#include <iostream>
#include <iomanip>
#include <stdexcept>

#define MAX_LOOP_ITERATIONS 1024

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
private:
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
	virtual void remove(const T& item) {
		this->remove(this->root, item);
	}

	virtual T& find(const T& item) {
		return this->find(this->root, item);
	}

	virtual T& find_iterative(const T& key) {

		Node *p = this->root;
		while (p) {
			if (p->data == key) return p->data;
			else if (p->data > key) p = p->left;
			else p = p->right;
		}
		throw std::logic_error("");

	}

	virtual void insert(const T& item) {
		this->insert(this->root, item);
	}

	virtual void insert_iterative(const T& key) {
		Node **pp = &this->root;
		while (*pp) {
			if ((*pp)->data > key) pp = &((*pp)->left);
			else pp = &((*pp)->right);
		}
		*pp = new Node(key);
	}
};

template <class T>
class AVLTree : public BSTree<T> {
protected:
	
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

	enum BalanceFactor {
		EH,
		LH,
		RH
	};

	struct Node {
		BalanceFactor b;

		T data;
		Node *left;
		Node *right;

		Node(const T& data, Node *left = nullptr, Node *right = nullptr, BalanceFactor b = EH): data(data), left(left), right(right), b(b) {}
		Node(const T&& data, Node *left = nullptr, Node *right = nullptr, BalanceFactor b = EH): data(data), left(left), right(right), b(b) {}

		bool isLeaf() {
			return (!this->left && !this->right);
		}
	};

	Node *root;

	AVLTree<T>(): root(nullptr) {}

	void traverse_nlr_recursive(Node *node, std::function<void (T&, Node &node)> execute) {
		if (node) {
			execute(node->data, *node);
			traverse_nlr_recursive(node->left, execute);
			traverse_nlr_recursive(node->right, execute);
		}
	}

	void traverse_nrl_recursive(Node *node, std::function<void (T&, Node &node)> execute) {
		if (node) {
			execute(node->data, *node);
			traverse_nrl_recursive(node->right, execute);
			traverse_nrl_recursive(node->left, execute);
		}
	}

	void traverse_lnr_recursive(Node *node, std::function<void (T&, Node &node)> execute) {
		if (node) {
			traverse_lnr_recursive(node->left, execute);
			execute(node->data, *node);
			traverse_lnr_recursive(node->right, execute);
		}
	}

	void traverse_rnl_recursive(Node *node, std::function<void (T&, Node &node)> execute) {
		if (node) {
			traverse_rnl_recursive(node->right, execute);
			execute(node->data, *node);
			traverse_rnl_recursive(node->left, execute);
		}
	}

	void traverse_lrn_recursive(Node *node, std::function<void (T&, Node &node)> execute) {
		if (node) {
			traverse_lrn_recursive(node->left, execute);
			traverse_lrn_recursive(node->right, execute);
			execute(node->data, *node);
		}
	}

	void traverse_rln_recursive(Node *node, std::function<void (T&, Node &node)> execute) {
		if (node) {
			traverse_rln_recursive(node->right, execute);
			traverse_rln_recursive(node->left, execute);
			execute(node->data, *node);
		}
	}

	void traverse_bf(Node *node, std::function<void (T&, Node &node)> execute) {
		std::queue<Node *> queue;
		if (node) queue.push(node);
		while (!queue.empty()) {
			Node *head = queue.front();
			if (head->left)
				queue.push(head->left);
			if (head->right)
				queue.push(head->right);
			execute(head->data, *head);
			queue.pop();
			
		}
	}

	void rotate_right(Node * &p) {
		Node *_p = p->left;
		p->left = _p->right;
		_p->right = p;
		p = _p;
	}

	void rotate_left(Node * &p) {
		Node *_p = p->right;
		p->right = _p->left;
		_p->left = p;
		p = _p;
	}

	bool balanceLeft(Node * &p) {
		if (p->b == EH) {
			p->b = LH;
			return true;
		} else if (p->b == RH) {
			p->b = EH;
			return false;
		}

		if (p->left->b == LH) {
			this->rotate_right(p);
			p->b = p->right->b = EH;
			return false;
		} else if (p->left->b == EH) {
			this->rotate_right(p);
			p->b = RH;
			p->right->b = LH;
			return true;
		}

		this->rotate_left(p->left);
		this->rotate_right(p);
		if (p->b == LH) {
			p->left->b = p->b = EH;
			p->right->b = RH;
			return false;
		} else if (p->b == EH) {
			p->left->b = p->right->b = EH;
		} else {
			p->right->b = p->b = EH;
			p->left->b = LH;
		}

		return false;
	}

	bool balanceRight(Node * &p) {
		if (p->b == EH) {
			p->b = RH;
			return true;
		} else if (p->b == LH) {
			p->b = EH;
			return false;
		}

		if (p->right->b == RH) {
			this->rotate_left(p);
			p->b = p->left->b = EH;
			return false;
		} else if (p->right->b == EH) {
			this->rotate_left(p);
			p->b = LH;
			p->left->b = RH;
			return true;
		}

		this->rotate_right(p->right);
		this->rotate_left(p);
		if (p->b == RH) {
			p->right->b = p->b = EH;
			p->left->b = RH;
			return false;
		} else if (p->b == EH) {
			p->right->b = p->left->b = EH;
		} else {
			p->left->b = p->b = EH;
			p->right->b = RH;
		}

		return false;
	}

	bool _insert(Node * &p, const T& key) {
		if (p) {
			if (p->data > key) {
				if (this->_insert(p->left, key)) {
					return balanceLeft(p);
				}
			} else if (p->data == key) {
				// make sure no duplication so this is a BST
				return false;
			} else {
				if (this->_insert(p->right, key)) {
					return balanceRight(p);
				}
			}
			return false;
		}
		p = new Node(key);
		return true;
	}

	bool remove(Node * &p, const T& key) {
		if (!p) return false;
		if (p->data == key) {
			if (p->left && p->right) {
				// take min right or max left will vastly affect final result,
				// so, know your requirements!
				Node *tmp = p->right;
				while (tmp->left) {
					tmp = tmp->left;
				}
				p->data = tmp->data;
				if (this->remove(p->right, p->data)) {
					return !this->balanceLeft(p);
				}
				return false;
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
			return true;
		} else if (p->data > key) {
			if (this->remove(p->left, key)) return !balanceRight(p);

		} else {
			if (this->remove(p->right, key)) return !balanceLeft(p);
		}
		return false;
	}

	void remove(const T& key) {
		this->remove(this->root, key);
	}

	void insert(const T& item) {
		bool result = this->_insert(this->root, item);
	}

	void traverse(std::function<void (T&, Node &node)> execute, TraversalOrder order = TraversalOrder::DF_NLR) {
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

	int getHeightRecursive(Node *node) {
	    if (!node) return 0;
	    int left_len = 0;
	    left_len = this->getHeightRecursive(node->left);
	    int right_len = 0;
	    right_len = this->getHeightRecursive(node->right);
	    if (left_len > right_len) return left_len + 1;
	    return right_len + 1;
	}

	int getHeight() {
	    // TODO: return height of the binary tree.
	    return this->getHeightRecursive(this->root);
	}

	int getDepthFull(Node *current, Node *target) {
		int i = 0;
		while (current && target && current != target) {
			if (current->data <= target->data) current = current->right;
			else current = current->left;
			i++;
		}
		if (!current || !target) throw std::logic_error("Could not get depth");
		return i;
	}

	int getDepth(Node *target) {
		return this->getDepthFull(this->root, target);
	}

	Node* retrieve_node(const T& key) {
		Node *buf = nullptr;
		this->traverse(
			[&](T& value, Node& node) {
				if (value == key) buf = &node;
			});
		return buf;
	}

	Node* retrieve_parent(Node *child) {
		Node *parent = nullptr;
		if (child == this->root) throw std::logic_error("is root");
		this->traverse(
			[&](T& value, Node& node) {
				if (node.left == child || node.right == child) parent = &node;
			});
		if (parent == nullptr) throw std::logic_error("could not find parent??");
		return parent;
	}

	T& find_common_ancestor(const T& a, const T& b) {
		Node *node_a = this->retrieve_node(a);
		if (!node_a) throw std::logic_error("Could not retrieve node with key");
		Node *node_b = this->retrieve_node(b);
		if (!node_a) throw std::logic_error("Could not retrieve node with key");
		int depth_a = this->getDepth(node_a);
		int depth_b = this->getDepth(node_b);
		int i = 0;
		while (depth_a != depth_b && i < MAX_LOOP_ITERATIONS) {
			if (depth_a > depth_b) {
				node_a = this->retrieve_parent(node_a);
				depth_a = this->getDepth(node_a);
			}
			else {
				node_b = this->retrieve_parent(node_b);
				depth_b = this->getDepth(node_b);
			}
			i++;
		}
		if (i >= MAX_LOOP_ITERATIONS)
			throw std::logic_error("Max loop iterations (sync height)");
		Node *parent_a = node_a;
		Node *parent_b = node_b;
		i = 0;
		while (parent_a != parent_b && i < MAX_LOOP_ITERATIONS) {
			parent_a = this->retrieve_parent(parent_a);
			parent_b = this->retrieve_parent(parent_b);
			i++;
		}
		if (i >= MAX_LOOP_ITERATIONS)
			throw std::logic_error("Max loop iterations (get common)");
		return parent_a->data;
	}
};
};

class BTree {
public:
	class Node {
	public:
	};
};

int main() {
	std::cout << "Binary Tree (Generic immutable 2-way tree)" << std::endl;
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

	std::cout << "Binary Search Tree (Mutable 2-way tree)" << std::endl;

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
	
	std::cout << "AVL Tree (Mutable self-balacing 2-way tree)" << std::endl;

	AVLTree<int> avl;
	int arr[] = {10,52,98,32,68,92,40,13,42,63,99,100};
	for (int i = 0; i < 12; i++){
		avl.insert(arr[i]);
	}
	avl.remove(52);
	avl.traverse(
		[](int num, AVLTree<int>::Node &node) {
			std::cout << std::setw(5) << num;
		},
		AVLTree<int>::TraversalOrder::DF_LNR);
	std::cout << std::endl;
	avl.traverse(
		[&](int num, AVLTree<int>::Node &node) {
			
				std::cout << std::setw(5) << avl.getDepth(&node);
			
		},
		AVLTree<int>::TraversalOrder::DF_LNR);
	std::cout << std::endl;

	std::cout << "Find common ancestor" << std::endl;

	std::cout << avl.find_common_ancestor(26, 72) << std::endl;
	
	return 0;
}

// reinterpret_cast