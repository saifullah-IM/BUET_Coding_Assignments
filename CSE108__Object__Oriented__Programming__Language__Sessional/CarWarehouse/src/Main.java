/**
 * Created by Saifullah on 12/
 *9/2017.
 */


import java.util.ArrayList;
import java.util.Scanner;
import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileReader;
import java.io.FileWriter;

public class Main {

    private static final String INPUT_FILE_NAME = "in.txt";
    private static final String OUTPUT_FILE_NAME = "out.txt";

    public static void main(String[] args) {
        ArrayList<Car> list = new ArrayList<Car>();

        try {
            String line;
            BufferedReader br = new BufferedReader(new FileReader(INPUT_FILE_NAME));
            while (true) {
                line = br.readLine();
                if (line == null) break;
                String[] out;
                out=line.split(",");
                Car car = new Car();
                car.setReg(out[0]);
                car.setYear(Integer.parseInt(out[1]));
                String[] clr=new String[3];
                for (int i=0;i<3;i++) clr[i]=out[i+2];
                car.setColor(clr);
                car.setMake(out[5]);
                car.setModel(out[6]);
                car.setPrice(Integer.parseInt(out[7]));
                list.add(car);
                //car.print();
            }
            br.close();
        } catch (Exception e) {
            e.printStackTrace();
        }

        Scanner scr = new Scanner(System.in);
        while (true) {
            int cmd;
            System.out.println("(1) Search Cars");
            System.out.println("(2) Add Car");
            System.out.println("(3) Delete Car");
            System.out.println("(4) Exit System");

            cmd=scr.nextInt();
            if (cmd<1 || cmd>4) {
                System.out.println("Error, please enter a valid command(1-4)");
                continue;
            }
            else if (cmd==4) break;
            else if (cmd==1) while (true) {
                int cmd2;
                System.out.println("Car Searching Options:");
                System.out.println("(1) By Registration Number");
                System.out.println("(2) By Car Make and Car Model");
                System.out.println("(3) Back to Main Menu");

                cmd2 = scr.nextInt();
                if (cmd2 < 1 || cmd2 > 3) {
                    System.out.println("Error, please enter a valid command(1-3)");
                    continue;
                }
                else if (cmd2==3) break;
                else if (cmd2==1) {
                    String in,str;
                    boolean chk=false;
                    System.out.println("Enter a registration number");
                    in=scr.next();

                    for (Car it: list) {
                        str=it.getReg();
                        if (str.equalsIgnoreCase(in)) {
                            it.print();
                            chk=true;
                            break;
                        }
                    }

                    if (!chk) System.out.println("No such car with this Registration Number”");
                }
                else if (cmd2==2) {
                    String in1,in2,str1,str2;
                    boolean chk=false;
                    System.out.println("Enter a Car Make");
                    in1=scr.next();
                    System.out.println("Enter a Car Model");
                    in2=scr.next();

                    if (in2.equalsIgnoreCase("ANY")) for (Car it : list) {
                        str1 = it.getMake();
                        if (str1.equalsIgnoreCase(in1)) {
                            it.print();
                            chk = true;
                        }
                    }
                    else for (Car it : list) {
                        str1 = it.getMake();
                        str2 = it.getModel();
                        if (str1.equalsIgnoreCase(in1) && str2.equalsIgnoreCase(in2)) {
                            it.print();
                            chk = true;
                        }
                    }

                    if (!chk) System.out.println("No such car with this Car Make and Car Model””");
                }
            }
            else if (cmd==2) {
                String str;
                boolean chk=true;
                String[] out;

                System.out.println("Enter car information");
                str=scr.nextLine();
                str=scr.nextLine();
                out=str.split(",");
                for (Car it: list) if (it.getReg().equalsIgnoreCase(out[0])) {
                    System.out.println("A car with this registration number already exists.");
                    chk=false;
                    break;
                }

                if (chk) {
                    Car car = new Car();
                    car.setReg(out[0]);
                    car.setYear(Integer.parseInt(out[1]));
                    String[] clr=new String[5];
                    for (int i=0;i<3;i++) clr[i]=out[i+2];
                    car.setColor(clr);
                    car.setMake(out[5]);
                    car.setModel(out[6]);
                    car.setPrice(Integer.parseInt(out[7]));
                    list.add(car);
                }
            }
            else if (cmd==3) {
                String reg;
                boolean chk=true;

                System.out.println("Enter a registration number");
                reg=scr.next();
                for (Car it: list) if (it.getReg().equalsIgnoreCase(reg)) {
                    list.remove(it);
                    chk=false;
                    break;
                }

                if (chk) System.out.println("No such car with this Registration Number”");
            }
        }

        try {
            BufferedWriter bw = new BufferedWriter(new FileWriter(OUTPUT_FILE_NAME));
            for (Car it: list) {
                bw.write(it.getReg()+","+Integer.toString(it.getYear())+",");
                String[] clr=new String[3];
                clr=it.getColor();
                for (int i=0;i<3;i++) bw.write(clr[i]+",");
                bw.write(it.getMake()+","+it.getModel()+","+Integer.toString(it.getPrice()));
                bw.newLine();
            }
            bw.close();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
