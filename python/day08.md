#正则表达式

**正则表达式：字符串匹配的一种规则**

##元字符

字符|作用
:--|:--
.|匹配换行符以外的字符
\w|匹配字母，数字，下划线
\s|匹配任意空白符
\d|匹配数字
\W|匹配非字母，数字，下划线
\D|匹配非数字
\S|匹配非空白符
\t|匹配一个制表符 -- tab
\n|匹配一个换行符
\b|匹配一个单词的结尾
^|匹配字符串的开始
$|匹配字符串的结尾

使用：`.\b` 匹配所有单词的结尾中间用空格隔开

`^[a-z]` 以小写字母开头
输入：
```
dasdda
adasdas
wqeqwe
```
输出：
```
d
a
w
```
`^[a-z]$`
输入：
`qq       q`
输出：
`无        q`

`a|b `  匹配a或者b
输入:`asadb` 
输出:`b` 

`abc|b `  优先匹配abc
输入:`abcbb`
输出:`abc bb`

`() `     匹配括号内的表达式
对多个字符组做整体约束
写在一个`()`里面的叫做一个分组
需要对某个表达式做整体的量词约束时加上`()`

**在python的re模块中**
**`findall `和 `split` 有分组优先**
`[...] `  匹配字符组中的字符
`[^...]`  匹配字符组中所有字符

`[^a]`除了a其他的都匹配

匹配任意字符包括回车:`\W\w]`或`[\S\s]`或`[\D\d]`

##量词
符号|作用
:--|:--
*|匹配多次
+|重复匹配尽量多次
?|匹配一条结果 没有也算一次
{n}|重复n次
{n,}|重复n次以上
{n,m}|重复n到m次
对于`*`,`+`和`?`

`*`是0到无限次
`+`是1到无限次
`?`是0到1次

**所有的量词都要用在正则规则后面**
**`\d{11} `:匹配连续11位数字**

##贪婪匹配和非贪婪匹配

### `*`和 `+` 是贪婪匹配

###`?`是非贪婪匹配

规则：`<.*>`
输入：`<script>...<script>dsadsa`
输出:`<script>...<script>`

规则：`<.*?>`
输入：`<script>...<script>dsadsa`
输出:
```
<script>
<script>
```
**`*`后面跟了`?`此时为非贪婪匹配**
**它会从第一个`<`开始直到找到第一个`>`然后循环**
**直到全部找完**
```
. 是任意字符
* 是取0 到 无限长度
? 是非贪婪模式
```

###一般的写法是:
`.*?abc`


取任意的长度直到遇到`abc`就返回结果
abc可以是任意的字符串

`[^和]+` 只要不是`和`就匹配
输入:`ab和abc和abcd`
输出:
```
ab
abc
abcd
```

##re模块



