=begin
/**------------------------------------------
//  Project 1 - Set Calculator
    Course: CS 474, Fall 2024.
    System: RubyMine 2024
    Author: Alejandro Bravo
---------------------------------------------**/
=end
class DoubleSet #super class double set
  attr_accessor :X, :Y #creates getters and setters

  def initialize #intiliazes our double set class data members
    @X = nil
    @Y = nil
  end #end of initialize

  def displayMenu #function to display menu for user
    puts "Enter the exact letter for the operation you want to do: \n"
    puts "X -> This command takes a comma-separated list of numeric arguments denoted by values for set X and is stored as a BST."
    puts "Y -> This command takes a comma-separated list of numeric arguments denoted by values for set Y and is stored as an array."
    puts "m -> This command takes a string as an argument a one-argument lambda expression in correct Ruby syntax as a string. And applies to every element in set X"
    puts "a -> This command takes a numeric argument. The number is added to set X."
    puts "u -> This command takes the set union of X and Y and stores the result as X."
    puts "i -> This command takes the set intersection of X and Y and stores the result as X."
    puts "x -> This command swaps the sets associated with X and Y, meaning that X will receive the previous content of Y set and vice versa."
    puts "l -> The content of the two sets are displayed on the console."
    puts "c -> The content of X is copied into Y."
    puts "q -> Exit the calculator"
  end #end of display menu

  def intersection #function to find the intersection for command i
    x_values = @X.is_a?(BranchingSet) ? @X.bstTraversal : @X.return_array #gets elements of set X
    y_values = @Y.is_a?(BranchingSet) ? @Y.bstTraversal : @Y.return_array #gets elements of set Y
    intersecting_values = x_values & y_values # gets the intersection between sets

    if @X.is_a?(BranchingSet) #checks if branching set
      intersecting_set = BranchingSet.new
      intersecting_values.each { |val| intersecting_set.insert(val) }
      @X = intersecting_set  #stores intersection as branched set
    elsif @X.is_a?(ArrayedSet) #checks if X is arrayed set
      intersecting_set = ArrayedSet.new
      intersecting_values.each { |val| intersecting_set.insert(val) }
      @X = intersecting_set #stores intersection as arrayed set
    end
  end#end of intersection

  def display#function to display content of set X and Y
    if @X.nil? #checks to see if set x is empty
      puts "Set X: Empty"
    else
      puts "Set X (#{@X.class}): " + (0...(@X.is_a?(BranchingSet) ? @X.bstTraversal.size : @X.return_array.size)).map { |i| @X[i] }.to_s #prints sets using [] operator and based on set X type
    end

    if @Y.nil? #checks to see if set Y is empty
      puts "Set Y: Empty"
    else
      puts "Set Y (#{@Y.class}): " + (0...(@Y.is_a?(BranchingSet) ? @Y.bstTraversal.size : @Y.return_array.size)).map { |i| @Y[i] }.to_s #prints sets using [] operator and based on set Y type
    end
  end #end of display

  def copy #function to copy content of set X into set Y
    Marshal.load(Marshal.dump(self))
    # if @X.is_a?(BranchingSet) #check if X is a BranchingSet
    #   @Y = BranchingSet.new #create a new BranchingSet for Y
    #   copy_bst(@X, @Y) #copy values and structure from X to Y
    # elsif @X.is_a?(ArrayedSet) #check if X is an ArrayedSet
    #   @Y = ArrayedSet.new #create a new ArrayedSet for Y
    #   @X.return_array.each { |value| @Y.insert(value) } #copy values from Array to Y
    # end
  end#end of copy

  def copy_bst(setX, setY) #helper function to transfer content of bst set X into set Y
    source_values = setX.bstTraversal #gets the values
    source_values.each { |value| setY.insert(value) } #inserts each value into the new BST
  end#end of copy_bst

  def swap_sets #function to swaps the sets types
    temp = @X
    @X = @Y
    @Y = temp
  end #end of swap_sets

  def union #function to find the union between X and Y
    if @X.is_a?(BranchingSet) && @Y.is_a?(ArrayedSet) #checks to see if X is BST and Y is an array
      @Y.return_array.each do |value| @X.insert(value) unless @X.bstTraversal.include?(value) end

    elsif @X.is_a?(ArrayedSet) && @Y.is_a?(BranchingSet) #checks if X is an array and Y is a BST
      @Y.bstTraversal.each do |value| @X.insert(value) unless @X.return_array.include?(value) end
    end
  end #end of union class
