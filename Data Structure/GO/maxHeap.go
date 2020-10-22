//date:2020.10.23
//path:~/Code/GO
//O(nlgn)

package main

import (
	"fmt"
	"math/rand"
	"time"
)

type heap struct {
	array []int
	size  int
}

func right(i int) int {
	return (i << 1) + 1
}

func left(i int) int {
	return i << 1
}

func parent(i int) int {
	return i >> 1
}

func newHeap(i int) *heap {
	return &heap{array: make([]int, i), size: i}
}

func (h *heap) randomHeap() {
	rand.Seed(time.Now().Unix())
	for i, _ := range h.array {
		ran := rand.Intn(10000)
		h.array[i] = ran
	}
}
func swap(a, b *int) {
	tmp := *a
	*a = *b
	*b = tmp
}

func (h *heap) maxHeapify(i int) {
	l := left(i)
	r := right(i)
	max := i
	if l < h.size && h.array[i] < h.array[l] {
		max = l
	}
	if r < h.size && h.array[max] < h.array[r] {
		max = r
	}
	if max != i {
		swap(&h.array[i], &h.array[max])
		h.maxHeapify(max) //h.array[max] now is smaller than its parent(h.array[i])
	}
}

//ensure every parents are greater than their left and right child
func (h *heap) buildMaxHeap() {
	for i := parent(h.size - 1); i >= 0; i-- {
		h.maxHeapify(i)
	}
}

func (h *heap) sort() {
	h.buildMaxHeap()
	for i := h.size - 1; i > 0; i-- {
		swap(&h.array[0], &h.array[i])
		h.size--
		h.maxHeapify(0)
	}
}

func (h *heap) printHeap() {
	for _, v := range h.array {
		fmt.Printf("%d ", v)
	}
	fmt.Println()
}

func main() {
	h := newHeap(10)
	h.randomHeap()
	h.printHeap()
	h.sort()
	h.printHeap()
}
