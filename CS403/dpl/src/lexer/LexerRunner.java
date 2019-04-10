
package lexer;

public final class LexerRunner {

	public static void main(String[] args) {
		Lexer l = new Lexer("anonymousFunctions.del");
		l.scanner();
	}

}