end #end of double set class

class BranchingSet < DoubleSet #subclass for BST
  class Node #a Node class to make BST
    attr_accessor :value, :left, :right # creates our getters and setters
    def initialize(value) # initializes our node
      @value = value #stores integer value
      @left = nil
      @right = nil
    end #end of initialize
  end#end of class node

  def initialize # initializes our class BranchingSet
    super() #calls super class
    @root = nil #initiliazes root node
  end #end of initialize

  def insert(value) #inserts value in BST
    @root = insertNode(@root, value)
  end#end of insert

  def insertNode(node, value) #insters node into the BST and sorts
    return Node.new(value) if node.nil? #returns if duplicate item
    if value < node.value #checks if its lower then current node value
      node.left = insertNode(node.left, value) #moves to next left node
    elsif value > node.value #checks if its higher then current node
      node.right = insertNode(node.right, value) #moves to next right node
    end
    node #returns the node
  end #end of insert node

  def bstTraversal
    traverse(@root)
  end

  def traverse(node) #function to traverse through the nodes
    return [] if node.nil? #returns empty array if there is no elements in node
    traverse(node.left) + [node.value] + traverse(node.right) #collects all left values of tree and all right values of tree
  end #end of traverse

  def [](index) #helper function to help display elements using [] operator
    bstTraversal[index] #returns the element at the given index
  end

end #end of branching set class

class ArrayedSet < DoubleSet #sub class ArrayedSet for arrays set
  def initialize
    super()#calls super class
    @array_elements = [] #creates a data member to store elements
  end

  def insert(value)
    return if @array_elements.include?(value) #returns to make sure we don't add duplicates
    @array_elements.push(value) #pushes into the array
    @array_elements.sort! #sorts array
  end #end of insert

  def return_array
    @array_elements #returns array elements
  end

  def [](index) #helper function to help display elements using [] operator
    @array_elements[index] #return the element at the given index
  end#end of [] operator function

end #end of ArrayedSet class

