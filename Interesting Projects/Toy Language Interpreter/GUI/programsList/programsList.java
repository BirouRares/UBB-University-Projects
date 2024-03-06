package GUI.programsList;

import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.*;

import GUI.programController.*;
import controller.Controller;
import model.ADT.*;
import model.MyException;
import model.PrgState;
import model.exp.*;
import model.stmt.*;
import model.type.*;
import model.value.BoolValue;
import model.value.IntValue;
import model.value.StringValue;
import model.value.Value;
import repository.IRepository;
import repository.Repository;

import java.io.BufferedReader;
import java.util.ArrayList;
import java.util.List;
public class programsList {
    private programController programExecutorController;

    public void setProgramExecutorController(programController programExecutorController) {
        this.programExecutorController = programExecutorController;
    }
    @FXML
    private ListView<IStmt> programsListView;

    @FXML
    private Button displayButton;

    @FXML
    public void initialize() {
        programsListView.setItems(getAllStatements());
        programsListView.getSelectionModel().setSelectionMode(SelectionMode.SINGLE);
    }

    @FXML
    private void displayProgram(ActionEvent actionEvent) {
        IStmt selectedStatement = programsListView.getSelectionModel().getSelectedItem();
        if (selectedStatement == null) {
            Alert alert = new Alert(Alert.AlertType.ERROR);
            alert.setTitle("Error encountered!");
            alert.setContentText("No statement selected!");
            alert.showAndWait();
        } else {
            int id = programsListView.getSelectionModel().getSelectedIndex();
            try {
                selectedStatement.typeCheck(new MyDictionary<String, Type>());
                PrgState prg1 = new PrgState(new MyStack<IStmt>(), new MyDictionary<String, Value>(), new MyList<Value>(),
                        new FileTable<String, BufferedReader>(), new Heap(), new LatchTable(), selectedStatement);
                ArrayList<PrgState> l1 = new ArrayList<PrgState>();
                l1.add(prg1);
                IRepository repo1 = new Repository(l1, "log" + (id + 1) + ".txt");
                Controller controller = new Controller(repo1);
                programExecutorController.setController(controller);
            } catch (MyException exception) {
                Alert alert = new Alert(Alert.AlertType.ERROR);
                alert.setTitle("Error encountered!");
                alert.setContentText(exception.getMessage());
                alert.showAndWait();
            }
        }
    }

