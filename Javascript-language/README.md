<div align="center"><h1>This is the Javascript version of the Battering-Ram</h1></div>

## How to use it?
The lib has some main functions that gives all the functionality of the bruteforce idea.
  ### Explaning the main functions
  The battering_ram class is the main structure of the library, it has a constructor that accept some boolean values, basically to enable and disable the chars types that will be used on the algorithm
  ```js
  constructor(enable_upper_case, enable_lower_case, enable_symbols, enable_numbers);
  ```
  <br/>
  
 The set_start_value is a method that will put a default value in the Battering-Ram data space, all next's values will be started from there,if not used then the first value will be defined by the class constructor looking for  compatibility with the chars config
  ```js
  set_start_value(initial_value);
  ```
   <br/>
  
The set_end_value function will set a max value to the algorithm, the main function will gives a flag which alerts you that the program reached the end, if not used the program never alerts you and probally will run forever.
```js
set_end_value(end_value);
```
<br/>
  

The get_next_sequence is the main function of the library, this will always get next next logical sequence of chars and put in a buffer that can be caught after. if set_end_value used then this function will return False when reached the target, if not then will always return True
```js
get_next_sequence();
```
<br/>  

The get_data function is the complement of the previous function, after of get_next_sequence you can use get_data to fetch the results
```js
get_data();
```
<br/>

## Simple Battering-Ram structure

Example:
```js
const battering_ram = require("./../battering_ram").battering_ram;

let my_object = new battering_ram(false, false, false, true);

let current_data = "";

do {
  current_data = my_object.get_data();
  if (current_data == "4346") {
    console.log("Gotcha!");
    break;
  }
  else {
    console.log(current_data);
  }
} while (my_object.get_next_sequence());
```
The output of the program above is:
```txt
1
2
3
4
5
6
...
...
...
4338
4339
4340
4341
4342
4343
4344
4345
Gotcha!
```
