# Shuffle Me

## Prerequisites

### Qt

Qt framework for c++ must installed.
To do so:
`sudo apt install qt5-default`

## Build

`make`

## CSV file

The file must be exported as a CSV file separated with `;`
The filename must be `words.list`
For a pair of question and answer, it follows this structure: `question;answer`
1) question:
    It is the text showed for the question
2) answer:
    It is the answer of the question

## Manual

### Run the program
You can run it by default ./shuffle_me. It will look for the default file which
is `words.list`.
Or you must add the -f options if you want to use a specific csv file:
`./shuffle_me -f filename.csv`


### Add
Add a pair of question and answer. Type the question first, then the answer

### Next
Go to the next question

### Show/Hide answer
Show or hide the answer. The answer is automatically hid when the user goes to the next question

### Exit
Exit the program
