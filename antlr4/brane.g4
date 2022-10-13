grammar brane;

NEWLINE : [\r\n]+ -> skip;
FLOAT   : [0-9]+('.'([0-9]*))?'f';
INT     : [0-9]+;

prog:	expr EOF ;
expr:	expr ('*'|'/') expr
    |	expr ('+'|'-') expr
    |	INT
    |   FLOAT
    |	'(' expr ')'
    ;