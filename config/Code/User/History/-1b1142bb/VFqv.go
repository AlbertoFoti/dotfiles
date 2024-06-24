package main

import (
	"fmt"
	"time"
)

func add(x int, y int) int {
	return x + y
}

func swap(x, y string) (string, string) {
	return y, x
}

func main() {
	fmt.Println("hello, world!\n")

	fmt.Println("The time is", time.Now())

	fmt.Println(add(42, 13))

	a, b := swap("hello", "world")
	fmt.Println(a, b)
}
