import java.util.ArrayList;

//Work needed
public class Client {
    public static void main(String[] args) throws InterruptedException {

        NetworkUtility networkUtility = new NetworkUtility("127.0.0.1", 4444);
        System.out.println("Connected to server");
        /**
         * Tasks
         */
        
        /*
        1. Receive EndDevice configuration from server
        2. Receive active client list from server
        3. for(int i=0;i<100;i++)
        4. {
        5.      Generate a random message
        6.      Assign a random receiver from active client list
        7.      if(i==20)
        8.      {
        9.            Send the message and recipient IP address to server and a special request "SHOW_ROUTE"
        10.           Display routing path, hop count and routing table of each router [You need to receive
                            all the required info from the server in response to "SHOW_ROUTE" request]
        11.     }
        12.     else
        13.     {
        14.           Simply send the message and recipient IP address to server.
        15.     }
        16.     If server can successfully send the message, client will get an acknowledgement along with hop count
                    Otherwise, client will get a failure message [dropped packet]
        17. }
        18. Report average number of hops and drop rate
        */
        EndDevice endDevice = null;
        Object receivedObject = networkUtility.read();
        if (receivedObject instanceof EndDevice) {
            endDevice = (EndDevice) receivedObject;
            System.out.println("Received endDevice configuration.");
        }
        else {
            System.out.println("End Device configuration not received.");
        }
        assert (endDevice != null);

        int dropCount = 0;
        int totalHopCount = 0;
        for (int i = 0; i < 100; i++) {
            String message = "This is a random message numbered " + (i + 1);
            Packet packet = new Packet(message,null, endDevice.getIpAddress(), null);
//            System.out.println("endDevice IP sending from source " + endDevice.getIpAddress());
//            System.out.println("endDevice routerIP sending from source " + endDevice.getGateway());
            System.out.println("Sending message " + i);
            if (i == 20) {
                packet.setSpecialMessage("SHOW_ROUTE");
                networkUtility.write(packet);
                receivedObject = networkUtility.read();
                Packet answer = null;
                if (receivedObject instanceof Packet) {
                    answer = (Packet) receivedObject;
                }
                assert (receivedObject instanceof Packet);
                System.out.println("Route is " + answer.getMessage());
                if (answer.hopcount == -1) dropCount += 1;
                else totalHopCount += answer.hopcount;
            }
            else {
                networkUtility.write(packet);
                receivedObject = networkUtility.read();
                Packet answer = null;
                if (receivedObject instanceof Packet) {
                    answer = (Packet) receivedObject;
                }
                assert (receivedObject instanceof Packet);
                if (answer.hopcount == -1) dropCount += 1;
                else totalHopCount += answer.hopcount;
            }
            System.out.println("Received reply " + i);
        }

        double dropRate = (dropCount * 1.0) / 100.0;
        double averageHopCount = (totalHopCount * 1.0) / (100 - dropCount);
        System.out.println("Average hop count is " + averageHopCount);
        System.out.println("Drop rate is " + dropRate);
    }
}
