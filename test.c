#include <stdio.h>
#include <string.h>

#include "hmac.h"

void test_hmac(const char* algorithm)
{
   const char* src = "kjhdskfhdskfjhdskjfdskfdskfjsdkfjds";
   const char* key = "kjshfkds";
   char* result = hmac(src, strlen(src), key, strlen(key), algorithm);
   if(result != NULL)
   {
      printf("%s result = [%s]\n", algorithm, result);
      delete result;
   }
}

int main()
{
   test_hmac("md5");
   test_hmac("sha1");
   test_hmac("sha224");
   test_hmac("sha256");
   test_hmac("sha384");
   test_hmac("sha512");
   test_hmac("xxx"); // xxx是不存在的算法
}
