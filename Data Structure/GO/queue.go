//data:10.22
//path:~/Code/GO
//method:newQueue(),enqueue(data),dequeue(),printQueue()
package main

import (
	"errors"
	"fmt"
)

//type node struct {
//	data interface{}
//	next *node
//}

type queue struct {
	head *node //just a dummy
	tail *node
}

func iniNode(t interface{}) *node {
	return &node{t, nil}
}

func newQueue() *queue {
	h := iniNode(0)
	return &queue{h, nil}
}

func (q *queue) enqueue(t interface{}) {
	n := iniNode(t)
	if q.tail == nil { //an empty queue
		q.head.next = n
		q.tail = n
		return
	}
	q.tail.next = n
	q.tail = n
}

func (q *queue) dequeue() (interface{}, error) {
	if q.head.next == nil {
		return nil, errors.New("empty queue")
	}
	tmp := q.head.next
	q.head.next = tmp.next
	return tmp.data, nil
}

func (q *queue) printQueue() {
	fmt.Println("Head")
	tmp := q.head.next
	for tmp != nil {
		fmt.Println(tmp.data)
		tmp = tmp.next
	}
	fmt.Println("Tail")
	fmt.Println()
}
