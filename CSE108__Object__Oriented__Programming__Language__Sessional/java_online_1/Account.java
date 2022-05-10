package Main;
public class Account {

    private int number;
    private String customer;
    private double balance;
    // you are not allowed to add any more class variables here

    // you are not allowed to write any other constructor
    public Account(int number, String customer, double balance) {
        this.number = number;
        this.customer = customer;
        this.balance = balance;
    }
    
    String getCustomer () {
        return customer;
    }
    
       public double addBalance (double val) {
        return this.balance+=val;
    }
        
    double getBalance () {
        return balance;
    }
    
    void printAccount() {
        System.out.println("Account Number: " + number + ", Customer Name: " + customer + ", Balance: " +balance);
    }
    // add your code here
}
