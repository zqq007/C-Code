.PHONY:all
all:server client

client:client.cpp
	g++ -o $@ $^

server:server.cpp
	g++ -o $@ $^

.PHONY:clean
clean:
	rm server client tp