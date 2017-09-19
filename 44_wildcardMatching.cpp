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

�ο���http://www.cnblogs.com/boring09/p/4246055.html
�ǳ��м����Ե�һ���⣬��Ȼ��������Ȼ������+���ݣ����ؼ�����δ���ģʽ����Ķ����*��
�������Ĳ��þͳ�ʱ�ˡ�
����������+�����㷨�������ģ�����ԭ��s��ģʽ��p�����α������ַ���
	(a) ���p[j]="*"�����ν�p[j+1..p.length]��s[i..s.length]��s[i+1..s.length]��s[i+2..s.length]...ƥ�䣬
		���ȫ��ʧ���ˣ���i��j���ݵ���һ��"*"��λ��
	(b) ���s[i]="?"��s[i]=p[j]��˵����ǰ�ַ�ƥ�䣬��ʱi++,j++
	(c) ����˵����ǰ�ַ���ƥ�䣬��������һ���Ǻ�λ��
���Կ��������"*"�ܶ࣬��������ʧ�ܣ���ô�㷨�Ļ��ݴ����Ǿ޴��

 
�Ż��ĵط����ڣ��������(a)�������ǰƥ��ʧ�ܣ���˵������ƥ��ʧ���ˣ�����Ҫ��������һ���ǺŴ���
˵���˾��ǣ������ݵ�p������һ��"*"�Ŵ�������ǰ��"*"���ù��ˡ�
   0 1 2 3 4 5 6 7 8 
s: a b c d a c c c
   | |  \ \ \ \
p: a b * c d * a c c
               |
              ʧ��
��������ӣ�s[5]!=p[6]����ô���ֻ��Ҫ���ݵ��ڶ����Ǻ�λ�ã�p[5]="*"��������Ҫ���ݵ���һ���Ǻ�λ�ã�p[2]="*"����
��Ϊ���ݵ������"*"��������µ�ƥ����������������Ժ��л���֤��һ�£�
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
				backup=i; //�����Ǻ�ʱ s����ƥ�䵽��λ��
				star=j++;//�Ǻ���p���е�λ��
			}
			else if(j<n && p[j]=='?' || s[i]==p[j]){
				i++,j++;  //ƥ�� ��ǰ�ƶ�
			}
			else if(star>=0){//����
				i=++backup; //���ݵ��ϴο�ʼλ�õ���һλ��
				j=star+1;//p�����Ǻ���һλλ�����¿�ʼ
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








