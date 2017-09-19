/*
Implement wildcard pattern matching with support for '?' and '*'.

'?' Matches any single character.
'*' Matches any sequence of characters (including the empty sequence).

The matching should cover the entire input string (not partial).

The function prototype should be:
bool isMatch(const char *s, const char *p)

Some examples:
isMatch("aa","a") ? false
isMatch("aa","aa") ? true
isMatch("aaa","aa") ? false
isMatch("aa", "*") ? true
isMatch("aa", "a*") ? true
isMatch("ab", "?*") ? true
isMatch("aab", "c*a*b") ? false

参考：http://www.cnblogs.com/boring09/p/4246055.html
非常有技巧性的一道题，虽然本质上仍然是搜索+回溯，但关键是如何处理模式串里的多余的*，
如果处理的不好就超时了。
基本的搜索+回溯算法是这样的，对于原串s和模式串p，依次遍历其字符：
	(a) 如果p[j]="*"，依次将p[j+1..p.length]和s[i..s.length]、s[i+1..s.length]、s[i+2..s.length]...匹配，
		如果全都失败了，将i和j回溯到上一个"*"号位置
	(b) 如果s[i]="?"或s[i]=p[j]，说明当前字符匹配，此时i++,j++
	(c) 否则，说明当前字符不匹配，回溯至上一个星号位置
可以看出，如果"*"很多，而且总是失败，那么算法的回溯代价是巨大的

 
优化的地方在于：对于情况(a)，如果当前匹配失败，就说明整个匹配失败了，不需要回溯至上一个星号处。
说白了就是，最多回溯到p串的上一个"*"号处，在往前的"*"不用管了。
   0 1 2 3 4 5 6 7 8 
s: a b c d a c c c
   | |  \ \ \ \
p: a b * c d * a c c
               |
              失配
上面的例子，s[5]!=p[6]，那么最多只需要回溯到第二个星号位置（p[5]="*"），不需要回溯到第一个星号位置（p[2]="*"）。
因为回溯到更早的"*"不会产生新的匹配结果。（这个结论以后有机会证明一下）
*/
#include <stdio.h>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <string>
#include <cstdlib>
using namespace std;

class Solution {
public:
    bool isMatch(string s, string p) {
        int m=s.size(),n=p.size();
		int i=0,j=0,star=-1,backup=-1;
		while(i<m)
		{
			if(j<n && p[j]=='*'){
				backup=i; //出现星号时 s串中匹配到的位置
				star=j++;//星号在p串中的位置
			}
			else if(j<n && p[j]=='?' || s[i]==p[j]){
				i++,j++;  //匹配 向前移动
			}
			else if(star>=0){//回溯
				i=++backup; //回溯到上次开始位置的下一位置
				j=star+1;//p串从星号下一位位置重新开始
			}
			else
				return false;
		}
		while(j<n && p[j]=='*') j++;
		return j==n;
    }
};
int main()
{
	Solution mys;
	string s="aab";
	string p="a*";
	cout<<mys.isMatch(s,p)<<endl;
	return 0;
}








