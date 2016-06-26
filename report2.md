# NS3学习报告2

标签（空格分隔）：NS3学习

---

##一.网络拓扑与运行结果
###1.ns3-lec-pro2_third.cc的网络拓扑
    两个csma局域网通过一个p2p信道连接：
![struction1](http://ww2.sinaimg.cn/mw690/9fae6ceagw1f50gptm9z1j20hg05tmxq.jpg)
server安装在节点n4上，四个客户机程序分别安装在节点n5,n6,n7和n0上。
###2.ns3-lec-pro2_third.cc的运行结果
![ns3-lec-pro2_third.cc运行结果](http://ww4.sinaimg.cn/mw690/9fae6ceagw1f4wxbytt3mj20k00c2jzv.jpg)
并且生成“ns3-lec-pro2_third-0-0”,"ns3-lec-pro2_third-0-1","ns3-lec-pro2_third-1-0","ns3-lec-pro2_third-1-1"的.pcap文件。
![](http://a1.qpic.cn/psb?/V12cRcVV46ogeS/9kNwHCln3Yntk99hCmc4L4GWEIP3x5ZJh.8SU*FuNq0!/b/dAgBAAAAAAAA&bo=7QHHAAAAAAAFBw8!&rf=viewer_4)
###3.ns3-lec-pro2_third1.cc的网络拓扑
    一个wifi小组依次连接两个p2p信道：
![struction2](http://ww1.sinaimg.cn/mw690/9fae6ceagw1f50gpsztmwj20dx052gm2.jpg)
###4.ns3-lec-pro2_third1.cc的运行结果
PS：ns3-lec-pro2_third1.cc运用的依然是随机游走模型
![ns3-lec-pro2_third1.cc运行结果](http://ww1.sinaimg.cn/mw690/9fae6ceagw1f4wxby6jlsj20k70b2n50.jpg)
并且生成“ns3-lec-pro2_third1-0-0”,"ns3-lec-pro2_third1-0-1","ns3-lec-pro2_third1-1-0","ns3-lec-pro2_third1-1-1"，“ns3-lec-pro2_third1-2-0”的.pcap文件。
![](http://a2.qpic.cn/psb?/V12cRcVV46ogeS/COve6jVFSqxdR8xyvSKyXX*aQBM7uqCxNdI9e4DDABs!/b/dFcBAAAAAAAA&bo=5QErAQAAAAAFB.o!&rf=viewer_4)

##二.移动模型修改与运行结果
###1.移动模型修改
    在ns3-lec-pro2_third1.cc的基础上修改，将wifi节点的随机游走模型改成线性远离AP节点的移动模型。
修改后的代码为：

```c++
  mobility.SetMobilityModel("ns3::ConstantVelocityMobilityModel");
  mobility.Install (wifiStaNodes);
  for (uint n=0 ; n < wifiStaNodes.GetN() ; n++)
  {
     Ptr<ConstantVelocityMobilityModel> mob = wifiStaNodes.Get(n)->GetObject<ConstantVelocityMobilityModel>();
     mob->SetVelocity(Vector(10, 0, 0));
  }
```

###2.运行结果
![ns3-lec-pro2_third2.cc运行结果](http://ww2.sinaimg.cn/mw690/9fae6ceagw1f50g0zcc2nj20k00b1ahs.jpg)
并且生成“ns3-lec-pro2_third2-0-0”,"ns3-lec-pro2_third2-0-1","ns3-lec-pro2_third2-1-0","ns3-lec-pro2_third2-1-1"，“ns3-lec-pro2_third2-2-0”的.pcap文件。
![](http://a2.qpic.cn/psb?/V12cRcVV46ogeS/HAQ75slJXlaYcMekoq2mzxOhPxEJM0zML53orqTZ5dI!/b/dFoBAAAAAAAA&bo=3gEeAQAAAAAFB.Q!&rf=viewer_4)
##三.总结
>    NS3仿真脚本的编写方式为：
>     1 创建网络节点；
>    2 设置链路；
>    3 安装设备；
>     3 安装ip协议栈；
>    4 分配ip地址；
>    5 安装应用程序；
>    6 设置仿真时间参数。
    

　　　　　　　　    　　　　　　　　 










