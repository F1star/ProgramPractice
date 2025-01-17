#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "hmac.h"

#define RESULT_MAX_SIZE 1024

void test_hmac(const char* algorithm)
{
   const char* src = "kjhdskfhdskfjhdskjfdskfdskfjsdkfjds";
   const char* key = "kjshfkds";
   char *result = (char*)malloc(sizeof(char) * RESULT_MAX_SIZE);
   int code = hmac(src, key, algorithm, result);
   switch (code){
      case 0 :
         printf("%s result = [%s]\n", algorithm, result);
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
   free(result);
   result = NULL;
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
