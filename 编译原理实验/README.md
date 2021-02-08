## 实验题目

编译原理实验三：关于tiny语言的文法扩充

 

## 中文摘要

Tiny语言的程序结构非常简单，它在语法上与Ada或Pascal的语法相似，仅有一个分号分隔开的语句序列。本实验基于Tiny语言原有文法的基础上对其进行扩充新的语法规则。使其能够对加入扩充文法的tiny程序语句序列进行语法分析和语法树的生成。

图形界面使用了跨平台C++图形用户界面应用程序开发框架QT来实现。

 

## 实验目的

基于Tiny语言原有文法的基础上对其进行扩充新的语法规则。使其能够对加入扩充文法的tiny程序语句序列进行语法分析和语法树的生成。掌握语法分析中自顶而下的递归下降分析方法。

 

## 实验意义

掌握语法分析中自顶而下的递归下降分析方法。明确递归算法的调用流程，体会如何利用语法分析的递归下降程序对程序序列进行语法分析。更加清楚、了解编译原理的实际应用，提高代码编写能力。

 

## 实验设计

扩充的文法如下图所示



![image-20210208110006381](https://gitee.com/chen_jian_hang/pic/raw/master/image/image-20210208110006381.png)



### 文法修改：

```
Stament -> if-stmt|repeat-stmt|assgin-stmt|read-stmt|write-stmt|plus_assgin_stmt
```

```
Plus-assgin_stmt ->identifier += exp; 
```

```
Mulop -> * | / | **
```



### 实验软件界面

#### 主界面

![image-20210208110059766](https://gitee.com/chen_jian_hang/pic/raw/master/image/image-20210208110059766.png)



#### 代码编辑区

![](C:\Users\jankin\AppData\Roaming\Typora\typora-user-images\image-20210208110107776.png)



#### 语法树展示

![](https://gitee.com/chen_jian_hang/pic/raw/master/image/image-20210208110107776.png)

#### 核心代码实现（递归下降方法实现）



##### if语句

```c++
TreeNode * if_stmt(void)
{
    TreeNode * t = newStmtNode(IfK);
    match(IF);
    match(LPAREN);
    if (t != NULL) t->child[0] = exp();
    match(RPAREN);
    if (t != NULL) t->child[1] = stmt_sequence();
    if (token == ELSE) {
        match(ELSE);
        if (t != NULL) t->child[2] = stmt_sequence();
    }
    return t;
}
```



##### for语句

```c++
TreeNode * for_stmt(void)
{
    TreeNode * t = newStmtNode(ForK);
    match(FOR);
    if ((t != NULL) && (token == ID))
    {
        t->attr.name = copyString(tokenString);
    }
    match(ID);
    match(ASSIGN);
    if (t != NULL)
    {
        t->child[0] = simple_exp();
    }
    if (token == TO)
    {
        match(TO);
    }
    if (token == DOWNTO)
    {
        match(DOWNTO);
    }

    if (t != NULL)
    {
        t->child[1] = simple_exp();
    }

    match(DO);

    if (t != NULL)
    {
        t->child[2] = stmt_sequence();
    }

    match(ENDDO);
    return t;
}
```



##### dowhile

```c++
TreeNode * dowhile_stmt(void)
{
    TreeNode * t = newStmtNode(DoWhileK);
    match(DO);
    if (t != NULL) t->child[0] = stmt_sequence();
    match(WHILE);
    match(LPAREN);
    if (t != NULL) t->child[1] = exp();
    match(RPAREN);
    return t;
}
```



##### while

```c++
TreeNode * while_stmt(void)
{
    TreeNode * t = newStmtNode(WhileK);
    match(WHILE);
    if (t != NULL) t->child[0] = exp();
    match(DO);
    if (t != NULL) t->child[1] = stmt_sequence();
    match(ENDWHILE);
    return t;
}
```



##### +=

```c++
TreeNode * plusAssign_stmt(void)
{
    TreeNode * t = newStmtNode(PlusAssignK);
    if((t!=NULL) && (token==ID))
        t->attr.name = copyString(tokenString);
    match(ID);
    match(PLUSASSIGN);
    if(t!=NULL){
        t->child[0] = exp();
    }

    return t;
}
```



```c++
TreeNode * term(void)
{
  TreeNode * t = factor();
  while ((token==TIMES)||(token==OVER)||(token==DBMULTI))
  { TreeNode * p = newExpNode(OpK);
    if (p!=NULL) {
      p->child[0] = t;
      p->attr.op = token;
      t = p;
      match(token);
      p->child[1] = factor();
    }
  }
  return t;
}
```



```c++
TreeNode * statement(void)
{
    TreeNode * t = NULL;
    switch (token) {
    case IF: t = if_stmt(); break;
    case REPEAT: t = repeat_stmt(); break;
    case ID : if(isPlusAssign==true)
                {
                    t = plusAssign_stmt();
                }
              else
                { t = assign_stmt();}
              break;
    case READ: t = read_stmt(); break;
    case WRITE: t = write_stmt(); break;

    case DO: t = dowhile_stmt(); break;
    case WHILE: t = while_stmt(); break;
    case FOR: t = for_stmt(); break;

    default: syntaxError((char *)"unexpected token -> ");
        printToken(token, tokenString);
        token = getToken();
        break;
    } /* end case */
    return t;
}
```



## 感想

​		通过这次编译原理实验，对编译原理中递归下降的分析方法有了新的认识，不只停留在手工的做法而是能用算法的思想去进一步理解递归下降的方法，能够更好地掌握编译原理的思想与方法。