    @FXML
    private ObservableList<IStmt> getAllStatements() {
        List<IStmt> allStatements = new ArrayList<>();

        /*  Ref int v1; Ref int v2; Ref int v3; int cnt;
            new(v1,2);new(v2,3);new(v3,4);newLatch(cnt,rH(v2));
            fork(wh(v1,rh(v1)*10);print(rh(v1));countDown(cnt);
            fork(wh(v2,rh(v2)*10);print(rh(v2));countDown(cnt);
            fork(wh(v3,rh(v3)*10);print(rh(v3));countDown(cnt))));
            await(cnt);
            print(100);
            countDown(cnt);
            print(100)
            The final Out should be {20,id-first-child,30,id-second-child,40, id-third-child, 100,id_parent,100}
            where id-first-child, id-second-child and id-third-child are the unique identifiers of those three new threads created by fork,
             while id_parent is the identifier of the main thread.*/

        IStmt ex1 = new CompStmt(new VarDeclStmt("v1", new RefType(new IntType())),
                    new CompStmt(new VarDeclStmt("v2", new RefType(new IntType())),
                    new CompStmt(new VarDeclStmt("v3", new RefType(new IntType())),
                    new CompStmt(new VarDeclStmt("cnt", new IntType()),
                    new CompStmt(new NewStmt("v1", new ValueExp(new IntValue(2))),
                    new CompStmt(new NewStmt("v2", new ValueExp(new IntValue(3))),
                    new CompStmt(new NewStmt("v3", new ValueExp(new IntValue(4))),
                    new CompStmt(new NewLatch("cnt", new ReadHeapExp(new VarExp("v2"))),
                    new CompStmt(new ForkStmt(new CompStmt(new WriteHeapStmt("v1", new ArithExp("*", new ReadHeapExp(new VarExp("v1")), new ValueExp(new IntValue(10)))),
                                              new CompStmt(new PrintStmt(new ReadHeapExp(new VarExp("v1"))),
                                              new CompStmt(new CountDown("cnt"),
                                                      new ForkStmt(new CompStmt(new WriteHeapStmt("v2", new ArithExp("*", new ReadHeapExp(new VarExp("v2")), new ValueExp(new IntValue(10)))),
                                                                   new CompStmt(new PrintStmt(new ReadHeapExp(new VarExp("v2"))),
                                                                   new CompStmt(new CountDown("cnt"),
                                                                           new ForkStmt(new CompStmt(new WriteHeapStmt("v3", new ArithExp("*", new ReadHeapExp(new VarExp("v3")), new ValueExp(new IntValue(10)))),
                                                                                        new CompStmt(new PrintStmt(new ReadHeapExp(new VarExp("v3"))),
                                                                                                new CountDown("cnt")))))))))))),
                    new CompStmt(new Await("cnt"),
                    new CompStmt(new PrintStmt(new ValueExp(new IntValue(100))),
                    new CompStmt(new CountDown("cnt"),
                        new PrintStmt(new ValueExp(new IntValue(100)))))))))))))));

        allStatements.add(ex1);




        /*Ref int a; Ref int b; int v;
            new(a,0); new(b,0);
            wh(a,1); wh(b,2);
            v=(rh(a)<rh(b))?100:200;
            print(v);
            v= ((rh(b)-2)>rh(a))?100:200;
            print(v);
            The final Out should be {100,200}*/
        IStmt ex2 = new CompStmt(new VarDeclStmt("a", new RefType(new IntType())),
                new CompStmt(new VarDeclStmt("b", new RefType(new IntType())),
                        new CompStmt(new VarDeclStmt("v", new IntType()),
                                new CompStmt(new NewStmt("a", new ValueExp(new IntValue(0))),
                                        new CompStmt(new NewStmt("b", new ValueExp(new IntValue(0))),
                                                new CompStmt(new WriteHeapStmt("a", new ValueExp(new IntValue(1))),
                                                        new CompStmt(new WriteHeapStmt("b", new ValueExp(new IntValue(2))),
                                                                new CompStmt(new ConditionalAssignment("v", new RelationalExp("<", new ReadHeapExp(new VarExp("a")), new ReadHeapExp(new VarExp("b"))), new ValueExp(new IntValue(100)), new ValueExp(new IntValue(200))),
                                                                        new CompStmt(new PrintStmt(new VarExp("v")),
                                                                                new CompStmt(new ConditionalAssignment("v", new RelationalExp(">", new ArithExp("-", new ReadHeapExp(new VarExp("b")), new ValueExp(new IntValue(2))), new ReadHeapExp(new VarExp("a"))), new ValueExp(new IntValue(100)), new ValueExp(new IntValue(200))),
                                                                                        new PrintStmt(new VarExp("v"))))))))))));

        allStatements.add(ex2);



        /*IStmt ex1 = new CompStmt(new VarDeclStmt("v", new IntType()),
                new CompStmt(new AssignStmt("v", new ValueExp(new IntValue(2))), new PrintStmt(new VarExp("v"))));
        allStatements.add(ex1);

        IStmt ex2 = new CompStmt(new VarDeclStmt("a", new IntType()),
                new CompStmt(new VarDeclStmt("b", new IntType()),
                        new CompStmt(new AssignStmt("a", new ArithExp("+", new ValueExp(new IntValue(2)),
                                new ArithExp("*", new ValueExp(new IntValue(3)), new ValueExp(new IntValue(5))))),
                                new CompStmt(new AssignStmt("b", new ArithExp("+", new VarExp("a"),
                                        new ValueExp(new IntValue(1)))), new PrintStmt(new VarExp("b"))))));
        allStatements.add(ex2);

        IStmt ex3 = new CompStmt(new VarDeclStmt("a", new BoolType()),
                new CompStmt(new VarDeclStmt("v", new IntType()),
                        new CompStmt(new AssignStmt("a", new ValueExp(new BoolValue(true))),
                                new CompStmt(new IfStmt(new VarExp("a"), new AssignStmt("v", new ValueExp(new IntValue(2))),
                                        new AssignStmt("v", new ValueExp(new IntValue(3)))), new PrintStmt(new VarExp("v"))))));
        allStatements.add(ex3);

        IStmt ex4 = new CompStmt(new VarDeclStmt("varf", new StringType()),
                new CompStmt(new AssignStmt("varf", new ValueExp(new StringValue("test.in"))),
                new CompStmt(new OpenRFile(new VarExp("varf")),
                new CompStmt(new VarDeclStmt("varc", new IntType()),
                                        new CompStmt(new ReadFile(new VarExp("varf"), "varc"),
                                                new CompStmt(new PrintStmt(new VarExp("varc")),
                                                        new CompStmt(new ReadFile(new VarExp("varf"), "varc"),
                                                                new CompStmt(new PrintStmt(new VarExp("varc")), new CloseRFile(new VarExp("varf"))))))))));
        allStatements.add(ex4);

        IStmt ex5 = new CompStmt(new VarDeclStmt("v", new IntType()),
                new CompStmt(new AssignStmt("v", new ValueExp(new IntValue(4))),
                        new CompStmt(new WhileStmt(new RelationalExp(">", new VarExp("v"), new ValueExp(new IntValue(0))),
                                new CompStmt(new PrintStmt(new VarExp("v")), new AssignStmt("v", new ArithExp("-", new VarExp("v"), new ValueExp(new IntValue(1)))))),
                                new PrintStmt(new VarExp("v")))));
        allStatements.add(ex5);

        IStmt ex6 = new CompStmt(new VarDeclStmt("v", new RefType(new IntType())),
                new CompStmt(new NewStmt("v", new ValueExp(new IntValue(20))),
                        new CompStmt(new VarDeclStmt("a", new RefType(new RefType(new IntType()))),
                                new CompStmt(new NewStmt("a", new VarExp("v")),
                                        new CompStmt(new NewStmt("v", new ValueExp(new IntValue(30))),
                                                new PrintStmt(new ReadHeapExp(new ReadHeapExp(new VarExp("a")))))))));
        allStatements.add(ex6);

        IStmt ex7 = new CompStmt(new VarDeclStmt("v", new IntType()),
                new CompStmt(new VarDeclStmt("a", new RefType(new IntType())),
                        new CompStmt(new AssignStmt("v", new ValueExp(new IntValue(10))),
                                new CompStmt(new NewStmt("a", new ValueExp(new IntValue(22))),
                                        new CompStmt(new ForkStmt(new CompStmt(new WriteHeapStmt("a", new ValueExp(new IntValue(30))),
                                                new CompStmt(new AssignStmt("v", new ValueExp(new IntValue(32))),
                                                        new CompStmt(new PrintStmt(new VarExp("v")), new PrintStmt(new ReadHeapExp(new VarExp("a")))
                                                        )))),
                                                new CompStmt(new PrintStmt(new VarExp("v")), new PrintStmt(new ReadHeapExp(new VarExp("a")))))))));
        allStatements.add(ex7);

        IStmt ex8 = new CompStmt(new VarDeclStmt("v", new BoolType()),
                new CompStmt(new AssignStmt("v", new ValueExp(new IntValue(2))), new PrintStmt(new VarExp("v"))));

        allStatements.add(ex8);*/
        return FXCollections.observableArrayList(allStatements);
    }
}
