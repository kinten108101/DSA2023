// STUDENT ANSWER BEGIN
// You can define other functions here to help you.

int getHeightRecursive(Node *node) {
    if (!node) return 0;
    int left_len = 0;
    left_len = this->getHeightRecursive(node->pLeft);
    int right_len = 0;
    right_len = this->getHeightRecursive(node->pRight);
    if (left_len > right_len) return left_len + 1;
    return right_len + 1;
}

int getHeight() {
    // TODO: return height of the binary tree.
    return this->getHeightRecursive(this->root);
}

bool first = true;
string ret = "";

void execute(K key, V value) {
    if (!first) ret += " ";
    ret += to_string(value);
    first = false;
}

void traverse_nlr_recursive(Node *node) {
	if (node) {
		execute(node->key, node->value);
		traverse_nlr_recursive(node->pLeft);
		traverse_nlr_recursive(node->pRight);
	}
}

string preOrder() {
    // TODO: return the sequence of values of nodes in pre-order.
    ret = "";
    first = true;
    traverse_nlr_recursive(this->root);
    return ret;
}

void traverse_lnr_recursive(Node *node) {
	if (node) {
		traverse_lnr_recursive(node->pLeft);
		execute(node->key, node->value);
		traverse_lnr_recursive(node->pRight);
	}
}

string inOrder() {
    // TODO: return the sequence of values of nodes in in-order.
    ret = "";
    first = true;
    traverse_lnr_recursive(this->root);
    return ret;
}

void traverse_lrn_recursive(Node *node) {
	if (node) {
		traverse_lrn_recursive(node->pLeft);
		traverse_lrn_recursive(node->pRight);
		execute(node->key, node->value);
	}
}

string postOrder() {
    // TODO: return the sequence of values of nodes in post-order.
    ret = "";
    first = true;
    traverse_lrn_recursive(this->root);
    return ret;
}

// STUDENT ANSWER END