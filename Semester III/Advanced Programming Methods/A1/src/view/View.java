package view;
import controller.Controller;
import exception.MyException;
import model.*;
import java.rmi.UnexpectedException;
import java.util.List;
import java.util.Scanner;
public class View
{
    private Controller controller;
    public View(Controller controller)
    {
        this.controller=controller;
    }
    public void printMenu()
    {
        System.out.println();
        System.out.println("1.Add vehicle");
        System.out.println("2.Remove vehicle");
        System.out.println("3.Get all vehicles");
        System.out.println("4.Filter vehicles");
        System.out.println("0.Quit");
        System.out.println();
    }
    public void printSubmenu()
    {
        System.out.println();
        System.out.println("1.Car");
        System.out.println("2.Bicycle");
        System.out.println("3.Motorcycle");
        System.out.println();
    }

    public void run() throws MyException
    {
        Car c1 = new Car("VW","red");
        Bike c2 = new Bike("BMX","black");
        Motorcycle c3 = new Motorcycle("Yamaha","blue");
        Car c4 = new Car("Audi","white");
        Motorcycle c5 = new Motorcycle("Kawasaki","red");
        controller.addToRepo(c1);
        controller.addToRepo(c2);
        controller.addToRepo(c3);
        controller.addToRepo(c4);
        controller.addToRepo(c5);


        int r=0;
        Scanner sc = new Scanner(System.in);
        do
        {
            this.printMenu();
            System.out.print(">");
            r = sc.nextInt();
            switch (r)
            {
                default:
                    System.out.println("Error");
                    break;
                case 0:
                    break;
                case 1:
                    this.printSubmenu();
                    System.out.print(">");
                    int addChoice =  sc.nextInt();
                    if(addChoice==1)
                    {
                        System.out.println();
                        System.out.println("Name:");
                        System.out.print(">");
                        String name = sc.next();
                        System.out.println("Color:");
                        System.out.print(">");
                        String color = sc.next();
                        Car car = new Car(name,color);
                        try
                        {
                            controller.addToRepo(car);
                        }
                        catch (Exception e)
                        {
                            System.out.println(e.getMessage());
                        }
                        System.out.println();
                        System.out.println("Operation ended successfully!");
                        System.out.println();
                    }
                    else if(addChoice==2)
                    {
                        System.out.println();
                        System.out.println("Name:");
                        System.out.print(">");
                        String name = sc.next();
                        System.out.println("Color:");
                        System.out.print(">");
                        String color = sc.next();
                        Bike bicycle = new Bike(name,color);
                        try
                        {
                            controller.addToRepo(bicycle);
                        }
                        catch (Exception e)
                        {
                            System.out.println(e.getMessage());
                        }
                        System.out.println();
                        System.out.println("Operation ended successfully!");
                        System.out.println();
                    }
                    else if(addChoice==3)
                    {
                        System.out.println();
                        System.out.println("Name:");
                        System.out.print(">");
                        String name = sc.next();
                        System.out.println("Color:");
                        System.out.print(">");
                        String color = sc.next();
                        Motorcycle motorcycle = new Motorcycle(name,color);
                        try
                        {
                            controller.addToRepo(motorcycle);
                        }
                        catch (Exception e)
                        {
                            System.out.println(e.getMessage());
                        }
                        System.out.println();
                        System.out.println("Operation ended successfully!");
                        System.out.println();
                    }
                    else
                    {
                        System.out.println("Invalid choice!");
                    }
                    break;
                case 2:
                    System.out.println();
                    System.out.println("Name:");
                    System.out.print(">");
                    String name = sc.next();

                    boolean found = false;
                    Vehicles[] allv = controller.getAll();
                    for (int i=0;i<allv.length;i++)
                    {
                        if(allv[i]!=null && allv[i].getName().equals(name))
                        {
                            controller.removeFromRepo(allv[i]);
                            System.out.println();
                            System.out.println("Removed!");
                            System.out.println();
                            found = true;
                            break;
                        }
                    }
                    if(found==false)
                        System.out.println("The vehicle does not exist!");
                    break;

                case 3:
                    Vehicles[] all = controller.getAll();
                    for(Vehicles item : all)
                    {
                        if(item!=null)
                            System.out.print("Name: "+item.getName()+" " + "Color: "+item.getColor()+"\n");
                        else
                            continue;
                    }
                    System.out.println();
                    break;
                case 4:
                    System.out.println();
                    System.out.println("Color:");
                    System.out.print(">");
                    String color = sc.next();
                    List<Vehicles> result = controller.filterRepo(color);
                    for(Vehicles item : result)
                        if(item!=null)
                            System.out.print("Name: "+item.getName()+" " + "Color: "+item.getColor()+"\n");
                        else
                            continue;
                    System.out.println();
                    break;

            }

        }while(r!=0);
        sc.close();
    }
}
