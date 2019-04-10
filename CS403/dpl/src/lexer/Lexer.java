package lexer;

import java.io.EOFException;

import io.FileInput;

public class Lexer {

	FileInput file;
	Lexeme currentLexeme;
	private boolean endOfFile;
	private Integer currentLine;
	
	public Lexer(String fileName) {
		file = new FileInput(fileName);
		endOfFile = false;
		currentLine = 1;
		advance();
	}
	
	public Lexeme getCurrentLexeme() {
		return currentLexeme;
	}

	public void setCurrentLexeme(Lexeme currentLexeme) {
		this.currentLexeme = currentLexeme;
	}

	public void scanner() {
		currentLexeme.display();
		while(currentLexeme.type != "ENDofINPUT") {
			advance();
			currentLexeme.display();
		}
	}
	
	public void advance() {
		if(endOfFile)
			currentLexeme = new Lexeme("ENDofINPUT", currentLine);
		else
			try {
				currentLexeme = lex();
			} catch (EOFException e) {
				currentLexeme = new Lexeme("ENDofINPUT", currentLine);

			}
	}
	
	public boolean statementPending() {
		return expressionPending() || variableDefPending() || functionDefPending()
				|| arrayDefPending() || classDefPending() || objectDefPending() 
				|| conditionalPending() || currentLexeme.check("INCLUDE") || commentPending() 
				|| currentLexeme.check("NEWLINE");
	}
	
	public boolean expressionPending() {
		return unaryPending();
	}
	
	public boolean variableDefPending() {
		return currentLexeme.check("VARIABLE_DEFINE");
	}
	
	public boolean functionDefPending() {
		return currentLexeme.check("FUNCTION");
	}
	
	public boolean arrayDefPending() {
		return currentLexeme.check("ARRAY");
	}
	
	public boolean classDefPending() {
		return currentLexeme.check("CLASS");
	}
	
	public boolean objectDefPending() {
		return currentLexeme.check("OBJECT");
	}
	
	public boolean conditionalPending() {
		return ifPending() || whilePending();
	}
	
	public boolean commentPending() {
		return currentLexeme.check("COMMENT");
	}
	
	public boolean unaryPending() {
		return currentLexeme.check("INTEGER") || currentLexeme.check("REAL") 
				|| currentLexeme.check("STRING") || currentLexeme.check("ASSIGN") 
				|| currentLexeme.check("VARIABLE") || anonymousPending();
	}
	
	public boolean initializerExpressionPending() {
		return currentLexeme.check("OPEN_PAREN");
	}
	
	public boolean anonymousPending() {
		return currentLexeme.check("ANONYMOUS") || currentLexeme.check("OPEN_PAREN"); 
	}
	
	public boolean objectExpressionPending() {
			return currentLexeme.check("DOT");
	}
	
	public boolean variableExpressionPending() {
		return currentLexeme.check("VARIABLE");
	}
	
	public boolean ifPending() {
		return currentLexeme.check("IF");
	}
	
	public boolean whilePending() {
		return currentLexeme.check("WHILE");
	}	
	
	public boolean optParameterListPending() {
		return currentLexeme.check("VARIABLE");
	}

	public Lexeme lex() throws EOFException {
		Character c;
		file.skipWhitespace();
		c = file.readNextRawCharacter();
		switch(c) {
		case '(':	return new Lexeme("OPEN_PAREN", currentLine);
		case ')': 	return new Lexeme("CLOSE_PAREN", currentLine);
		case '{': 	return new Lexeme("OPEN_BRACE", currentLine);
		case '}':	return new Lexeme("CLOSE_BRACE", currentLine);
		case '=':	return new Lexeme("ASSIGN", currentLine);
		case '.': 	return new Lexeme("DOT", currentLine);
		case '[': 	return lexComment();
		case '\n':	{
			currentLine += 1;
			return new Lexeme("NEWLINE", currentLine - 1);
		}
		default:
			if(Character.isDigit(c) || c == '-') {
				file.pushbackCharacter(c);
				return lexNumber();
			}
			else if(Character.isLetter(c)) {
				file.pushbackCharacter(c);
				return lexVarOrKeyword();
			}
			else if(c == '\"') {
				return lexString();
			}
			else {
				return new Lexeme("UNKNOWN", currentLine);
			}
		}
	}	

	private Lexeme lexString() throws EOFException {
		Character c;
		String token = new String();
		c = file.readNextRawCharacter();
		while(c != '\"' && !endOfFile) {
			token = token.concat(Character.toString(c));
			try {
				c = file.readNextRawCharacter();
			} catch (EOFException e) {
				endOfFile = true;
			}
		}
		return new Lexeme("STRING", token, currentLine);
	}

	private Lexeme lexVarOrKeyword() throws EOFException {
		Character c;
		String token = new String();
		c = file.readNextRawCharacter();
		while(Character.isLetterOrDigit(c) && !endOfFile) {
			token = token.concat(Character.toString(c));
			try {
				c = file.readNextRawCharacter();
			} catch (EOFException e) {
				endOfFile = true;
			}
		}
		file.pushbackCharacter(c);
		if(token.equals("function")) return new Lexeme("FUNCTION", currentLine);
		else if(token.equals("variable")) return new Lexeme("VARIABLE_DEFINE", currentLine);
		else if(token.equals("if")) return new Lexeme("IF", currentLine);
		else if(token.equals("else")) return new Lexeme("ELSE", currentLine);
		else if(token.equals("while")) return new Lexeme("WHILE", currentLine);
		else if(token.equals("array")) return new Lexeme("ARRAY", currentLine);
		else if(token.equals("class"))	return new Lexeme("CLASS", currentLine);
		else if(token.equals("object")) return new Lexeme("OBJECT", currentLine);
		else if(token.equals("include")) return new Lexeme("INCLUDE", currentLine);
		else if(token.equals("anonymous")) return new Lexeme("ANONYMOUS", currentLine);
		else return new Lexeme("VARIABLE", token, currentLine);	
	}

	private Lexeme lexNumber() throws EOFException {
		Character c;
		String token = new String();
		c = file.readNextRawCharacter();
		while((Character.isDigit(c) || c == '.' || c == '-') && !endOfFile) {
			token = token.concat(Character.toString(c));
			try {
				c = file.readNextRawCharacter();
			} catch (EOFException e) {
				endOfFile = true;
			}
		}
		file.pushbackCharacter(c);
		if(token.contains(Character.toString('.'))) {
			try {
				return new Lexeme("REAL", Double.parseDouble(token), currentLine);
			} catch(NumberFormatException e) {
				return new Lexeme("UNKNOWN", currentLine);
			}
		}
		else {
			try {
				return new Lexeme("INTEGER", Integer.parseInt(token), currentLine);
			} catch(NumberFormatException e) {
				return new Lexeme("UNKNOWN", currentLine);
			}
		}
	}

	private Lexeme lexComment() throws EOFException {
		Character c;
		String token = new String();
		c = file.readNextRawCharacter();
		while(c != ']' && !endOfFile) {
			token = token.concat(Character.toString(c));
			try {
				c = file.readNextRawCharacter();
			} catch (EOFException e) {
				endOfFile = true;
			}
		}
		return new Lexeme("COMMENT", token, currentLine);
	}
}
