import java.util.ArrayList;
import java.util.Iterator;
public class HMIterator<T> implements Iterator<T>{//creates hmi iterator
		private ArrayList<GenericQueue<T>> map;//to access map
	    private int index;//index variable
	    private Iterator<T> queueIterator;//queue iterator
	    public HMIterator(ArrayList<GenericQueue<T>> map){//default constructor
	        this.map = map;//takes map
	        this.index = 0;
	        this.queueIterator = null;//sets iterator to null
	    }
	    
	    private Iterator<T> queueIterator() {
	        while (index < map.size()){//makes sure index doesnt go past 10
	            GenericQueue<T> queue = map.get(index);//gets queue at index
	            if (queue != null && queue.getLength()!=0) {//makes sure queue isnt full
	                return queue.iterator();//returns iterator for the queue
	            }
	            index++;//increments the index
	        }
	        return null;//returns null when theres no more values in queue
	    }

	    @Override
	    public boolean hasNext(){//overrides has next function 
	        while (index < map.size()){//makes sure it's in bounds
	            if (queueIterator == null || !queueIterator.hasNext()){//checks to make sure the queue isnt null
	                queueIterator = queueIterator();//gets queue iterator
	            }

	            if (queueIterator != null && queueIterator.hasNext()){//checks if queue has other value
	                return true;
	            }
	        }
	        return false;//returns false when theres no more values
	    }

	    @Override
	    public T next(){//next function that returns value
	        if(!hasNext()){//checks to make sure queue has values
	            return null;//returns null when it doesnt have any values
	        }
	        return queueIterator.next();//returns value
	    }
}
