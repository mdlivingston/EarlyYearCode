package recognizer;

import io.Fatal;
import lexer.Lexer;

public class Recognizer {

	private Lexer l;
	
	public Recognizer(String fileName) {
		l = new Lexer(fileName);
	}
	
	public void run() {
		while(!check("ENDofINPUT")) {
			statements();
		}
		System.out.println("Recognizer parsed through the entire file successfully.");
	}
	
	public void statements() {
		statement();
		if(l.statementPending()) {
			statements();
		}
	}
	
	public void statement() {
		if(check("NEWLINE")) match("NEWLINE");
		else if(l.expressionPending()) expression();
		else if(l.variableDefPending()) variableDef();
		else if(l.functionDefPending()) functionDef();
		else if(l.arrayDefPending()) arrayDef();
		else if(l.classDefPending()) classDef();
		else if(l.objectDefPending()) objectDef();
		else if(l.conditionalPending()) conditional();
		else if(check("INCLUDE")) include();
		else
			comment();
	}
	
	public void expression() {
		unary();
			if(l.expressionPending()) expression();
	}
	
	public void variableDef() {
		match("VARIABLE_DEFINE");
		match("VARIABLE");
		initializerExpression();	
	}
	
	public void functionDef() {
		match("FUNCTION");
		match("VARIABLE");
		parameterExpression();
		block();
	}
	
	
	
	public void arrayDef() {
		match("ARRAY");
		match("VARIABLE");
		initializerExpression();
	}
	
	public void classDef() {
		match("CLASS");
		match("VARIABLE");
		block();
	}
	
	public void objectDef() {
		match("OBJECT");
		match("VARIABLE");
		initializerExpression();
	}
	
	public void conditional() {
		if(l.ifPending()) ifStatement();
		else whileLoop();	
	}
	
	public void include() {
		match("INCLUDE");
		match("STRING");
	}
	
	public void comment() {
		match("COMMENT");
	}
	
	public void unary() {
		if(check("INTEGER")) match("INTEGER");
		else if(check("REAL")) match("REAL");
		else if(check("STRING")) match("STRING");
		else if(check("ASSIGN")) match ("ASSIGN");
		else if(l.anonymousPending()) anonymousExpression();
		else {
			match("VARIABLE");
			if(l.variableExpressionPending()) {
				variableExpression();
			}
		}
	}
	
	public void initializerExpression() {
		match("OPEN_PAREN");
		expression();
		match("CLOSE_PAREN");
	}
	
	public void parameterExpression() {
		match("OPEN_PAREN");
		optParameterList();
		match("CLOSE_PAREN");
	}
	
	public void block() {
		match("OPEN_BRACE");
		if(l.statementPending())
			statements();
		match("CLOSE_BRACE");
		if(check("NEWLINE"))
			match("NEWLINE");
	}
	
	public void ifStatement() {
		match("IF");
		match("OPEN_PAREN");
		expression();
		match("CLOSE_PAREN");
		block();
		optElse();
	}
	
	
	public void whileLoop() {
		match("WHILE");
		match("OPEN_PAREN");
		expression();
		match("CLOSE_PAREN");
		block();
	}
	
	public void anonymousExpression() {
		if(l.getCurrentLexeme().check("OPEN_PAREN"))
			anonymousCall();
		else
			anonymousDefine();
	}
	
	public void variableExpression() {
		if(check("DOT")) {
			match("DOT");
			match("VARIABLE");
			}
		if(l.initializerExpressionPending()) {
				initializerExpression();
		}
	}
	
	public void objectExpression() {
		match("VARIABLE");
		if(l.initializerExpressionPending()) {
			initializerExpression();
		}
	}
	
	public void optParameterList() {
		if(check("VARIABLE")) {
			match("VARIABLE");
			optParameterList();
		}
	}
	
	public void optElse() {
		if(check("ELSE")) {
			match("ELSE");
			if(l.ifPending()) ifStatement();
			else block();
		}
	}
	
	private boolean check(String string) {
		return l.getCurrentLexeme().check(string);
	}
	
	private void match(String type) {
		if(!check(type)) {
			Fatal.FATAL("Expected " + type, l.getCurrentLexeme().getLine());
		}
		l.advance();
	}	
	
	public void anonymousCall() {
		match("OPEN_PAREN");
		match("ANONYMOUS");
		parameterExpression();
		block();
		initializerExpression();
		match("CLOSE_PAREN");
	}
	
	public void anonymousDefine() {
		match("ANONYMOUS");
		parameterExpression();
		block();
	}
}
