

import java.util.ArrayList;
import java.util.Random;

public class ServerThread implements Runnable {

    NetworkUtility networkUtility;
    EndDevice endDevice;

    ServerThread(NetworkUtility networkUtility, EndDevice endDevice) {
        this.networkUtility = networkUtility;
        this.endDevice = endDevice;
        System.out.println("Server Ready for client " + NetworkLayerServer.clientCount);
        NetworkLayerServer.clientCount++;  // why again?
        new Thread(this).start();
    }

    @Override
    public void run() {
        /**
         * Synchronize actions with client.
         */
        
        /*
        Tasks:
        1. Upon receiving a packet and recipient, call deliverPacket(packet)
        2. If the packet contains "SHOW_ROUTE" request, then fetch the required information
                and send back to client
        3. Either send acknowledgement with number of hops or send failure message back to client
        */
        networkUtility.write(endDevice);
//        System.out.println("endDevice IP sending to source " + endDevice.getIpAddress());
//        System.out.println("endDevice routerIP sending to source " + endDevice.getGateway());

        Random random = new Random(System.currentTimeMillis());
        for (int i = 0; i < 100; i++) {
            try {
                Packet packet = null;
                Object receivedObject = networkUtility.read();
                if (receivedObject instanceof Packet) {
                    packet = (Packet) receivedObject;
                } else {
                    System.out.println("Packet receiving error.");
                }
                assert (packet != null);

                String specialMessage = packet.getSpecialMessage();
                if (specialMessage != null) {
                    assert (specialMessage.equals("SHOW_ROUTE"));
                    Packet answer = getRoute(packet, random);
                    networkUtility.write(answer);
                } else {
                    //System.out.println("delivering");       // here
                    deliverPacket(packet, random);
                }
            }
            catch (Exception exception) {
                exception.printStackTrace();
                //break;
            }
        }
    }

    private Packet getRoute(Packet packet, Random random) {
        IPAddress sourceInterface = endDevice.getGateway();
        Integer sourceRouterID = NetworkLayerServer.interfacetoRouterID.get(sourceInterface);

        int r = Math.abs(random.nextInt(NetworkLayerServer.endDevices.size()));
        EndDevice destinationEndDevice = NetworkLayerServer.endDevices.get(r);
        IPAddress destinationInterface = destinationEndDevice.getGateway();
        Integer destinationRouterID = NetworkLayerServer.interfacetoRouterID.get(destinationInterface);
//        Random random = new Random(System.currentTimeMillis());
//        int r = Math.abs(random.nextInt(NetworkLayerServer.routers.size()));
//        Integer destinationRouterID = NetworkLayerServer.routers.get(r).getRouterId();

        Integer currentRouterID = sourceRouterID;
        String answer = sourceRouterID.toString();

        while (!currentRouterID.equals(destinationRouterID)) {
            Router currentRouter = NetworkLayerServer.routerMap.get(currentRouterID);
            ArrayList<RoutingTableEntry> routingTable = currentRouter.getRoutingTable();
            boolean failed = false;
            for (RoutingTableEntry entry : routingTable) {
                if (entry.getRouterId().equals(destinationRouterID)) {
                    Integer nextRouterID = entry.getGatewayRouterId();
                    if (nextRouterID == null) {
                        failed = true;
                        break;
                    }
                    Router nextRouter = NetworkLayerServer.routerMap.get(nextRouterID);
                    if (nextRouter.getState()) {
                        answer = answer + " -> " + nextRouterID.toString();
                        currentRouterID = nextRouterID;
                        packet.hopcount += 1;
                        if ((packet.hopcount * 1.0) >= Constants.INFINITY) {
                            failed = true;
                        }
                    }
                    else {
                        failed = true;
                    }
                    break;
                }
            }
            if (failed) {
                answer = "Failed to reach the destination.";
                packet.hopcount = -1;
                break;
            }
        }
        packet.setMessage(answer);
        return packet;
    }


