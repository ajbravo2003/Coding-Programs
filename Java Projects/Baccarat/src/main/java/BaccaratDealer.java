import java.util.ArrayList;
import java.util.Collections;
public class BaccaratDealer {
  private ArrayList<Card> deck; //Initializes deck
  public BaccaratDealer(){//default constructor
    deck = new ArrayList<Card>();//makes new card array list
    generateDeck();//generates deck
  }

  public void generateDeck(){ 
    String[] suits = {"Hearts", "Diamonds", "Clubs", "Spades"}; //creates array of suits
    int[] values = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13}; //creates array of values for each card
    for(int i = 0; i < suits.length; i++){ //Loops through each suit and value and create each card
      for(int j = 0; j < values.length; j++){
        deck.add(new Card(suits[i], values[j]));
      }
    }
  }

  public ArrayList<Card> dealHand(){//function that gives hand to dealer and user
    ArrayList<Card> hand = new ArrayList<Card>();//creates new array list of cards
    hand.add(drawOne());//adds one card to user/dealer hand
    hand.add(drawOne());//adds one card to user/dealer hand
    return hand;
  }

  public Card drawOne(){//draws a card from the deck
    return deck.remove(0);//removes a card from the deck and returns to hand
  }

  public void shuffleDeck(){ //Shuffles the array of cards/deck
    Collections.shuffle(deck);
  }

  public int deckSize(){ //returns size of deck
    return deck.size();
  }

  public ArrayList<Card> getDeck() {
    return deck;
  }
}