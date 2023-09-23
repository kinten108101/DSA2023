#include <functional>
#include <memory>
#include <random>
#include <string>
#include <iostream>
#include <iomanip>
#include <map>
#include "../Utils/utils.h"

class Serializable {
public:
	virtual std::string to_string() {
		throw utils::NotImplementedException("to_string");
	};
};

class Integer : public Serializable {
private:
	int _data;
public:

private:
public:
	Integer(): _data(0) {}

	Integer(const int &val): _data(val) {}

	virtual std::string to_string() {
		return std::to_string(_data);
	}
	friend int operator==(const Integer & src, const int &rhs);
	friend bool operator!=(const Integer & lhs, const int &rhs) {
		return lhs._data != rhs;
	}
	bool operator>=(const Integer &rhs) {
		return this->_data >= rhs._data;
	}
	bool operator>(const Integer &rhs) {
		return this->_data > rhs._data;
	}
	bool operator<=(const Integer &rhs) {
		return this->_data <= rhs._data;
	}
	bool operator<(const Integer &rhs) {
		return this->_data < rhs._data;
	}
	bool operator==(const Integer &rhs) {
		return this->_data == rhs._data;
	}
};

template <typename T>
class TreeNode {
	static_assert(std::is_base_of<Serializable, T>::value, "Child must inherit LinkedListNode");
public:
	static int prev_id;
	static int generate_id() {
		return ++prev_id;
	}
public:
	int id;
	TreeNode *left, *right;
	T data;
public:
	TreeNode(): id(TreeNode::generate_id()), data(), left(nullptr), right(nullptr) {}
	TreeNode(const T& data): id(TreeNode::generate_id()), data(data), left(nullptr), right(nullptr) {}
	bool operator>=(TreeNode<T> rhs) const {
		return this->data >= rhs.data;
	}
	bool operator>(TreeNode<T> rhs) const {
		return this->data > rhs.data;
	}
	bool operator<=(TreeNode<T> rhs) const {
		return this->data <= rhs.data;
	}
	bool operator<(TreeNode<T> rhs) const {
		return this->data < rhs.data;
	}
	bool operator==(TreeNode<T> rhs) const {
		return this->data == rhs.data;
	}
};

template <typename T> int TreeNode<T>::prev_id = 0;

template <typename T>
class Tree {
public:
	TreeNode<T> root;
	std::map<int, bool> visit_map;
public:
	Tree(): root() {}
	Tree(std::vector<Integer> numbers): root() {
		for (Integer num : numbers) {
			// TODO
		}
	}

	int preorder_traverse(std::function<void(T&)> execute) {
		return this->_preorder_traverse(this->root, execute, this->visit_map);
	}

	int insert_sorted(const T & data) {
		TreeNode<T> *node = &root;
		TreeNode<T> *target = node;
		int decision = 0;
		while (node != nullptr) {
			if ((T &)data < (T &)node->data) {
				node = node->left;
				if (node != nullptr) target = node;
				decision = 0;
			} else {
				node = node->right;
				if (node != nullptr) target = node;
				decision = 1;				
			}
		}
		if (decision == 0) {
			target->left = new TreeNode<T>(data);
		} else {
			target->right = new TreeNode<T>(data);
		}
		return 0;
	}
	std::vector<T> to_list() {
		std::vector<T> list;
		this->preorder_traverse([&](Integer &item) {
			list.push_back(item);
		});
		return list;
	}

	std::string to_string() {
		std::string str("");
		int i = 0;
		this->preorder_traverse([&](Integer &item) {
			if (i == 0) {
				str += item.to_string();
				i = 1;
				return;
			}
			str += " " + item.to_string();
		});
		return str;
	}
private:
	int _preorder_traverse(TreeNode<T> &target, std::function<void(T&)> execute, std::map<int, bool> &visit_map) const {
		if (target.left != nullptr) this->_preorder_traverse(*target.left, execute, visit_map);
		bool visited = false;
		if (visit_map.find(target.id) != visit_map.end()) {
			visited = visit_map.at(target.id);
		}
		execute((T&)target.data);
		if (!visited) {
			visit_map.insert_or_assign(target.id, true);
		}

		if (target.right != nullptr) this->_preorder_traverse(*target.right, execute, visit_map);
		return 0;
	}

	void _insert_sorted_recursive(const T & data) {

	}
};

void print_map(std::map<int, bool> map) {
	auto it = map.begin();
	// Iterate through the map and print the elements
	while (it != map.end())
	{
	std::cout << "Key: " << it->first << ", Value: " << it->second << std::endl;
	++it;
	}
}

int main() {
	Tree<Integer> tree;
	utils::assert([]() {
		return 0;
	});
	if (tree.root.data != 0) throw std::exception();
	tree.insert_sorted(*(new Integer(5)));
	tree.insert_sorted(*(new Integer(-4)));
	tree.insert_sorted(*(new Integer(-6)));
	tree.insert_sorted(*(new Integer(7)));
	std::vector<Integer> buffer = tree.to_list();
	std::cout << tree.to_string() << std::endl;
	print_map(tree.visit_map);
	return 0;
}