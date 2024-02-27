# all:in out

# in:in_fifo.cc
# 	g++ -o $@ $^ -std=c++11

# out:out_fifo.cc
# 	g++ -o $@ $^ -std=c++11

# .PHONY:clean
# clean:
# 	rm in
# 	rm out
# 	# rm tp

.PHONY:all
all:server client

server:serverPipe.cc
	g++ -o $@ $^ -std=c++11

client:clientPipe.cc
	g++ -o $@ $^ -std=c++11

.PHONY:clean
clean:
	rm server
	rm client