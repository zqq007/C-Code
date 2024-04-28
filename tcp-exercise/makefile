.PHONY:all
all:server client

server:tcp_server.cpp
	g++ -o $@ $^

client:tcp_client.cpp
	g++ -o $@ $^

.PHONY:clean
clean:
	rm server client