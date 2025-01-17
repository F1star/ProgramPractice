#include <stdio.h>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <vector>
#include <algorithm>
#include <chrono>  // 引入chrono库来测量时间

// 定义 WordInfo 结构
struct WordInfo
{
   std::unordered_set<int> lines; // 使用 unordered_set 来避免重复行号
};

// 使用 unordered_map 替代 map，提高查找效率
typedef std::unordered_map<std::string, WordInfo> WordsStatis;

// 单词统计。输入参数为统计信息map，当前单词word，当前单词出现的行号lineNo
void statisWord(WordsStatis& wordsStatis, const std::string& word, int lineNo)
{
   wordsStatis[word].lines.insert(lineNo);  // 使用 unordered_set 来避免重复行号
}

// 排序所需的比较函数
bool cmp(const std::pair<std::string, WordInfo>& a, const std::pair<std::string, WordInfo>& b)
{
   return a.second.lines.size() > b.second.lines.size();  // 按行号出现次数降序排序
}

void printStatis(const WordsStatis& wordsStatis)
{
   // 将统计信息map中的数据复制到一个vector中
   std::vector<std::pair<std::string, WordInfo>> wordsVector(wordsStatis.begin(), wordsStatis.end());

   // 对vector进行排序（三个参数：起点，终点，比较函数指针）
   std::sort(wordsVector.begin(), wordsVector.end(), cmp);

   printf("WORD                 COUNT APPEARS-LINES\n");
   // 对vector中的每一个元素进行打印
   for (const auto& pair : wordsVector)
   {
      // 打印单词以及出现的次数统计
      printf("%-20s %-5ld ", pair.first.c_str(), pair.second.lines.size());

      // 下面打印此单词出现的行号，最多打印20个
      int i = 0;
      for (const auto& line : pair.second.lines)
      {
         if (i != 0)
            printf(",");
         printf("%d", line);
         if (++i >= 20)
            break;
      }
      printf("\n");
   }
}

int main(int argc, const char* argv[])
{
   // 获取程序开始时间
   auto start_time = std::chrono::high_resolution_clock::now();

   // 命令行需要1个参数，指定要处理的文本文件
   if (argc != 2)
   {
      printf("Usage: %s filename\n", argv[0]);
      return 1;
   }
   const char* fileName = argv[1];

   FILE* f = fopen(fileName, "r");
   if (f == NULL)
   {
      printf("can not open file %s\n", fileName);
      return 1;
   }

   WordsStatis wordsStatis;  // 用于存放统计结果
   std::vector<char> word;   // 使用字符数组代替 std::string
   int lastChar = 0;         // 上一个被处理的字符
   int curChar;              // 当前被处理字符
   int lineNo = 1;           // 记录当前行号

   while ((curChar = fgetc(f)) != EOF)  // 依次读取文件中每一个字符，直到遇到EOF结束
   {
      if (curChar == '\n')  // 遇到回车符，则行号加1
         lineNo++;

      if (isalpha(curChar))  // 如果当前字符是字母，则当前单词追加这个字母（统一转换为小写字母）
         word.push_back((char)tolower(curChar));
      else
      {
         // 如果当前字符不是字母，并且上一个字符是字母，则表明一个单词处理完毕，统计它
         if (isalpha(lastChar))
         {
            // 将字符数组转换为字符串并统计
            std::string currentWord(word.begin(), word.end());
            statisWord(wordsStatis, currentWord, lineNo);
            word.clear();  // 清空字符数组，准备处理下一个单词
         }
      }
      lastChar = curChar;
   }

   fclose(f);

   printStatis(wordsStatis);

   // 获取程序结束时间
   auto end_time = std::chrono::high_resolution_clock::now();

   // 计算时间差
   auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);

   // 输出程序运行时间
   printf("Time taken: %lld ms\n", duration.count());

   return 0;
}
