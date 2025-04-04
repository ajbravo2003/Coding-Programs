import static org.junit.jupiter.api.Assertions.*;
import java.util.ArrayList;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.DisplayName;
import org.junit.jupiter.params.ParameterizedTest;
import org.junit.jupiter.params.provider.ValueSource;
class MyTest {
	private BaccaratDealer dealer;
	private BaccaratGameLogic gameLogic;
	private BaccaratGame game;
	
	@BeforeEach
	void setUpBaccaratDealer(){//sets up code
		dealer = new BaccaratDealer();
		gameLogic = new BaccaratGameLogic();
	}

	@Test
	void testGenerateDeck(){//Makes sure deck is loaded with all 52 cards
		assertEquals(52, dealer.deckSize());
	}
	
	@Test
	void testGenerateDeckSize2(){//Makes sure deck doesn't have less than 52 cards
		assertNotEquals(50, dealer.deckSize());
	}
	
	@Test
	public void testShuffleDeck() { //Make array with starting deck and make sure shuffles deck isn't in the same order as the starting deck
		ArrayList<Card> startingDeck = new ArrayList<>(dealer.getDeck());
	    dealer.shuffleDeck();
	    ArrayList<Card> shuffledDeck = dealer.getDeck();
	    assertNotEquals(startingDeck, shuffledDeck);
	}
	
	@Test
	public void testShuffleDeck2() { //Make array with starting deck and make sure shuffles deck isn't in the same order as the starting deck multiple times
		ArrayList<Card> startingDeck = new ArrayList<>(dealer.getDeck());
		dealer.shuffleDeck();
		ArrayList<Card> shuffledDeck = dealer.getDeck();
		dealer.shuffleDeck();
		dealer.shuffleDeck();
		dealer.shuffleDeck();
		dealer.shuffleDeck();
		dealer.shuffleDeck();
		dealer.shuffleDeck();
		assertNotEquals(startingDeck, shuffledDeck);
		assertEquals(52, dealer.deckSize());
	}
	
	@Test
	public void testDealHand() {//tests dealer hand
		ArrayList<Card> hand = dealer.dealHand();
	    assertEquals(2, hand.size());//makes sure only two cards are given
	    assertEquals(50, dealer.deckSize());//makes sure deck size is subtracted
	}
	
	@Test
	public void testDealHandShuffled() {//tests dealer hand SHUFFLED
		dealer.shuffleDeck();
	    ArrayList<Card> hand = dealer.dealHand();
	    assertEquals(2, hand.size());//makes sure only two cards are given
	    assertEquals(50, dealer.deckSize());//makes sure deck size is subtracted
	}
	
	@Test
	public void testDrawOneShuffled() {//Draws one card and makes sure it is not null even when shuffled
	    Card card = dealer.drawOne();
	    assertNotNull(card);
	    assertEquals(51, dealer.deckSize());//Makes sure size is 1 less after card is drawn
	}

	@Test
	public void testDrawOne() {//Draws one card and makes sure it is not null
	    Card card = dealer.drawOne();
	    assertNotNull(card);
	    assertEquals(51, dealer.deckSize());//Makes sure size is 1 less after card is drawn
	}
	
	@Test
	public void testTopCards(){//Makes sure the first couple cards have the correct suit and value
		Card card;
		card = dealer.drawOne();
		assertEquals(card.getValue(), 1);//Makes sure beginning of heart cards are correct
		assertEquals(card.getSuite(), "Hearts");
		card = dealer.drawOne();
		assertEquals(card.getValue(), 2);
		assertEquals(card.getSuite(), "Hearts");
		card = dealer.drawOne();//Skips heart cards until it reaches diamonds
		card = dealer.drawOne();
		card = dealer.drawOne();
		card = dealer.drawOne();
		card = dealer.drawOne();
		card = dealer.drawOne();
		card = dealer.drawOne();
		card = dealer.drawOne();
		card = dealer.drawOne();
		card = dealer.drawOne();
		card = dealer.drawOne();
		card = dealer.drawOne();
		assertEquals(card.getValue(), 1);//makes sure diamonds 1 is next card
		assertEquals(card.getSuite(), "Diamonds");
		card = dealer.drawOne();
		assertEquals(card.getValue(), 2);
		assertEquals(card.getSuite(), "Diamonds");
	}
	
