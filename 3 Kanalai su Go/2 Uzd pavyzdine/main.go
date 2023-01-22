package main

import "fmt"

func Sender(sendReceiveChannel chan<- int, finishSend <-chan int, start int) {
	//for i := start; i < start+10; i++ {
	//	sendReceiveChannel <- i
	//}

	for value := range finishSend {
		sendReceiveChannel <- start
		start = start + value
	}
}

func Receiver(sendReceiveChannel chan int, finishSend chan<- int, evenResult chan<- int, oddResult chan<- int, printResults chan<- int, elementCnt int) {
	for i := 0; i < elementCnt; i++ {
		finishSend <- 1
		n := <-sendReceiveChannel
		//fmt.Println(n)
		if n%2 == 0 || n == 0 {
			evenResult <- n
		} else {
			oddResult <- n
		}
	}
	close(finishSend)
	close(evenResult)
	close(oddResult)
	printResults <- 0
	printResults <- 0
}

func Results(results <-chan int, printResults <-chan int, finishedWork chan<- int) {
	var values []int
	for value := range results {
		values = append(values, value)
		fmt.Println(value)
	}

	<-printResults
	fmt.Println("LLL")
	fmt.Println(values)
	finishedWork <- 0
}

func main() {
	elementCnt := 20
	sendReceiveChannel := make(chan int)
	finishedWork := make(chan int)
	finishSend := make(chan int)
	evenResult := make(chan int)
	oddResult := make(chan int)
	printResults := make(chan int)
	go Sender(sendReceiveChannel, finishSend, 0)
	go Sender(sendReceiveChannel, finishSend, 11)
	go Receiver(sendReceiveChannel, finishSend, evenResult, oddResult, printResults, elementCnt)
	go Results(evenResult, printResults, finishedWork)
	go Results(oddResult, printResults, finishedWork)

	for i := 0; i < 2; i++ {
		<-finishedWork
	}

	close(finishedWork)
	close(printResults)
	close(sendReceiveChannel)
}
