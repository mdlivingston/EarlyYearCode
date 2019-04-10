package parser;

import java.util.ArrayList;

import io.Fatal;
import lexer.Lexeme;
import lexer.Lexer;
import printer.PrettyPrinter;

public class Parser {

	private Lexer l;
	private Lexeme root;
	
	public Parser(String fileName) {
		l = new Lexer(fileName);
	}
	
	public Lexeme run() {
		root = statements();
		return root;
	}
	
	public Lexeme getStatement(Lexeme tree) {
		return tree.getLeft();
	}
		
	public Lexeme getParams(Lexeme tree) {
		return tree.getLeft().getLeft().getLeft();
	}
	
	public Lexeme getInclude(Lexeme tree) {
		return tree.getLeft();
	}
	
	public Lexeme getConditional(Lexeme tree) {
		return tree.getLeft();
	}
	
	public Lexeme getIfExpression(Lexeme tree) {
		return tree.getLeft().getLeft();
	}
	
	public boolean hasElse(Lexeme tree) {
		return tree.getRight().getRight() != null;
	}
	
	public boolean hasElseIf(Lexeme tree) {
		return tree.getRight().getRight().getLeft().check("IF");
	}
	
	public Lexeme getElseIfExpression(Lexeme tree) {
		return tree.getRight().getRight().getLeft();
	}
	
	public Lexeme getElseExpression(Lexeme tree) {
		return tree.getRight().getRight().getLeft().getLeft();
	}
	
	public Lexeme getIfBlock(Lexeme tree) {
		return tree.getRight().getLeft().getLeft();
	}
	
	public Lexeme getIfOptElse(Lexeme tree) {
		return tree.getRight().getRight();
	}
	
	public Lexeme getWhileExprssion(Lexeme tree) {
		return tree.getLeft().getLeft();
	}
	
	public Lexeme getWhileBlock(Lexeme tree) {
		return tree.getRight().getLeft();
	}
	
	public Lexeme getFirstExpression(Lexeme tree) {
		return tree.getLeft().getLeft().getLeft();
	}
	
	public Lexeme getSecondExpression(Lexeme tree) {
		return tree.getLeft().getLeft().getRight().getLeft();
	}
	
	public Lexeme getVariable(Lexeme tree) {
		return tree.getLeft();
	}
	
	public Lexeme getBlock(Lexeme tree) {
		return tree.getRight();
	}
	
	public Lexeme getClassName(Lexeme tree) {
		return tree.getRight().getLeft().getLeft().getLeft();
	}
	
	public Lexeme getAnonymousParameters(Lexeme tree) {
		return tree.getLeft().getLeft();
	}
	
	public Lexeme getAnonymousBlock(Lexeme tree) {
		return tree.getRight().getLeft().getLeft();
	}
	
	public ArrayList<Lexeme> getArrayInitilizers(Lexeme tree) {
		ArrayList<Lexeme> lex = new ArrayList<Lexeme>();
		Lexeme l = tree.getRight().getLeft();
		while(l != null) {
			lex.add(l.getLeft());
			l = l.getRight();
		}
		return lex;
	}
	
	public ArrayList<Lexeme> getFunctionInitializers(Lexeme tree) {
		ArrayList<Lexeme> lex = new ArrayList<Lexeme>();
		Lexeme l = tree.getLeft().getLeft();
		while(l != null) {
			lex.add(l.getLeft());
			l = l.getRight();

		}
		return lex;
	}
	
	public ArrayList<Lexeme> getObjectExpressionInitializers(Lexeme tree) {
		ArrayList<Lexeme> lex = new ArrayList<Lexeme>();
		Lexeme l = tree.getRight().getLeft();
		while(l != null) {
			lex.add(l.getLeft());
			l = l.getRight();

		}
		return lex;
	}
	
	public ArrayList<Lexeme> getObjectDefineInitializers(Lexeme tree) {
		ArrayList<Lexeme> lex = new ArrayList<Lexeme>();
		Lexeme l = tree.getRight().getLeft().getLeft().getLeft().getLeft().getLeft();
		while(l != null) {
			lex.add(l.getLeft());
			l = l.getRight();

		}
		return lex;
	}
	 
	public ArrayList<Lexeme> getAnonymousInitilizers(Lexeme tree) {
		ArrayList<Lexeme> lex = new ArrayList<Lexeme>();
		Lexeme l = tree.getRight().getRight().getLeft();
		while(l != null) {
			lex.add(l.getLeft());
			l = l.getRight();
		}
		return lex;
	}
	
	public Lexeme  getUnary(Lexeme tree) {
		return tree.getLeft();
	}
	
