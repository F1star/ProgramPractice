libhmac.dll: hmac.c hmac.h
	g++ -shared -o libhmac.dll hmac.c -lssl -lcrypto -I e:/msys64/ucrt64/include -L e:/msys64/ucrt64/lib

test: test.c libhmac.dll
	g++ -Wall -Wextra test.c -o test -L. -lhmac
	./test

clean:
	rm -f test libhmac.dll