	@Test
	public void testCardConstructor() {//Tests the card constructor and get functions
		Card card = new Card("Hearts", 2);
	    assertEquals("Hearts", card.getSuite());
	    assertEquals(2, card.getValue());
	}
	
	@Test
	public void testWhoWonBanker(){//function that tests who wins between player and dealer
		ArrayList<Card> playerHand = new ArrayList<>();//makes a player array list
		playerHand.add(new Card("Hearts", 3));//adds two cards into the list for the player
		playerHand.add(new Card("Diamonds", 7));

		ArrayList<Card> bankerHand = new ArrayList<>();//creates new array list for the banker
		bankerHand.add(new Card("Clubs", 9));//adds two cards into the list for the banker
		bankerHand.add(new Card("Spades", 5));

		assertEquals("Banker", gameLogic.whoWon(playerHand, bankerHand));//checks to make sure the banker wins
	}

	@Test 
	public void testWhoWonPlayer(){//function that tests to make sure player wins 
		ArrayList<Card> playerHand = new ArrayList<>();//creates array list for player
		playerHand.add(new Card("Hearts", 3));//adds two cards to player
		playerHand.add(new Card("Diamonds", 6));

		ArrayList<Card> bankerHand = new ArrayList<>();//creates array list for banker
		bankerHand.add(new Card("Hearts", 9));//adds two cards to banker
		bankerHand.add(new Card("Hearts", 5));

		assertEquals("Player", gameLogic.whoWon(playerHand, bankerHand));//makes sure player wins the game
	}
  
	@Test
	public void testWhoWonDraw(){//Tests to make sure it's a draw
		ArrayList<Card> playerHand = new ArrayList<>(); //Creates players hand
		playerHand.add(new Card("Hearts", 3));
	    playerHand.add(new Card("Diamonds", 2));

	    ArrayList<Card> bankerHand = new ArrayList<>();//Creates bankers hand
	    bankerHand.add(new Card("Spades", 9));
	    bankerHand.add(new Card("Spades", 6));

	    assertEquals("Draw", gameLogic.whoWon(playerHand, bankerHand)); //Tests draw
	}
	
	@Test
	public void testHandTotal(){//function that tests hand total
		ArrayList<Card> hand = new ArrayList<>();
	    hand.add(new Card("Hearts", 3));//adds two cards into the list
	    hand.add(new Card("Diamonds", 7));
	    
	    assertEquals(0, gameLogic.handTotal(hand));//checks to make sure hand total is 0 since 10%10==0
	}
	
	@Test
	public void testHandTotal2() {//function that tests hand total
	    ArrayList<Card> hand = new ArrayList<>();
	    hand.add(new Card("Spades", 1));//adds two different types of cards
	    hand.add(new Card("Spades", 2));
	    assertEquals(3, gameLogic.handTotal(hand));//makes sure hand total is 3 
	}

	@Test
	public void testEvaluateBankerDraw() {//function that tests banker draw
	    ArrayList<Card> hand = new ArrayList<>();
	    hand.add(new Card("Hearts", 3));//adds two cards for banker
	    hand.add(new Card("Diamonds", 7));
	    Card playerCard = new Card("Clubs", 8);//makes a player draw card
	    assertTrue(gameLogic.evaluateBankerDraw(hand, playerCard));//makes sure that banker draws a card
	}

