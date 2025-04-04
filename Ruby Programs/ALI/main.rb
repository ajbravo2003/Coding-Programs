=begin
/**------------------------------------------
//  Project 2 - Assembly Language Interpreter
    Course: CS 474, Fall 2024.
    System: RubyMine 2024
    Author: Alejandro Bravo
---------------------------------------------**/
=end
require_relative 'ali'
require_relative 'commands'
ali = ALI.new #creats a new class ALI object
puts "Enter the filename of the SAL program: " #asks user for filename
filename = gets.chomp #takes user input
ali.ReadFile(filename)#file is broken down
ali.userLoop#calls user loop to start running
