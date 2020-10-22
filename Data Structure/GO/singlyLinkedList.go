package main

import (
	"fmt"
)

type node struct {
	data interface{}
	next *node
}

func newNode(t interface{}) *node {
	return &node{t, nil}
}

type singleList struct {
	dummy *node
}

func newSingleList() *singleList {
	n := newNode(1)
	return &singleList{n}
}

//head insert
func (l *singleList) insert(t interface{}) {
	n := newNode(t)
	n.next = l.dummy.next
	l.dummy.next = n
}

func (l *singleList) append(t interface{}) {
	n := newNode(t)
	walk := l.dummy
	for walk.next != nil {
		walk = walk.next
	}
	walk.next = n
}

func (l *singleList) search(target interface{}) (*node, bool) {
	walk := l.dummy.next
	for walk.data != target && walk.next != nil {
		walk = walk.next
	}
	if walk.data == target {
		return walk, true
	}
	return nil, false
}

func (l *singleList) delete(target interface{}) {
	walk := l.dummy
	for walk.next.data != target && walk.next != nil {
		walk = walk.next
	}
	if walk.next == nil {
		tmp := walk.next
		walk.next = tmp.next
	}
}

func (l *singleList) modify(tar interface{}, sub interface{}) {
	tmp, ok := l.search(tar)
	if ok == false {
		return
	}
	tmp.data = sub
}

func (l *singleList) printSingleList() {
	walk := l.dummy.next
	for walk != nil {
		fmt.Println(walk.data)
		walk = walk.next
	}
	fmt.Println()
}

func main() {
	l := newSingleList()
	l.insert(5)
	l.insert(9)
	l.append(4)
	l.printSingleList()
	l.delete(7)
	l.modify(3, 8)
	l.printSingleList()
}
