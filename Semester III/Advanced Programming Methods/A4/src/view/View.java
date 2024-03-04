package view;
import model.MyException;
import controller.Controller;
public class View
{
    private Controller controller;
    public View(Controller controller)
    {
        this.controller = controller;
    }
    public void setController(Controller controller)
    {
        this.controller = controller;
    }
    public Controller getController()
    {
        return controller;
    }
    public void run() throws MyException
    {
        controller.allStep();

    }
}
