/**
 * Created by Pavilion on 12/9/2017.
 */
public class Car {
    private String reg;
    private int year;
    private String[] color = new String[3];
    private String make;
    private String model;
    private int price;

    String getReg () {
        return reg;
    }
    int getYear () {
        return year;
    }
    String[] getColor () {
        return color;
    }
    String getMake () {
        return make;
    }
    String getModel () {
        return model;
    }
    int getPrice () {
        return price;
    }

    void setReg (String val) {
        reg=val;
    }
    void setYear (int val) {
        year=val;
    }
    void setColor (String[] val) {
        for (int i=0;i<3;i++) color[i]=val[i];
    }
    void setMake (String val) {
        make=val;
    }
    void setModel (String val) {
        model=val;
    }
    void setPrice (int val) {
        price=val;
    }

    void print () {
        System.out.println("Registration number = " + reg);
        System.out.println("Year made =" + year);
        System.out.print("Colour = ");
        for (int i=0;i<3;i++) System.out.print(color[i]+" ");
        System.out.println();
        System.out.println("Car make = "+make);
        System.out.println("Car model = "+model);
        System.out.println("Price = "+price);
    }
}