    public Boolean deliverPacket(Packet p, Random random) {

        
        /*
        1. Find the router s which has an interface
                such that the interface and source end device have same network address.
        2. Find the router d which has an interface
                such that the interface and destination end device have same network address.
        3. Implement forwarding, i.e., s forwards to its gateway router x considering d as the destination.
                similarly, x forwards to the next gateway router y considering d as the destination,
                and eventually the packet reaches to destination router d.

            3(a) If, while forwarding, any gateway x, found from routingTable of router r is in down state[x.state==FALSE]
                    (i) Drop packet
                    (ii) Update the entry with distance Constants.INFTY
                    (iii) Block NetworkLayerServer.stateChanger.t
                    (iv) Apply DVR starting from router r.
                    (v) Resume NetworkLayerServer.stateChanger.t

            3(b) If, while forwarding, a router x receives the packet from router y,
                    but routingTableEntry shows Constants.INFTY distance from x to y,
                    (i) Update the entry with distance 1
                    (ii) Block NetworkLayerServer.stateChanger.t
                    (iii) Apply DVR starting from router x.
                    (iv) Resume NetworkLayerServer.stateChanger.t

        4. If 3(a) occurs at any stage, packet will be dropped,
            otherwise successfully sent to the destination router
        */

//        EndDevice sourceEndDevice = NetworkLayerServer.endDeviceMap.get(p.getSourceIP());
//        System.out.println(p.getSourceIP());
//        System.out.println("++++++++++++++++++++++++++ "   + sourceEndDevice);
        IPAddress sourceInterface = endDevice.getGateway();
        Integer sourceRouterID = NetworkLayerServer.interfacetoRouterID.get(sourceInterface);

        int r = Math.abs(random.nextInt(NetworkLayerServer.endDevices.size()));
        EndDevice destinationEndDevice = NetworkLayerServer.endDevices.get(r);
        IPAddress destinationInterface = destinationEndDevice.getGateway();
        Integer destinationRouterID = NetworkLayerServer.interfacetoRouterID.get(destinationInterface);
//        Random random = new Random(System.currentTimeMillis());
//        int r = Math.abs(random.nextInt(NetworkLayerServer.routers.size()));
//        Integer destinationRouterID = NetworkLayerServer.routers.get(r).getRouterId();

        //System.out.println("Source : " + sourceRouterID + " Destination : " + destinationRouterID);

        Packet packet = forward(sourceRouterID, destinationRouterID, p);
        networkUtility.write(packet);

        return true;
    }

    public Packet forward(Integer currentRouterID, Integer destinationRouterID, Packet packet) {
        while (!currentRouterID.equals(destinationRouterID)) {

            //System.out.println("Packet at " + currentRouterID + " Destination : " + destinationRouterID);

            Router currentRouter = NetworkLayerServer.routerMap.get(currentRouterID);
            ArrayList<RoutingTableEntry> routingTable = currentRouter.getRoutingTable();
            for (RoutingTableEntry entry : routingTable) {
                if (entry.getRouterId().equals(destinationRouterID)) {
                    Integer nextRouterID = entry.getGatewayRouterId();
                    if (nextRouterID == null) {
                        packet.hopcount = -1;
                        break;
                    }
                    Router nextRouter = NetworkLayerServer.routerMap.get(nextRouterID);
                    if (nextRouter.getState()) {
                        packet.hopcount += 1;
                        boolean ifDVR = false;
                        for (RoutingTableEntry x_entry : routingTable) {
                            if (x_entry.getRouterId().equals(nextRouterID)) {
                                if (x_entry.getDistance() >= (Constants.INFINITY * 1.0)) ifDVR = true;
                                break;
                            }
                        }
                        if (ifDVR) {
                            entry.setDistance(1);
                            NetworkLayerServer.stateChanger.islocked = true;
                            //NetworkLayerServer.simpleDVR(nextRouterID);
                            NetworkLayerServer.DVR(nextRouterID);
                            NetworkLayerServer.stateChanger.islocked = false;
                        }
                        currentRouterID = nextRouterID;
                        if ((packet.hopcount * 1.0) >= Constants.INFINITY) {
                            packet.hopcount = -1;
                        }
                    }
                    else {
                        packet.hopcount = -1;
                        for (RoutingTableEntry x_entry : routingTable) {
                            if (x_entry.getRouterId().equals(nextRouterID)) {
                                x_entry.setDistance(Constants.INFINITY * 1.0);
                                break;
                            }
                        }
                        NetworkLayerServer.stateChanger.islocked = true;
                        //NetworkLayerServer.simpleDVR(currentRouterID);
                        NetworkLayerServer.DVR(currentRouterID);
                        NetworkLayerServer.stateChanger.islocked = false;
                    }
                    break;
                }
            }
            if (packet.hopcount == -1) break;
        }
        return packet;
    }

    @Override
    public boolean equals(Object obj) {
        return super.equals(obj); //To change body of generated methods, choose Tools | Templates.
    }
}
