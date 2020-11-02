//date:2020.10.30
//This is a red-black tree

//red-black tree properties:
//1.every node is either red or black
//2.the root is black
//3.every leaf(nil) is black
//4.children of a red node are black
//for each node,all simple paths from the node to descendant leaves
//contain the same number of black nodes(so bh(x) is well-defined)

//a RBtree with n internal nodes has height at most 2lg(n+1)

package main

import "fmt"

type col bool

const (
	red   col = true
	black col = false
)

type redBlackTreeNode struct {
	color  col
	parent *redBlackTreeNode
	left   *redBlackTreeNode
	right  *redBlackTreeNode
	key    int
}

type redBlackTree struct {
	root  *redBlackTreeNode
	t_nil *redBlackTreeNode
}

func newRedBlackTreeNode(t int, _nil *redBlackTreeNode) *redBlackTreeNode {
	return &redBlackTreeNode{color: red, key: t, parent: _nil, left: _nil, right: _nil}
}

func newRedBlackTree() *redBlackTree {
	t := &redBlackTreeNode{color: black}
	return &redBlackTree{t, t}
}

//Rotation maintain the bst properties but don't maintain rbt properties
func (rbt *redBlackTree) leftRotate(x *redBlackTreeNode) {
	y := x.right
	if y == rbt.t_nil {
		return //rotate nothing
	}
	x.right = y.left //turn y's subtree into x's subtree
	if y.left != rbt.t_nil {
		y.left.parent = x
	}
	y.parent = x.parent
	if x.parent == rbt.t_nil {
		rbt.root = y //x is the root of RBT
	} else if x == x.parent.left {
		x.parent.left = y
	} else {
		x.parent.right = y
	}
	y.left = x //put x on y's left
	x.parent = y
}

//symmetric to the left rotate
func (rbt *redBlackTree) rightRotate(y *redBlackTreeNode) {
	x := y.left
	if x == rbt.t_nil {
		return
	}
	y.left = x.right //turn x'subtree into y's subtree
	if x.right != rbt.t_nil {
		x.right.parent = y
	}
	x.parent = y.parent
	if y == rbt.root {
		rbt.root = x
	} else if y == y.parent.left {
		y.parent.left = x
	} else {
		y.parent.right = x
	}
	x.right = y
	y.parent = x
}

//we inserted a red node n

/*case 1:parent of the node to be inserted is a black node
insert a red node won't change black height
a black parent is quietly safe
this is a condition we need to fix nothing
*/

/*case 2:parent of the node to be inserted is a red node,which means its grandparent is absolutely black
case A:n's uncle is red
case B:n's uncle is black
	case a:n is a rightchild
	case b:n is a leftchild
*/

func (rbt *redBlackTree) insertFixUp(n *redBlackTreeNode) {
	for n.parent.color == red { //case 3
		if n.parent == n.parent.parent.left {
			uncle := n.parent.parent.right
			//case A
			if uncle.color == red {
				n.parent.color = black
				uncle.color = black
				n.parent.parent.color = red
				n = n.parent.parent
			} else if n == n.parent.right { //case a
				n = n.parent
				rbt.leftRotate(n) //turn to case b
			} else { //case b
				n.parent.color = black
				n.parent.parent.color = red
				rbt.rightRotate(n.parent.parent)
			}
		} else {
			uncle := n.parent.parent.left
			if uncle.color == red {
				n.parent.color = black
				uncle.color = black
				n.parent.parent.color = red
				n = n.parent.parent
			} else if n == n.parent.left {
				n = n.parent
				rbt.rightRotate(n)
			} else {
				n.parent.parent.color = red
				n.parent.parent.color = black
				rbt.leftRotate(n.parent.parent)
			}
		}
	}
	rbt.root.color = black
}

func (rbt *redBlackTree) insert(key int) {
	n := newRedBlackTreeNode(key, rbt.t_nil)
	n.left = rbt.t_nil
	n.right = rbt.t_nil
	if rbt.root == rbt.t_nil { //empty tree
		rbt.root = n
		n.color = black //the root of RBT is black
		return
	}
	tmp := rbt.t_nil
	walker := rbt.root
	for walker != rbt.t_nil {
		tmp = walker
		if key < walker.key {
			walker = walker.left
		} else {
			walker = walker.right
		}
	}
	n.parent = tmp
	if key < tmp.key {
		tmp.left = n
	} else {
		tmp.right = n
	}
	rbt.insertFixUp(n)
}

func (n *redBlackTreeNode) inorder(_nil *redBlackTreeNode) {
	if n == _nil {
		return
	}
	n.left.inorder(_nil)
	fmt.Printf("%d/%d:", n.parent.key, n.key)
	if n.color == red {
		fmt.Printf("red   ")
	} else {
		fmt.Printf("black   ")
	}
	n.right.inorder(_nil)
}

