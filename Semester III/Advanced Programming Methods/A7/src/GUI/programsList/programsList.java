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
                selectedStatement.typecheck(new MyDictionary<String, Type>());
                PrgState prg1 = new PrgState(new MyStack<IStmt>(), new MyDictionary<String, Value>(), new MyList<Value>(),
                        new MyFileTable<String, BufferedReader>(), selectedStatement, new MyHeap());
                ArrayList<PrgState> l1 = new ArrayList<PrgState>();
                l1.add(prg1);
                IRepository repo1 = new Repository(l1, "log1.txt");
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

        IStmt ex1 = new CompStmt(new VarDeclStmt("v", new IntType()),
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
                        new CompStmt(new OpenReadFileStatement(new VarExp("varf")),
                                new CompStmt(new VarDeclStmt("varc", new IntType()),
                                        new CompStmt(new ReadFileStatement(new VarExp("varf"), "varc"),
                                                new CompStmt(new PrintStmt(new VarExp("varc")),
                                                        new CompStmt(new ReadFileStatement(new VarExp("varf"), "varc"),
                                                                new CompStmt(new PrintStmt(new VarExp("varc")), new CloseReadFileStatement(new VarExp("varf"))))))))));
        allStatements.add(ex4);

        IStmt ex5 = new CompStmt(new VarDeclStmt("v", new IntType()),
                new CompStmt(new AssignStmt("v", new ValueExp(new IntValue(4))),
                        new CompStmt(new WhileStatement(new RelationalExpressions(">", new VarExp("v"), new ValueExp(new IntValue(0))),
                                new CompStmt(new PrintStmt(new VarExp("v")), new AssignStmt("v", new ArithExp("-", new VarExp("v"), new ValueExp(new IntValue(1)))))),
                                new PrintStmt(new VarExp("v")))));
        allStatements.add(ex5);

        IStmt ex6 = new CompStmt(new VarDeclStmt("v", new RefType(new IntType())),
                new CompStmt(new NewStatement("v", new ValueExp(new IntValue(20))),
                        new CompStmt(new VarDeclStmt("a", new RefType(new RefType(new IntType()))),
                                new CompStmt(new NewStatement("a", new VarExp("v")),
                                        new CompStmt(new NewStatement("v", new ValueExp(new IntValue(30))),
                                                new PrintStmt(new ReadHeap(new ReadHeap(new VarExp("a")))))))));
        allStatements.add(ex6);

        IStmt ex7 = new CompStmt(new VarDeclStmt("v", new IntType()),
                new CompStmt(new VarDeclStmt("a", new RefType(new IntType())),
                        new CompStmt(new AssignStmt("v", new ValueExp(new IntValue(10))),
                                new CompStmt(new NewStatement("a", new ValueExp(new IntValue(22))),
                                        new CompStmt(new ForkStatement(new CompStmt(new WriteHeapStatement("a", new ValueExp(new IntValue(30))),
                                                new CompStmt(new AssignStmt("v", new ValueExp(new IntValue(32))),
                                                        new CompStmt(new PrintStmt(new VarExp("v")), new PrintStmt(new ReadHeap(new VarExp("a")))
                                                        )))),
                                                new CompStmt(new PrintStmt(new VarExp("v")), new PrintStmt(new ReadHeap(new VarExp("a")))))))));
        allStatements.add(ex7);

        IStmt ex8 = new CompStmt(new VarDeclStmt("v", new BoolType()),
                new CompStmt(new AssignStmt("v", new ValueExp(new IntValue(2))), new PrintStmt(new VarExp("v"))));

        allStatements.add(ex8);


        return FXCollections.observableArrayList(allStatements);
    }
}