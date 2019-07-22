# Park

Park is a Parser for the fictitious __Eyement__ programming language.

## Inner workings

Park consists of a top-down parser with an accompanying lexer. The parser uses a stack of symbols, which can be terminal or nonterminal. At each step of the process, the parser asks the lexer for a single token (terminal symbol) and acts upon it accordingly with the elements of the stack.

At the end of the parsing process, Park reports if the analysed code is valid or if an error occured while parsing; whether it be of lexical or syntactical nature. Furthermore, it provides a derivation tree of the code.

### Lexer

The input of the parser is a string of characters which encodes the code to be analysed. The parser actually requires tokens for the analysis and because of this it requires a lexer to obtain them from the given string.

The lexer used in this project is mostly based in Lexy. See [this repository](https://github.com/Heladio-ac/Lexy) for more information.

The lexer is also responsible of advancing through the string, keeping the index of the following character to be read. This index is also called the cursor.

At the beggining of each step, the parser asks the lexer for a token. The lexer transduces through the string beggining at the position of the cursor until it completes a token and then passes it to the parser, moving the cursor one position over with each read character.

### Symbol's Stack

The stack of symbols begins with only two elements: _Program_ and _EOF_, with the former being at the top of the stack. Intuitively this means that Park expects to read a valid Eyement program and then find the end of the file.

After getting a token from the lexer, the parser will compare it with the symbol at the top of the stack. If the top of the stack is a terminal symbol and coincides with the token it will then proceed with the next token.

In the case of a nonterminal symbol, the parser will use the prediction matrix to determine the production rule to use. Then, it will pop the top of the stack and push each derived symbol to it from back to front; so the first symbol of the right hand side of the production rule becomes the top of the stack. Afterwards, the same token is used and the process is repeated until the top of the stack and the token coincide or a syntactical error is found.

### Derivations

...

### Errors

If there are errors in the provided Eyement code, Park will find and report them to the user. This errors may be of different nature: lexical or syntactical. The distinction is made by where the error is found, whether it be in the lexer or the parser.

#### Lexical errors

...

#### Syntactical errors

Even if a valid token is passed by the lexer, the parser may find that the token does not fit within the rest of the program following the syntax of the language. This may occur in two different situations.

##### Non matching terminal symbol

...

In the following example, there is a missing semicolon after the write statement.
~~~
if (A > B)
    write("A is greater than B")
endif;
~~~
In this case, the parser would a read a correct write statement and then expect to see a semicolon following. Instead, it encounters the `endif` reserved word and thus reports that the token does not correspond with the expected one.

##### Invalid derivation

A different kind of syntactical error can occur ...
