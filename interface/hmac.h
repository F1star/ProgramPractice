#ifndef _HMAC_H_
#define _HMAC_H_

// 一个通用接口，用于使用不同的算法求得一个字符串的hash摘要字符串。
// 输入参数str: 要处理的字符串
// 输入参数key: 秘钥
// 输入参数algorithm: 算法名称，目前支持md5, sha1, sha256, sha512等
// 输入参数result: 存放结果字符串的地址
// 返回值：0表示成功，1表示没有该算法，2表示调用HMAC_Init_ex失败，3表示调用HMAC_Update失败，4表示调用HMAC_Final失败，5表示HMAC_Final返回的长度不合法。
int hmac(const char* str, const char* key, const char* algorithm, char *result);

#endif
