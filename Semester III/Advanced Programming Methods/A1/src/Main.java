import controller.Controller;
import exception.MyException;
import model.*;
import repository.*;
import view.*;
public class Main
{
    public static void main(String[] args) throws MyException
    {
        View ui = new View(new Controller(new Repository()));
        ui.run();
    }
}
