import static org.junit.jupiter.api.Assertions.*;
import java.util.Iterator;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
class GQTests {
    private GenericQueue<Integer> queue;
 
    @BeforeEach
    void setUp(){//sets up code
        queue = new GenericQueue<>(6);
    }
    
	@Test
    void ConstructorTest(){//test case for constructor
    assertEquals(1, queue.getLength());//checks to make sure length is correct
    assertEquals(6, queue.get(0));//makes sure to check if value is 6
    assertEquals(6,queue.getHead().data);//makes sure data of queue of head is 6 
    assertEquals(0,queue.getHead().code,"constructor doesnt work");//checks to make sure code of queue is 0
    }
	
	@Test
    void Enqeune(){//test case for Enqeune function which just calls our add function
		queue.enqueue(24124);//adds 24124 to the list
		queue.enqueue(423);//adds value 423 to list
		queue.enqueue(53123);//adds 53123 to the list
		queue.enqueue(6414);//adds 6414 to the list
		queue.enqueue(712);//adds 712 to the list 
	    assertEquals(6, queue.getLength());//checks to make sure length is correct
	    Integer[] values1 = {6,24124, 423,53123,6414,712};//a array of values in the list			
		Integer arr[]  = new Integer[queue.getLength()];//creates new array
		arr = queue.dumpList().toArray(arr);//turns list into a array
		assertArrayEquals(values1, arr, "Wrong values in list for enqueue");//compares values in the list to the given lists
    }
	
	@Test
    void Deqeune(){//test case for dequeue function and that tests the delete function
		queue.dequeue();//makes sure first node can be deleted 
	    assertEquals(0, queue.getLength());//checks to make sure length is correct after
		queue.enqueue(6);//adds 6 to the list
	    queue.enqueue(352);//adds 352 to the list
		queue.enqueue(5);//adds value 5 to list
		queue.enqueue(42124);//adds 42124 to the list
		queue.enqueue(46346);//adds 46346 to the list
		queue.enqueue(7675);//adds 7675 to the list 
		queue.enqueue(2);//adds 2 to the list 
		queue.enqueue(4);//adds 4 to the list 
		queue.enqueue(2);//adds 2 to the list to see if dupe values work
	    assertEquals(9, queue.getLength());//checks to make sure length is correct after
	    assertEquals(6, queue.dequeue());//checks to make sure the head is deleted and vlaue is returned
	    assertEquals(8, queue.getLength());//checks to make sure length is correct after deletion
	    Integer[] values1 = {352,5,42124,46346,7675,2,4,2};//a array of values in the list after deletion		
		Integer arr[]  = new Integer[queue.getLength()];//creates new array
		arr = queue.dumpList().toArray(arr);//turns list into a array
		assertArrayEquals(values1, arr, "Wrong values in list for dequeue");//compares values in the list to the given lists
		queue.dequeue();//calls multiple dequeues
		queue.dequeue();
		queue.dequeue();
		queue.dequeue();
		queue.dequeue();
	    assertEquals(3, queue.getLength());//checks to make sure length is correct after
	    Integer[] values2 = {2,4,2};//a array of values in the list after deletion		
		Integer arr2[]  = new Integer[queue.getLength()];//creates new array
		arr2 = queue.dumpList().toArray(arr2);//turns list into a array
		assertArrayEquals(values2, arr2, "Wrong values in list for dequeue2");//compares values in the list to the given lists
    }
	
	@Test
	void add(){//this function calls the 2 parameter add function with code in its parameter
		queue.add(3, 5436536);
		queue.add(4, 53252);
		queue.add(3, 67867867);
		queue.add(3, 765756);
		queue.add(3, 54645);
	    assertEquals(6, queue.getLength());//checks to make sure length is correct 
	    assertEquals(0, queue.getHead().code);//checks to make sure code is correct for first value 
	    queue.dequeue();//deletes the head to check other values.
	    assertEquals(5436536, queue.getHead().code);//checks to make sure code is correct for second value 
	    queue.dequeue();//deletes the head to check other values.
	    assertEquals(53252, queue.getHead().code);//checks to make sure code is correct for 3rd value 
	    queue.dequeue();//deletes the head to check other values.
	    assertEquals(67867867, queue.getHead().code);//checks to make sure code is correct for 4th value 
	    queue.dequeue();//deletes the head to check other values.
	    assertEquals(765756, queue.getHead().code);//checks to make sure code is correct for 5th value 
	    queue.dequeue();//deletes the head to check other values.
	    assertEquals(54645, queue.getHead().code,"add function doesnt work");//checks to make sure code is correct for 6th value 
	}
	
	@Test
	public void NodeClass(){//tests node class constructor
		GenericQueue<Integer> queue2 = new GenericQueue<>(null);//creates a new queue
		GenericList<Integer>.Node<Integer> node = queue2.getHead();//creates a node instance
        assertEquals(null, node.data);//checks to make constructor of node class is null
        assertEquals(null, node.next);//checks to make constructor of node class is called and next is null
        assertEquals(0, node.code,"Node class constructor failed");//checks to make constructor of node class is called and code is 0
	}
		
	 @Test
	 public void DescendingIterator(){
		GenericQueue<Integer> queue2 = new GenericQueue<>(3);//creates a new queue
	    queue.enqueue(2);//adds 2 to the list
		queue.enqueue(54);//adds value 54 to list
		queue.enqueue(654);//adds 654 to the list
		queue.enqueue(67);//adds 67 to the list
		queue.enqueue(89);//adds 89 to the list 
		queue.enqueue(34);//adds 34 to the list 
		queue.enqueue(344);//adds 344 to the list 
		queue.enqueue(344);//adds 344 to the list to see if dupe values work
	    Iterator<Integer> iterator = queue2.descendingIterator();
	    assertEquals(iterator.hasNext(),true);
        assertEquals(3, iterator.next(),"DescendingIterator failed");
	 }

	 @Test
	 public void GLLIterato4(){//test GLL iterator 
		 Iterator<Integer> iterator = new GLLIterator<>(queue);//sends queue to iterator class	
		 queue.enqueue(1);//adds values to enqueue
	     queue.enqueue(2);//adds values to enqueue
	     queue.enqueue(3);//adds values to enqueue
	     queue.enqueue(4);//adds values to enqueue
	     queue.enqueue(5);//adds values to enqueue
	     queue.enqueue(6);//adds values to enqueue
	     assertEquals(6, iterator.next());//keeps going to next value and checks if iterates the right way 
	     assertEquals(1, iterator.next());
	     assertEquals(2, iterator.next());
	     assertEquals(3, iterator.next());
	     assertEquals(4, iterator.next());
	     assertEquals(5, iterator.next());
	     assertEquals(6, iterator.next(),"GLLIterator Next failed(can possibly be hasNext)");
	    }
}