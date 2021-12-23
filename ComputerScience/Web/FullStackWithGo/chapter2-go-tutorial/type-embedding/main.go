package main

import "fmt"

// 베이스 구조체
type Person struct {
	name string
	age  int
}

func (p Person) getName() string {
	return p.name
}

func (p Person) getAge() int {
	return p.age
}

// 상속 구조체 : Go에서는 타입 임베딩을 통해 상속과 비슷한 방식을 구현함
type Student struct {
	Person // 필드명이 없음 => 타입 임베딩임을 알린다 => 해당 타입에 대한 메서드 바로 접근 가능
	score  int
}

func (s Student) getScore() int {
	return s.score
}

func main() {
	var p Person = Person{"YJ", 29}
	var s Student = Student{Person{"Yoonjeong", 29}, 77}

	fmt.Printf("Person: %s, %d\n", p.getName(), p.getAge())
	fmt.Printf("Studnet: %s, %d, %d\n", s.getName(), s.getAge(), s.getScore())
}
