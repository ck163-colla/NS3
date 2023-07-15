#include <ns3/core-module.h>
#include <ns3/network-module.h>
#include <ns3/csma-module.h>
#include <ns3/internet-module.h>
#include <ns3/ofswitch13-module.h>
#include <ns3/internet-apps-module.h>
#include <ns3/tap-bridge-module.h>
#include <ns3/netanim-module.h>

using namespace ns3;

int main(int argc, char *argv[])
{
  uint16_t simTime = 50; // 仿真模拟时间
  bool verbose = false;
  bool trace = false;
  uint16_t numHosts = 9;
  uint16_t numSwitches = 9;
  uint16_t numPings = 20;
  uint16_t pingTime = 10;

  // Configure command line parameters
  CommandLine cmd;
  cmd.AddValue ("simTime", "Simulation time (seconds)", simTime);
  cmd.AddValue ("verbose", "Enable verbose output", verbose);
  cmd.AddValue ("trace", "Enable datapath stats and pcap traces", trace);
  cmd.AddValue ("numHosts", "Number of hosts in the simulation", numHosts);
  cmd.AddValue ("numSwitches", "Number of switches in the simulation", numSwitches);
  cmd.AddValue ("numPings", "Number of ping apps int the simulation", numPings);
  cmd.AddValue ("pingTime", "Ping time (seconds)", pingTime);
  cmd.Parse (argc, argv);

  // if (verbose)
  //   {
  //     OFSwitch13Helper::EnableDatapathLogs ();
  //     LogComponentEnable ("OFSwitch13Interface", LOG_LEVEL_ALL);
  //     LogComponentEnable ("OFSwitch13Device", LOG_LEVEL_ALL);
  //     LogComponentEnable ("OFSwitch13Port", LOG_LEVEL_ALL);
  //     LogComponentEnable ("OFSwitch13Queue", LOG_LEVEL_ALL);
  //     LogComponentEnable ("OFSwitch13SocketHandler", LOG_LEVEL_ALL);
  //     LogComponentEnable ("OFSwitch13Controller", LOG_LEVEL_ALL);
  //     LogComponentEnable ("OFSwitch13LearningController", LOG_LEVEL_ALL);
  //     LogComponentEnable ("OFSwitch13Helper", LOG_LEVEL_ALL);
  //     LogComponentEnable ("OFSwitch13InternalHelper", LOG_LEVEL_ALL);
  //   }

  // Enable checksum computations (required by OFSwitch13 module)
  GlobalValue::Bind ("ChecksumEnabled", BooleanValue (true));

  // Set simulator to real time mode
  GlobalValue::Bind ("SimulatorImplementationType", StringValue ("ns3::RealtimeSimulatorImpl"));

  // Create switch nodes
  NodeContainer switches;
  switches.Create (numSwitches);

    // Create host nodes
  NodeContainer hosts;
  hosts.Create (numHosts);

  // Use the CsmaHelper to connect host and switch
  CsmaHelper csmaHelper;
  csmaHelper.SetChannelAttribute ("DataRate", DataRateValue (DataRate ("8Mbps")));
  csmaHelper.SetChannelAttribute ("Delay", TimeValue (MilliSeconds (2)));

  PointToPointHelper pointToPoint;
  pointToPoint.SetDeviceAttribute ("DataRate", StringValue ("5Mbps"));
  pointToPoint.SetChannelAttribute ("Delay", StringValue ("2ms"));

  NodeContainer pair;
  NetDeviceContainer pairDevs;
  NetDeviceContainer hostDevices;
  NetDeviceContainer switchPorts [numSwitches];

  for (int i = 0; i < numSwitches; i++)
  {
    switchPorts[i] = NetDeviceContainer();
  }

  // Connect hosts to switches
  for(size_t i = 0; i < numHosts; i++)
  {
    pair = NodeContainer(hosts.Get(i), switches.Get(i));
    pairDevs = csmaHelper.Install(pair);
    hostDevices.Add(pairDevs.Get(0));
    switchPorts[i].Add(pairDevs.Get(1));
  }

  //Connect the switches
  pair = NodeContainer(switches.Get(0), switches.Get(1));
  pairDevs = csmaHelper.Install(pair);
  switchPorts [0].Add (pairDevs.Get (0));
  switchPorts [1].Add (pairDevs.Get (1));

  pair = NodeContainer(switches.Get(0), switches.Get(5));
  pairDevs = csmaHelper.Install(pair);
  switchPorts [0].Add (pairDevs.Get (0));
  switchPorts [5].Add (pairDevs.Get (1));

  pair = NodeContainer(switches.Get(0), switches.Get(6));
  pairDevs = csmaHelper.Install(pair);
  switchPorts [0].Add (pairDevs.Get (0));
  switchPorts [6].Add (pairDevs.Get (1));

  pair = NodeContainer(switches.Get(0), switches.Get(8));
  pairDevs = csmaHelper.Install(pair);
  switchPorts [0].Add (pairDevs.Get (0));
  switchPorts [8].Add (pairDevs.Get (1));

  pair = NodeContainer(switches.Get(1), switches.Get(2));
  pairDevs = csmaHelper.Install(pair);
  switchPorts [1].Add (pairDevs.Get (0));
  switchPorts [2].Add (pairDevs.Get (1));

  pair = NodeContainer(switches.Get(1), switches.Get(8));
  pairDevs = csmaHelper.Install(pair);
  switchPorts [1].Add (pairDevs.Get (0));
  switchPorts [8].Add (pairDevs.Get (1));

  pair = NodeContainer(switches.Get(2), switches.Get(3));
  pairDevs = csmaHelper.Install(pair);
  switchPorts [2].Add (pairDevs.Get (0));
  switchPorts [3].Add (pairDevs.Get (1));

  pair = NodeContainer(switches.Get(2), switches.Get(7));
  pairDevs = csmaHelper.Install(pair);
  switchPorts [2].Add (pairDevs.Get (0));
  switchPorts [7].Add (pairDevs.Get (1));

  pair = NodeContainer(switches.Get(2), switches.Get(8));
  pairDevs = csmaHelper.Install(pair);
  switchPorts [2].Add (pairDevs.Get (0));
  switchPorts [8].Add (pairDevs.Get (1));

  pair = NodeContainer(switches.Get(3), switches.Get(4));
  pairDevs = csmaHelper.Install(pair);
  switchPorts [3].Add (pairDevs.Get (0));
  switchPorts [4].Add (pairDevs.Get (1));

  pair = NodeContainer(switches.Get(3), switches.Get(7));
  pairDevs = csmaHelper.Install(pair);
  switchPorts [3].Add (pairDevs.Get (0));
  switchPorts [7].Add (pairDevs.Get (1));

  pair = NodeContainer(switches.Get(4), switches.Get(5));
  pairDevs = csmaHelper.Install(pair);
  switchPorts [4].Add (pairDevs.Get (0));
  switchPorts [5].Add (pairDevs.Get (1));

  pair = NodeContainer(switches.Get(4), switches.Get(7));
  pairDevs = csmaHelper.Install(pair);
  switchPorts [4].Add (pairDevs.Get (0));
  switchPorts [7].Add (pairDevs.Get (1));

  pair = NodeContainer(switches.Get(5), switches.Get(6));
  pairDevs = csmaHelper.Install(pair);
  switchPorts [5].Add (pairDevs.Get (0));
  switchPorts [6].Add (pairDevs.Get (1));

  pair = NodeContainer(switches.Get(6), switches.Get(7));
  pairDevs = csmaHelper.Install(pair);
  switchPorts [6].Add (pairDevs.Get (0));
  switchPorts [7].Add (pairDevs.Get (1));

  pair = NodeContainer(switches.Get(6), switches.Get(8));
  pairDevs = csmaHelper.Install(pair);
  switchPorts [6].Add (pairDevs.Get (0));
  switchPorts [8].Add (pairDevs.Get (1));
  
  // Create the controller node
  Ptr<Node> controllerNode = CreateObject<Node> ();

  // Configure the OpenFlow network domain using an external controller
  Ptr<OFSwitch13ExternalHelper> of13Helper = CreateObject<OFSwitch13ExternalHelper> ();
  Ptr<NetDevice> ctrlDev = of13Helper->InstallExternalController (controllerNode);
  for (int i = 0; i < numSwitches; i++)
    {
      of13Helper->InstallSwitch (switches.Get (i), switchPorts [i]);
    }
  
  of13Helper->CreateOpenFlowChannels ();

  // TapBridge the controller device to local machine
  // The default configuration expects a controller on local port 6653
  TapBridgeHelper tapBridge;
  tapBridge.SetAttribute ("Mode", StringValue ("ConfigureLocal"));
  tapBridge.SetAttribute ("DeviceName", StringValue ("ctrl"));
  tapBridge.Install (controllerNode, ctrlDev);

  // Install the TCP/IP stack into hosts nodes
  InternetStackHelper internet;
  internet.Install (hosts);

  // Set IPv4 host addresses
  Ipv4AddressHelper ipv4helpr;
  Ipv4InterfaceContainer hostIpIfaces;
  ipv4helpr.SetBase ("10.1.1.0", "255.255.255.0");
  hostIpIfaces = ipv4helpr.Assign (hostDevices);

  // // Random number generators for ping applications
  // Ptr<UniformRandomVariable> randomHostRng = CreateObject<UniformRandomVariable> ();
  // randomHostRng->SetAttribute ("Min", DoubleValue (0));
  // randomHostRng->SetAttribute ("Max", DoubleValue (numHosts - 1));

  // Ptr<ExponentialRandomVariable> randomStartRng = CreateObject<ExponentialRandomVariable> ();
  // randomStartRng->SetAttribute ("Mean", DoubleValue (20));

  // // Configure ping application between random hosts
  // Time startTime = Seconds (1);
  // for (int i = 0; i < numPings; i++)
  //   {
  //     int srcHost = randomHostRng->GetInteger ();
  //     int dstHost = randomHostRng->GetInteger ();

  //     V4PingHelper pingHelper = V4PingHelper (hostIpIfaces.GetAddress (dstHost));
  //     pingHelper.SetAttribute ("Verbose", BooleanValue (true));
  //     Ptr<Application> pingApp = pingHelper.Install (hosts.Get (srcHost)).Get (0);

  //     startTime += Seconds (std::abs (randomStartRng->GetValue ()));
  //     pingApp->SetStartTime (startTime);
  //     pingApp->SetStopTime (startTime + Seconds (pingTime));
  //   }

  // Enable datapath stats and pcap traces at hosts, switch(es), and controller(s)
  if (trace)
    {
      of13Helper->EnableOpenFlowPcap ("openflow");
      of13Helper->EnableDatapathStats ("switch-stats");
      csmaHelper.EnablePcap ("host", hostDevices);
      for (int i = 0; i < numSwitches; i++)
        {
          csmaHelper.EnablePcap ("switch", switchPorts [i], true);
        }
    }

  // AnimationInterface("ifcn_topo.xml");
  // AnimationInterface anim("ifcn_topo.xml");
  // anim.SetConstantPosition(switches.Get(0), 70.0, 25.0);
  // anim.SetConstantPosition(switches.Get(1), 30.0, 25.0);
  // anim.SetConstantPosition(switches.Get(2), 10.0, 50.0);
  // anim.SetConstantPosition(switches.Get(3), 30.0, 70.0);
  // anim.SetConstantPosition(switches.Get(4), 70.0, 70.0);
  // anim.SetConstantPosition(switches.Get(5), 90.0, 50.0);
  // anim.SetConstantPosition(switches.Get(6), 70.0, 50.0);
  // anim.SetConstantPosition(switches.Get(7), 40.0, 60.0);
  // anim.SetConstantPosition(switches.Get(8), 40.0, 40.0);

  // anim.SetConstantPosition(hosts.Get(0), 70.0, 25.0);
  // anim.SetConstantPosition(hosts.Get(0), 70.0, 25.0);
  // anim.SetConstantPosition(hosts.Get(0), 70.0, 25.0);
  // anim.SetConstantPosition(hosts.Get(0), 70.0, 25.0);
  // anim.SetConstantPosition(hosts.Get(0), 70.0, 25.0);
  // anim.SetConstantPosition(hosts.Get(0), 70.0, 25.0);
  // anim.SetConstantPosition(hosts.Get(0), 70.0, 25.0);
  // anim.SetConstantPosition(hosts.Get(0), 70.0, 25.0);
  // anim.SetConstantPosition(hosts.Get(0), 70.0, 25.0);

  // Run the simulation
  Simulator::Stop (Seconds (simTime));
  Simulator::Run ();
  Simulator::Destroy ();
}
