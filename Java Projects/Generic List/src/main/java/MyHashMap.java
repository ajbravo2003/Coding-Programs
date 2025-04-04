import java.util.ArrayList;
import java.util.Iterator;

public class MyHashMap<T> implements Iterable<T>{//Declares MyHashMap class
	 private ArrayList<GenericQueue<T>> map;//creates data memeber to store the queues
	 private Integer size;//int variable to keep track of map size
	 public MyHashMap(String key, T value){//parametized constructor 
	        map = new ArrayList<>(10);//makes a new list of 10
	        for (int i = 0; i < 10; i++){//traverses the list
	            map.add(null);//adds null to all arraylist values
	        }
	        size = 0;//sets the size to 0
	        put(key, value);//calls put function to store key and value
	 } 

	 public void put(String key, T value){//put function to store the queue into the map
		    int hashValue = key.hashCode();//gets hashcode
		    int hashIndex = hashValue & 9;//gets index of hashcode
		    GenericQueue<T> queue = map.get(hashIndex);//gets the queue at the index
		    if(queue == null){//checks to make sure its empty
		        queue = new GenericQueue<>(value, hashValue);//makes a queue with the value and hash value
		        map.set(hashIndex, queue);//sets the queue into the map at the index
		    } 
		    
		    else{//if queue already exists just add it into the queue
		        queue.add(value, hashValue);
		    }
		    size++;//increase the size of map
	 }
	 
	 public boolean contains(String key){//contain function that checks if key exists in map
		    GenericQueue<T> queue = map.get(key.hashCode()&9);//gets queue at the index
		    while(queue.getHead()!= null) {//traverses through the head
		    	if(queue.getHead().code==key.hashCode()) {//checks to see if code and keys hashcode is the same
		    		return true;//returns true since key is found
		    	}
		    	queue.setHead(queue.getHead().next);//goes to next value in queue
		    }
		    return false;//no key is found so returns false
	}
	 
	  public T get(String key){//get function that returns value of key
		    int hashValue = key.hashCode();//gets hashcode of key
		    int hashIndex = hashValue & 9;//gets index of key
		    GenericQueue<T> queue = map.get(hashIndex);//gets the queue of map at the index
		    if (queue != null){//checks to make sure its not empty
		        while (queue.getHead() != null){//traverses through the head
		            if (queue.getHead().code == hashValue){//checks to see if key is found
		                return queue.getHead().data;//returns the data value of the key
		            }
		            queue.setHead(queue.getHead().next);//goes on to next value in queue
		        }
		    }
		    return null;//returns null if no key is found
	  }
	  
	  public int size(){//size function
		  return size;//returns size
	  }
	  
	  public boolean isEmpty(){//checks to see if map is empty
		    if(size==0){//checks to see if size is 0
		    	return true;
		    }
		    return false;//otherwise returns false
	 }
	  
	  public T replace(String key, T value){//replace function that replaces the value and returns old value
		  int hashValue = key.hashCode();//gets hash code from key
		  int hashIndex = hashValue & 9;//gets index of hashvalue
		  GenericQueue<T> queue = map.get(hashIndex);//gets queue at the index
		  if (queue != null){//checks to make sure its not empty
			  T oldVal = null;//creates a new T value to store the old value 
		      while (queue.getHead()!= null){//traverses through the head
		    	  if (queue.getHead().code == hashValue){//checks to see if key is found
		    		  oldVal = queue.getHead().data;//sets old value to variable
		              queue.getHead().data = value;//replaces data with new data
		              break;//once key is found break out of loop
		            }
		            queue.setHead(queue.getHead().next);//moves to next node in queue
		        }
		        return oldVal;//returns the old value 
		    }
		    return null;//if key isnt found the returns null
	}

	  @Override
	  public Iterator<T> iterator() {
	      return new HMIterator<>(map);
	  }
}
