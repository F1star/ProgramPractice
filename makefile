libhmac.dll: hmac.c hmac.h
	g++ -shared -o libhmac.dll hmac.c -lssl -lcrypto -I e:/msys64/ucrt64/include -L e:/msys64/ucrt64/lib

test: test.c libhmac.dll
	g++ -o test test.c -L. -lhmac
	./test

clean:
	rm -f test libhmac.dll
