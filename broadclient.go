package main

import "net"
import "fmt"

func main() {
	// 这里设置发送者的IP地址，自己查看一下自己的IP自行设定
	laddr := net.UDPAddr{
		IP:   net.IPv4(192,168,0,199),
		Port: 10001,
	}
	// 这里设置接收者的IP地址为广播地址
	raddr := net.UDPAddr{
		IP:   net.IPv4(255, 255, 255, 255),
		Port: 10001,
	}
	conn, err := net.DialUDP("udp", &laddr, &raddr)
	if err != nil {
		println(err.Error())
		return
	}
	conn.Write([]byte(`hello peers`))
    for {
        // 读取数据
        data := make([]byte, 4096)
        read , remoteAddr, err := conn.ReadFromUDP(data)
        if err != nil {
            fmt.Println("读取数据失败!", err)
            continue
        }
        fmt.Println(read, remoteAddr)
        fmt.Printf("%s\n\n", data)

        // 发送数据
    }
	conn.Close()
}