func (rbt *redBlackTree) inorderTraversal() {
	rbt.root.inorder(rbt.t_nil)
	fmt.Println()
}

//let n's parent link to suc,abandon n
func (rbt *redBlackTree) transplant(n *redBlackTreeNode, suc *redBlackTreeNode) {
	if n == rbt.root {
		rbt.root = suc
	} else if n == n.parent.left {
		n.parent.left = suc
	} else {
		n.parent.right = suc
	}
	suc.parent = n.parent
}

func (rbt *redBlackTree) search(v int) *redBlackTreeNode {
	walker := rbt.root
	for walker != rbt.t_nil && walker.key != v {
		if v < walker.key {
			walker = walker.left
		} else {
			walker = walker.right
		}
	}
	return walker
}

func (n *redBlackTreeNode) successor(_nil *redBlackTreeNode) *redBlackTreeNode {
	pre := n.right
	for pre != _nil && pre.left != _nil {
		pre = pre.left
	}
	return pre
}

/*case 1:the node we deleted is red
Safe,the delete operation won't change the bh
And it won't violate the rule 4
*/
/*case 2:the node we deleted is black:
case A:n's sibling is red(so n's parent must be black)
case B:n's sibling is black
		case a:n's sibling has 2 black child
		case b:n's sibling has a red left child and a black right child
		case c:n's sibling has a red right child(no matter what color the left child is)
*/
func (rbt *redBlackTree) deleteFixUp(n *redBlackTreeNode) {
	for n != rbt.root && n.color == black { //case 2
		if n == n.parent.left {
			sibling := n.parent.right
			if sibling.color == red { //case A
				sibling.color = black
				n.parent.color = red
				rbt.leftRotate(n.parent)
				sibling = n.parent.right //turn to case B
			}
			if sibling.left.color == black && sibling.right.color == black { //case a
				sibling.color = red
				n = n.parent
			} else {
				if sibling.right.color == black { //case b
					sibling.color = red
					sibling.left.color = black
					rbt.rightRotate(sibling)
					sibling = n.parent.right //turn to case c
				}
				sibling.color = n.parent.color
				n.parent.color = black
				sibling.right.color = black
				rbt.leftRotate(n.parent)
				n = rbt.root
			}
		} else {
			sibling := n.parent.left
			if sibling.color == red {
				sibling.color = black
				n.parent.color = red
				rbt.rightRotate(n.parent)
				sibling = n.parent.left
			}
			if sibling.left.color == black && sibling.right.color == black {
				sibling.color = red
				n = n.parent
			} else {
				if sibling.left.color == black {
					sibling.right.color = black
					sibling.color = red
					rbt.leftRotate(sibling)
					sibling = n.parent.left
				}
				sibling.color = n.parent.color
				n.parent.color = black
				sibling.left.color = black
				rbt.rightRotate(n.parent)
				n = rbt.root
			}
		}
	}
	n.color = black
}

func (rbt *redBlackTree) delete(v int) {
	n := rbt.search(v)
	if n == rbt.t_nil {
		return
	}
	y := n //maintain y as a node either removed or moved
	yColor := y.color
	var x *redBlackTreeNode
	if n.left == rbt.t_nil { //turn n's right subtree to n's parent's subtree,we won't violate the bst properties
		x = n.right
		rbt.transplant(n, n.right) //it is safe when n is a (internal) leaf
	} else if n.right == rbt.t_nil {
		x = n.left
		rbt.transplant(n, n.left)
	} else { //n has both left subtree and right subtree
		y = n.successor(rbt.t_nil)
		yColor = y.color
		x = y.right
		if n == rbt.root { //change the root aritribute of rbt
			if n.left == rbt.t_nil && n.right == rbt.t_nil {
				rbt.root = rbt.t_nil
				return
			}
			if y == n.right {
				y.left = n.left
				rbt.root = y
			}
		}
		if y.parent != n {
			rbt.transplant(y, y.right)
			y.right = n.right
			y.right.parent = y
		} else {
			x.parent = y
		}
		rbt.transplant(n, y)
		y.left = n.left
		y.left.parent = y
		y.color = n.color
	}
	if yColor == black {
		rbt.deleteFixUp(x)
	}
}

func main() {
	rbt := newRedBlackTree()
	rbt.insert(26)
	rbt.insert(17)
	rbt.insert(41)
	rbt.insert(47)
	rbt.insert(30)
	rbt.insert(21)
	rbt.insert(14)
	rbt.insert(10)
	rbt.delete(26)
	rbt.inorderTraversal()
}
