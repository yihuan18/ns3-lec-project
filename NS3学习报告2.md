# NS3学习报告2

标签（空格分隔）：NS3学习

---

##一.网络拓扑与运行结果
###1.third.cc的网络拓扑
    两个csma局域网通过一个p2p信道连接：
![struction1](http://ww2.sinaimg.cn/mw690/9fae6ceagw1f50gptm9z1j20hg05tmxq.jpg)
server安装在节点n4上，四个客户机程序分别安装在节点n5,n6,n7和n0上。
###2.third.cc的运行结果
![third.cc运行结果](http://ww4.sinaimg.cn/mw690/9fae6ceagw1f4wxbytt3mj20k00c2jzv.jpg)
并且生成“third-0-0”,"third-0-1","third-1-0","third-1-1"的.pcap文件。
###3.third1.cc的网络拓扑
    一个wifi小组依次连接两个p2p信道：
![struction2](http://ww1.sinaimg.cn/mw690/9fae6ceagw1f50gpsztmwj20dx052gm2.jpg)
###4.third1.cc的运行结果
PS：third1.cc运用的依然是随机游走模型
![third1.cc运行结果](http://ww1.sinaimg.cn/mw690/9fae6ceagw1f4wxby6jlsj20k70b2n50.jpg)
并且生成“third1-0-0”,"third1-0-1","third1-1-0","third1-1-1"，“third1-2-0”的.pcap文件。

##二.移动模型修改与运行结果
###1.移动模型修改
    在third1.cc的基础上修改，将wifi节点的随机游走模型改成线性远离AP节点的移动模型。
修改后的代码为：
![移动模型代码](http://ww1.sinaimg.cn/mw690/9fae6ceagw1f50g6wjbovj20jq06xacx.jpg)

###2.运行结果
![third2.cc运行结果](http://ww2.sinaimg.cn/mw690/9fae6ceagw1f50g0zcc2nj20k00b1ahs.jpg)
并且生成“third2-0-0”,"third2-0-1","third2-1-0","third2-1-1"，“third2-2-0”的.pcap文件。
##三.总结
>    NS3仿真脚本的编写方式为：
>     1 创建网络节点；
>    2 设置链路；
>    3 安装设备；
>     3 安装ip协议栈；
>    4 分配ip地址；
>    5 安装应用程序；
>    6 设置仿真时间参数。
    

　　　　　　　　    　　　　　　　　 










