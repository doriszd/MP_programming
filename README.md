### Multi-paradigm programming

##### Shop Assignment

##### Student: Doris Zdravkovic

----------------------------------------------------------


The aim of this assignment is to bulid on the shop programme provided by the professor
and to add additional functionality. 

Functionality that the shop programme should have is:

1. The shop CSV should hold the initial cash value for the shop

2. Read in customer orders from a CSV file. The file should include all the products
they want to buy and the quantity, and it should also include their name and their budget.

3. the shop should be able to process the orders of the customer.

4. It should operate in live mode. User can enter a product by name, specify a quantity,
and pay for it. The user should be able to buy more products.



There will be 3 different programmes. The above described functionality should be completed
in Python and C language. These 2 programmes will be done in procedural programming style.
The second part of the assignment involves replicating the functionality of the shop
programme in Object - oriented style. This will also be performed in Python language. 
The last part of this assignment consists of a report that explains and analyses similarities and
differences of programming languages (Python and C) and styles (procedural and object - orijented).

-------------------------------------------------------------------------------------------------

#### Procedural Programming


The procedural programming model is derived from structured programming and also uses selection, repetition,
and sequences. Procedural programming uses procedures to instruct the computer what to do in a series of steps.
These procedures can also be referred to as functions, routines, or subroutines. A program or any part of it can
call any routine at any time during its execution. Procedural programming is also referred to as "inline programming", 
and it takes a top-down approach to execute instructions and solve problems. A simple program that calls any number 
of routines for different operations can be said to use a procedural programming approach. [1]


#### Object-orientated programming

Object-oriented programming, also known as OOP, is an approach to problem-solving where all computations use objects.
An object is a component of a program that knows how to perform certain actions and how to interact with other elements of 
the program. Objects are the basic units of object-oriented programming. A simple example of an object would be a person. 
Name of a person would be considered a their property while walking would be considered a method of the person.
A method in object-oriented programming is like a procedure in procedural programming. The key difference here is that the 
method is part of an object. In object-oriented programming, you organize your code by creating objects, and then you can give
those objects properties and you can make them do certain things.

A key aspect of object-oriented programming is the use of classes. A class is a blueprint of an object. You can think of a class
as a concept and the object as the embodiment of that concept. So, let's say you want to use a person in your program. You want 
to be able to describe the person and have the person do something. A class called 'person' would provide a blueprint for what a 
person looks like and what a person can do. Examples of object-oriented languages include C#, Java, Perl and Python.[2]


----------------------------------------------------------------------------------------------------------------------------------

#### Similarities and differences in procedural and object oriented programming

When you compare Python procedural and Python OOP style you can see some differences although the language is the same. With procedural style 
we break a problem into function and each function does one task. When we run the programme our main program is a series of calls to the 
different functions. In shop case in Python procedural style functions or methods are firstly written separately and then called in the main 
function when needed. For example, display_menu function. Whereas in OOP programme starts by making a class that contains specific information.  
In shop case class Product contains information about its name and price. Once classes are defined we need to write what operations need to happen 
on the data. These are called methods. Once we have everything defined we can create objects. When you create and object they have all of the attributes 
and methods defined in their class. .__init__ is a reserved function in Python that is invoked when an object of a class is created. We can also pass 
arguments to the __init__ method to initialize data members of different objects with unique values.[3] In shop example this is __init__ function with 
parameters: 

def__init__(self,name,price=0):
self.name = name	
self.price = price	
	
When we talk about similarities in OOP and procedural programming style it is obvious that Python OOP and procedural is more similar than procedural style
in C.  The same syntax can be used in OOP and procedural style in Python  such as the use of if __name__=”main”: Indicating the execution of the code. 
This is expected as we are talking about the same language, but still few adjustments should be made for calling functions. For example in the OOP shop 
code each class has a def__repr__function that prints the representation of the object. [4]

To conclude, both programming languages have pros and cons. The important thing is to know in which situation to chose which language. Although C wouldn’t 
be my first choice because of its complexity it is widely used in industry in the development of firmware and mobile systems where high speed and high 
performance are very important. Python, on the other hand, is more common to be used in Data Science and related disciplines. 





---------------------------------------------------------------------------------------------------------------------------------------

References:

-[1] https://www.makeuseof.com/object-oriented-programming-vs-procedural-programming-what-makes-them-different/
-[2] https://study.com/academy/lesson/object-oriented-programming-vs-procedural-programming.html
-[3] http://theteacher.info/index.php/algorithms-and-problem-solving-2/problem-solving-and-programming/programming-techniques/object-oriented-techniques/4055-object-oriented-versus-procedural-languages-using-python
-[4] https://www.geeksforgeeks.org/difference-between-c-and-python/








