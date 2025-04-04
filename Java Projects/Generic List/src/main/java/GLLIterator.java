import java.util.Iterator;
public class GLLIterator<E>implements Iterator<E> {
	 private GenericQueue<E> queue;//private queue variable to acess the list
	    public GLLIterator(GenericQueue<E> queue){//default constructor that sets the queue
	        this.queue = queue;
	    }
	    
	    @Override
	    public boolean hasNext(){//has next function
	        return queue.getLength()!= 0;//keeps returning true till length is 0
	    }

	    @Override
	    public E next(){//next function returns next value
	        if (!hasNext()){//checks if there is another value
	            return null;
	        }
	        return queue.dequeue();//returns value data and deletes the value
	    }
}
