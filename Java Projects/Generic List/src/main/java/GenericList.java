import java.util.Iterator;
import java.util.ArrayList;
public abstract class GenericList<T> implements Iterable<T> {
    private Node<T> head;//private node that contains head pointer
    private int length;//stores length of list
    
    public class Node<T> {//node class
         T data;//stores nodes data value
         int code;//stores codes value
         Node<T> next;//stores next value in list

        public Node(T data) {
            this.data = data;//sets data to nodes value
            this.code = 0;//Initializes code to 0
            this.next = null;//sets next value to null  
        }
    }
    
    public GenericList(){//constructor for the GenericList class
        this.length = 0;//sets length to 0
        this.head=null;//sets head to null
    }

    abstract void add(T data);//declares add function
    
    
    public abstract T delete();//declares delete function

    
    public ArrayList<T> dumpList(){//function that adds all nodes values into a array list
      ArrayList<T> newList = new ArrayList<>();//creates a new list of type T
      Node<T> tempNode = head;//sets the temp node to head 
      while (tempNode != null) {//keeps looping till end of list
            newList.add(tempNode.data);//adds values of nodes into the array list
            tempNode = tempNode.next;//goes to next node
        }
      return newList;//returns the array list
    }

    public T set(int index, T element){//sets element at a index
    	if (index < 0 || index >= length){//checks to see if out of bounds
    	     return null;//returns null
    	}

    	Node<T> tempNode = head;//temp node that is set to the head
    	   for (int i = 0; i < index; i++){//for loop to go to index
    	      tempNode = tempNode.next;//traverses till it reaches the index
    	}
    	   
    	T oldNode = tempNode.data;//sets data of previous node into variable with type T
    	tempNode.data = element;//sets new value to the node at the index
    	return oldNode;//returns old nodes value
    }
    
    
    public T get(int index){//function that gets value from a certain index
    	if (index < 0 || index >= length){//checks to see if out of bounds
   	     return null;//returns null
    	}
    	 
    	Node<T> tempNode = head;//temp node that is set to the head
    	for (int i = 0; i < index; i++){//for loop to go to index
  	      tempNode = tempNode.next;//traverses till it reaches the index
    	}
    	
    	return tempNode.data;//returns node value at the index
    }

    public void setLength(int length){//function that sets length from user
        this.length = length;//sets the length to value provided
    }
    
    public int getLength(){//function that gets and returns length
        return this.length;//returns the current length
    }

    public void setHead(Node<T> head) {//function that sets head 
        this.head = head;//sets head to provided node
    }
    
    public Node<T> getHead(){//function that returns current head
    	return this.head;//returns head
    }
    
    public Iterator<T> descendingIterator(){//function for desceding iterator
        ArrayList<T> newList = new ArrayList<>();//creates a new array list
        Node<T> tempNode = head;//sets temp node to the head
        while (tempNode != null) {
            newList.add(tempNode.data);//adds all values in queue into the arraylist
            tempNode = tempNode.next;//goes to next value
        }
        return new Iterator<T>() {//returns new iterator reverseed
            int index = newList.size() - 1;//gets end index
            @Override
            public boolean hasNext() {//checks if theres any value
                return index >= 0;
            }

            @Override
            public T next(){  
                return newList.get(index--);//returns value of next number going backwards
            }
        };
    }

    public void print(){//function that prints the list
        if (head == null) {//checks if the list is empty
            System.out.println("Empty List");//prints empty list
        } 
        
        else{
            Node<T> tempNode = head;//sets a node to head
            while (tempNode != null) {//traverses in list until end
                System.out.println(tempNode.data);//prints each value on separate line
                tempNode = tempNode.next;//goes to next value in list
            }
        }
    }
}