/** Grammars always start with a grammar header. This grammar is called
 *  SPCalculator and must match the filename: SPCalculator.g4
 */
grammar SPCalculator;

/**
* All generated files must reside in the package SP alongside our implementation
* of the tree and the main function.
*/
@header{
package SP;
import java.lang.*;
}

@parser::members{
	//We define a new method in our praser. This method will return a string
	//Representing our tree in LISP-Style
	public String getLisp(){
		StatContext ctx = (StatContext)stat();
		if(ctx.exception!=null){
			return new String("Invalid Expression!");		
		}else{
			return ctx.tree.getLisp();
		}
	}
}

//Valid statement is either a termination command || an arithmetical expression followed by a semicolon
stat returns [SPTree tree] : e1=TERMINATION SEMICOLON {$tree = new SPTree($e1.text);}
			   | e2=exp SEMICOLON {$tree = $e2.tree;}
			   | e3=min SEMICOLON {$tree = $e3.tree;}
			   | e4 = max SEMICOLON {$tree = $e4.tree;}
			   | e5 = assigment SEMICOLON {$tree = $e5.tree;}
; 

min returns [SPTree tree = new SPTree("min")]:
		MIN
		LBRACKET 
		e24=exp{$tree.insertChild($e24.tree);} (COMMA e25=exp{$tree.insertChild($e25.tree);})* 
		RBRACKET
;

max returns [SPTree tree = new SPTree("max")]:
MAX
LBRACKET 
e24=exp{$tree.insertChild($e24.tree);} (COMMA e25=exp{$tree.insertChild($e25.tree);})* 
RBRACKET
;

assigment returns [SPTree tree = new SPTree("=")]:
e19=STRING EQUAL e21=exp{
				SPTree child = new SPTree($e19.text);
				$tree.insertChild(child);
 				$tree.insertChild($e21.tree);
 }
;

exp returns [SPTree tree] :
LBRACKET e1=exp RBRACKET { $tree = $e1.tree;}
 |
e29=min{$tree = $e29.tree;}
 |
e30=max{$tree = $e30.tree;}

 | e7=OP1 e8=exp { 	SPTree temp1 = new SPTree($e7.text);
 			temp1.insertChild($e8.tree);
 			$tree = temp1;
					
 }
 | e9=exp e10=OP3 e11=exp { 	SPTree temp2 = new SPTree($e10.text);
 				temp2.insertChild($e9.tree);
 				temp2.insertChild($e11.tree);
 				$tree = temp2;
											
 
 }
 | e12=exp e13=OP2 e14=exp { 	SPTree temp3 = new SPTree($e13.text);
 				temp3.insertChild($e12.tree);
 				temp3.insertChild($e14.tree);
 				$tree = temp3;
											
 }
 | e15=exp e16=OP1 e17=exp { 	SPTree temp4 = new SPTree($e16.text);
 				temp4.insertChild($e15.tree);
 				temp4.insertChild($e17.tree);
 				$tree = temp4;
											
 }
 | e18=INT { $tree = new SPTree($e18.text);
			
 }
 | e22=STRING { $tree = new SPTree($e22.text);
			
 }




;  //Define an arithmetical expression here




LBRACKET: '(';
RBRACKET: ')';
OP1 : '+'|'-';
OP2 : '*'|'/';
OP3 : '$';
MIN : 'min';
MAX : 'max';
EQUAL : '=';
COMMA : ',';
INT : [0-9]+ ;
STRING : [a-zA-Z]+;
SEMICOLON: ';';

WS : [ \t\r\n ]+ -> skip ;
// parser rules start with lowercase letters, lexer rules with uppercase
TERMINATION: '<>';
