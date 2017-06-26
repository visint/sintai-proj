package main

import (
	"fmt"
	"net"
	"net/http"
	"net/url"
)

const (
	API_SERVER = "http://x.x.x"
	UDP_PORT   = 9998
)

func main() {
	socket, err := net.ListenUDP("udp4", &net.UDPAddr{
		IP:   net.IPv4(0, 0, 0, 0),
		Port: UDP_PORT,
	})

	if err != nil {
		fmt.Println("监听失败", err)
		return
	}

	defer socket.Close()

	for {
		data := make([]byte, 256)
		read, _, err := socket.ReadFromUDP(data)

		if err != nil {
			fmt.Println("读取数据失败", err)
			continue
		}

		fmt.Println(string(data[:read]))
	}
}

func forward(data string) {
	fmt.Printf("%s\n", data)

	resp, err := http.PostForm(API_SERVER,
		url.Values{"data": {data}})

	if err != nil {
		fmt.Println("请求API错误", err)
	}

	resp.Body.Close()
}
