package environment;

import java.util.ArrayList;

import lexer.Lexeme;
import printer.PrettyPrinter;

public class Closure {
	
	private Environment definingEnvironment;
	private ArrayList<Lexeme> parameters;
	private Lexeme bodyTree;
	
	public Closure(Environment def, Lexeme paramTree, Lexeme body) {
		ArrayList<Lexeme> params = new ArrayList<Lexeme>();
		Lexeme current = paramTree;
		while(current != null) {
			params.add(current.getLeft());
			current = current.getRight();
		}
		definingEnvironment = def;
		parameters = params;
		bodyTree = body;
	}
	
	public Closure(Environment def, ArrayList<Lexeme> params, Lexeme body) {
		definingEnvironment = def;
		parameters = params;
		bodyTree = body;
	}
	
	public Environment getDefiningEnvironment() {
		return definingEnvironment;
	}

	public ArrayList<Lexeme> getParameters() {
		return parameters;
	}

	public Lexeme getBodyTree() {
		return bodyTree;
	}
	
	public void displayClosure() {
		System.out.print("Parameters: ");
		for(int i = 0; i < parameters.size(); i++) {
			System.out.print(parameters.get(i).getValue() + " ");
		}
		System.out.print("Body: ");
		PrettyPrinter d = new PrettyPrinter();
		d.displayParseTree(bodyTree);
		System.out.println("(end body)");
	}
}
