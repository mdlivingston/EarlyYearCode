
********VARIABLES********

Variable Definition:
    Variables are defined using the keyword 'variable'. An optional initializer can be given. The syntax for variable definition is the following:
    variable variable_name()
    variable variable_name(initializer)

Variable Assignment:
    Variables are assigned with the following syntax:
    variable_name = expression
    They can be assigned to a unary or an expression, such as a function call


********FUNCTIONS*********

Function Definition:
    Functions are defined using the keyword 'function'. Their syntax is as follows
    function variable_name(parameters) {
        block
    }

    Any parameters in the function must be variables. The block is a collection of expressions, and the result of the last expression evaluated is the return value for the function.

Function Calls:
    Syntax for function calls:
        variable_name(function_initializerList)

Anonymous Functions:
    Anonymous functions are recognized with the keyword 'anonymous' and can be defined using the following syntax:
    anonymous (parameterList) { 
        block
    }
    This will create a closure just like a regular function definition would, but the defining environment will have no knowledge of its existence unless it is assigned to a variable.
    Anonymous functions can be immediately evaluated with the following syntax:
    (anonymous (parameterList) {
        block
    } (function_initializerList))

********CLASSES********

Classes use the 'class' keyword and are defined as follows:
class class_name {
    class_block
}
The class block can be a collection of variables, objects, and functions.

********OBJECTS********

Objects are instances of classes and are defined with the keyword 'object'.

Object Definition:
    object variable_name(optional_class)
    If the class has a create function, it will automatically be called upon defining the object.

Object Expression:
    object_name.variable
    object_name.function(initializerList)

    Objects within objects can be accessed like so:
    object_name.object_name....

********ARRAYS*********

Arrays can be defined using the keyword 'array'
array variable_name(array_initializerList)

However, an array class has been provided in the library, which allows for neater use of arrays.

********INCLUDES********

Files can be included using the keyword 'include'
    include "file_name.del"

********CONDITIONALS********

If statements use the following syntax:
if(expression) {
    block
}

They can have optional else statements, or else if statements, as such:
if(expression) {
    block
} else if(expression) {
    block
} else {
    block
}

*********LOOPS********

While loops are defined with the syntax:
while(expression) {
    *block*
}

********KEYWORDS********

The following is a list of keywords, which, as such, cannot be redefined:
    variable
    function
    class
    object
    anonymmous
    if
    else
    while
    null
    true
    false

********BUILTINS********

The following is a list of the builtins:
    and(op1 op2)				returns true if both operands are true, false otherwise.
    or(op1 op2)					returns true if one of the operands is true, false otherwise.

    add(op1 op2):				adds the two operands together.
    sub(op1 op2):				subtracts the second operand from the first.
    mult(op1 op2):				multiplies the two operands together.
    div(op1 op2):				divides the first operand by the second. 
    raise(op1 op2):				raises the first operand to the second.

    eq(op1 op2):				returns true if the two operands are equal, false otherwise.
    neq(op1 op2):				returns true if the two operands are not equal, false otherwise.
    greater(op1 op2):			returns true if the first operand is greater than the second, false otherwise.
    less(op1 op2):				returns true if the first operand is less than the second, false otherwise.
    greaterEq(op1 op2):			returns true if the first operand is greater than or equal to the second, false otherwise.
    lessEq(op1 op2):			returns true if the first operand is less than or equal to the second, false otherwise.

    inc(op):					increments the operand and returns it
    dec(op):					decrements the operand and returns it

    print(param ...):			prints the list of parameters to stdout without a new line.
    printLn(param ...):			prints the list of parameters to stdout with a new line at the end.

    appendArray(array item): 	appends the item to the array
    prependArray(array item): 	prepends the item to the array
    displayArray(array): 		displays the array
    getArray(array index):		returns the item at the given index in the array
    setArray(array index val):	sets the item at the given index in the array to the given value
    removeArray(array index):	removes the item at the given index in the array
    sizeArray(array):			returns the size of the array

********LIBRARY*********

A library directory includes basic classes that have already been defined:

    Array.del:
        append(item) - appends the item to the array
        prepend(item) - prepends the item to the array
        get(index) - gets the item at given index
        set(index item) - sets the item at the given index
        remove(index) - removes the given index from the array
        size() - returns the size of the array
        display() - displays the array

    Stack.del:
        push(item) - pushes the item onto the stack
        pop() - pops the top of off the stack
        peek() - peeks at the top of the stack
        size() - returns the size of the stack
        display() - displays the stack

    Dictionary.del:
        insert(key value) - inserts the value into the dictionary based on the key
        lookupKey(key) - looks up the value at the given key
        lookupValue(value) - looks up the key for the given value
        show() - displays the dictionary from smallest key to largest

    AVL.del:
        insert(key value) - inserts the value into the tree based on the key
        lookupKey(key) - lookup the value at the given key
        lookupValue(value) - lookup the key for the given value
        show() - displays the tree using an in-order transversal
