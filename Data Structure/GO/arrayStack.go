package main

import (
	"errors"
)

type stack struct {
	top   int
	array []interface{}
}

func newStack() *stack {
	return &stack{array: make([]interface{}, 0)}
}

func (s *stack) isEmpty() bool {
	return (s.top == 0)
}

func (s *stack) push(data interface{}) {
	s.top = s.top + 1
	s.array = append(s.array, data)
}

func (s *stack) pop() (interface{}, error) {
	if s.isEmpty() == true {
		return nil, errors.New("empty stack")
	}
	s.top = s.top - 1
	ret := s.array[s.top]
	s.array = s.array[:s.top]
	return ret, nil
}
