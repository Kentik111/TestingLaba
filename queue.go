package queue

import (
	"fmt"
)

type Queue struct {
	front *Node
	rear  *Node
}

type Node struct {
	data interface{}
	next *Node
}

func NewQueue() *Queue {
	return &Queue{nil, nil}
}

func (q *Queue) IsEmpty() bool {
	return q.front == nil
}

func (q *Queue) Push(value interface{}) {
	newNode := &Node{value, nil}
	if q.IsEmpty() {
		q.front = newNode
		q.rear = newNode
	} else {
		q.rear.next = newNode
		q.rear = newNode
	}
}

func (q *Queue) Pop() {
	if q.IsEmpty() {
		fmt.Println("Queue is empty. Cannot remove element.")
		return
	}
	//temp := q.front
	q.front = q.front.next
	if q.front == nil {
		q.rear = nil
	}
}

func (q *Queue) Peek() interface{} {
	if q.IsEmpty() {
		panic("Queue is empty. Cannot read element.")
	}
	return q.front.data
}

func (q *Queue) Display() {
	current := q.front
	for current != nil {
		fmt.Print(current.data, " ")
		current = current.next
	}
	fmt.Println()
}





