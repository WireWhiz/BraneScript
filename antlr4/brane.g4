grammar brane;

NEWLINE : [\r\n]+ -> skip;
COMMENT : '//'(.*?)[\r\n(EOF)] -> skip;
BLOCK_COMMENT : '/*'.*?'*/' -> skip;
SPACE   : (' '|'\t') -> skip;

BOOL    : ('true'|'false');
INT     : [0-9]+;
FLOAT   : INT('.'([0-9]*))?'f';
CHAR    : '\''.'\'';
STRING  : '"'.*?'"';

ID      : [a-zA-Z_]([a-zA-Z0-9_]*);

MUL     : '*';
DIV     : '/';
ADD     : '+';
SUB     : '-';

program     : (progSegment+ EOF | EOF);

progSegment : function
            | preprocessor NEWLINE
            | link
            | structDef
            | global
            ;

global      : declaration ';';

type        : isConst='const'? isRef='ref'? id=ID;
declaration : type id=ID;
argumentList: (declaration (',' declaration)*)?;
argumentPack: (expression (',' expression)*)?;
function    : type id=ID '(' arguments=argumentList ')' '{' statements=statement* '}';

preprocessor: '#include' content=.*? NEWLINE                                #include;
link        : 'link' library=STRING ('as' alias=STRING)? ';';

structMember  : (var=declaration ';' | func=function);
structMembers : structMember*;
structDef     : isPublic='public'? packed='packed'? 'struct' id=ID '{' memberVars=structMembers '}';

statement   : expression ';'                                                #exprStatement
            | '{' statement* '}'                                            #scope
            | 'return' expression ';'                                       #returnVal
            | 'return' ';'                                                  #returnVoid
            | 'if' '(' cond=expression ')' operation=statement              #if
            | 'while' '(' cond=expression ')' operation=statement           #while
            ;

expression  : INT                                                           #constInt
            | FLOAT                                                         #constFloat
            | CHAR                                                          #constChar
            | STRING                                                        #constString
            | BOOL                                                          #constBool
            | declaration                                                   #decl
            | 'delete' ptr=expression                                       #delete
            | name=ID '(' argumentPack ')'                                  #functionCall
            | base=expression '.' name=ID '(' argumentPack ')'              #memberFunctionCall
            | ID                                                            #id
            | base=expression '[' arg=expression ']'                        #indexAccess
            | base=expression '.' member=ID                                 #memberAccess
            | '(' ID ')' expression                                         #cast
            | left=expression op=(MUL | DIV) right=expression               #muldiv
            | left=expression op=(ADD | SUB) right=expression               #addsub
            | left=expression op=('==' | '!=' | '<' | '>' | '<=' | '>=') right=expression #comparison
            | '(' expression ')'                                            #inlineScope
            | dest=expression '=' expr=expression                           #assignment
            ;

