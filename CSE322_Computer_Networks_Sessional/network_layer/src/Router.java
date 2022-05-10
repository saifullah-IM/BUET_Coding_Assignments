//Work needed
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map;
import java.util.Random;

public class Router {
    private Integer routerId;
    private int numberOfInterfaces;
    private ArrayList<IPAddress> interfaceAddresses;//list of IP address of all interfaces of the router
    private ArrayList<RoutingTableEntry> routingTable;//used to implement DVR
    private ArrayList<Integer> neighborRouterIDs;//Contains both "UP" and "DOWN" state routers
    private Boolean state;//true represents "UP" state and false is for "DOWN" state
    private Map<Integer, IPAddress> gatewayIDtoIP;

    public Router() {
        interfaceAddresses = new ArrayList<>();
        routingTable = new ArrayList<>();
        neighborRouterIDs = new ArrayList<>();

        /**
         * 80% Probability that the router is up
         */
        Random random = new Random();
        double p = random.nextDouble();
        if (p < 0.80) state = true;
        else state = false;

        numberOfInterfaces = 0;
    }

    public Router(Integer routerId, ArrayList<Integer> neighborRouters, ArrayList<IPAddress> interfaceAddresses, Map<Integer, IPAddress> gatewayIDtoIP) {
        this.routerId = routerId;
        this.interfaceAddresses = interfaceAddresses;
        this.neighborRouterIDs = neighborRouters;
        this.gatewayIDtoIP = gatewayIDtoIP;
        routingTable = new ArrayList<>();


        /**
         * 80% Probability that the router is up
         */
        Random random = new Random();
        double p = random.nextDouble();
        if (p < 0.80) state = true;
        else state = false;

        numberOfInterfaces = interfaceAddresses.size();
    }

    @Override
    public String toString() {
        String string = "";
        string += "Router ID: " + routerId + "\n" + "Interfaces: \n";
        for (int i = 0; i < numberOfInterfaces; i++) {
            string += interfaceAddresses.get(i).getString() + "\t";
        }
        string += "\n" + "Neighbors: \n";
        for (int i = 0; i < neighborRouterIDs.size(); i++) {
            string += neighborRouterIDs.get(i) + "\t";
        }
        return string;
    }


    /**
     * Initialize the distance(hop count) for each router.
     * for itself, distance=0; for any connected router with state=true, distance=1; otherwise distance=Constants.INFTY;
     */
    public void initiateRoutingTable() {
        for (Router router : NetworkLayerServer.routers) {
            Integer ID = router.getRouterId();
            double distance = Constants.INFINITY;
            Integer next_hop = null;
            if (ID.equals(routerId)) {
                distance = 0;
                next_hop = ID;
            } else {
                for (Integer neighbour : neighborRouterIDs) {
                    if (neighbour.equals(ID)) {
                        if (NetworkLayerServer.routerMap.get(neighbour).getState()) {
                            distance = 1.0;
                            next_hop = ID;
                        }
                        break;
                    }
                }
            }
            RoutingTableEntry newRoutingTable = new RoutingTableEntry(ID, distance, next_hop);
            routingTable.add(newRoutingTable);
        }
    }

    /**
     * Delete all the routingTableEntry
     */
    public void clearRoutingTable() {
        routingTable.clear();
    }

    /**
     * Update the routing table for this router using the entries of Router neighbor
     *
     * @param neighbour
     */
    public boolean updateRoutingTable(Router neighbour) {
        boolean result = false;
        ArrayList<RoutingTableEntry> neighbourRoutingTable = neighbour.getRoutingTable();
        for (RoutingTableEntry neighbourEntry : neighbourRoutingTable) {
            Integer neighbourID = neighbour.getRouterId();
            Integer destination = neighbourEntry.getRouterId();
            RoutingTableEntry currentEntry = null;
            double neighbourDistance = Constants.INFINITY;

            for (RoutingTableEntry entry : routingTable) {
                if (entry.getRouterId().equals(neighbourID)) neighbourDistance = entry.getDistance();
                if (entry.getRouterId().equals(destination)) {
                    currentEntry = entry;
                    //System.out.println("here " + entry);
                }
            }

//            System.out.println("dest " +destination);
//            System.out.println("size " + routingTable.size());

            assert (currentEntry != null);
//            System.out.println(neighbourDistance);
//            System.out.println(currentEntry);
//            System.out.println(routingTable.size());
            double newDistance = Math.min(neighbourDistance + neighbourEntry.getDistance(), Constants.INFINITY * 1.0);
            double currentDistance = currentEntry.getDistance();

            if (newDistance < currentDistance) {
                currentEntry.setDistance(newDistance);
                currentEntry.setGatewayRouterId(neighbourID);
                result = true;
            }
        }

        return result;
    }

