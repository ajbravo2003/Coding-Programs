import static org.junit.jupiter.api.Assertions.*;

import java.util.ArrayList;
import java.util.Iterator;

import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
class HMTest {
	 private MyHashMap<Integer> hashMap;
	 @BeforeEach
	    void setUp(){//sets up code
		 hashMap = new MyHashMap<>("Cozmo",34);
	    
	    }

	    @Test
	    public void MyHashMap(){//testing the constructor class of hash map and put function
	    	MyHashMap<Integer> hashMap2; //create a new hashMap2
	    	hashMap2 = new MyHashMap<>("Cozmo",87);//calls constructor and put function
	    	assertEquals(hashMap2.size(), 1);
	    	assertEquals(hashMap2.contains("Cozmo"),true,"Hashmap constructor failed");//checks to see if hashmap is added into the map
	    }
	    
	    @Test
	    public void contains(){//testing the contains function
	    	assertEquals(hashMap.contains("Cozmo"),true);//makes sure the contains function finds the key
	    	hashMap.put("easy", 2131);//adds into queue
	    	hashMap.put("hard", 2131);//adds into queue
	    	hashMap.put("mediuk", 2131);//adds into queue
	    	hashMap.put("sda", 2131);//adds into queue
	    	assertEquals(hashMap.contains("easy"),true);//makes sure easy is in the map
	    	assertEquals(hashMap.contains("s"),false);//makes sure that s isnt in the map
	    	assertEquals(hashMap.contains("hard"),true);//makes sure that hard is in the map
	    	assertEquals(hashMap.contains("ss"),false,"HashMap contains failed");//makes sure ss isnt in the map
	    	assertEquals(hashMap.size(), 5);
	    }
	    
	    @Test
	    public void get(){//testing the get function 
	    	hashMap.put("easadsy", 6);//adds into queue
	    	hashMap.put("das", 3);//adds into queue
	    	hashMap.put("asd", 2);//adds into queue
	    	hashMap.put("sder32a", 1);//adds into queue
	    	assertEquals(hashMap.get("easadsy"),6);//checks to make sure it returns keys value
	    	assertEquals(hashMap.get("das"),3);//checks to make sure it returns keys value
	    	assertEquals(hashMap.get("asd"),2);//checks to make sure it returns keys value
	    	assertEquals(hashMap.get("sder32a"),1);//checks to make sure it returns keys value
	    	assertEquals(hashMap.size(), 5);
	    	hashMap.put("123123", 25);//adds into queue
	    	hashMap.put("213123", 156);//adds into queue
	    	assertEquals(hashMap.get("123123"),25);//checks to make sure it returns keys value
	    	assertEquals(hashMap.get("213123"),156);//checks to make sure it returns keys value
	    	assertEquals(hashMap.get("fakeval"),null,"Hashmap get failed");//checks to make sure it returns null since key dont exist
	    }
	    
	    @Test
	    public void size(){//testing the size function 
	    	assertEquals(hashMap.size(), 1);//makes sure size is one from default constructor
	    	hashMap.put("12", 6);//adds into queue
	    	assertEquals(hashMap.size(), 2);//makes sure size is one from default constructor
	    	hashMap.put("3", 3);//adds into queue
	    	assertEquals(hashMap.size(), 3);//makes sure size is one from default constructor
	    	hashMap.put("5", 2);//adds into queue
	    	assertEquals(hashMap.size(), 4);//makes sure size is one from default constructor
	    	hashMap.put("6", 1);//adds into queue
	    	assertEquals(hashMap.size(), 5);//makes sure size is one from default constructor
	    	for(int i =0 ; i<20;i++){//adds 20 new keys into hash map
		    	hashMap.put("1", i);//adds into queue
	    	}
	    	assertEquals(hashMap.size(), 25,"hash map size function failed");//makes sure size is one from default constructor
	    }
	    
	    @Test
	    public void isEmpty(){//testing the isEmpty function 
	    	assertEquals(hashMap.isEmpty(), false);//makes sure map isnt empty since default constructor
	    	hashMap.put("23", 6222);//adds into queue
	    	assertEquals(hashMap.isEmpty(), false);//makes sure map isnt empty
	    	hashMap.put("4", 32222);//adds into queue
	    	assertEquals(hashMap.isEmpty(), false);//makes sure map isnt empty
	    	hashMap.put("5", 22222);//adds into queue
	    	assertEquals(hashMap.isEmpty(), false);//makes sure map isnt empty
	    	hashMap.put("1", 622222);//adds into queue
	    	assertEquals(hashMap.isEmpty(), false);//makes sure map isnt empty
	    	hashMap.put("2333333333", 322222);//adds into queue
	    	assertEquals(hashMap.isEmpty(), false,"hashMap is empty failed");//makes sure map isnt empty
	    	hashMap.put("5343241233421", 112333333);//adds into queue
	    }
	    
	    @Test
	    public void replace(){//testing the replace function 
	    	assertEquals(hashMap.size(), 1);//tests default constructor
	    	hashMap.put("A", 1);//adds into queue
	    	hashMap.put("L", 2);//adds into queue
	    	hashMap.put("E", 3);//adds into queue
	    	hashMap.put("J", 4);//adds into queue
	    	hashMap.put("N", 6);//adds into queue
	    	hashMap.put("D", 7);//adds into queue
	    	hashMap.put("R", 8);//adds into queue
	    	hashMap.put("0", 9);//adds into queue
	    	hashMap.replace("A",34);//replaces value of A
	    	hashMap.replace("L",33);//replaces value of L
	    	assertEquals(hashMap.get("A"), 34);//checks to make sure value is replaced
	    	assertEquals(hashMap.get("L"), 33,"hashMap replace function failed");//checks to make sure value is replaced
	    	assertEquals(hashMap.get("Lsadas"), null);//checks to make sure nothing is replaced
	    	assertEquals(hashMap.size(), 9);
	    }
	    
	    @Test
	    public void HMIIterator(){//tests HMI iterator
	        Iterator<Integer> iterator = hashMap.iterator();//creates a iterator
	        ArrayList<Integer> result = new ArrayList<>();//creates new array list to store values
	        hashMap.put("Nasdas", 6);//adds into queue
	    	hashMap.put("Rasdas", 889);//adds into queue
	    	hashMap.put("0dasdas", 977);//adds into queue
	    	for (Integer value : hashMap){//traveres the hash map 
	            result.add(value);//stores values
	        }
	        Integer[] vals = {34,6,889,977};//values that are expected if traversed correclty
	        assertArrayEquals(vals, result.toArray(new Integer[0]),"hashMap iterator failed");//makes sure values are read correclty
	    }
}