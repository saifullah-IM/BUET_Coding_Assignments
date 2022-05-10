package Main;
public class Branch {

    private int id;
    private String name;
    private Account []  accounts;
    private int accountCount;
    // add your code here
    // there can be at most 20 branches 
    
    static int ID;
    static String Name;
    static Account[] AC;

     // you are not allowed to write any other constructor
    public Branch(int id, String name) {
        this.id = id;
        this.name = name;
        this.accounts = new Account[10];
        accountCount=0;
        ID=id;
        Name=name;
        AC=accounts;
        // add your code here
    }

    public void addAccount(Account a) {
        accounts[accountCount++] = a;
    }
    
    double getBranchBalance () {
        double ans=0;
        for (Account acc : accounts) {
            ans+=acc.getBalance();
        }
        return ans;
    }
    
    Account getMinBalanceAccount () {
        Account ans=accounts[0];
        for (Account acc : accounts) {
            if (acc.getBalance()<ans.getBalance()) ans=acc;
        }
        return ans;
    }
    
    static void transferBalance (Account from, Account to, double amount) {
        double chk,res;
        chk=from.getBalance();
        if (chk>amount) res=amount;
        else res=chk;
        from.addBalance(-res);
        to.addBalance(res);
    }
    
    static void printAllBranchesInfo () {
        System.out.println("Branch Id: " + ID + ", Branch Name: " + Name);
        for (Account acc : AC) {
            acc.printAccount();
        }
    }

    // add your code here

}
