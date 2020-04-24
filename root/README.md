# root
## histogram
>Problem
发现直接使用下面代码输出的分布不是高斯分布，还未经过复现确定问题
```
{
Float x=gRandom->Gaus();
Float y=gRandom->Gaus();
}
```

目前代码中包括(hist/)

+ Gauss2.root:产生的root文件
+ GaussEach.pdf:将二维图投影至一维**(在读root后才进行的投影)**
+ GaussLEGO3.pdf  GaussSURF1POL.pdf   GaussCOLZ.pdf  GaussLEGO1.pdf  Gauss.pdf:使用不同的画图格式绘制的二维图
+ hist2.C:包含写root和读root文件程序

chiCaculate.C
+ 加入直接定义hist中bin的数据值
## tree
+ ex41.C:使用类进行tree的单branch多leaf的实现
+ tree.C:使用结构体进行tree的单branch多leaf的实现,同时实现从root文件读取tree并且打印
可以使用数组进行多leaf添加，注意
数组int p[n]中p与&p返回的地址一样，但是类型不同
p: int*
&p: int[n]*

+ 使用class和struct分别存储的root文件在读取后,TTree::Print()结果有差异，struct符合预期，class中每个变量都是branch，待研究
+ root userguide中`12.15.1 Writing the Tree`对struct的写入很特别，似乎与class方式的写入很像
### readtree
TTree::MakeClass()给出了一个非常好的读取root文件的代码框架
+ 框架内部如何实现读取branch内部的leaf，待研究

目前在`treeMk.C`中实现了使用数组读取对应的数组branch
## Fit
> 拟合
`fit`文件夹中包含
+ `fitGaus.C`对拟合后的`mu`,`sigma`,`chi`分布进行绘制，`paraDistri.png`是未对`sigma`取绝对值，发现拟合后竟然有负值，也很符合常理，因为平方后不会有影响，于是剩下两张图均取了绝对值；`paraDistri.png`每个高斯分布仅有100个点，因此`sigma`的分布偏差较大；为了验证上述断言，我将每个高斯分布的点数增加至1000个点，再次绘制，发现此次拟合结果变好，sigma均接近1，第一种拟合更接近。


