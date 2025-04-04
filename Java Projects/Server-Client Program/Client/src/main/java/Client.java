import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.Socket;	
public class Client{//client class 
    public static void main(String[] args) {
        try {
            Socket socket = new Socket("127.0.0.1", 12345);//creates a new socket
            // Create a thread to read messages from the server
            new Thread(() -> {//creates new thread 
                try {
                    BufferedReader serverIn = new BufferedReader(new InputStreamReader(socket.getInputStream()));
                    String serverResponse;//gets messages from server
                    while ((serverResponse = serverIn.readLine()) != null){//reads line of user input
                        System.out.println(serverResponse);//prints the response
                    }
                } catch (IOException e) {//handles exceptions
                    e.printStackTrace();
                }
            }).start();//starts the thread

            // Create a thread to send messages to the server
            new Thread(() -> {
                try {
                    PrintWriter out = new PrintWriter(socket.getOutputStream(), true);
                    BufferedReader consoleIn = new BufferedReader(new InputStreamReader(System.in));
                    String userInput;
                    while ((userInput = consoleIn.readLine()) != null) {//reads line
                        out.println(userInput);//prints userInput
                    }
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }).start();//starts thread

        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
