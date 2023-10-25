#include <functional>
#include <queue>

#include "../Utils/utils.h"
#include <iostream>
#include <iomanip>

template <class T>
class BinTree {
public:
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

int main() {
	BinTree<char> tree(
		new BinTree<char>::Node('a',
			new BinTree<char>::Node('b',
				new BinTree<char>::Node('e'),
				new BinTree<char>::Node('c',
					new BinTree<char>::Node('f'),
					nullptr
				)
			),
			new BinTree<char>::Node('d',
				nullptr,
				new BinTree<char>::Node('g',
					new BinTree<char>::Node('h'),
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
	return 0;
}

// reinterpret_cast