	public boolean anonymousHasCall(Lexeme tree) {
		return tree.getLeft().getRight().check("CALL");
	}

	public boolean variableExpressionLookup(Lexeme tree) {
		return tree.getLeft() == null;
	}

	public Lexeme getVariableExpression(Lexeme tree) {
		return tree.getLeft();
	}

	public Lexeme getInitilizer(Lexeme tree) {
		if(tree.getRight().getLeft() == null)
			return null;
		else
			return tree.getRight().getLeft().getLeft();
	}

	public Lexeme getObject(Lexeme tree) {
		return tree.getLeft();
	}

	public Lexeme getObjectAssignInitilizers(Lexeme tree) {
		return tree.getRight().getLeft();
	}
	
	private Lexeme statements() {
		Lexeme tree = statement();
		while(tree == null && l.statementPending()) {
			tree = statement();
		}
		if(l.statementPending()) {
			tree.setRight(statements());
		}
		return tree;
	}
	
	private Lexeme statement() {
		Lexeme tree = null;
		if(check("NEWLINE")) {
			match("NEWLINE");
		}
		else if(check("COMMENT")) {
			match("COMMENT");
		}
		else {
			tree = new Lexeme("STATEMENT", l.getCurrentLexeme().getLine());
			if(l.expressionPending()) tree.setLeft(expression());
			else if(l.variableDefPending()) tree.setLeft(variableDef());
			else if(l.functionDefPending()) tree.setLeft(functionDef());	
			else if(l.arrayDefPending()) tree.setLeft(arrayDef());
			else if(l.classDefPending()) tree.setLeft(classDef());
			else if(l.objectDefPending()) tree.setLeft(objectDef());
			else if(l.conditionalPending()) tree.setLeft(conditional());
			else if(check("INCLUDE")) tree.setLeft(include());
		}
		return tree;
	}
	
	private Lexeme expression() {
		Lexeme tree = new Lexeme("EXPRESSION", l.getCurrentLexeme().getLine());
		tree.setLeft(unary());
		if(l.expressionPending()) {
			tree.setRight(expression());
		}
		return tree;
	}
	
	private Lexeme variableDef() {
		Lexeme tree = match("VARIABLE_DEFINE");
		tree.setLeft(match("VARIABLE"));
		tree.setRight(initializerExpression());
		return tree;
	}
	
	private Lexeme functionDef() {
		Lexeme tree = match("FUNCTION");
		tree.setLeft(match("VARIABLE"));
		tree.getLeft().setLeft(parameterExpression());
		tree.setRight(block());
		return tree;
	}
	
	private Lexeme arrayDef() {
		Lexeme tree = match("ARRAY");
		tree.setLeft(match("VARIABLE"));
		tree.setRight(initializerExpression());
		return tree;
	}
	
	private Lexeme classDef() {
		Lexeme tree = match("CLASS");
		tree.setLeft(match("VARIABLE"));
		tree.setRight(block());
		return tree;
	}
	
	private Lexeme objectDef() {
		Lexeme tree = match("OBJECT");
		tree.setLeft(match("VARIABLE"));
		tree.setRight(initializerExpression());
		return tree;
	}
	
	private Lexeme conditional() {
		Lexeme tree = new Lexeme("CONDITIONAL", l.getCurrentLexeme().getLine());
		if(l.ifPending()) {
			tree.setLeft(ifStatement());
		}
		else tree.setLeft(whileLoop());	
		return tree;
	}
	
	private Lexeme include() {
		Lexeme tree = match("INCLUDE");
		tree.setLeft(match("STRING"));
		return tree;
	}
	
	private Lexeme unary() {
		Lexeme tree = new Lexeme("UNARY", l.getCurrentLexeme().getLine());
		if(check("INTEGER")) tree.setLeft(match("INTEGER"));
		else if(check("REAL"))	tree.setLeft(match("REAL"));
		else if(check("STRING")) tree.setLeft(match("STRING"));
		else if(l.anonymousPending()) tree.setLeft(anonymousExpression());
		else tree.setLeft(variableExpression());
		return tree;
	}
	
	private Lexeme initializerExpression() {
		Lexeme tree = new Lexeme("INITIALIZER_EXPRESSION", l.getCurrentLexeme().getLine());
		match("OPEN_PAREN");
		if(l.unaryPending())
			tree.setLeft(expression());
		match("CLOSE_PAREN");
		return tree;
	}
	
	private Lexeme parameterExpression() {
		Lexeme tree = new Lexeme("PARAMETER_EXPRESSION", l.getCurrentLexeme().getLine());
		match("OPEN_PAREN");
		tree.setLeft(optParameterList());
		match("CLOSE_PAREN");
		return tree;
	}
	
