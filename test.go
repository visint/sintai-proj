package main

import (
	"fmt"
	"net"
	"os"
	//  "io"
)

func main() {
	conn, err := net.Dial("udp", "255.255.255.255:10001")
	defer conn.Close()
	if err != nil {
		os.Exit(1)
	}

	conn.Write([]byte("Hello world!"))

	fmt.Println("send msg")

	var msg [50]byte
	conn.Read(msg[0:])

	fmt.Println("msg is", string(msg[0:10]))
}
