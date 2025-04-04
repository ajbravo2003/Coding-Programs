class ALI
  ProgramMemory = 128 #declares program memory and other memories based on requirements
  DataMemory = 128
  Memory = 256
  attr_accessor :memory, :accumulator, :DataRegister, :ProgramCounter, :ZeroBit, :instructionHash, :halted #gets getters for our data members

  def initialize#intiliazes our data members
    @memory = Array.new(Memory, 0) #creates a new array with the memory wanted
    @DataRegister = 0
    @accumulator = 0 #sets data all to 0
    @ProgramCounter = 0
    @opcode = ''
    @ZeroBit = false #starts with false on zero bit
    @instructionHash = {} #stores all of the variables declared
    @halted = false #sets halted to false
    @counter = 0 #to check if it does more than 1000 instructions
  end #end of initialize
  
  def allocateData #function to allocate memory for objects
    (DataMemory...Memory).each do |i| #traverses through memory array and checks if the current position is occupied
      return i unless @instructionHash.value?(i) #tries to find an unoccupied position
    end
    "Error: No available data memory" #else no space is available
  end

  def ReadFile(filename) #function to read in the instructions assuming its in correct format
    File.open(filename, 'r') do |file| #opens file to read
      file.each_with_index do |line, index|
        break if index >= ProgramMemory #stops reading in if it exceeds our program memory
        @memory[index] = line.strip #stores line into memory
      end
    end
  end #end of ReadFile

  def userLoop #takes user loop to either step or do all instructions at once
    command = ''
    puts "Welcome to my ALI interpreter:"
    while command != 'q' #keeps looping until user exits
      puts " Enter a command:
      a - Run all instructions at once:
      s - Step into next instruction
      q - Exit"
      command = gets.chomp #takes user input
      if command == 's' #checks if user wants to step
        executeLine #only runs one line
      elsif command == 'a' #checks if user wants to do all instructions
        executeAll #runs all instructions
      elsif command == 'q' #checks if user wants to quit
        puts "Exiting..."
        break
      else
        puts "INVALID INPUT. Enter only 'a','s', or 'q'"
      end
    end
  end #end of userLoop


  def executeLine #function that handles our 's' command
    return puts "Program has halted." if @halted #checks if program is halted before we try to execute line
    instruction = @memory[@ProgramCounter] #gets current instruction
    puts "Executing instruction at line=#{@ProgramCounter}:"
    executeInstruction(instruction) #runs only one instruction
    @ProgramCounter += 1 #adds 1 to counter
    @counter+=1
    printData #prints info of current memory
  end#end of executeLine

  def executeAll #function that handles 'a' command
    while @ProgramCounter < ProgramMemory && !@halted #makes sure we dont pass our program memory and that program has not halted
      @counter+=1
      if @counter >= 1000
        puts "want to continue enter y or n?"
        input = gets.chomp
        if input == 'n'
          @halted = true

        else input == 'y'
           @counter = 0
        end
      end
      instruction = @memory[@ProgramCounter]#gets instruction at current index
      executeInstruction(instruction)#executes the instruction
      @ProgramCounter += 1 #adds to counter to go to next instruction
    end
    printData #prints info of current memory
  end #end of executeAll

  def executeInstruction(instruction) #function to handle our instructions
    parts = instruction.split #splits the line between instruction and variable/number
    command = parts[0] #instruction will always be first
    if command == 'DEC' #checks if instruction is DEC
      variable = parts[1] #takes the variable name
      address = allocateData #creates a space in memory
      @instructionHash[variable] = address #assigns variable to the next address
      puts "Executed opcode: DEC" #printsOpcode only for this and LDI


    elsif command == 'LDA' #checks if command is LDA
      LDA.new(self, parts[1]).execute  #calls load command and passes the variable name of object wanted to load

    elsif command == 'LDI' #checks if command is LDI
      @accumulator = parts[1].to_i #loads integer into accumulator
      puts "Executed opcode: LDI" #prints opcode


    elsif command == 'STR' #checks if command is STR
      STR.new(self).execute(parts[1]) #calls store command and passes symbol name of what we want to store

    elsif command == 'ADD'
      ADD.new(self).execute  # No additional parameters needed

    elsif command == 'SUB'
      SUB.new(self, parts[1]).execute  # Pass the symbol to SubCommand

    elsif command == 'XCH' #checks if command is XCH
      return XCH.new(self).execute #calls X

    elsif command == 'JMP' #check if command is JMP
      JMP.new(self, parts[1].to_i).execute #calls jump command and passes the line number we want to jump too

    elsif command == 'JZS' #check if command is JZS
      JZS.new(self, parts[1].to_i).execute #calls jump if zero command and passes line number to jump too

    elsif command == 'HLT' #check if command is HLT
      HLT.new(self).execute #calls halt command

    else #anything else as instruction will lead to error
      puts "ERROR: #{command}"
    end
  end #end of executeInstruction

  def printData #function to prints all our important data
    puts "Accumulator: #{@accumulator}"
    puts "Data Register: #{@DataRegister}"
    puts "Program Counter: #{@ProgramCounter}"
    puts "Zero Bit: #{@ZeroBit}"
    puts "Memory: #{@memory[0...DataMemory]}"
    puts "Data Memory: #{@memory[DataMemory...Memory]}"
  end #end of printData

end #end of class ALI
