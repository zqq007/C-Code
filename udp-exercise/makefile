.PHONY:all
all:server client

server:udp_server.cpp
	g++ -o $@ $^

client:udp_client.cpp
	g++ -o $@ $^

.PHONY:clean
clean:
	rm server client