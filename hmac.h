#ifndef _HMAC_H_
#define _HMAC_H_

// 一个通用接口，用于使用不同的算法求得一个字符串的hash摘要字符串。
// 输入参数str: 要处理的字符串
// 输入参数str_length: 要处理的字符串的长度
// 输入参数key: 秘钥
// 输入参数key_length: 秘钥长度
// 输入参数algorithm: 算法名称，目前支持md5, sha1, sha256, sha512等
// 返回值：如果出现错误，返回NULL，否则返回摘要字符串（已经转换为asc格式），注意，这个返回指针用后要删除
char* hmac(const char* str, int str_length, const char* key, int key_length, const char* algorithm);

#endif
