//Done!
public class RoutingTableEntry {

    private Integer routerId;
    private double distance;
    private Integer gatewayRouterId;

    public RoutingTableEntry(Integer routerId, double distance, Integer gatewayRouterId) {
        this.routerId = routerId;
        this.distance = distance;
        this.gatewayRouterId = gatewayRouterId;
    }

    public Integer getRouterId() {
        return routerId;
    }

    public void setRouterId(Integer routerId) {
        this.routerId = routerId;
    }

    public double getDistance() {
        return distance;
    }

    public void setDistance(double distance) {
        this.distance = distance;
    }

    public Integer getGatewayRouterId() {
        return gatewayRouterId;
    }

    public void setGatewayRouterId(Integer gatewayRouterId) {
        this.gatewayRouterId = gatewayRouterId;
    }

}
