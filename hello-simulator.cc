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

#include <iostream>

using namespace ns3;

NS_LOG_COMPONENT_DEFINE ("HelloSimulator");

static void printHello(std::string word,std::string word1) {
	std::cout<<Simulator::Now()<<" Hello "<<word<<" "<<word1<<std::endl;
	Simulator::Schedule(Seconds(1),&printHello,word,word1); 
        //insert an event 1s later to call printHello function
}

int main (int argc, char *argv[])
{
	CommandLine cmd;
	std::string name;
        std::string id;
	cmd.AddValue ("name", "my name", name);
        cmd.AddValue ("id", "my id", id);
	cmd.Parse(argc,argv);

	printHello(name,id);
	std::cout<<"hello commit"<<std::endl;

	Simulator::Stop(Seconds(5));
	Simulator::Run ();
	Simulator::Destroy ();
}
