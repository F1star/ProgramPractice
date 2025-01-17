# 北京邮电大学计算机学院程序设计实践风格作业

## 程序：`fifo_queue.c`
### 问题1：
43行存在未使用一致的花括号风格，应修改为
```
	else
	{
		queue->queue_head = item->next_item;
	}
```
### 问题2：
18和33行存在函数名太过冗长的问题，应修改为 `push_queue` 和 `pop_queue`
### 问题3：
7，8，13，14行存在变量名太过冗长的问题，应修改为 `value` , `next` , `head` , `tail`

## 程序：`serialize_json.cpp`
### 问题1：
22行存在未使用表达式的自然形式的问题，应修改为 `if ('\x00' > *c || *c > '\x1f')`
### 问题2：
37行存在“否定之否定”的问题，37-42行应修改为
```
	bool isfirst = true;
   	for(i = m.begin(); i != m.end(); i++){
      		if(isfirst)
        		isfirst = false;
      		else
        		o << ",";
```
### 问题3：
36行存在迭代器过于复杂的问题，应删除36行 `map<string, string>::iterator i;`
	修改38行为 
```
	for(auto i = m.begin(); i != m.end(); i++){
```
### 问题4：
11和34行存在变量名过于简单，缺乏描述性的问题，应修改为 `ostringstream output;`

## 程序：`split_str.cpp`
### 问题1：
37行逻辑出现错误，因为 `while` 的条件就是 `buffer[i] != 0` , 所以跳出 `while` 循环就不会在满足这个条件了，所以这个条件语句在这里是多余的，应在51行后加入
```
	if (argc == 0) {
		printf("invalid command.\n");
	}
```
	并删去37-41行
### 问题2：
数值较多，该参数值较麻烦，应将代码其中的30和32改为宏定义，在程序的第2行加入
```
	#define MAX_LENGTH 32
	#define MAX_NUM 30 
```

然后将程序中的 32 都改为 `MAX_LENGTH` ，31 改为  `MAX_LENGTH - 1` ，30 改为 `MAX_NUM`
	
### 问题3：
50行通过 `new` 申请的内存未释放，会导致内存的泄漏，应该在 `main` 函数的末尾加入 
```
	for(i = 0; i < 30; i++) {    
            	delete[] argv[i];             
		argv[i] = nullptr;  
   	}  
```