package main

import (
	"fmt"
	"time"
)

func main() {
	fmt.Println("Unix Epoch time: ", time.Now().Unix())

	t := time.Now()
	fmt.Println("\nCurrent time :", t)
	fmt.Println("RFC3339 format :", t.Format(time.RFC3339))
	fmt.Println("Week/Day/Month/Year :", t.Weekday(), t.Day(), t.Month(), t.Year())

	time.Sleep(time.Second)
	t_next := time.Now()
	fmt.Println("Time Difference :", t_next.Sub(t))

	fmt.Println("Korea to Paris")
	t = time.Now()
	paris, _ := time.LoadLocation("Europe/Paris")
	parisTime := t.In(paris)
	fmt.Println("Koera Time :", t)
	fmt.Println("Paris Time :", parisTime)
}