def main #main function to run user inputs and call other functions
  userCalculator = DoubleSet.new #creates new double set instance
  puts "Hello, Welcome to Set Calculator \n"
  userCalculator.displayMenu #displays menu for user
  userInput = gets.chomp #takes user input
  while userInput != 'q' #while loop to handle user inputs

    if userInput == 'X' #checks if user input is X
      puts "Enter numeric values for set X seperated by a comma: "
      user_numbers = gets.chomp # gets user numbers
      values = user_numbers.split(',').map(&:to_f) #gets values and splits them from commas
      userCalculator.X = BranchingSet.new #creates a new branching set for X
      values.each {|value| userCalculator.X.insert(value)} #inserts values into BST
      puts "Created BST Set X with values: #{userCalculator.X.bstTraversal}" #prints out values

    elsif userInput == 'Y' #checks if user input is Y
      puts "Enter numeric values for set Y seperated by a comma: "
      user_numbers = gets.chomp #gets user numbers
      values = user_numbers.split(',').map(&:to_f) #gets values and splits them from commas
      userCalculator.Y = ArrayedSet.new #creates a new arrayed set for Y
      values.each { |value| userCalculator.Y.insert(value) } # Insert values
      puts "Created Arrayed Set Y with values: #{userCalculator.Y.return_array}" #prints out array

    elsif userInput == 'm' #checks if input is m
      puts "Enter a lambda expression in correct ruby format for set X"
      lambda_input = gets.chomp #takes user lambda expression
      lambda_expr = eval(lambda_input) #makes sure its a correct input
      current_values = userCalculator.X.is_a?(BranchingSet) ? userCalculator.X.bstTraversal : userCalculator.X.return_array #gets values from set x
      new_values = current_values.map { |val| lambda_expr.call(val) } #applies lambda expression to values
      if userCalculator.X.is_a?(BranchingSet) #checks if x is branching set
        userCalculator.X = BranchingSet.new
        new_values.each { |val| userCalculator.X.insert(val)}
      elsif userCalculator.X.is_a?(ArrayedSet) #checks if x is an arrayed set
        userCalculator.X = ArrayedSet.new
        new_values.each { |val| userCalculator.X.insert(val) } #inserts the value
      end
      puts "Set X with new values: #{userCalculator.X.is_a?(BranchingSet) ? userCalculator.X.bstTraversal : userCalculator.X.return_array}" #prints out new updated values

    elsif userInput == 'a' #checks to see if user input is a
      puts "Enter a number to add to set X: "
      user_number = gets.chomp #gets user input
      if userCalculator.X.is_a?(BranchingSet) #checks if its a branching set
        userCalculator.X.insert(user_number.to_f) #adds value to BST
        puts "Set X with new added number: #{userCalculator.X.bstTraversal}" #prints the set traversing the BST
      elsif userCalculator.X.is_a?(ArrayedSet)#checks if its arrayed set
        userCalculator.X.insert(user_number.to_f) #inserts number into the arrayed set
        puts "Updated Set X with number: #{userCalculator.X.return_array}" #prints out array elements
      end

    elsif userInput == 'u' #checks to see if u is the input
      userCalculator.union #calls union function
      if userCalculator.X.is_a?(BranchingSet) #checks if its a branching set
        puts "Updated Set X after union: #{userCalculator.X.bstTraversal}" #displays X set by traversing the BST
      elsif userCalculator.X.is_a?(ArrayedSet) #checks if its a arrayed set
        puts "Updated Set X after union: #{userCalculator.X.return_array}" #displays X set by printing elements in array
      end

    elsif userInput == 'i'#checks if user input is i
      userCalculator.intersection #calls intersection function
      if userCalculator.X.is_a?(BranchingSet)#checks if X is a Branching set
        puts "Updated Set X after intersection: #{userCalculator.X.bstTraversal}" #displays X set by traversing the BST
      elsif userCalculator.X.is_a?(ArrayedSet)#checks if X is a ArrayedSet
        puts "Updated Set X after intersection: #{userCalculator.X.return_array}" #displays X set by printing elements in array
      end

    elsif userInput == 'x'#checks if user input is x
      puts "Before swap:"
      userCalculator.display #displays sets
      userCalculator.swap_sets #calls swap sets function
      puts "After swap:"
      userCalculator.display #displays new sets when swapped

    elsif userInput == 'l' #checks if user input i
      userCalculator.display #displays the contents of both sets

    elsif userInput == 'c' #checks if user inputs c
      userCalculator.Y = ArrayedSet.new #creates a new branching set for X
      userCalculator.Y = userCalculator.Y.copy #calls the copy method
      # puts "Copied Set X into Set Y."
      # if userCalculator.Y.is_a?(BranchingSet)#checks if X is a Branching set
      #   puts "Updated Set Y after copy: #{userCalculator.Y.bstTraversal}" #displays Y set by traversing the BST
      # elsif userCalculator.Y.is_a?(ArrayedSet)#checks if X is a ArrayedSet
      #   puts "Updated Set Y after copy: #{userCalculator.Y.return_array}" #displays Y set by printing elements in array
      # end

    else #user doesnt pick a correct command
      puts" PLEASE ENTER A CORRECT COMMAND"
    end #end of if statements
    userCalculator.displayMenu #keep displaying menu
    userInput = gets.chomp #takes user input until q is pressed
  end #end of while loop
  puts "Exiting...Thanks For Playing!"
end#end of main function
main #runs main function