    public boolean sfupdateRoutingTable(Router neighbour) {
        boolean result = false;
        ArrayList<RoutingTableEntry> neighbourRoutingTable = neighbour.getRoutingTable();
        for (RoutingTableEntry neighbourEntry : neighbourRoutingTable) {
            if (routerId.equals(neighbourEntry.getGatewayRouterId())) continue;

            Integer neighbourID = neighbour.getRouterId();
            Integer destination = neighbourEntry.getRouterId();
            RoutingTableEntry currentEntry = null;
            double neighbourDistance = Constants.INFINITY;

            for (RoutingTableEntry entry : routingTable) {
                if (entry.getRouterId().equals(neighbourID)) neighbourDistance = entry.getDistance();
                if (entry.getRouterId().equals(destination)) currentEntry = entry;
            }

            assert (currentEntry != null);
            double newDistance = Math.min(neighbourDistance + neighbourEntry.getDistance(), Constants.INFINITY * 1.0);
            double currentDistance = currentEntry.getDistance();

            //System.out.println("size " + routingTable.size());

//            System.out.println(currentEntry);
//            System.out.println(currentEntry.getGatewayRouterId());

            if (newDistance < currentDistance) {
                currentEntry.setDistance(newDistance);
                currentEntry.setGatewayRouterId(neighbourID);
                result = true;
            }
            else if (currentEntry.getGatewayRouterId() != null && currentEntry.getGatewayRouterId().equals(neighbourID)) {
                if (Math.abs(currentDistance - newDistance) > 0.1) result = true;
                currentEntry.setDistance(newDistance);
            }
        }

        return result;
    }

    /**
     * If the state was up, down it; if state was down, up it
     */
    public void revertState() {
        state = !state;
        if (state) {
            initiateRoutingTable();
        } else {
            clearRoutingTable();
        }
    }

    public Integer getRouterId() {
        return routerId;
    }

    public void setRouterId(Integer routerId) {
        this.routerId = routerId;
    }

    public int getNumberOfInterfaces() {
        return numberOfInterfaces;
    }

    public void setNumberOfInterfaces(int numberOfInterfaces) {
        this.numberOfInterfaces = numberOfInterfaces;
    }

    public ArrayList<IPAddress> getInterfaceAddresses() {
        return interfaceAddresses;
    }

    public void setInterfaceAddresses(ArrayList<IPAddress> interfaceAddresses) {
        this.interfaceAddresses = interfaceAddresses;
        numberOfInterfaces = interfaceAddresses.size();
    }

    public ArrayList<RoutingTableEntry> getRoutingTable() {
        return routingTable;
    }

    public void addRoutingTableEntry(RoutingTableEntry entry) {
        this.routingTable.add(entry);
    }

    public ArrayList<Integer> getNeighborRouterIDs() {
        return neighborRouterIDs;
    }

    public void setNeighborRouterIDs(ArrayList<Integer> neighborRouterIDs) {
        this.neighborRouterIDs = neighborRouterIDs;
    }

    public Boolean getState() {
        return state;
    }

    public void setState(Boolean state) {
        this.state = state;
    }

    public Map<Integer, IPAddress> getGatewayIDtoIP() {
        return gatewayIDtoIP;
    }

    public void printRoutingTable() {
        System.out.println("Router " + routerId);
        System.out.println("DestID Distance Nexthop");
        for (RoutingTableEntry routingTableEntry : routingTable) {
            System.out.println(routingTableEntry.getRouterId() + " " + routingTableEntry.getDistance() + " " + routingTableEntry.getGatewayRouterId());
        }
        System.out.println("-----------------------");
    }

    public String strRoutingTable() {
        String string = "Router" + routerId + "\n";
        string += "DestID Distance Nexthop\n";
        for (RoutingTableEntry routingTableEntry : routingTable) {
            string += routingTableEntry.getRouterId() + " " + routingTableEntry.getDistance() + " " + routingTableEntry.getGatewayRouterId() + "\n";
        }

        string += "-----------------------\n";
        return string;
    }
}


