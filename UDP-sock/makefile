all : udp_server udp_client

udp_server : udp_server.cc
	g++ -o $@ $^ 

udp_client : udp_client.cc
	g++ -o $@ $^

.PHONY:clean
clean:
	rm -f udp_server udp_client