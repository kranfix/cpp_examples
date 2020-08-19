CC=g++ -std=c++14
binaries=problem1 problem2
problem1: problem1.cpp
	$(CC) problem1.cpp -o $@

run1: problem1
	./problem1 < input1.txt 

problem2: problem2.cpp
	$(CC) problem2.cpp -o $@

run2: problem2
	./problem2

clean:
	rm -f $(binaries)

.PHONY: clean
  