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
## tree
+ ex41.C:使用类进行tree的单branch多leaf的实现
+ tree.C:使用结构体进行tree的单branch多leaf的实现,同时实现从root文件读取tree并且打印

