import javafx.application.Application;//all imports
import javafx.application.Platform;
import javafx.geometry.Pos;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.TextArea;
import javafx.scene.control.TextField;
import javafx.scene.layout.BorderPane;
import javafx.scene.layout.VBox;
import javafx.stage.Stage;
import javafx.scene.control.Label;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.Socket;
public class JavaFXTemplate extends Application {//javaFX file for client
    private Socket socket;//declares javaFX variables and buffer to read in information
    private BufferedReader in;
    private PrintWriter out;
    private TextArea clientTextArea;
    private TextField messageTextField;
    private Stage primaryStage;

    public static void main(String[] args) {//main that calls launch
        launch(args);
    }

    @Override
    public void start(Stage primaryStage){//start method that handles our GUI
      this.primaryStage = primaryStage;//sets primary stage to our variable
        primaryStage.setTitle("Client Program");//sets our client GUI title
        clientTextArea = new TextArea();//creates new text area
        clientTextArea.setEditable(false);
        clientTextArea.setPrefHeight(200);
        logMessage("Press Connect To Server Button to connect AFTER the server is started.");//displays message in GUI
        messageTextField = new TextField();//creates new textField
        Button sendButton = new Button("Send");//Creates new button to send messages
        sendButton.setOnAction(event -> sendMessage(messageTextField.getText()));//when button is clicked it sends message to server
        Button connectButton = new Button("Connect To Server");//button to connect to server
        connectButton.setOnAction(event -> connectToServer());//when clicked it connects to server
        Button instructionsButton = new Button("Instructions"); //Instructions button sends you to instructions page
        instructionsButton.setOnAction(e -> displayInstructionsScreen());//when button is pressed instructions is called
        Button exit = new Button("Exit");//creates exit button
        exit.setOnAction(e -> {//exits out program when clicked
          Platform.exit();
        });
        VBox vbox = new VBox(clientTextArea, messageTextField, sendButton, connectButton, instructionsButton, exit);//creates new vbox
        Scene scene = new Scene(vbox, 400, 400);//creates new scene
        primaryStage.setScene(scene);//sets scene
        primaryStage.show();//shows stage
    }

    private void connectToServer(){//function that connects to server
        if (socket == null || socket.isClosed()) {//checks to make sure server has been started
            try {
                socket = new Socket("127.0.0.1", 12345);//creates new socket
                in = new BufferedReader(new InputStreamReader(socket.getInputStream()));//opens the streams and collects all data
                out = new PrintWriter(socket.getOutputStream(), true);//opens out stream and gets data
                new Thread(this::receiveMessages).start();
                logMessage("Connected to the server");
                logMessage("Pick a category from the following List.");
                logMessage("Food, Animals, or Superheroes. (Case Sensitive)");
                logMessage("When the game begins, USE LOWER CASE LETTERS to guess the word.");
            } catch (IOException e) {
                e.printStackTrace();
                logMessage("Connection failed");
            }
        } else {//gives message when attempting to connect again
            logMessage("Already connected to the server");
        }
    }

    private void sendMessage(String message) {//function that sends the message 
        if (socket != null && !socket.isClosed()){//makes sure socket isn't closed
            out.println(message);
            logMessage("[Client] Sent: " + message);//shows what user sent to the server
            messageTextField.clear();//clears text field
        } else {
            logMessage("Not connected to the server");//returns message when not connected to client
        }
    }

    private void receiveMessages(){//function so that server receives messages
        try {
            String serverResponse;//creates string
            while ((serverResponse = in.readLine()) != null){//reads line
                logMessage(serverResponse);//sends message to client
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private void logMessage(String message) {//function to send message into client text area
        Platform.runLater(() -> clientTextArea.appendText(message + "\n"));//prints message of client an
    }

    private void displayInstructionsScreen(){//function that displays instructions screen
        BorderPane instructionsScreen = new BorderPane();
        instructionsScreen.setStyle("-fx-background-color: cyan;");//creates a BorderPane and changes background
        VBox centerBox = new VBox(20);
        centerBox.setAlignment(Pos.CENTER);
        TextArea instructionsTextArea = new TextArea(//adds text we want for instructions
            "1) Hello and welcome...I want to play a game." + "The rules are simple...\n" + "2) You must first start server then connect to the server in the client program\n"
            + "3) Next, you will pick a category...the category names are case sensitive so spell exactly how displayed \n"
            + "4) Once connected you will be given the amount of letters the word is and you must guess the word LETTER BY LETTER ALL LOWERCASE\n"
            + "5) You have 6 attempts to guess the word...right letter choices dont count as attempts\n"
                + "6) Once you guess the word right you can pick another category...if you dont get your word within 6 attempts you can choose any of the 3 categories again\n"
                + "7) IN ORDER TO WIN YOU MUST WIN ONCE IN EVERY CATEGORY\n"
                + "8) If you lose 3 times total across any of the 3 categories you LOSE!\n"
                + "9) Live or Die make you choice.\n");
        instructionsTextArea.setEditable(false);//creates a text area to display instructions and modify its attributes
        instructionsTextArea.setStyle("-fx-font-size: 14; -fx-text-fill: red; -fx-font-family: 'Comic Sans MS';");
        instructionsTextArea.setMaxWidth(400); 
        instructionsTextArea.setMaxHeight(350);
        instructionsTextArea.setWrapText(true);
        Label instructionsText = new Label("  Instructions");//uses a label to make a title since text field highlights text
        instructionsText.setStyle("-fx-font-size: 60;");//modifies size and font
        instructionsText.setMaxWidth(400); 
        Button backButton = new Button("Back to Game");
        backButton.setStyle("-fx-font-size: 24;"); 
        backButton.setOnAction(e -> start(primaryStage));//when user clicks on button it takes back to menu screen
        centerBox.getChildren().addAll(instructionsText, instructionsTextArea, backButton);
        instructionsScreen.setCenter(centerBox);//sets box to center
        Scene instructionsScene = new Scene(instructionsScreen, 400, 400);
        primaryStage.setScene(instructionsScene);//sets scene
    }
}
