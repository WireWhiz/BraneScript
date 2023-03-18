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

ID      : [a-zA-Z_]([a-zA-Z0-9_:]*);


MUL     : '*';
DIV     : '/';
ADD     : '+';
SUB     : '-';
COMPARE : ('==' | '!=' | '<' | '>' | '<=' | '>=');
LOGIC   : ('&&'|'||');

program     : (progSegment+ EOF | EOF);

progSegment : function
            | functionStub
            | structDef
            | global
            | link
            | export
            ;

global      : type id=ID ';';


templateArgDef : id=ID isPack='...';
template    : 'template' '<' templateArgDef (',' templateArgDef)* '>';
templateArgs: '<'type (',' type)*'>';

type        : isConst='const'? isRef='ref'? id=ID tArgs=templateArgs?;
declaration : type id=ID;
argumentList: (declaration (',' declaration)*)?;
argumentPack: (expression (',' expression)*)?;
functionStub: ((type (id=ID | ('opr' oprID=(ADD|SUB|MUL|DIV|COMPARE|LOGIC|'[]')))) | ('opr' castType=type)) '(' arguments=argumentList ')' isConst='const'? 'ext' ';';
function    : template? ((type (id=ID | ('opr' oprID=(ADD|SUB|MUL|DIV|COMPARE|LOGIC|'[]')))) | ('opr' castType=type)) '(' arguments=argumentList ')' isConst='const'? '{' statements=statement* '}';

link          : 'link' library=STRING ('as' alias=STRING)? ';';
export        : 'export as' libID=STRING '{' exportSegment* '}';
exportSegment : function
              | functionStub
              | structDef
              | global
              ;

structMember  : (var=declaration ';' | func=function);
structMembers : structMember*;
structDef     : template? packed='packed'? 'struct' id=ID '{' memberVars=structMembers '}';

statement   : expression ';'                                                              #exprStatement
            | lValue=expression '=' rValue=expression ';'                                 #assignment
            | '{' statement* '}'                                                          #scope
            | 'return' expression? ';'                                                    #return
            | 'if' '(' cond=expression ')' operation=statement ('else' elseOp=statement)? #if
            | 'while' '(' cond=expression ')' operation=statement                         #while
            ;

expression  : INT                                                           #constInt
            | FLOAT                                                         #constFloat
            | CHAR                                                          #constChar
            | STRING                                                        #constString
            | BOOL                                                          #constBool
            | declaration                                                   #decl
            | name=ID '(' argumentPack ')'                                  #functionCall
            | base=expression '.' name=ID '(' argumentPack ')'              #memberFunctionCall
            | ID                                                            #id
            | base=expression '[' arg=expression ']'                        #indexAccess
            | base=expression '.' member=ID                                 #memberAccess
            | '(' type ')' expression                                       #cast
            | left=expression opr=(MUL | DIV) right=expression              #muldiv
            | left=expression opr=(ADD | SUB) right=expression              #addsub
            | left=expression opr=LOGIC       right=expression              #logic
            | left=expression opr=COMPARE     right=expression              #comparison
            | '(' expression ')'                                            #paren
            | templateExpr                                                  #templateExpr
            ;

templateExpr: ID '...' #templateExpansion
            ;

