# NS3学习报告三

---

##Logging系统
在脚本中定义和启动记录组件：
```c++
NS_LOG_COMPONENT_DEFINE(“...”)；
LogComponentEnable（“...”，LOG_LEVEL_...）;
```
在命令行中启动记录组件：
```cmd
①export NS_LOG=...= LOG_LEVEL_...
```
在ns3-lec-pro3.cc中启动UdpEchoClientApplication记录组件，并且记录下所有日志消息：

![logging记录](http://ww4.sinaimg.cn/mw690/9fae6ceagw1f57go386icj211y0lcnca.jpg)

##Tracing系统
>ASCII Tracing：以ASCII格式的信息输出
① 声明一个AsciiTraceHelper对象
```c++
AsciiTraceHelper ascii;
```
>② 激活Ascii Tracing，并输出文件为··.tr
```c++
pointToPoint.EnableAsciiAll (ascii.CreateFileStream (“***.tr”));
```

>PCAP Tracing::输出为pcap文件，可通过wireshark，TcpDump查看
```c++
PointToPointHelper::EnablePcapAll ("example");
```
在ns3-lec-pro3.cc同时使用ASCII Tracing和PCAP Tracing输出以下文件：

![文件名截图](http://ww4.sinaimg.cn/mw690/9fae6ceagw1f57go18c4aj20e107z3zk.jpg)

（除LICENSE和Makefile的7个文件）

##PyViz系统
NS3中的仿真可视化工具，调用如下命令行：
```cmd
./waf –run scratch/ns3-lec-pro3 --vis
```
可得到仿真可视化结果：

![仿真图](http://ww4.sinaimg.cn/mw690/9fae6ceagw1f57go23l2zj20m80gogp5.jpg)

其中红色的点为wifi节点，灰色的点为P2P节点。

##Wireshark工具使用
>Wireshark（前称Ethereal）是一个网络封包分析软件。网络封包分析软件的功能是撷取网络封包，并尽可能显示出最为详细的网络封包资料。

如果使用Wireshark工具打开由Tracing系统记录的pcap文件，可以看到：

![ns3-lec-pro3-0-0.pcap](http://ww3.sinaimg.cn/mw690/9fae6ceagw1f57go47h0zj211y0lcdso.jpg)

有对网络中发送的数据的解析。

##Matlab数据处理
用Matlab绘制出回音壁模拟的时间：

![diagram](http://a1.qpic.cn/psb?/V12cRcVV46ogeS/9FObwzuucDe*IPP1Zku7uchEp.GzkQiNOdcBHZ.i0Eo!/b/dAUBAAAAAAAA&bo=jQH9AAAAAAAFB1U!&rf=viewer_4)

##Wireshark安装步骤
系统自动下载安装：
```cmd
$sudo apt-get update
$sudo apt-get install wireshark
```
启动wireshark软件：
```cmd
$wireshark
```
##PyViz安装步骤
安装依赖包：
```cmd
$sudo apt-get install python-dev python-pygraphviz python-kiwi python-pygoocanvas python-gnome2 python-gnomedesktop python-rsvg
```

安装交互python
```cmd
$sudo apt-get install ipython
```

测试：
```cmd
$./waf --run ··· --vis
```


###参考网址:
http://blog.sina.com.cn/s/blog_7ec2ab360102wx5z.html
http://blog.csdn.net/mars_nudt/article/details/7464088#comments
http://blog.csdn.net/bo5509/article/details/8189757


