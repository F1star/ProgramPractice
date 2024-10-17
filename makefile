libhmac.so: hmac.c hmac.h
	g++ -shared -o libhmac.so hmac.c -lssl -lcrypto

test: test.c libhmac.so
	g++ -o test test.c -L. -lhmac
	./test

clean:
	rm -f test libhmac.so
