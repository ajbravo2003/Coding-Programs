import java.util.Iterator;
public class GenericQueue<T> extends GenericList<T> {
    private Node<T> tail;//private tail variable
    public GenericQueue(T data) {
    	 super();//calls generic list constructor
         setLength(1);//sets length to 1
         Node<T> tempNode = new Node<>(data);//makes a new node with data member
         setHead(tempNode);//sets node as the head 
         tail = tempNode;//sets node to the node as well since only one node
    }
    
    public GenericQueue(T data, int code) {
   	 super();//calls generic list constructor
        setLength(1);//sets length to 1
        Node<T> tempNode = new Node<>(data);//makes a new node with data member
        setHead(tempNode);//sets node as the head 
        getHead().code = code;//sets head value to code
        tail = tempNode;//sets node to the node as well since only one node
   }
    
    void add(T data){//add function that adds to the list at the end
        Node<T> newNode = new Node<>(data);//creates node
        if (getHead() == null) {//checks if there are nodes
            setHead(newNode);//sets head as the node
            tail = newNode;//sets tail as node
            setLength(getLength() + 1);//adds one to the length
        } 
        
        else {//when more then one node
            tail.next = newNode;//adds node to end 
            tail = newNode;//sets the new tail as node since it moves to back of list
            setLength(getLength() + 1);//adds one to the length
        }
    }

    void add(T data, int code){//add function overloader that will be used to add hashcodes
        add(data); //adds node with value
        tail.code = code;//sets code value to tail
    }

    public T delete(){//function that deletes end node and returns its value
        if (getLength() == 0) {//checks if there is any nodes already
            return null;
        }

        else if (getLength() == 1) {//checks if theres only one node which is head
        	T data = getHead().data;//gets the data of it
            setHead(null);//sets head to null since it will be deleted
            tail = null;//tail is also null
            setLength(0);//sets length to 0 since no more nodes
            return data;//returns the data of deleted head
        }
        
        else {//when more then one node
        	Node<T> tempNode = getHead();//gets head of node
        	T data = tempNode.data;//gets first values data
        	setHead(tempNode.next);
        	setLength(getLength() - 1);//subtracts 1 to length
        	return data;//returns deleted value data
        }
    }

    public void enqueue(T data){//function that adds to end of list
        add(data);//calls add function and makes node with data value
    }

    public T dequeue(){//deletes last node of list
        return delete();//calls delete and returns deleted node value 
    }
    
    @Override
	public Iterator<T> iterator() {
		return new GLLIterator(this);
	}
}
