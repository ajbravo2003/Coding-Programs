import static org.junit.jupiter.api.Assertions.*;
import java.util.ArrayList;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.DisplayName;
import org.junit.jupiter.params.ParameterizedTest;
import org.junit.jupiter.params.provider.ValueSource;
class MyTest {

	  private Server server;//creates server variable

	    @BeforeEach
	    void setUp(){
	        server = new Server();//Creates new server
	        server.usedLetters = new ArrayList<>();
	        server.currentWord = "pizza";//uses pizza as a current word
	    }

	    @Test
	    void testGenerateWordFood(){//tests generate word for food list
	        Server server2 = new Server();//makes new server
	        String word = server2.generateWord("Food");//generates word
	        //checks to make sure the word generated is from the categories
	        assertTrue(word.equals("pizza") || word.equals("sushi") || word.equals("hamburger") || word.equals("rice") || word.equals("hotdog"), "testGenerateWordFood");
	    }

	    @Test
	    void testGenerateWordAnimals(){//tests that a word is generated correctly from our animal list
	        Server server2 = new Server();
	        String word = server2.generateWord("Animals");//Generates word from animals

	      //Check that the generated word is one of the expected words
	        assertTrue(word.equals("panda") || word.equals("tiger") || word.equals("lion") || word.equals("cheetah") || word.equals("whale"), "testGenerateWordAnimals");
	    }

	    @Test
	    void testGenerateWordSuperheroes(){//tests to make sure word is generated correctly from super heroes list
	        Server server2 = new Server();
	        String word = server2.generateWord("Superheroes");//generates random word from list

	        //Check that the generated word is one of the expected words
	        assertTrue(word.equals("batman") || word.equals("spiderman") || word.equals("superman") || word.equals("daredevil") || word.equals("flash"), "testGenerateWordSuperheroes");
	    }

	    @Test
	    void testGenerateWordInvalid(){//checks to make sure that a invalid categories doesn't accept
	        Server server2 = new Server();
	        String word = server2.generateWord("cars");//tries to generate word from a category that doesn't exist
	        assertEquals(word, "Invalid category try again.", "Not Invalid");//checks to make sure it's invalid
	    }

	    @Test
	    void testCheckWordValidGuess(){//tests to make sure letter is given in a valid choice
	        String result = server.checkWord("p");
	        assertEquals("p", result);//checks to make sure p is in letter
	        assertTrue(server.usedLetters.contains('p'));//makes sure p is added to used letters so user doesn't choose same letter.
	    }

	    @Test
	    void testCheckWordInvalidGuess() {//checks to make sure user only gives letters
	        String result = server.checkWord("pizza");//tests to make sure words aren't accepted only letters
	        assertEquals("Invalid Guess", result);//makes sure result is invalid guess
	    }

	    @Test
	    void testCheckWordLetterGuessedAlready(){//tests to make sure a letter is only guessed once
	        server.usedLetters.add('p');//p is used
	        String result = server.checkWord("p");//tries to guess p again
	        assertEquals("Letter Already Guessed", result);//checks to make sure user can't use p again
	    }

	    @Test
	    void testCheckWordNotInWord(){//tests to make sure a invalid guess is handled properly
	        String result = server.checkWord("x");//user guess x
	        assertEquals("x not in Word, you lost a Guess. Number of Guesses left: 5", result);//checks to make sure letter isn't in word and they lose a guess
	        assertEquals(5, server.numberGuesses); //Check that the number of guesses has decreased
	    }

	    @Test
	    void testDisplayLetters(){//makes sure screen updates when letters are being guessed
	        server.usedLetters.add('z');//guesses z 
	        server.usedLetters.add('p');//guesses p
	        String result = server.displayLetters();//Displays letters
	        assertEquals("p _ z z _ ", result);//Word is pizza, so checks to make the printout is p_zz_ if p and z are guessed
	    }

	    @Test
	    public void testCheckWin() { //makes sure win is false
	        assertFalse(server.checkWin());
	    }

	    @Test
	    public void testResetGame() { //Makes sure game is reset after correct guess but not fully reset
	        server.resetGame();
	        assertFalse(server.checkWin());
	        assertEquals("", server.currentCategory);
	        assertEquals("", server.currentCategory);
	        assertEquals(6, server.getLives());
	        assertTrue(server.usedLetters.isEmpty());
	    }

	    @Test
	    public void testGetLives() { //Checks lives are all set to 6
	        assertEquals(6, server.getLives());
	    }

	    @Test
	    public void testCheckLoss() { //Checks win and loss at certain amount of wrong answers in each category
	        assertFalse(server.checkLoss());//checks to see that we don't lose
	        server.cFood++;//increments category losses
	        server.cAnimals++;
	        server.cHeros++;
	        assertFalse(server.checkLoss());//checks to see that we don't lose
	        server.cFood+=2;
	        assertTrue(server.checkLoss());//makes sure we lost game
	    }

	    @Test
	    public void testReplayGame() { //Checks game restarted properly after being played
	        server.cFood++;
	        server.cAnimals++;
	        server.cHeros++;
	        server.numberGuesses = 3;
	        server.replayGame();//replays game
	        assertFalse(server.checkWin());//checks to make sure we didn't win
	        assertFalse(server.checkLoss());//checks to make sure we didn't lose
	        assertEquals("", server.currentCategory);
	        assertEquals("", server.currentWord);
	        assertEquals(6, server.getLives());//makes sure we get our 6 guesses back
	        assertTrue(server.usedLetters.isEmpty());//makes sure arrayLists are cleared
	        assertEquals(0, server.cFood);//makes sure variables are set to 0
	        assertEquals(0, server.cAnimals);
	        assertEquals(0, server.cHeros);
	    }

	    @Test
	    void testMultipleClientsCategory(){
	      //Makes sure after the second client gets their category, it doesn't affect the current clients category or any of their Global variable
	      Server server1 = new Server();
	      Server server2 = new Server();
	      server1.generateWord("Food");//sets words to be guessed
	      server2.generateWord("Animals");
	      assertNotEquals(server1.currentCategory, "Animals"); //Make sure first category stays as food
	      assertEquals(server1.currentCategory, "Food");
	    }

	    @Test
	    void testMultipleClientsWords(){
	      //Makes sure after the second client gets their word, it doesn't affect the current clients word or any of their Global variable
	      Server server1 = new Server();
	      Server server2 = new Server();
	      server1.currentWord = "pizza";//sets words to be guessed
	      server2.currentWord = "lion";
	      assertNotEquals(server1.currentWord, "lion"); //Make sure the first clients word doesn't change after client 2 get their word
	    }
	}
