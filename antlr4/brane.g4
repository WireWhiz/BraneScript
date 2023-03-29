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
LOGIC   : '&&'|'||';

program     : (progSegment+ EOF | EOF);

progSegment : function
            | functionStub
            | structDef
            | global
            | link
            | export
            ;

global      : type id=ID ';';


templateArgument : id=ID isPack='...'?;
templateDef      : 'template' '<' templateArgument (',' templateArgument)* '>';
templateArgs     : '<' type (',' type)* '>';

type        : isConst='const'? isRef='ref'? id=ID (template=templateArgs)?;
declaration : type id=ID;
argumentList: (declaration (',' declaration)*)?;
argumentPack: (expression (',' expression)*)?;
functionSig : (template=templateDef)? ((type (id=ID | ('opr' oprID=(ADD|SUB|MUL|DIV|'==' | '!=' | '<' | '>' | '<=' | '>='|LOGIC|'[]')))) | ('opr' castType=type));
functionStub: sig=functionSig '(' arguments=argumentList ')' isConst='const'? 'ext' ';';
function    : sig=functionSig '(' arguments=argumentList ')' isConst='const'? '{' statements=statement* '}';

link          : 'link' library=STRING ('as' alias=STRING)? ';';
export        : 'export as' libID=STRING '{' exportSegment* '}';
exportSegment : function
              | functionStub
              | structDef
              | global
              ;

structMember  : (var=declaration ';' | func=function);
structMembers : structMember*;
structDef     : (template=templateDef)?  packed='packed'? 'struct' id=ID '{' memberVars=structMembers '}';

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
            | name=ID (template=templateArgs)? '(' argumentPack ')'         #functionCall
            | base=expression '.' name=ID (template=templateArgs)? '(' argumentPack ')' #memberFunctionCall
            | ID                                                            #id
            | base=expression '[' arg=expression ']'                        #indexAccess
            | base=expression '.' member=ID                                 #memberAccess
            | '(' type ')' expression                                       #cast
            | left=expression opr=(MUL | DIV) right=expression              #muldiv
            | left=expression opr=(ADD | SUB) right=expression              #addsub
            | left=expression opr=LOGIC       right=expression              #logic
            | left=expression opr=('==' | '!=' | '<' | '>' | '<=' | '>=') right=expression #comparison
            | '(' expression ')'                                            #paren
            ;