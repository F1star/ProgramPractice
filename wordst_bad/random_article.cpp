#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <string>

using namespace std;

// 生成随机字符
char getRandomChar() {
    return 'a' + rand() % 26;  // 生成一个小写字母 a-z
}

// 生成一个随机单词
string getRandomWord() {
    int length = rand() % 10 + 3;  // 生成一个长度在 3-12 的随机单词
    string word;
    for (int i = 0; i < length; ++i) {
        word += getRandomChar();
    }
    return word;
}

// 生成随机文章
string generateRandomArticle(int wordCount) {
    string article;
    for (int i = 0; i < wordCount; ++i) {
        string word = getRandomWord();
        article += word + " ";
        if(i % 10 == 9) {  // 每生成 10 个单词，换行
            article += "\n";
        }
    }
    return article;
}

int main() {
    srand(time(0));  // 使用当前时间作为随机数种子

    int wordCount = 10000;  // 生成文章的单词数量
    string article = generateRandomArticle(wordCount);

    // 输出到文件
    ofstream outFile("random_article.txt");
    if (outFile.is_open()) {
        outFile << article;
        outFile.close();
        cout << "Random article has been generated and saved to random_article.txt!" << endl;
    } else {
        cout << "Unable to open file for writing!" << endl;
    }

    return 0;
}
