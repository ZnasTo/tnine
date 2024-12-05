# tnine
A school project implementing a simplified contact search algorithm.

## Description
`tnine` is a program that simulates a simplified T9 predictive text algorithm to search for contacts.
- **Input:** A sequence of digits provided as the first argument and a list of contacts read from `stdin`.
- **Functionality:** - Matches contacts based on the sequence of digits, interpreting each digit as a key on a phone's numeric keypad.

## Usage 
Example with letters which define that contact is found in uppercase:

### Input data format
```
Name Surname
number
```
### Command Syntax
```
$ ./tnine NUMBER
```
### Output Format 
```
Name Surname, number
```

## Example Usage
### Command Example
The `list.txt` file contains a list of contacts to be searched. Execute the program with the following syntax:

```
$ ./tnine 38 <list.txt
```
### Output Example
Contacts matching the search query (`38`) will be displayed with the matched letters in uppercase for clarity:

```
pETr DVorak, 603123456
bedrich smETana ml., 541141120
```

## Output Explanation
- **Matched Contacts**: Names where the query `38` matches the T9-style mapping are highlighted.
- **Capitalized Letters**: Letters corresponding to the query sequence are shown in uppercase.

