# Chapter 6: Trees (Forests)

Root: Indegree 0
Leaf: Outdegree 0
Internal node: Indegree == 1 && Outdegree != 0
Siblings: Nodes of same level

Level is counted from root. Level 0 is root.
Height = max(Level) + 1


Views:
- organization chart
- parenthetical listing	A((BC)D)
- indented list (filesystem tree)

## Binary tree

Balance factor = Height(left) - Height(right)

Balanced tree: |balance factor| <= 1

Complete tree: Last lvel is full. N = Nmax = 2^H - 1
Nearly complete tree: Nodes in the last level are on the left

Completeness -> Array representation

A [B C] [D E F G]

Depth-first traversal
- Pre-order
	- Left Right
	- Right Left
- In-order
	- Left Right
	- Right Left
- Post-order
	- Left Right
	- Right Left
Breadth-first traversal

### Application

Expression Tree. Each leaf is an operand and the root and internal nodes are operators. Subtrees are subexpressions.

## BST

find
insert
remove

## AVL Tree

It's a binary search tree

EH: equal height
LH: left higher
RH: right higher

## M-Way Tree

Degree.

## B-Tree

Balanced M-Way tree.
No duplicate
The root is either a leaft or has at least 2 subtrees.
ALl other nodes have at least (m/2)-1 entries
All leaf nodes are at the same level

### Application

Filesystem indexing using B*-Tree

## B\*Tree

ALl other nodes have at least 2\*(max)/3 entries. Maintain over time. Merge more than two nodes.

## B\+Tree

All data in leafs. All keys in internal nodes.
Each leaf node has one additional pointer to move to the next leaf node