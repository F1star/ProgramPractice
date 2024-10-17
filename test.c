#include <stdio.h>
#include <string.h>

#include "hmac.h"

void test_hmac(const char* algorithm)
{
   const char* src = "kjhdskfhdskfjhdskjfdskfdskfjsdkfjds";
   const char* key = "kjshfkds";
   char *result;
   int code = hmac(src, key, algorithm, result);
   switch (code){
      case 0 :
         printf("%s result = [%s]\n", algorithm, result);
         delete result;
         break;
      case 1:
         printf("invalid algorithm %s for hmac\n", algorithm);
         break;
      case 2:
         printf("HMAC_Init_ex fail\n");
         break;
      case 3:
         printf("HMAC_Update fail\n");
         break;
      case 4:
         printf("HMAC_Final fail");
         break;
      case 5:
         printf("HMAC_Final return invalid output length %s\n", result);
         break;
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
