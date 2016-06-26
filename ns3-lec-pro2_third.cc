/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation;
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include "ns3/core-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/network-module.h"
#include "ns3/applications-module.h"
#include "ns3/wifi-module.h"
#include "ns3/mobility-module.h"
#include "ns3/csma-module.h"
#include "ns3/internet-module.h"

// Default Network Topology
//默认网络拓扑
// Number of wifi or csma nodes can be increased up to 250
//                          |
//                 Rank 0   |   Rank 1
// -------------------------|----------------------------
//   LAN 10.1.3.0    
//                         
//  =====================
//  |      |      |     |      10.1.1.0
//    n5   n6   n7   n0 ------------------ n1   n2   n3   n4
//                     point-to-point      |    |    |    |
//                                         ================
//                                             LAN 10.1.2.0

using namespace ns3;

NS_LOG_COMPONENT_DEFINE ("ThirdScriptExample");		//定义记录组件

int 
main (int argc, char *argv[])
{
  bool verbose = true;                  //记录组件boot or not
  uint32_t nCsma = 3;			//csma节点数量
  uint32_t nCsma1 = 3;				//wifi节点数量
   bool tracing = false;


  CommandLine cmd;
  cmd.AddValue ("nCsma", "Number of \"extra\" CSMA nodes/devices", nCsma);
  cmd.AddValue ("nCsma1", "Number of wifi STA devices", nCsma1);
  cmd.AddValue ("verbose", "Tell echo applications to log if true", verbose);
  cmd.AddValue ("tracing", "Enable pcap tracing", tracing);

  cmd.Parse (argc,argv);

  // Check for valid number of csma or wifi nodes
  // 250 should be enough, otherwise IP addresses 
  // soon become an issue		//判断是否超过了250个，超过报错 , 原因？
  if (nCsma1 > 250 || nCsma > 250)
    {
      std::cout << "Too many csma nodes, no more than 250 each." << std::endl;
      return 1;
    }

  if (verbose)
    {
      LogComponentEnable ("UdpEchoClientApplication", LOG_LEVEL_INFO);
      LogComponentEnable ("UdpEchoServerApplication", LOG_LEVEL_INFO);	//启动记录组件
    }


  //创建2个节点，p2p链路两端
  NodeContainer p2pNodes;               //NodeContainer
  p2pNodes.Create (2);

  //创建信道，设置信道参数，在设备安装到节点上
  PointToPointHelper pointToPoint;
  pointToPoint.SetDeviceAttribute ("DataRate", StringValue ("5Mbps"));
  pointToPoint.SetChannelAttribute ("Delay", StringValue ("2ms"));

  NetDeviceContainer p2pDevices;          //NetDeviceContainer
  p2pDevices = pointToPoint.Install (p2pNodes);

  //创建csma节点，包含一个p2p节点
 
  NodeContainer csmaNodes;                        
  csmaNodes.Add (p2pNodes.Get (1));
  csmaNodes.Create (nCsma);
 
  NodeContainer csmaNodes1; 
  csmaNodes1.Add(p2pNodes.Get(0)); 
  csmaNodes1.Create (nCsma1);

  //创建信道，设置信道参数，在设备安装到节点上
  CsmaHelper csma;
  csma.SetChannelAttribute ("DataRate", StringValue ("100Mbps"));
  csma.SetChannelAttribute ("Delay", TimeValue (NanoSeconds (6560)));

  NetDeviceContainer csmaDevices;
  csmaDevices = csma.Install (csmaNodes);

  NetDeviceContainer csmaDevices1;
  csmaDevices1=csma.Install(csmaNodes1);

  //已经创建了节点，设备，信道和移动模型，接下来配置协议栈
  InternetStackHelper stack;
  stack.Install (csmaNodes);
  stack.Install(csmaNodes1);

  //分配IP地址
  Ipv4AddressHelper address;
 //P2P信道
  address.SetBase ("10.1.1.0", "255.255.255.0");
  Ipv4InterfaceContainer p2pInterfaces;
  p2pInterfaces = address.Assign (p2pDevices);
 //csma信道
  address.SetBase ("10.1.2.0", "255.255.255.0");
  Ipv4InterfaceContainer csmaInterfaces;
  csmaInterfaces = address.Assign (csmaDevices);
//csma1 channel
  address.SetBase("10.1.3.0","255.255.255.0");
  Ipv4InterfaceContainer csmaInterfaces1;
  csmaInterfaces1=address.Assign(csmaDevices1);

  //放置echo服务端程序在最右边的csma节点,端口为9
  UdpEchoServerHelper echoServer (9);

  ApplicationContainer serverApps = echoServer.Install (csmaNodes.Get (nCsma));
  serverApps.Start (Seconds (1.0));
  serverApps.Stop (Seconds (10.0));

  //回显客户端放在最后的STA节点，指向CSMA网络的服务器，上面的节点地址，端口为9
  UdpEchoClientHelper echoClient (csmaInterfaces.GetAddress (nCsma), 9);
  echoClient.SetAttribute ("MaxPackets", UintegerValue (1));
  echoClient.SetAttribute ("Interval", TimeValue (Seconds (1.0)));
  echoClient.SetAttribute ("PacketSize", UintegerValue (1024));

  //安装其他节点应用程序
    ApplicationContainer clientApps = 
    echoClient.Install (csmaNodes1.Get (nCsma1));
ApplicationContainer clientApps1 = 
    echoClient.Install (csmaNodes1.Get (nCsma1-1));
ApplicationContainer clientApps2 = 
    echoClient.Install (csmaNodes1.Get (nCsma1-2));
ApplicationContainer clientApps3 = 
    echoClient.Install (csmaNodes1.Get (nCsma1-3));
  clientApps.Start (Seconds (2.0));
  clientApps.Stop (Seconds (10.0));
  clientApps1.Start (Seconds (2.0));
  clientApps1.Stop (Seconds (10.0));
  clientApps2.Start (Seconds (2.0));
  clientApps2.Stop (Seconds (10.0));
  clientApps3.Start (Seconds (2.0));
  clientApps3.Stop (Seconds (10.0));

  //启动互联网络路由
  Ipv4GlobalRoutingHelper::PopulateRoutingTables ();

  Simulator::Stop (Seconds (10.0));

  if (tracing == true)
    {
      pointToPoint.EnablePcapAll ("ns3-lec-pro2_third");
      //phy.EnablePcap ("third", apDevices.Get (0));
      csma.EnablePcap ("ns3-lec-pro2_third", csmaDevices.Get (0), true);
      csma.EnablePcap("ns3-lec-pro2_third",csmaDevices1.Get(0),true);
    }

  Simulator::Run ();
  Simulator::Destroy ();
  return 0;
}
