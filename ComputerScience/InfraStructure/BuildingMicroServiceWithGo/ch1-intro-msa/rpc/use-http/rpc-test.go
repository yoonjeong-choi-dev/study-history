package main

import (
	"fmt"

	"building_msa_with_go/ch1/rpc/use-http/client"
	"building_msa_with_go/ch1/rpc/use-http/server"
)

func main() {
	go server.StartServer()

	c := client.CreateClient()
	defer c.Close()

	reply := client.PerformRequest(c)
	fmt.Println(reply.Message)
}
