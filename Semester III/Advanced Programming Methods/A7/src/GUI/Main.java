package GUI;

import GUI.programController.programController;
import GUI.programsList.*;


import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.stage.Stage;

import java.util.Objects;

public class Main extends Application{
    @Override
    public void start(Stage primaryStage) throws Exception {
        FXMLLoader programListLoader = new FXMLLoader();
        programListLoader.setLocation(Main.class.getResource("/GUI/programsList/programsList.fxml"));
        Parent programListRoot = programListLoader.load();
        Scene programListScene = new Scene(programListRoot, 500, 550);
        programListScene.getStylesheets().add(Objects.requireNonNull(Main.class.getResource("button_style.css")).toExternalForm());
        programsList programChooserController = programListLoader.getController();
        primaryStage.setTitle("Programs List - Choose a program to execute ");
        primaryStage.setScene(programListScene);
        primaryStage.show();

        FXMLLoader programExecutorLoader = new FXMLLoader();
        programExecutorLoader.setLocation(Main.class.getResource("programController/programController.fxml"));
        Parent programExecutorRoot = programExecutorLoader.load();
        Scene programExecutorScene = new Scene(programExecutorRoot, 700, 500);
        programExecutorScene.getStylesheets().add(Objects.requireNonNull(Main.class.getResource("button_style.css")).toExternalForm());
        programController programExecutorController = programExecutorLoader.getController();
        programChooserController.setProgramExecutorController(programExecutorController);
        Stage secondaryStage = new Stage();
        secondaryStage.setTitle("Interpreter");
        secondaryStage.setScene(programExecutorScene);
        secondaryStage.show();
    }

    public static void main(String[] args) {
        launch(args);
    }

}