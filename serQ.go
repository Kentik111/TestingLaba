package main

import (
    "fmt"
    "os"
    "bufio"
)

type Queue struct {
    front *Node
    rear  *Node
}

type Node struct {
	data string
    next *Node
}

func NewQueue() *Queue {
    return &Queue{front: nil, rear: nil}
}

func (q *Queue) IsEmpty() bool {
    return q.front == nil
}

func (q *Queue) Push(value string) {
    newNode := &Node{data: value, next: nil}
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
    temp := q.front
    q.front = q.front.next
    temp.next = nil
    if q.front == nil {
        q.rear = nil
    }
}

func (q *Queue) Peek() string {
    if q.IsEmpty() {
        panic("Queue is empty. Cannot read element.")
    }
    return q.front.data
}

func (q *Queue) Display() {
    current := q.front
    for current != nil {
        fmt.Printf("%s ", current.data)
        current = current.next
    }
    fmt.Println()
}

func (q *Queue) SerializeToText(filename string) {
    file, err := os.Create(filename)
    if err != nil {
        fmt.Println("Failed to open file for writing.")
        return
    }
    defer file.Close()

    current := q.front
    for current != nil {
        fmt.Fprintln(file, current.data)
        current = current.next
    }
}

func (q *Queue) DeserializeFromText(filename string) {
    file, err := os.Open(filename)
    if err != nil {
        fmt.Println("Failed to open file for reading.")
        return
    }
    defer file.Close()

    for !q.IsEmpty() {
        q.Pop()
    }

    scanner := bufio.NewScanner(file)
    for scanner.Scan() {
        value := scanner.Text()
        q.Push(value)
    }
}

func main() {
    q := NewQueue()

    q.Push("Hello")
    q.Push("World")

    q.SerializeToText("queue.txt")

    fmt.Println("Queue content before deserialization:")
    q.Display()

    q.DeserializeFromText("queue.txt")

    fmt.Println("Queue content after deserialization:")
    q.Display()
}
