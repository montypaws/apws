*************************************
Author - Mufaddal Makati			|
Website - http://www.rawbytes.com   |
*************************************
#Description -
An Algorithm and C program that finds out for any string that is twisted and tangled, if it will form a Knot or not when its two ends are stretched. The problem originally appears here.
The input will consist of a diagram of one single continuous string described in a two-dimensional grid of characters such as shown above. The
‘-’ and ‘|’ characters represent a horizontal and vertical segment of the string, respectively. ‘+’ characters represent corners where the string turns at right angles on the table. ‘I’ or ‘H’ characters represent locations where parts of the strings cross:
‘H’ represents locations where the horizontal string passes over the vertical string
‘I’ represents locations where the horizontal string passes under the vertical string
The dot character, ‘.’, obviously,represents empty spaces of the table unoccupied by the string. Two horizontally adjacent non-empty spaces of the table are connected by the string iff neither of them are ‘|’ characters. Similarly, vertically adjacent non-empty spaces are connected by the string iff neither of them are ‘-’ characters. Inputs will be such that every ‘+’ character will represent a proper corner where the string turns at a unambiguously at a right angle: formally, every ‘+’ character will be connected to exactly one vertically adjacent and exactly one horizontally adjacent space. Moreover, to further simplify matters, you can assume that the only characters along the border of the given diagram, other than dots, will represent endpoints of the string. In short,the input will unambiguously specify a valid piece of string starting and ending at the border of the input diagram. Finally, assume that the string has negligible width and is made of a very smooth material, so that parts of the string can easily slide over each other with negligible friction.
I have written the solution to this problem in C programming language. It can be compiled on any linux platform. The input file is apws.in. Also included another input file named apws (2).in as an alternative input.
The apws.in file serves as an input file which the program will use. Make sure to put both – the source file and the apws.in file in the same directory. 