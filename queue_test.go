package queue

import (
 	"fmt"
 	"testing"
)

func TestNewQueue(t *testing.T) {
 	q := NewQueue()
 	if !q.IsEmpty() {
  		t.Error("Expected queue to be empty")
 	}
}

func TestPush(t *testing.T) {
 	q := NewQueue()
 	q.Push("one")
 	if q.IsEmpty() {
  		t.Error("Expected queue not to be empty after Push")
 	}
 	if q.Peek() != "one" {
  		t.Errorf("Expected front of the queue to be 'one', got '%v'", q.Peek())
 	}

 	q.Push("two")
 	if q.Peek() != "one" {
  		t.Errorf("Expected front of the queue to be 'one', got '%v'", q.Peek())
 	}
}

func TestPop(t *testing.T) {
 	q := NewQueue()
 	q.Push("one")
 	q.Push("two")

 	q.Pop()
 	if q.Peek() != "two" {
  		t.Errorf("Expected front of the queue to be 'two', got '%v'", q.Peek())
 	}

 	q.Pop()
 	if !q.IsEmpty() {
  		t.Error("Expected queue to be empty after popping all elements")
 	}

 	q.Pop() // This should not cause any panic or error
}

func TestPeek(t *testing.T) {
 	q := NewQueue()
 	defer func() {
  	if r := recover(); r == nil {
   		t.Errorf("Expected panic when peeking into an empty queue")
  	}
 	}()
 	q.Peek() // Should panic
}

func TestDisplay(t *testing.T) {
 	q := NewQueue()
 	q.Push("one")
 	q.Push("two")

 	fmt.Println("Displaying queue:")
 	q.Display() // Just for visual confirmation, no assertion here
}

func TestIsEmpty(t *testing.T) {
 	q := NewQueue()
 	if !q.IsEmpty() {
  		t.Error("Expected queue to be empty")
 	}
 	q.Push("one")
 	if q.IsEmpty() {
  		t.Error("Expected queue not to be empty after Push")
 	}
 	q.Pop()
 	if !q.IsEmpty() {
  		t.Error("Expected queue to be empty after Pop")
 	}
}


