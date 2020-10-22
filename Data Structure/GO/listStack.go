package main

import (
	"errors"
	"fmt"
)

type listStack struct {
	data interface{}
	next *listStack
}

func newListStack() *listStack {
	return &listStack{0, nil}
}

func (l *listStack) push(t interface{}) {
	node := &listStack{data: t, next: l.next}
	l.next = node
}

func (l *listStack) pop() (interface{}, error) {
	if l.next == nil {
		return nil, errors.New("stack underflow")
	}
	tmp := l.next
	l.next = tmp.next
	return tmp.data, nil
}

func (l *listStack) printListStack() {
	fmt.Println("Top:")
	tmp := l.next
	for tmp != nil {
		fmt.Println(tmp.data)
		tmp = tmp.next
	}
	fmt.Println("Bottom")
	fmt.Println()
}
