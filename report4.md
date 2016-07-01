# NS3学习报告四

周裔欢 2013100102029

---

>wifi网络搭建步骤：
1. 分别创建sta节点和ap节点 （NodeContainer wifiApNode）；
2. 设置wifi节点间的信道，分别利用WifiChannelHelper，WifiPhyHelper，WifiHelper，WifiMacHelper；
3. 在节点上安装设备；
4. 设置节点的初始位置和移动模型；
5.  配置协议栈，分配ip地址；
6.  在节点上安装应用程序；
7.  启动应用程序，进行仿真。

##拓扑搭建
**要求**：两个wifi网络，各有6个sta，1个ap；实现两个wifi网络之间的通信
**完成**：
　　1. 首先分别创建两个wifi网络，他们互相独立。
　　2. 然后创建第三个wifi网络，取第一个wifi网络的ap节点作为其的ap节    点，并且取第二个wifi网络的ap节点作为其的唯一sta节点。
　　3. 如此，该网络中的ap节点均有两个身份。
　
##场景范围
场景范围：500m*500m

##传播模型设置
设置传播模型为ConstantSpeedPropagationDelayModel
```c++:
YansWifiChannelHelper channel = YansWifiChannelHelper::Default ();
channel.SetPropagationDelay("ns3::ConstantSpeedPropagationDelayModel");
```
##Mac类型设置
要求：设置Mac类型为NqosWifiMacHelper（没有QoS保障的Mac层机制）
```c++:
NqosWifiMacHelper mac = NqosWifiMacHelper::Default ();
```

##移动模型设置
**要求**：移动模型为随机游走模型，设定初始位置为两个六边形，边长10m，sta在6个顶点上，ap在六边形中间；两个六边形中心相距50m
```c++:
 MobilityHelper mobility; 
 Ptr<ListPositionAllocator> positionAlloc = CreateObject<ListPositionAllocator> (); 
  //第一个wifi网络的sta节点位置
  positionAlloc->Add (Vector (5.0, 0.0, 0.0)); 
  positionAlloc->Add (Vector (0.0, 8.66, 0.0)); 
  positionAlloc->Add (Vector (5.0, 17.32, 0.0)); 
  positionAlloc->Add (Vector (15.0, 17.32, 0.0)); 
  positionAlloc->Add (Vector (20.0, 8.66, 0.0)); 
  positionAlloc->Add (Vector (15.0, 0.0, 0.0));
  //第2个wifi网络的sta节点位置
  positionAlloc->Add (Vector (55.0, 0.0, 0.0)); 
  positionAlloc->Add (Vector (50.0, 8.66, 0.0)); 
  positionAlloc->Add (Vector (55.0, 17.32, 0.0)); 
  positionAlloc->Add (Vector (65.0, 17.32, 0.0)); 
  positionAlloc->Add (Vector (70.0, 8.66, 0.0)); 
  positionAlloc->Add (Vector (65.0, 0.0, 0.0));
  //两个Ap节点的位置
  positionAlloc->Add (Vector (10.0, 8.66, 0.0)); 
  positionAlloc->Add (Vector (60.0, 8.66, 0.0));
  mobility.SetPositionAllocator (positionAlloc); 
  
mobility.SetMobilityModel ("ns3::RandomWalk2dMobilityModel",
                             "Bounds", RectangleValue (Rectangle (-25, 25, -50, 50)));
mobility.Install (wifiStaNodes);
mobility.SetMobilityModel ("ns3::RandomWalk2dMobilityModel",
                             "Bounds", RectangleValue (Rectangle (25, 95, -50, 50)));
mobility.Install (wifiStaNodes1);
```

##echoAPP传输包参数设置
**要求**：packet size为512byte，包间隔为100ms
```c++:
echoClient.SetAttribute ("MaxPackets", UintegerValue (1));
echoClient.SetAttribute ("Interval", TimeValue (Seconds (0.1)));
echoClient.SetAttribute ("PacketSize", UintegerValue (512));
```
##仿真结果
![运行](http://ww4.sinaimg.cn/mw690/9fae6ceagw1f5dmv762r2j211y0lctn3.jpg)
使用PyViz查看:
① 拓扑搭建:
![拓扑](http://ww3.sinaimg.cn/mw690/9fae6ceagw1f5dmv9gh1nj211y0lcn37.jpg)
② 运行时仿真图：
![](http://ww4.sinaimg.cn/mw690/9fae6ceagw1f5dmv8dglbj211y0lc0zb.jpg)

![](http://ww4.sinaimg.cn/mw690/9fae6ceagw1f5e89llr2zj20m80gon1s.jpg)

##Tracing
记录两个ap节点（第三个wifi信道），并在两个wifi网络的sta节点中各取一个进行记录。
```c++:
phy2.EnablePcap("pro4",staDevices2.Get(0));
phy2.EnablePcap("pro4",apDevices2.Get(0));    
phy1.EnablePcap("pro4",staDevices1.Get(0));
phy.EnablePcap ("pro4", staDevices.Get (0));
```
得到：
![pcap](http://ww1.sinaimg.cn/mw690/9fae6ceagw1f5e8okcgf7j20m80gowji.jpg)

##Matlab数据处理
```matlab:
clear all;
cli_send=[2,2.5,3,3.5,4,4.5,5];
ser_recv=[2.01458,2.50721,3.00618,3.50079,4.00849,4.50348,5.0034];
cli_recv=[2.02525,2.50927,3.01625,3.50168,4.01273,4.51372,5.0076];
client_num=[1,2,3,4,5,6,7];
time_slot1=ser_recv-cli_send;  %客户机到服务器发送时间
time_slot2=cli_recv-ser_recv;  %服务器到客户机回送时间
time_slot=time_slot1+time_slot2;
figure(1),plot(client_num,time_slot);
f = figure('Position',[440 500 461 146]);
data=[cli_send',ser_recv',cli_recv',time_slot1',time_slot2',time_slot'];
colnames = {'client发送时间', '到达server时间', '回送到client时间','发送时间差','回送时间差','网络延迟'};
figure(2),t = uitable(f,'Data',data,'ColumnName',colnames);
t.Position(3) = t.Extent(3);
t.Position(4) = t.Extent(4);
```
![](http://ww1.sinaimg.cn/mw690/9fae6ceagw1f5ehpq7ii1j20g307ntb5.jpg)

![](http://ww3.sinaimg.cn/mw690/9fae6ceagw1f5ehppriosj20fx0e6myh.jpg)
##遇到的问题
1. 如果多个客户机同时发送，则会出现服务器只回弹部分数据的情况
解决：将模拟时间错开，每隔0.5s发送一次。








