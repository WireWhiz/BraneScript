grammar brane;

COMMENT : '//' .*? [\r\n] -> skip;
NEWLINE : [\r\n]+ -> skip;
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
LOGIC   : '&&'|'||';

modules       : module* EOF?;

link          : isPublic='public'? 'link' library=STRING ('as' alias=STRING)?;
linkList      : link*;

tags   : '[' (tag=STRING (',' tag=STRING)*)? ']';
module        : modTags=tags? 'module' id=STRING linkList '{' moduleComponent* '}';

moduleComponent : function
                | functionStub ';'
                | structDef
                | global
                ;

global        : type id=ID ';';


templateDefArgument : ((exprType=type) | (isTypedef='typedef')) isPack='...'? id=ID;
templateDef      : 'template' '<' templateDefArgument (',' templateDefArgument)* '>';
templateArg      : t=type          #templateTypeArg
                 | expr=expression #templateExprArg
                 | packID=ID '...' #packExpansionArg
                 ;
templateArgs     : '<' templateArg (',' templateArg)* '>';

scopedID    : id=(ID | 'Lambda') (template=templateArgs)? ('::' child=scopedID)?;

type        : isConst='const'? (isRef='ref' | isArrayRef='ref' '[' size=INT? ']')?  name=scopedID;
declaration : type id=ID;
argumentListItem : declaration | pack=ID '...' id=ID;
argumentList: (argumentListItem (',' argumentListItem)*)?;
argumentPackItem : expr=expression | packID=ID '...';
argumentPack: (argumentPackItem (',' argumentPackItem)*)?;
bracketOpr : ('('')') | ('['']');
functionSig : funcTags=tags? (template=templateDef)? isConstexpr='constexpr'? ((type (id=ID | ('opr' (oprID=(ADD|SUB|MUL|DIV|'=='|'!='|'<'|'>'|'<='|'>='|'!'|LOGIC) | bracketOprID=bracketOpr)))) | ('opr' castType=type));
functionStub: sig=functionSig '(' arguments=argumentList ')' isConst='const'? 'ext';
function    : sig=functionSig '(' arguments=argumentList ')' isConst='const'? '{' statements=statement* '}';

capturedVar : isRef='ref'? id=scopedID;
varCapture : capturedVar (',' capturedVar)*;

structDef     : structTags=tags? (template=templateDef)?  packed='packed'? 'struct' id=(ID | 'Lambda') '{' memberVars=structMember* '}';
structMember  : functionStub ';'    #memberFunctionStub
              | func=function       #memberFunction
              | var=declaration ';' #memberVariable
              ;

statement   : expression ';'                                                              #exprStatement
            | '{' statement* '}'                                                          #scope
            | 'return' expression? ';'                                                    #return
            | 'if' '(' cond=expression ')' operation=statement ('else' elseOp=statement)? #if
            | 'while' '(' cond=expression ')' operation=statement                         #while
            | 'for' '(' init=expression? ';' cond=expression ';' step=expression? ')' operation=statement #for
            | ';'                                                                         #empty
            ;

expression  : INT                                                           #constInt
            | FLOAT                                                         #constFloat
            | CHAR                                                          #constChar
            | STRING                                                        #constString
            | BOOL                                                          #constBool
            | 'sizeof' '(' t=type ')'                                       #sizeOfType
            | 'sizeof' '...' '(' id=ID ')'                                  #sizeOfPack
            | declaration                                                   #decl
            | overrides=expression '(' argumentPack ')'                     #functionCall
            | scopedID                                                      #id
            | base=expression '[' arg=expression ']'                        #indexAccess
            | base=expression '.' member=ID  (template=templateArgs)?       #memberAccess
            | '(' type ')' expression                                       #cast
            | '++' value=expression                                         #preInc
            | '--' value=expression                                         #preDec
            | value=expression '++'                                         #postInc
            | value=expression '--'                                         #postDec
            | left=expression opr=(MUL | DIV) right=expression              #muldiv
            | left=expression opr=(ADD | SUB) right=expression              #addsub
            | left=expression opr=('==' | '!=' | '<' | '>' | '<=' | '>=') right=expression #comparison
            | left=expression opr=LOGIC       right=expression              #logic
            | '!' value=expression                                          #not
            | '(' expression ')'                                            #paren
            | returnType=type label='Lambda' ('[' capture=varCapture ']')? '(' arguments=argumentList ')' '{' statement* '}' #lambda
            | lValue=expression '=' rValue=expression                       #assignment
            | lValue=expression '<-' rValue=expression                      #refAssignment
            ;