	private Lexeme block() {
		Lexeme tree = new Lexeme("BLOCK", l.getCurrentLexeme().getLine());
		match("OPEN_BRACE");
		if(l.statementPending()) {
			tree.setLeft(statements());
		}
		match("CLOSE_BRACE");
		if(check("NEWLINE"))
			match("NEWLINE");
		return tree;
	}
	
	private Lexeme ifStatement() {
		Lexeme tree = match("IF");
		match("OPEN_PAREN");
		tree.setLeft(expression());
		match("CLOSE_PAREN");
		tree.setRight(new Lexeme("DO", l.getCurrentLexeme().getLine()));
		tree.getRight().setLeft(block());
		tree.getRight().setRight(optElse());
		return tree;
	}
	
	private Lexeme whileLoop(){
		Lexeme tree = match("WHILE");
		match("OPEN_PAREN");
		tree.setLeft(expression());
		match("CLOSE_PAREN");
		tree.setRight(block());
		return tree;
	}
	
	private Lexeme anonymousExpression() {
		Lexeme tree = new Lexeme("ANONYMOUS_EXPRESSION", l.getCurrentLexeme().getLine());
		if(check("ANONYMOUS")) 
			tree.setLeft(anonymousDefine());
		else 
			tree.setLeft(anonymousCall());
		return tree;
	}
	
	private Lexeme variableExpression() {
		Lexeme lex = match("VARIABLE");
		Lexeme tree = null;
		if(l.initializerExpressionPending()) {
			tree = lex;
			tree.setLeft(initializerExpression());
		}
		else if(l.objectExpressionPending())
			tree = objectExpression(lex);
		else {
			tree = lex;
			tree.setLeft(optionalVariableAssign());
		}
		return tree;
	}
	
	private Lexeme optParameterList() {
		Lexeme tree = null;
		if(check("VARIABLE")) {
			tree = new Lexeme("PARAMETER", l.getCurrentLexeme().getLine());
			tree.setLeft(match("VARIABLE"));
			tree.setRight(optParameterList());
		}
		return tree;
	}
	
	private Lexeme optElse() {
		Lexeme tree = null;
		if(check("ELSE")) {
			tree = match("ELSE");
			if(l.ifPending()) {
				tree.setLeft(ifStatement());
			}
			else tree.setLeft(block());
		}
		return tree;
	}
	
	private Lexeme anonymousDefine() {
		Lexeme tree = match("ANONYMOUS");
		tree.setLeft(parameterExpression());
		tree.setRight(block());
		return tree;
	}
	
	private Lexeme anonymousCall() {
		match("OPEN_PAREN");
		Lexeme tree = match("ANONYMOUS");
		tree.setLeft(parameterExpression());
		tree.setRight(new Lexeme("CALL", l.getCurrentLexeme().getLine()));
		tree.getRight().setLeft(block());
		tree.getRight().setRight(initializerExpression());
		match("CLOSE_PAREN");
		return tree;
	}
	
	private Lexeme objectExpression(Lexeme variable) {
		Lexeme tree = new Lexeme("OBJECT_EXPRESSION", l.getCurrentLexeme().getLine());
		tree.setLeft(variable);
		Lexeme lex = tree.getLeft();
		while(check("DOT")) {
			match("DOT");
			lex.setLeft(match("VARIABLE"));
			lex = lex.getLeft();
		}
		if(check("ASSIGN"))
			tree.setRight(objectAssign());
		else if(l.initializerExpressionPending())
			tree.setRight(initializerExpression());
		return tree;
	}
	
	private Lexeme optionalVariableAssign() {
		if(check("ASSIGN")) {
			Lexeme tree = match("ASSIGN");
			tree.setLeft(unary());
			return tree;
		}
		return null;
	}
	
	private Lexeme objectAssign() {
		Lexeme tree = match("ASSIGN");
		tree.setLeft(unary());
		return tree;
	}
	private boolean check(String type) {
		return l.getCurrentLexeme().check(type);
	}
	
	private Lexeme match(String type) {
		if(!check(type)) 
			Fatal.FATAL("Expected " + type, l.getCurrentLexeme().getLine());
		Lexeme previousLexeme = l.getCurrentLexeme();
		l.advance();
		return previousLexeme;
	}

	public static void main(String[] args) {
	    if(!args[0].endsWith(".max")) {
            Fatal.FATAL("Incorrect file type", -1);
        }
        Parser p = new Parser(args[0]);
		Lexeme tree = p.run();
		PrettyPrinter d = new PrettyPrinter();
		d.displayParseTree(tree);
	}
}
