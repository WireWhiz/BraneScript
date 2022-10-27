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
function    : type=ID id=ID '(' arguments=argumentList? ')' '{' expressions=exprList '}';
preprocessor: '#include' content=.*? NEWLINE                                #include;
exprList    : expression*;
expression  : INT                                         #constInt
            | FLOAT                                                         #constFloat
            | STRING                                                        #constString
            | ('true'|'false')                                              #constBool
            | declaration                                                   #decl
            | ID                                                            #id
            | left=expression op=(MUL | DIV) right=expression               #muldiv
            | left=expression op=(ADD | SUB) right=expression               #addsub
            | left=expression op=('==' | '!=' | '<' | '>' | '<=' | '>=') right=expression             #comparison
            | '(' expression ')'                                            #inlineScope
            | '{' exprList '}'                                              #scope
            | '(' ID ')' expression                                         #cast
            | 'if' '(' cond=expression ')' operation=expression             #if
            | dest=expression '=' expr=expression ';'                       #assignment
            | 'return' expression ';'                                       #returnVal
            | 'return' ';'                                                  #returnVoid
            ;
declaration : type=ID id=ID
            ;