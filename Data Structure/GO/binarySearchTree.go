//date:2020.10.30
//Action:push(),delete(),search(),inorderTraversal()
package main

import "fmt"

//This is a binary search tree
//All the values in the left subtree is smaller than the root
//All the values in the right subtree are greater than the root

type treeNode struct {
	data  int
	left  *treeNode
	right *treeNode
}

type binarySearchTree struct {
	root *treeNode
}

func newTreeNode(t int) *treeNode {
	return &treeNode{data: t}
}

func newBinarySearchTree(r int) *binarySearchTree {
	return &binarySearchTree{root: newTreeNode(r)}
}

//Insert a leaf into a tree
func (tree *binarySearchTree) push(t int) {
	n := newTreeNode(t)
	if tree.root == nil {
		tree.root = n
		return
	}
	ftr := tree.root
	walk := tree.root
	for walk != nil {
		ftr = walk
		if t < walk.data {
			walk = walk.left
		} else {
			walk = ftr.right
		}
	}
	if t < ftr.data {
		ftr.left = n
	} else {
		ftr.right = n
	}
}


//the iteration stop when the walker walk out of the tree
//or the walker walk to the node we want
func (tree *binarySearchTree) search(key int) *treeNode {
	walker := tree.root
	for walker != nil && walker.data != key {
		if key < walker.data {
			walker = walker.left
		} else {
			walker = walker.right
		}
	}
	return walker
}

func (node *treeNode) predecessor() (*treeNode, *treeNode) {
	walker := node
	pre := walker.left
	for pre != nil && pre.right != nil {
		walker = pre
		pre = pre.right
	}
	return pre, walker
}

func (node *treeNode) successor() (*treeNode, *treeNode) {
	walker := node
	pre := walker.right
	for pre != nil && pre.left != nil {
		walker = pre
		pre = pre.left
	}
	return pre, walker
}

//the case following are disjoint
//case 1:no node to be deleted
//case 2:the node to be deleted is a leaf
//case 3:the node to be deleted has both predecessor and successor
//case 4:the node to be deleted has either successor or predecessor
//successor and predecessor has no subtree,it is a leaf
func (tree *binarySearchTree) delete(key int) {
	n := tree.search(key)
	if n == nil { //case 1
		return
	}
	if n.left == nil && n.right == nil { //case 2
		n = nil
		return
	}
	var suc, f *treeNode
	if n.right == nil { //case 4
		suc, f = n.predecessor()
	} else { //case 3 or 4
		suc, f = n.successor()
	}
	if n == tree.root { //those case will change the root aritribute
		if n.left == nil && n.right == nil {
			tree.root = nil
			return
		}
		if suc == n.left {
			suc.right = n.right
			tree.root = suc
		}
		if suc == n.right {
			suc.left = n.left
			tree.root = suc
		}
	}
	n.data = suc.data
	if suc == f.left {
		f.left = nil
	} else {
		f.right = nil
	}
}

func (node *treeNode) inorder() {
	if node != nil {
		node.left.inorder()
		fmt.Printf("%d ", node.data)
		node.right.inorder()
	}
}

func (tree *binarySearchTree) inorderTraversal() {
	tree.root.inorder()
	fmt.Println()
}

func main() {
	tree := newBinarySearchTree(5)
	tree.push(5)
	tree.push(7)
	tree.push(4)
	tree.push(1)
	tree.push(6)
	tree.push(3)
	tree.inorderTraversal()
	tree.delete(5)
	tree.inorderTraversal()
	tree.delete(5)
	tree.inorderTraversal()
	tree.delete(6)
	tree.delete(7)
	tree.inorderTraversal()
}
