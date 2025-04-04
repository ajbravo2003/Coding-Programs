/**------------------------------------------
  Program 2 - Baccarat JavaFX GUI
  Course: CS 342, Fall 2023.
  System: Eclipse IDE for Java Developers 2023
  Author: Alejandro Bravo
  Description: We will be creating the card game 'Baccarat' with a JavaFx GUI
 ---------------------------------------------**/
import javafx.scene.control.Menu;
import javafx.scene.control.MenuBar;
import javafx.scene.control.MenuItem;
import java.util.ArrayList;//all imports 
import javax.print.attribute.standard.Media;
import javafx.animation.PauseTransition;
import javafx.application.Application;
import javafx.application.Platform;
import javafx.event.ActionEvent;
import javafx.event.EventHandler;
import javafx.geometry.Insets;
import javafx.geometry.Pos;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.TextArea;
import javafx.scene.control.TextField;
import javafx.scene.image.Image;
import javafx.scene.image.ImageView;
import javafx.scene.layout.BorderPane;
import javafx.scene.layout.HBox;
import javafx.scene.layout.VBox;
import javafx.stage.Stage;
import javafx.util.Duration;
public class BaccaratGame extends Application{//Baccarat class that contains the game and user gui
    private ArrayList<Card> playerHand;//variables for hands
    private ArrayList<Card> bankerHand;
    private BaccaratDealer theDealer;//Variables to access other class data member and run game
    private BaccaratGameLogic gameLogic = new BaccaratGameLogic();//creates new game logic object
    private double currentBet;//variables for bets
    private double totalWinnings;
    private String userBetChoice;
    private PauseTransition pause = new PauseTransition(Duration.seconds(1));//variable to pause between screens
    private Stage primaryStage;
    Label playerHandText = new Label("\t\tPlayer hand: "+  gameLogic.handTotal(playerHand));//makes");//uses a label to tell user cards are players
    Label dealerHandText = new Label("\t\tDealer hand: " + gameLogic.handTotal(bankerHand));//uses a label to tell user cards are dealers

    //Initializes bet buttons and card buttons
    Button d1 = new Button(), d2 = new Button(), d3 = new Button(), p1 = new Button(), p2 = new Button(), p3 = new Button();//creates buttons for cards
    TextArea winLossText = new TextArea("");//Blank until it shows if you win or lose
    Button yesButton = new Button("Yes");
    Button noButton = new Button("No");
    Button betPlayer = new Button("Bet on Player");//creates bet buttons
    Button betBanker = new Button("Bet on Banker");
    Button betDraw = new Button("Bet on Draw");
    TextField betAmountField = new TextField();//creates bet amount field
    Button startGameButton = new Button("Start Game");//creates a start game button
    TextField balText = new TextField();//creates text field to display balance   
    
    public double evaluateWinnings(){//function that calculates winnings of user
      double winnings = 0;
      if(gameLogic.whoWon(playerHand, bankerHand) == "Player" && "Player" == userBetChoice){//checks if player wins and user made a bet on player
      winnings = currentBet * 2;//doubles winnings for user
      }
      else if(gameLogic.whoWon(playerHand, bankerHand) == "Banker" && "Banker" == userBetChoice){//checks if banker won and user put a bet on banker
      winnings = (currentBet*2)*0.95;//doubles winnings and takes 5% of earnings
      }
      else if (gameLogic.whoWon(playerHand, bankerHand) == "Draw" && "Draw" == userBetChoice){//Bet is 8:1 so they receive twice their money
      winnings = currentBet*9; 
      }
      totalWinnings += winnings; //adds winnings to total winnings/money they have
      return winnings;
    }

    public void setPlayerAndBankerHand(ArrayList<Card> p, ArrayList<Card> b){//Sets both hands only used in test cases
      playerHand = p;
      bankerHand = b;
    }


    public void setVarsForTests(double winnings, double bet, String userBet){ //Sets winnings, bet, and what the user bet on, only used for test cases
      totalWinnings = winnings;
      currentBet = bet;
      userBetChoice = userBet;
    }

    public double getTotalWinning(){//Returns total winnings, only used for test cases
      return totalWinnings;
    }

    public static void main(String[] args){
      launch(args);
    }

    @Override
    public void start(Stage primaryStage) {//function that creates a main screen
        this.primaryStage = primaryStage;
        primaryStage.setTitle("Baccarat"); //Sets title
        displayMainMenu(); //Displays the main menu screen

    }

