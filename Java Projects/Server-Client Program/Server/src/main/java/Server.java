import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.lang.reflect.Array;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.ArrayList;
import java.util.Random;
public class Server {//class that handles the server
	  int numberGuesses = 6;//sets number of user guesses
	  int cFood = 0, cAnimals = 0, cHeros = 0;//creates categories variables
	  ArrayList<String> usedCategory = new ArrayList<>();//creates 3 arrayList for the game
	  ArrayList<String> usedWords = new ArrayList<>();
	  ArrayList<Character> usedLetters = new ArrayList<>();
	  String currentWord;//creates variable to hold the current word
	  boolean win = false;//Boolean variables to check if user wins or loses
	  boolean loss = false;
	  String currentCategory;
	  public static void main(String[] args) {
	        ServerSocket serverSocket = null;//creates socket

	        try {
	            serverSocket = new ServerSocket(12345);//assigns socket 12345 and creates it
	            System.out.println("Server listening for clients");//prints that the server to client

	            while (true) {
	                Socket clientSocket = serverSocket.accept();//waits for connections
	                System.out.println("Accepted connection from " + clientSocket.getInetAddress().getHostAddress());//prints to server that client connected
	                ClientHandler clientHandler = new ClientHandler(clientSocket);//creates new threads
	                new Thread(clientHandler).start();//starts the thread
	            }
	        } catch (IOException e) {
	            e.printStackTrace();
	        } 
	        finally {
	            if (serverSocket != null && !serverSocket.isClosed()){//makes sure the socket isnt closed
	                try {
	                    serverSocket.close();//closes socket
	                } catch (IOException e) {
	                    e.printStackTrace();
	                }
	            }
	        }
	    }

	    static class ClientHandler implements Runnable {//runnable client handler class
	        private Socket clientSocket;//creates client socket 
	        public ClientHandler(Socket clientSocket){//constructor
	            this.clientSocket = clientSocket;//assigns socket to our variable
	        }

	        @Override
	        public void run() {
	          //Overridden in Server's JavaFXTemplate
	        }
	    }

	    public String generateWord(String category){//function to generate word
	      if (usedCategory.contains(category)){//checks to make sure user input is not the same category
	        return "Invalid category try again.";//gives statement saying user is picking invalid category
	      }

	      String[] words = new String[5];//makes a string array
	      if (category.equals("Food")) {//checks to see if category is food
	        currentCategory = "Food";//assigns to current category
	        cFood += 1;//adds to category count
	        words[0] = "pizza";//stores all strings into the array
	        words[1] = "sushi";
	        words[2] = "hamburger";
	        words[3] = "rice";
	        words[4] = "hotdog";
	      } 
	      else if (category.equals("Animals")){//checks to see if category is Animals
	        currentCategory = "Animals";//assigns to current category
	        cAnimals += 1;//adds to category count
	        words[0] = "panda";//stores all strings into the array 
	        words[1] = "tiger";
	        words[2] = "lion";
	        words[3] = "cheetah";
	        words[4] = "whale";
	      } 
	      else if (category.equals("Superheroes")){//checks to see if category is Super heroes
	        currentCategory = "Superheroes";//assigns to current category
	        cHeros += 1;
	        words[0] = "batman";//stores all strings into the array 
	        words[1] = "spiderman";
	        words[2] = "superman";
	        words[3] = "daredevil";
	        words[4] = "flash";
	      } else {
	        return "Invalid category try again.";//any other category is invalid
	      }

	      Random random = new Random();//creates new random variable
	      int randomNumber = random.nextInt(5) + 1; //creates random number from 1-5

	      while (usedWords.contains(words[randomNumber-1])){//picks random word
	          randomNumber = random.nextInt(5) + 1;
	      }

	      currentWord = words[randomNumber-1];//assigns random word 
	      usedWords.add(words[randomNumber-1]);//adds random word to arrayList
	    return words[randomNumber-1];//returns the random word
	    }

	    public String checkWord(String word){//function that checks user letter
	      if (word.length() > 1) {//makes sure its only 1 letter
	        return "Invalid Guess";//gives invalid output
	      } else if (usedLetters.contains(word.charAt(0))){//checks to see if letter has been guessed
	        return "Letter Already Guessed";
	      } else if (currentWord.contains(word)){//checks to make sure letter is in word
	        usedLetters.add(word.charAt(0));//adds word to display
	        displayLetters();//displays new output
	        return word;
	      } else {//user guessed wrong and loses a guess
	        numberGuesses -= 1;
	        return (word + " not in Word, you lost a Guess. Number of Guesses left: " + numberGuesses);
	      }
	    }

	    public String displayLetters(){//function that displays game 
	      String returnString = "";
	      String compare = "";
	      for (char currChar : currentWord.toCharArray()){//loops through current word array
	            if (usedLetters.contains(currChar)) {//checks to make sure letter is in list
	              returnString = returnString.concat(String.valueOf(currChar) + " ");//adds that letter to the current string
	              compare = compare.concat(String.valueOf(currChar));//adds both strings into one
	            } else {
	              returnString = returnString.concat("_ ");//adds _ where the user hasn't guessed yet/spots letter hasn't been guessed
	              compare = compare.concat("_");
	            }
	      }

	      if (compare.equals(currentWord)) {//checks to see if user guessed the word
	        win = true;//sets win to true
	        numberGuesses = 6;//resets number guesses
	        usedCategory.add(currentCategory);//adds category to list so user can't play it again
	      }

	      return returnString;
	    }

	    public boolean checkWin(){//checks for win
	      return win;
	    }

	    public void resetGame() {//function that resets game
	      win = false;//sets win to false 
	      usedLetters.clear();//clears array list
	      currentCategory = "";
	      currentWord = "";
	      numberGuesses = 6;//sets number of guesses back
	    }

	    public int getLives(){//returns number of guesses left
	      return numberGuesses;
	    }

	    public boolean checkLoss() {//checks to see if you lost the game
	      if (cFood == 3 || cAnimals == 3 || cHeros == 3){//if any category has 3 losses game over
	        return true;
	      }
	      return false;
	    }

	    public void replayGame(){//function that lets you replay the game
	      usedLetters.clear();//clears array lists
	      usedCategory.clear();
	      usedWords.clear();
	      currentCategory = "";
	      currentWord = "";
	      numberGuesses = 6;//sets numbers of guesses back to 6
	      win = false;
	      loss = false;
	      cFood = 0;//sets category counts back to 0
	      cAnimals = 0;
	      cHeros = 0;
	    }
	}


