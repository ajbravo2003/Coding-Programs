import javafx.application.Application;
import javafx.application.Platform;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.TextArea;
import javafx.scene.layout.VBox;
import javafx.stage.Stage;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.ServerSocket;
import java.net.Socket;
public class JavaFXTemplate extends Application{//class that handles the serverFX
    private ServerSocket serverSocket;//creates server socket
    private TextArea logTextArea;//creates text area
    public static void main(String[] args) {
        launch(args);
    }

    @Override
    public void start(Stage primaryStage){//start function that handles GUI
        primaryStage.setTitle("Server Program");//sets title to server program
        logMessage("Start the Server to begin.");//displays instructions for the server
        logMessage("Game Instructions on Client GUI.");
        logTextArea = new TextArea();//creates new text area
        logTextArea.setEditable(false);
        logTextArea.setPrefHeight(250);
        Button startButton = new Button("Start Server");//button to start server
        startButton.setOnAction(event -> startServer());//when clicked the server is started
        Button stopButton = new Button("Stop Server");//button to stop the server
        stopButton.setOnAction(event -> stopServer());//when clicked the server is disconnected
        VBox vbox = new VBox(logTextArea, startButton, stopButton);//creates VBox to store all buttons and text area
        Scene scene = new Scene(vbox, 400, 400);//creates scene
        primaryStage.setScene(scene);
        primaryStage.setOnCloseRequest(event -> stopServer());//stops server when closed
        primaryStage.show();//shows scene
    }

    private void startServer(){//function that starts the server
        if (serverSocket == null || serverSocket.isClosed()){//makes sure server is closed
            new Thread(() -> {//makes new thread
                try {
                    serverSocket = new ServerSocket(12345);//creates socket
                    logMessage("Server listening for clients");

                    while (true) {
                        Socket clientSocket = serverSocket.accept();//listens for clients
                        logMessage("Accepted connection from " + clientSocket.getInetAddress().getHostAddress());//prints output message when client connects
                        ClientHandler clientHandler = new ClientHandler(clientSocket);//creates client handler
                        new Thread(clientHandler).start();//starts thread
                    }
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }).start();//starts thread
        } else {//if server has been started then its not started again
            logMessage("Server is already running");
        }
    }

    private void stopServer(){//function to stop the server
        if (serverSocket != null && !serverSocket.isClosed()){//makes sure is active
            try {
                serverSocket.close();//closes socket
                logMessage("Server stopped");//prints server was stopped
            } catch (IOException e) {
                e.printStackTrace();
            }
        } else {
            logMessage("Server is not running");//outputs message when user tries to stop server when its not running
        }
    }

    private void logMessage(String message) {//function to display messages
        Platform.runLater(() -> logTextArea.appendText(message + "\n"));//prints message to server GUI
    }

    class ClientHandler implements Runnable{//function that handles clients
        private Socket clientSocket;//creates socket
        private BufferedReader in;//creates buffer to read in data
        private Server server;//creates server

        public ClientHandler(Socket clientSocket){//constructor
            this.clientSocket = clientSocket;//sets socket
            this.server = new Server();//sets server
            try {
                this.in = new BufferedReader(new InputStreamReader(clientSocket.getInputStream()));//creates new buffer reader
            } catch (IOException e) {
                e.printStackTrace();
            }
        }

        @Override
        public void run(){//run function that handles client messages
            try {
              int i = 1;
              int wonCategorys = 0;
              int gameFinished = 0;
                String clientMessage;
                while ((clientMessage = in.readLine()) != null){//reads line of client message
                    logMessage("[Client] " + clientSocket.getInetAddress().getHostAddress() + ": " + clientMessage);//Display the received message from the client on the server log
                    PrintWriter out = new PrintWriter(clientSocket.getOutputStream(), true);//creats printWriter
                    if (clientMessage.equals("Play")){//checks if user enters play
                      server.replayGame();//replays game
                      i = 1;
                      gameFinished = 0;
                      out.println();
                      out.println("Game Reset.");//displays that game was reset
                      out.println("Pick a category from the following List.");
                      out.println("Food, Animals, or Superheroes. (Case Sensitive)");
                      out.println("When the game begins, USE LOWER CASE LETTERS to guess the word.");
                    } else if (gameFinished == 0) {
                      if (i == 1) {
                        String g = server.generateWord(clientMessage);
                        if (g == "Invalid category try again.") {//user guess wrong category
                              out.println("Invalid category try again.");
                          } else {
                            out.println("The Category is " + clientMessage + " and the word to guess is " + g.length() + " letters long.");//displays the random word chosen and its size
                            out.println("You have 6 Guesses Left.");
                            out.println(server.displayLetters());//outputs the visual to show what has been guessed 
                            i = 0;
                          }
                    } else if (clientMessage.length() == 1){//checks if user guesses a letter
                      String c = server.checkWord(clientMessage);//checks to make sure letter valid
                      if (c.length() > 1) {
                        out.println(c);//prints user message
                      }
                      out.println(server.displayLetters());//displays letters
                      if (server.checkWin()){//if user wins adds to category
                        wonCategorys++;
                        if (server.checkWin() && wonCategorys == 3) {//checks to see if user has won 3 times
                          out.println();
                          out.println("YOU BEAT THE GAME!!!!!!!!!!");//prints win statements
                          out.println("If you would like to play again TYPE: 'Play'");
                          out.println("If you woulf like to quit PRESS the Exit Button");
                          gameFinished = 1;
                        } else {
                          i = 1;
                          server.resetGame();//resets game
                          out.println();
                          out.println("You Guessed Right!!!");//tells user to pick another category when they guess correctly
                          out.println("Pick another category from the following List.");
                          out.println("Food, Animals, or Superheroes. (Case Sensitive)");
                          out.println("When the game begins, USE LOWER CASE LETTERS to guess the word.");
                        }
                      }
                    } else {
                      out.println("Input needs to be ONLY ONE letter to guess.");//checks to make sure user only uses one letter
                      out.println(server.displayLetters());
                    }
                      if (server.getLives() == 0){//checks to make sure user didn't guess more then 6 times
                        out.println();
                        out.println("You ran out of Guesses!");
                        if (server.checkLoss()) {//checks to see if attempted categories more then 3 times
                          gameFinished = 1;
                          out.println("You have failed to many times.");//outputs loss message
                          out.println("GAME OVER");
                          out.println("If you would like to play again TYPE: 'Play'");//prompts to exit or play again
                        out.println("If you woulf like to quit PRESS the Exit Button");
                        } else {
                          out.println("Pick another category from the following List.");//else tells user to pick another category
                        out.println("Food, Animals, or Superheroes. (Case Sensitive)");
                        out.println("When the game begins, USE LOWER CASE LETTERS to guess the word.");
                            server.resetGame();//resets game
                            i = 1;
                        }
                      }
                    }
                }
            } catch (IOException e) {
                e.printStackTrace();
            } finally {
                try {
                    clientSocket.close();
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
        }
    }
}
