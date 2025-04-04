public class Card {
  private String suite; //initializes private data members
  private int value; 
  Card(String suite, int value){ //constructor
    this.suite = suite;
    this.value = value;
  }

  public int getValue() { //returns value
    return value;
  }

  public String getSuite() { //returns suite
    return suite;
  }
  public String getPNG(){//function that gets PNG for the card
	  if (this.value == 13){//checks if its a king
	    return "king_of_" + this.suite + ".png";
	  } 
	  else if (this.value == 12){//checks if its a queen
		  return "queen_of_" + this.suite + ".png";
	  } 
	  else if (this.value == 11){//checks if its a jack
		  return "jack_of_" + this.suite + ".png";
	  } 
	  else if (this.value == 1){//checks if its a ace
		  return "ace_of_" + this.suite + ".png";
	  } 
	  else {//any other card
		  return this.value + "_of_" + this.suite + ".png";
	  }
	}  
}