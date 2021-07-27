package main

import (
	"fmt"

	"building_msa_with_go/ch1/rpc/simple-example/client"
	"building_msa_with_go/ch1/rpc/simple-example/server"
)

func main() {
	go server.StartServer()

	c := client.CreateClient()
	defer c.Close()

	reply := client.PerformRequest(c)
	fmt.Println(reply.Message)
}
