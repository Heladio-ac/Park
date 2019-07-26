# Park

Park is a Parser for the fictitious __Eyement__ programming language.

## Inner workings

Park consists of a top-down parser with an accompanying lexer. The parser uses a stack of symbols, which can be terminal or nonterminal. At each step of the process, the parser asks the lexer for a single token (terminal symbol) and acts upon it accordingly with the elements of the stack.

At the end of the parsing process, Park reports if the analysed code is valid or if an error occurred while parsing; whether it be of lexical or syntactical nature. Furthermore, it provides a derivation tree of the code.

### Lexer

The input of the parser is a string of characters which encodes the code to be analysed. The parser actually requires tokens for the analysis and thus it uses a lexer to obtain them from the string.

The lexer used in this project is mostly based in Lexy. See [this repository](https://github.com/Heladio-ac/Lexy) for more information.

The lexer is also responsible of advancing through the string, keeping the index of the following character to be read. This index is also called the cursor.

At the beggining of each step, the parser asks the lexer for a token. The lexer then transduces through the string beggining at the position of the cursor until it completes a token and passes it to the parser, moving the cursor one position forward with each read character.

### Symbol's Stack

The stack of symbols begins with only two elements: _Program_ and _EOF_, with the former being at the top of the stack. Intuitively this means that Park expects to read a valid Eyement program and then find the end of the file.

After getting a token from the lexer, the parser will compare it with the symbol at the top of the stack. If this symbol is a terminal one and coincides with the token it will then proceed with the following token.

In the case of a nonterminal symbol, the parser will use the prediction matrix to determine the production rule to use. Then, it will replace the symbol with its derivation. Afterwards, the same token is used and the process is repeated until the top of the stack and the token coincide or a syntactical error is found.

### Derivations

The __Eyement__ is a context-free language described by a set of production rules. See `productions.txt`. As such, there exists a relation between the set of nonterminal with a subset of the Kleene closure of the union of terminal and nonterminal symbols. This relation may map a single element of the domain to multiple elements of the range; a nonterminal symbol may derive into different strings.

The parser determines the correct production rule to use by comparing the nonterminal symbol at the top of the stack and the following token extracted from the string. Once the derivation is found, the stack pops the nonterminal symbol and pushes each symbol from the derivation in reverse order; the left-most element of the derivation becomes the top of the stack.

### Errors

If there are errors in the provided Eyement code, Park will find and report them to the user. This errors may be of different nature: lexical or syntactical. The distinction is made by where the error is found, whether it be in the lexer or the parser.

#### Lexical errors

The parser expects a token from the lexer at each step. This token may or may not contain a valid lexeme from the lexicon of the language. The grammeme of the token will reflect this fact. See [Lexy](https://github.com/Heladio-ac/Lexy) for more information on the handling of non valid lexemes.

If the parser receives a token with a grammeme code that signifies a lexical error it will report it to the user and halt the parsing process.

#### Syntactical errors

Even if a valid token is passed by the lexer, the parser may find that the token does not fit within the rest of the program following the syntax of the language. This may occur in two different situations.

##### Non matching terminal symbol

The parser may expect a specific terminal symbol and find a different one extracted from the string.

In the following example, there is a missing semicolon after the write statement.
~~~
if (A > B)
    write("A is greater than B")
endif;
~~~
In this example, the parser would read a correct write statement and then expect to see a semicolon following. Instead, it encounters the `endif` reserved word and thus reports that the token does not correspond with the expected one.

##### Invalid derivation

A different kind of syntactical error happends when not a specific token is expected but a language construction (subset of strings of the language) is.

In the following example, there is a statement inside the conditional of an if statement. Regularly there would be an expression.
~~~
if (write('Hello world'))
    ...
endif;
~~~
In this example, the parser expects an expression to be inside of the conditional but finds the `write` reserved word which corresponds with the beggining of a statement. The parser finds no production rules that fits with this occurrence and reports a syntax error.