    private void displayMainMenu(){//function that displays the main menu
        BorderPane root = new BorderPane();
        TextField title = new TextField("Baccarat"); //Name of game displayed
        title.setEditable(false); //Field can't be edited
        title.setStyle("-fx-font-size: 40;"); //Font size changed
        title.setMaxWidth(250); //Set width of field
        title.setAlignment(Pos.CENTER);
        title.setFocusTraversable(false); //Make sure the text field isn't highlighted when entering scene
        BorderPane.setAlignment(title, Pos.TOP_CENTER);//makes sure title is in top center
        BorderPane.setMargin(title, new javafx.geometry.Insets(20)); //Add top spacing
        root.setStyle("-fx-background-color: Black;");//sets color to black
        root.setTop(title);
        Button playButton = new Button("Play"); //Play button sends you to game starting screen
        playButton.setPrefSize(300, 100);
        playButton.setOnAction(e -> displayGameScreen());
        Button instructionsButton = new Button("Instructions"); //Instructions button sends you to instructions page
        instructionsButton.setPrefSize(300,100);
        instructionsButton.setOnAction(e -> displayInstructionsScreen());
        VBox buttons = new VBox(20); //Vbox to hold buttons
        buttons.setAlignment(Pos.CENTER);
        buttons.getChildren().addAll(playButton, instructionsButton);//adds button to box
        root.setCenter(buttons); //Adds Vbox to root
        Scene mainMenuScene = new Scene(root, 1350, 825);//creates new scene
        primaryStage.setScene(mainMenuScene);//sets main screen at start
        primaryStage.show();
    }

    void updateLabels() {
        playerHandText.setText("\t\tPlayer hand: " +  gameLogic.handTotal(playerHand));//makes");//uses a label to tell user cards are players
        dealerHandText.setText("\t\tDealer hand: " +  gameLogic.handTotal(bankerHand));//makes");//uses a label to tell user cards are dealer
    }

