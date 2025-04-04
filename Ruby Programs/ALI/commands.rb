# commands.rb
class Command #command class
  def initialize(ali)#intiliazes command class
    @ali = ali
    @opcode = ''
    @symbol = ''
  end

  def execute #will be defined in other sub classes
  end
  attr_reader :opcode #reader method for opcode

end#end of command

class LDA < Command #creates LDA subclass that loads value of object into the accumulator
  def initialize(ali, symbol)#intializes class
    super(ali) #calls super class
    @symbol = symbol #assigns the symbol
  end

  def execute
    address = @ali.instructionHash[@symbol] #gets the address of the symbol/variable
    if address #makes sure we fine a address
      @ali.accumulator = @ali.memory[address ]
      @ali.ZeroBit = (@ali.accumulator == 0) ? true : false #sets the zero bit accordingly
      @opcode = 'LDA'
      puts "Executed opcode: #{@opcode}" # Print opcode
    else
      puts "Error: Symbol '#{@symbol}' not found." #else gives error saying object they want to load wasn't found.
    end
  end

end #end of LDA

class STR < Command #store subclass with a command that stores our objects into memory with value
  def execute(symbol) #execute function that stores our object
    address = @ali.instructionHash[symbol] #gets the address of the object
    @ali.memory[address] = @ali.accumulator #stores the accumulator value into the address
    @opcode = 'STR'
    puts "Executed opcode: #{@opcode}" # Print opcode

  end
end #end of STR

class ADD < Command #ADD subclass that adds the accumulator and data register values
  def initialize(ali)
    super(ali)#calls super class
  end

  def execute
    dataRegister = @ali.DataRegister #gets data register value
    result = @ali.accumulator + dataRegister #adds the accumulator and register
    if result > 32767 || result < -32768 #makes sure no overflow happens
      puts "OVERFLOW ADDING DIDNT HAPPEN"
      return
    end
    @ali.accumulator = result #stores the sum into the accumulator
    @ali.ZeroBit = (@ali.accumulator == 0) ? true : false #sets the zero bit accordingly
    @opcode = 'ADD'
    puts "Executed opcode: #{@opcode}" # Print opcode
  end
end #end of ADD

class SUB < Command # creates subclass SUB that includes subtraction command that subtracts the accumulator with the data register
  def initialize(ali, symbol)
    super(ali)#calls super class
    @symbol = symbol
    @opcode = 'SUB'
  end

  def execute
    puts "Executed opcode: #{@opcode}" # Print opcode
    dataRegisterAddress = @ali.instructionHash[@symbol] #gets address of the object/symbol
    if dataRegisterAddress.nil? #makes sure its found
      puts "Error: Symbol '#{@symbol}' not found."
      return
    end
    dataRegisterValue = @ali.memory[dataRegisterAddress] #stores the dataRegister value
    result = @ali.accumulator - dataRegisterValue #gets the difference
    if result > 32767 || result < -32768 #checks for overflow
      puts "OVERFLOW SUB DIDNT HAPPEN."
      return
    end
    @ali.accumulator = result #else stores the difference
    @ali.ZeroBit = (@ali.accumulator == 0) #checks zero bit accordingly
  end
end #end of SUB

class XCH < Command #creates XCH subclass that swaps the value of accumulator into data register.
  def execute
    @opcode = 'XCH'
    puts "Executed opcode: #{@opcode}" # Print opcode
    temp = @ali.accumulator #stores accumulator value into a temp
    @ali.accumulator = @ali.DataRegister
    @ali.DataRegister = temp #swaps values
  end
end#end of XCH

class JMP < Command # creates subclass Jump that jumps to the line wanted
  def initialize(ali, address)
    super(ali)  #calls super class
    @address = address #stores address
  end

  def execute
    @opcode = 'JMP'
    puts "Executed opcode: #{@opcode}" # Print opcode
    @ali.ProgramCounter = @address - 1 #sets program counter so it jumps to instruction line wanted
  end
end#end of JMP

class JZS < Command #creates jump if zero subclass that jumps to a line instruction depending on sign bit
  def initialize(ali, address)
    super(ali) #calls superclass
    @address = address - 1
  end

  def execute
    @opcode = 'JZS'
    puts "Executed opcode: #{@opcode}" # Print opcode
    if @ali.ZeroBit #checks if its a zero bit
      @ali.ProgramCounter = @address - 1  #sets counter so it jumps to line it wants too
    end
  end
end #end of JFS

class HLT < Command #halt subclass the stops the program
  def execute
    @ali.halted = true #assigns true so program wont run anymore
    @opcode = 'HLT'
    puts "Executed opcode: #{@opcode}" # Print opcode
  end


end #end of HLT