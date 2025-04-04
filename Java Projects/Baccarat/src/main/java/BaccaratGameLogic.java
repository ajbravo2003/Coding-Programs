import java.util.ArrayList;
public class BaccaratGameLogic {
  public String whoWon(ArrayList<Card> hand1, ArrayList<Card> hand2){
    int total1 = handTotal(hand1); //Gets players and bankers hands
    int total2 = handTotal(hand2);
    //Checks who won by checking who's number is closest to 9
    if(total1 > total2){ //Player wins
      return "Player";
    } else if (total1 < total2) { //Banker wins
      return "Banker";
    } else { //Draw if hands are equal
      return "Draw";
    }
  }

  public int handTotal(ArrayList<Card> hand) {//returns total of current hand of dealer/user
	  int total = 0;
	  if(hand==null) {
		  return 0;
	  }
	  for(Card card: hand){//iterates through hand
	    if (card.getValue() < 10) {
	      total += card.getValue();//adds values of cards
	    }
	  }
	  return total%10;//returns total points of hand
	}
  
  
  public boolean evaluateBankerDraw(ArrayList<Card> hand, Card playerCard){//function that checks if banker needs to draw hand  
    int total = handTotal(hand);//gets total of hand
    if(total >= 7){//if player hand is bigger then or equal to 7 dealer doesn't draw
      return false;
    } else if(total == 6 && playerCard.getValue() == 6 | playerCard.getValue() == 7){//checks if player card is 6 or 7 dealer draw
      return true; 
    } else if(total == 5 && playerCard.getValue() >= 4 && playerCard.getValue() <= 7){//checks if player card is between 5 and 4 dealer draw
      return true;
    } else if(total == 4 && playerCard.getValue() >= 2 && playerCard.getValue() <= 7){//if player card is between 2 and 7 and dealer has a value of 4 then dealer draw
      return true;
    } else if(total == 3 && playerCard.getValue() != 8){ //checks if player card is not 8 and dealer draw
      return true;
    } else if(total <= 2){ //checks if player card is 2 or less and dealer draw
      return true;
    }
    return false;
  }

  public boolean evaluatePlayerDraw(ArrayList<Card> hand) {
    int total = handTotal(hand); //Gets players hand total
    return total <= 5; //Player must draw if their hand total is 5 or less
  }
}