	@Test
	public void testEvaluateBankerDraw2(){//makes sure banker doesn't draw a card
	    ArrayList<Card> hand = new ArrayList<>();
	    hand.add(new Card("Hearts", 6));//adds two cards to list
	    hand.add(new Card("Diamonds", 2));
	    Card playerCard = new Card("Clubs", 8);//makes player draw a card 
	    assertFalse(gameLogic.evaluateBankerDraw(hand, playerCard));//makes sure that banker doesn't draw a card
	}

	@Test
	public void testEvaluatePlayerDraw(){//function that checks to see if player draws
		ArrayList<Card> hand = new ArrayList<>();
		hand.add(new Card("Hearts", 3));//adds two cards to player list
		hand.add(new Card("Diamonds", 7));
      	assertTrue(gameLogic.evaluatePlayerDraw(hand));//checks to make sure player draws a card 
	}

	@Test
	public void testEvaluatePlayerDraw2(){//function that checks to see if player doesn't draw
		ArrayList<Card> hand = new ArrayList<>();
		hand.add(new Card("Hearts", 3));//adds two cards into the player list
		hand.add(new Card("Diamonds", 6));
		assertFalse(gameLogic.evaluatePlayerDraw(hand));//makes sure that player doesn't draw
	}
	
	//Makes sure player receives the correct amount of money for betting on the player
    @Test
    public void testEvaluateWinningsPlayerWins(){
    	
    //	game.setVarsForTests(200.0, 100.0, "Player");//Sets winnings, bet and what the user bet on
    	ArrayList<Card> playerHand = new ArrayList<>();//creates array list for player
		playerHand.add(new Card("Clubs", 3));//adds two cards to player
		playerHand.add(new Card("Diamonds", 6));

		ArrayList<Card> bankerHand = new ArrayList<>();//creates array list for banker
		bankerHand.add(new Card("Hearts", 9));//adds two cards to banker
		bankerHand.add(new Card("Clubs", 5));
		
//		game.setPlayerAndBankerHand(playerHand, bankerHand);
		game.evaluateWinnings(); //Calls evaluate function to change the total winnings
//		
//        assertEquals(game.getTotalWinning(), 400.0);
    }
//    
//    //Makes sure player receives the correct amount of money for betting on the banker
//    @Test
//    public void testEvaluateWinningsBankerWins(){
//    	game.setVarsForTests(400.0, 200.0, "Banker");//Sets winnings, bet and what the user bet on
//    	ArrayList<Card> playerHand = new ArrayList<>();//creates array list for player
//		playerHand.add(new Card("Clubs", 3));//adds two cards to player
//		playerHand.add(new Card("Diamonds", 4));
//
//		ArrayList<Card> bankerHand = new ArrayList<>();//creates array list for banker
//		bankerHand.add(new Card("Hearts", 9));//adds two cards to banker
//		bankerHand.add(new Card("Clubs", 9));
//		
//		game.setPlayerAndBankerHand(playerHand, bankerHand);
//		game.evaluateWinnings(); //Calls evaluate function to change the total winnings
//		
//        assertEquals(game.getTotalWinning(), 780.0);
//    }
//    
//    //Makes sure player receives the correct amount of money for betting on a draw
//    @Test
//    public void testEvaluateWinningsDraw(){
//    	game.setVarsForTests(100.0, 10.0, "Draw");//Sets winnings, bet and what the user bet on
//    	ArrayList<Card> playerHand = new ArrayList<>();//creates array list for player
//		playerHand.add(new Card("Clubs", 4));//adds two cards to player
//		playerHand.add(new Card("Diamonds", 6));
//
//		ArrayList<Card> bankerHand = new ArrayList<>();//creates array list for banker
//		bankerHand.add(new Card("Hearts", 5));//adds two cards to banker
//		bankerHand.add(new Card("Clubs", 5));
//		
//		game.setPlayerAndBankerHand(playerHand, bankerHand);
//		game.evaluateWinnings(); //Calls evaluate function to change the total winnings
//		
//        assertEquals(game.getTotalWinning(), 190.0);
//    }
}