    private void displayGameScreen(){//function to handle game screen and implements the game 
    	balText.setText("Total Winnings: " + Double.toString(totalWinnings));//sets balance to screen
        theDealer = new BaccaratDealer();
	    BorderPane gameScreen = new BorderPane();
	    gameScreen.setStyle("-fx-background-color: green;");
	    balText.setEditable(false);//sets balance text field to non editable and changes its style
	    balText.setMaxWidth(350);
	    balText.setStyle("-fx-font-size: 20;");
	    balText.setAlignment(Pos.CENTER);
	    balText.setFocusTraversable(false);
	    
	    MenuBar menuBar = new MenuBar();
        Menu optionsMenu = new Menu("Options");//Create a menu called "Options"
        MenuItem exit = new MenuItem("Exit");// Create exit menu item
        exit.setOnAction(e -> {
        	Platform.exit();
        });

        MenuItem freshStart = new MenuItem("Fresh Start");//Create freshStart menu item
        freshStart.setOnAction(e -> {
        	totalWinnings = 0;
        	winLossText.clear();
        	displayGameScreen();
        });
        optionsMenu.getItems().addAll(exit, freshStart);//Add menu items to the Options menu
        menuBar.getMenus().add(optionsMenu);//Add the Options menu to the menu bar

        // Create a layout
        gameScreen.setTop(menuBar);
       
	    
	    Button drawCardButton = new Button("Draw Card");//button to draw a card
	    drawCardButton.setDisable(true);//Initially disabled
	    drawCardButton.setAlignment(Pos.CENTER);
	    drawCardButton.setOnAction(event -> {//event that adds a card to the hand when user clicks draw card button
	      pause.setOnFinished(e -> {
	        playerHand.add(theDealer.drawOne());//adds card to hand
	          if (gameLogic.evaluatePlayerDraw(bankerHand)){//checks to see if dealer draws as well
	            bankerHand.add(theDealer.drawOne());//adds card to dealer
	          }
	          dealHand();
	          updateLabels();
	          drawCardButton.setDisable(true);//once draw is complete user can't draw again
	          evaluateWinnings();//checks to see who won to update winnings
	          balText.setText("Total Winnings: " + Double.toString(totalWinnings));
	          gameRecord();
	          noButton.setDisable(false);
	          yesButton.setDisable(false);
	      });
	    pause.play();//lets there be a pause after the balance updates
	    Image image = new Image("200w.gif");
	    ImageView imageView = new ImageView(image);
	    p3.setGraphic(imageView);//sets gif before draw
	    });

	    startGameButton.setDisable(true);//Initially disabled
	    startGameButton.setAlignment(Pos.CENTER);
	    startGameButton.setOnAction(event -> {//once start game is pressed game starts
	    startGameButton.setDisable(true);
	    theDealer.shuffleDeck();//deck is shuffled
	    playerHand = theDealer.dealHand();//player gets a hand
	    bankerHand = theDealer.dealHand();//dealer gets a hand
	    dealHand();
	      updateLabels();
	    if (gameLogic.evaluatePlayerDraw(playerHand)){//checks to see if player needs to draw
	          drawCardButton.setDisable(false);
	    } else{
	          if(gameLogic.evaluatePlayerDraw(bankerHand)) {//checks to see if banker needs to draw
	            bankerHand.add(theDealer.drawOne());//adds hand to banker
	            pause.setOnFinished(e -> {
	              dealHand();
	            updateLabels();
	              evaluateWinnings();//evaluates winnings 
	              balText.setText("Total Winnings: " + Double.toString(totalWinnings));
	              gameRecord();
	              noButton.setDisable(false);
	              yesButton.setDisable(false);
	            });
	            pause.play();
	        } else{
	           evaluateWinnings();
	           balText.setText("Total Winnings: " + Double.toString(totalWinnings));//sets adjusted balance
	           gameRecord();
	           noButton.setDisable(false);//disables buttons
	           yesButton.setDisable(false);
	          }
	        }
	    });

        HBox buttonBox = new HBox(startGameButton, drawCardButton);//creates a HBox to store start and draw buttons
        buttonBox.setSpacing(20);//creates space between them
        buttonBox.setAlignment(Pos.CENTER);
        setStartingCards(d1); // Creates all buttons and sets starting pictures
        setStartingCards(d2);
        setStartingCards(d3);
        setStartingCards(p1);
        setStartingCards(p2);
        setStartingCards(p3);
        HBox dealer = new HBox(d1, d2, d3);// Put all dealer cards in HBox
        HBox player = new HBox(p1, p2, p3);// Put all player cards in HBox
        dealer.setSpacing(100);//makes space between dealer cards
        player.setSpacing(100);//makes space between player cards
        winLossText.setEditable(false);//Field can't be edited
        winLossText.setStyle("-fx-font-size: 15;");//Font size changed
        winLossText.setMaxWidth(700);//Set width of field
        winLossText.setPrefHeight(150);//Set height of field
        winLossText.setFocusTraversable(false);//Make sure the text field isn't highlighted when entering the scene
        VBox buttonContainer = new VBox(buttonBox);
        buttonContainer.setAlignment(Pos.CENTER);
        VBox rightVBox = new VBox();//creates a VBox
        betAmountField.setPromptText("Enter Bet Amount");
        betPlayer.setDisable(false);
        betPlayer.setOnAction(e -> {//if player button is clicked for bets it enters the bet and updates userBetChoice
          validBet();
          userBetChoice = "Player";
        });

        betBanker.setDisable(false);
        betBanker.setOnAction(e ->{//if banker button is clicked for bets it enters the bet and updates userBetChoice
          validBet();
          userBetChoice = "Banker";
        });

        betDraw.setDisable(false);//if draw button is clicked for bets it enters the bet and updates userBetChoice
        betDraw.setOnAction(e ->{
          validBet();
          userBetChoice = "Draw";
        });

        HBox playAgainBox = new HBox();//creates a new HBox
        HBox betBox = new HBox();
        TextField playAgainText = new TextField("Play Again?");
        playAgainText.setEditable(false);
        yesButton.setStyle("-fx-background-color: lime;");//modifies yes button to play again
        yesButton.setDisable(true);
        yesButton.setOnAction(e -> {
          displayGameScreen();//runs game if user clicks to play again
            yesButton.setDisable(true);
        });

        noButton.setStyle("-fx-background-color: red;");//modifies no button in case user doesn't want to play anymore
        noButton.setDisable(true);
        noButton.setOnAction(e ->{//if user doesn't want to play again and clicks button returns to start screen
        start(primaryStage); 
            noButton.setDisable(true);
        });

//        Button getMoreMoney = new Button("Refill Balance");
//        getMoreMoney.setOnAction(e -> balanceScreen());//if user clicks on refill balance then it takes back to balance screen
        playAgainBox.getChildren().addAll(playAgainText, yesButton, noButton);//sets everything back in screen when refill is complete
        betBox.getChildren().addAll(betPlayer, betDraw, betBanker);
        rightVBox.getChildren().addAll(betAmountField, betBox, playAgainBox); //can add getMoreMoney
        rightVBox.setSpacing(10);
        rightVBox.setAlignment(Pos.CENTER);
        playerHandText.setText("\t\tPlayer hand: "+  gameLogic.handTotal(playerHand));//makes");//uses a label to tell user cards are players
        playerHandText.setStyle("-fx-font-size: 35;");//modifies size 
        playerHandText.setMaxWidth(600);
        playerHandText.setAlignment(Pos.CENTER);
        dealerHandText.setText("\t\tDealer hand: " + gameLogic.handTotal(bankerHand));//uses a label to tell user cards are dealers
        dealerHandText.setStyle("-fx-font-size: 35;");//modifies size
        dealerHandText.setMaxWidth(600);
        dealerHandText.setAlignment(Pos.CENTER);
        VBox balanceLabel = new VBox(70);//makes a new VBox to store labels and balance
        balanceLabel.setSpacing(125);
        balanceLabel.getChildren().addAll(balText, dealerHandText, playerHandText);//sets into VBox
        gameScreen.setLeft(balanceLabel);//sets VBox on left side
        gameScreen.setCenter(new VBox(dealer, winLossText, player, buttonContainer));
        gameScreen.setRight(rightVBox);
        Scene gameScene = new Scene(gameScreen, 1350, 825);
        primaryStage.setScene(gameScene);//goes back to game scene      
    }

