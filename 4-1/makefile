# .PHONY:all
all: test out in

in:in.cpp
	g++ -o $@ $^

out:out.cpp
	g++ -o $@ $^ -g

test:test.cpp
	g++ -o $@ $^

.PHONY:clean
clean:
	rm test out in def