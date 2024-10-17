#include <openssl/ssl.h>
#include <stdio.h>
#define SUCCESS 0
#define INVALID_ALGORITHM 1
#define HMAC_INIT_EX_FAIL 2
#define HMAC_UPDATE_FAIL 3
#define HMAC_FINAL_FAIL 4
#define HMAC_FINAL_INVALID_OUTPUT 5

int hmac(const char* str, const char* key, const char* algorithm, char *result)
{
   int str_length = strlen(str);
   int key_length = strlen(key);

   // 根据算法名称获得算法引擎
   const EVP_MD* engine = EVP_get_digestbyname(algorithm);
   if(engine == NULL)
   {
      // printf("invalid algorithm %s for hmac\n", algorithm);
      return INVALID_ALGORITHM;
   }

   HMAC_CTX* ctx = HMAC_CTX_new();
   if(HMAC_Init_ex(ctx, key, key_length, engine, NULL) <= 0)
   {
      // printf("HMAC_Init_ex fail\n");
      HMAC_CTX_free(ctx);
      return HMAC_INIT_EX_FAIL;
   }
   if(HMAC_Update(ctx, (unsigned char*)str, str_length) <= 0)
   {
      // printf("HMAC_Update fail\n");
      HMAC_CTX_free(ctx);
      return HMAC_UPDATE_FAIL;
   }

   unsigned char output[EVP_MAX_MD_SIZE]; // 存放摘要输出的缓存
   unsigned int output_length; // 存放实际输出的摘要长度
   if(HMAC_Final(ctx, output, &output_length) <= 0)
   {
      // printf("HMAC_Final fail");
      HMAC_CTX_free(ctx);
      return HMAC_FINAL_FAIL;
   }
   if(output_length <= 0 || output_length > EVP_MAX_MD_SIZE)
   {
      // printf("HMAC_Final return invalid output length %d\n", output_length);
      HMAC_CTX_free(ctx);
      return HMAC_FINAL_INVALID_OUTPUT;
   }
   HMAC_CTX_free(ctx);

   // 将不可打印的摘要结果，转换为十六进制表示的asc码字符串，并返回
   result = (char*)malloc(output_length * 2 + 1);
static const char* hex_digits = "0123456789abcdef";
   for(int i = 0; i < output_length; i++)
   {
      result[i * 2] = hex_digits[output[i] >> 4]; // 偶数字节存放高四位对应的数字
      result[i * 2 + 1] = hex_digits[output[i] & 0x0F]; // 奇数字节存放低四位对应的数字
   }
   result[output_length * 2] = '\0';
   snprintf(result, sizeof(result), "%d", output_length);
   return SUCCESS;
}

