grammar brane;

NEWLINE : [\r\n]+ -> skip;
SPACE   : ' ' -> skip;
COMMENT : '//'(.*?)[\r\n(EOF)] -> skip;

FLOAT   : [0-9]+('.'([0-9]*))?'f';
INT     : [0-9]+;

MUL     : '*';
DIV     : '/';
ADD     : '+';
SUB     : '-';

program     : statement+ EOF;
statement   : expression ';'
            ;
expression  : left=expression mulop=(MUL | DIV) right=expression    #muldiv
            | left=expression addop=(ADD | SUB) right=expression    #addsub
            | INT                                                   #number
            | FLOAT                                                 #number
            | '(' expression ')'                                    #inlineScope
            ;