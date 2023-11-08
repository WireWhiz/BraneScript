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

tags          : '[' (tag=STRING (',' tag=STRING)*)? ']';
module        : modTags=tags? 'module' id=STRING module_item*;

module_item : imports
            | exports
            ;

imports      : 'imports' '{' mod_import* '}';
exports     : 'exports' '{' mod_export* '}';

mod_import      : 'module' id=STRING ';'  #importModule
                | 'memory' id=STRING ';'  #importMemory
                ;

mod_export      : function
                | structDef
                | global
                ;

global          : type id=ID ';';


templateDefArg   : ((exprType=type) | (isTypedef='typedef')) isPack='...'? id=ID;
templateDef      : 'template' '<' templateDefArg (',' templateDefArg)* '>';
templateArg      : t=type          #templateTypeArg
                 | expr=expression #templateExprArg
                 | packID=ID '...' #packExpansionArg
                 ;
templateArgs     : '<' templateArg (',' templateArg)* '>';

scopedID    : id=(ID | 'lambda') (template=templateArgs)? ('::' child=scopedID)?;

type        : (valueType | refType | sliceType);
valueType   : name=scopedID;
refType     : '&' refSource=scopedID? type;
sliceType   : '['type (';' size=INT)? ']';

declaration : mut='mut'? type id=ID;
argumentListItem : declaration | pack=ID '...' id=ID;
argumentList: (argumentListItem (',' argumentListItem)*)?;
argumentPackItem : expr=expression | packID=ID '...';
argumentPack: (argumentPackItem (',' argumentPackItem)*)?;
bracketOpr : ('('')') | ('['']');
functionSig : funcTags=tags? (template=templateDef)? isConstexpr='constexpr'? ((type (id=ID | ('opr' (oprID=(ADD|SUB|MUL|DIV|'=='|'!='|'<'|'>'|'<='|'>='|'!'|LOGIC) | bracketOprID=bracketOpr)))) | ('opr' castType=type));
functionStub: sig=functionSig '(' arguments=argumentList ')' isConst='const'? 'ext';
function    : sig=functionSig '(' arguments=argumentList ')' isConst='const'? '{' content=expressions '}';

capturedVar : isRef='&'? id=scopedID;
varCapture : capturedVar (',' capturedVar)*;

structDef     : structTags=tags? (template=templateDef)?  packed='packed'? 'struct' id=ID '{' memberVars=structMember* '}';
structMember  : functionStub ';'    #memberFunctionStub
              | func=function       #memberFunction
              | var=declaration ';' #memberVariable
              ;

expressions : ((expression ';') | ';')* returnValue=expression?;

            // Values
expression  : BOOL                                                          #constBool
            | INT                                                           #constInt
            | FLOAT                                                         #constFloat
            | CHAR                                                          #constChar
            | STRING                                                        #constString

            //Structure
            | '{' content=expressions '}'                                           #scope
            | '(' expression ')'                                            #paren

            //Control flow
            | 'return' expression? ';'                                      #return
            | 'if' '(' cond=expression ')' operation=expression ('else' elseOp=expression)? #if
            | 'while' '(' cond=expression ')' operation=expression                          #while
            | 'for' '(' init=expression? ';' cond=expression ';' step=expression? ')' operation=expression #for
            | 'switch' '(' value=expression ')' '{' switchCase* '}'         #switch
            | 'break' ';'                                                   #break
            | 'continue' ';'                                                #continue

            // Variables
            | declaration '=' expression                                    #decl
            | scopedID                                                      #id
            | returnType=type label='lambda' ('[' capture=varCapture ']')? '(' arguments=argumentList ')' content=expression #lambda

            // Unary operators
            | '++' value=expression                                         #preInc
            | '--' value=expression                                         #preDec
            | value=expression '++'                                         #postInc
            | value=expression '--'                                         #postDec
            | '!' value=expression                                          #not
            | '*' value=expression                                          #deref
            | '&' value=expression                                          #ref

            // Binary operators
            | base=expression '.' member=ID  (template=templateArgs)?       #memberAccess
            | base=expression '[' arg=expression ']'                        #indexAccess
            | expr=expression 'as' targetType=type                          #cast
            | left=expression opr=(MUL | DIV) right=expression              #muldiv
            | left=expression opr=(ADD | SUB) right=expression              #addsub
            | left=expression opr=('==' | '!=' | '<' | '>' | '<=' | '>=') right=expression #comparison
            | left=expression opr=LOGIC right=expression                    #logic
            | left=expression '='       right=expression                    #assignment

            // Function operators
            | overrides=expression '(' argumentPack ')'                     #functionCall

            // Edge cases
            | magicFunction                                                 #magicFunctionCall
            ;

switchCase  : 'case' value=expression '{' content=expressions '}'
            | 'default' '{' content=expressions '}'
            ;

magicFunction : 'sizeof' '(' t=type ')'                                       #sizeOfType
              | 'sizeof' '...' '(' id=ID ')'                                  #sizeOfPack
              | 'fail' '(' message=STRING ')'                                 #fail
              ;