    private void setStartingCards(Button b){//function that sets the starting cards to the screen
        b.setDisable(false); //Disable all buttons because you control the dealing with other buttons
        Image pic = new Image("Back.png");//Sets imagine of cards onto the buttons
        ImageView v = new ImageView(pic);
        v.setFitHeight(200);//sets size for image
        v.setFitWidth(300);
        v.setPreserveRatio(true);
        b.setGraphic(v);//adds empty card image to button
    }

    private void dealHand(){//function that deals hand
      int i = 0;
      for(Card card: playerHand){//traverses through each card
	      String png = card.getPNG();//gets image of card
	        Image pic = new Image(png); //Sets imagine of cards onto the buttons
	        ImageView v = new ImageView(pic);
	        v.setFitHeight(200);//sets image picture
	        v.setFitWidth(300);
	        v.setPreserveRatio(true);
	        if (i == 0){//sets image for first player card(most left)
	          p1.setGraphic(v);
	        } else if(i == 1){//sets image for second player card 
	          p2.setGraphic(v);
	        } else{//sets image for third player card
	          p3.setGraphic(v);
	        }
	        i++;
	      }
	      i = 0;
	      for(Card card: bankerHand) {
	          String png = card.getPNG();//gets image of card
	          Image pic = new Image(png); //Sets imagine of cards onto the buttons
	            ImageView v = new ImageView(pic);
	            v.setFitHeight(200);
	            v.setFitWidth(300);
	            v.setPreserveRatio(true);
	            if (i == 0) {//sets image for 1st dealer card(most left)
	              d1.setGraphic(v);
	            } else if (i == 1){//sets image of 2nd dealer card
	              d2.setGraphic(v);
	            } else {//sets image of dealers third card
	              d3.setGraphic(v);
	            }
	            i++;
	       }
	    }
    
    void gameRecord(){ //Prints out final game overview
    	if(userBetChoice == gameLogic.whoWon(playerHand, bankerHand)){
    	    winLossText.setText("Player Total: " +  gameLogic.handTotal(playerHand) + " Banker Total: "+ gameLogic.handTotal(bankerHand)+
    	          "\n"+ gameLogic.whoWon(playerHand, bankerHand)+ " wins!\n" + "Congrats, you bet "+ userBetChoice + "! You win!" );

    	} else {
    	    winLossText.setText("Player Total: " +  gameLogic.handTotal(playerHand) + " Banker Total: "+ gameLogic.handTotal(bankerHand)+
    	          "\n"+ gameLogic.whoWon(playerHand, bankerHand)+ " wins!\n" + "Sorry, you bet "+ userBetChoice + "! You lost your bet!" );
    	}
    }

    private void validBet(){//function that validates bets, updates winner, and updates balance
      String betAmount = betAmountField.getText();//gets current text of bet amount
      currentBet = Double.parseDouble(betAmount);
      betPlayer.setDisable(true);//Doesn't let user click on buttons to make a bet
      betBanker.setDisable(true);
      betDraw.setDisable(true);
      startGameButton.setDisable(false);//lets user start the game
      winLossText.setText("Bet Accepted Press Start!");
      balText.setText("Total Winnings: " + Double.toString(totalWinnings));
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
            		+ "8) If you lose more then 3 times total across any of the 3 categories you LOSE!\n"
            		+ "9) Live or Die make you choice.\n");
        instructionsTextArea.setEditable(false);//creates a text area to display instructions and modify its attributes
        instructionsTextArea.setStyle("-fx-font-size: 14; -fx-text-fill: red; -fx-font-family: 'Comic Sans MS';");
        instructionsTextArea.setMaxWidth(800); 
        instructionsTextArea.setMaxHeight(400);
        instructionsTextArea.setWrapText(true);
        Label instructionsText = new Label("\t\tInstructions");//uses a label to make a title since text field highlights text
        instructionsText.setStyle("-fx-font-size: 60;");//modifies size and font
        instructionsText.setMaxWidth(800); 
        Button backButton = new Button("Back to Game");
        backButton.setStyle("-fx-font-size: 24;"); 
        backButton.setOnAction(e -> start(primaryStage));//when user clicks on button it takes back to menu screen
        centerBox.getChildren().addAll(instructionsText, instructionsTextArea, backButton);
        instructionsScreen.setCenter(centerBox);//sets box to center
        Scene instructionsScene = new Scene(instructionsScreen, 1350, 825);
        primaryStage.setScene(instructionsScene);//sets scene
    }
  }