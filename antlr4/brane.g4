grammar brane;

NEWLINE : [\r\n]+ -> skip;
COMMENT : '//'(.*?)[\r\n(EOF)] -> skip;
SPACE   : (' '|'\t') -> skip;

INT     : [0-9]+;
FLOAT   : INT('.'([0-9]*))?'f';
STRING  : '"'.*?'"';

ID      : [a-zA-Z_]([a-zA-Z0-9_]*);

MUL     : '*';
DIV     : '/';
ADD     : '+';
SUB     : '-';

program     : (statement+ EOF | EOF);
statement   : function
            | preprocessor NEWLINE
            ;
argumentList: declaration (',' declaration)*;
function    : type=ID id=ID '(' arguments=argumentList? ')' '{' expressions=exprList '}'
            ;
preprocessor: '#include' content=.*? NEWLINE                                #include;
exprList    : (expression ';')*;
expression  : INT                                                           #constInt
            | FLOAT                                                         #constFloat
            | STRING                                                        #constString
            | ID                                                            #id
            | left=expression op=(MUL | DIV) right=expression               #muldiv
            | left=expression op=(ADD | SUB) right=expression               #addsub
            | '(' expression ')'                                            #inlineScope
            | '{' expression '}'                                            #scope
            | dest=expression '=' expr=expression                           #assignment
            | declaration                                                   #decl
            | 'return' expression                                           #returnVal
            | 'return'                                                      #returnVoid
            ;
declaration : type=ID id=ID
            ;