# MakeClass使用
## 生成Class
打开`root`文件，本例中直接运行
```
root -l ex42.C
# 进入root命令行环境
t3->MakeClass()
#文件夹下产生t3.h,t3.C
```
## 使用Class读取root
> 首先修改`t3.C`中的`Loop()`函数，详见`t3.C`文件
```
root -l t3.C
# 进入root命令行环境
t3 t
t.Loop()
#文件夹下产生ex42.png,包含部分和全部动量分布图
```
## 使用vector读取
> 在`t3.h`,`t3.C`中添加`void sortVector()`函数，具体参见代码文件
```
root -l t3.C
# 进入root命令行环境
t3 t
t.sortVector()
# 命令行会打印前100个数字，太多输出会看不清楚，姑且输出100个
`

