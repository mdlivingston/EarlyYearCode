package evaluator;

import java.util.ArrayList;

import environment.Environment;
import io.Fatal;
import lexer.Lexeme;

public class Builtin {

	public static boolean builtin(Lexeme tree) {
		return
			tree.getValue().equals("add") ||
			tree.getValue().equals("sub") ||
			tree.getValue().equals("mult") ||
			tree.getValue().equals("div") ||
			tree.getValue().equals("raise") ||
			tree.getValue().equals("eq") ||
			tree.getValue().equals("neq") ||
			tree.getValue().equals("greater") ||
			tree.getValue().equals("less") ||
			tree.getValue().equals("greaterEq") ||
			tree.getValue().equals("lessEq") ||
			tree.getValue().equals("inc") ||
			tree.getValue().equals("dec") ||
			tree.getValue().equals("print") ||
			tree.getValue().equals("printLn") ||
			tree.getValue().equals("displayArray") ||
			tree.getValue().equals("appendArray") ||
			tree.getValue().equals("prependArray") ||
			tree.getValue().equals("getArray") ||
			tree.getValue().equals("setArray") ||
			tree.getValue().equals("removeArray") ||
			tree.getValue().equals("sizeArray");
	}
			
	public static Lexeme evalBuiltin(Lexeme builtin, ArrayList<Lexeme> operands, Environment env) {
		String function = (String) builtin.getValue();
		int l = builtin.getLine();
		if(function.equals("add"))
			return addBuiltin(operands, env, l);
		else if(function.equals("sub"))
			return subBuiltin(operands, env, l);
		else if(function.equals("mult"))
			return multBuiltin(operands, env, l);
		else if(function.equals("div"))
			return divBuiltin(operands, env, l);
		else if(function.equals("raise"))
			return raiseBuiltin(operands, env, l);
		else if(function.equals("eq"))
			return eqBuiltin(operands, env, l);
		else if(function.equals("neq"))
			return neqBuiltin(operands, env, l);
		else if(function.equals("greater"))
			return greaterBuiltin(operands, env, l);
		else if(function.equals("less"))
			return lessBuiltin(operands, env, l);
		else if(function.equals("greaterEq"))
			return greaterEqBuiltin(operands, env, l);
		else if(function.equals("lessEq"))
			return lessEqBuiltin(operands, env, l);
		else if(function.equals("inc"))
			return incBuiltin(operands, env, l);
		else if(function.equals("dec"))
			return decBuiltin(operands, env, l);
		else if(function.equals("print"))
			return printBuiltin(operands, env, l);
		else if(function.equals("printLn"))
			return printLnBuiltin(operands, env, l);
		else if(function.equals("displayArray"))
			return displayArrayBuiltin(operands, env, l);
		else if(function.equals("appendArray"))
			return appendArrayBuiltin(operands, env, l);
		else if(function.equals("prependArray"))
			return prependArrayBuiltin(operands, env, l);
		else if(function.equals("getArray"))
			return getArrayBuiltin(operands, env, l);
		else if(function.equals("setArray"))
			return setArrayBuiltin(operands, env, l);
		else if(function.equals("removeArray"))
			return removeArrayBuiltin(operands, env, l);
		else if(function.equals("sizeArray"))
			return sizeArrayBuiltin(operands, env, l);
		else
			Fatal.FATAL("Function " + builtin.getValue() + " is not builtin", l);
		return null;
	}
	

	private static Lexeme addBuiltin(ArrayList<Lexeme> operands,  Environment env, int line) {
		 if(operands.size() != 2){
			Fatal.FATAL("Invalid number of arguments to builtin add", line);
		}
		Lexeme op1 = operands.get(0);
		Lexeme op2 = operands.get(1);
		
		if(op1.getType().equals("INTEGER")) {
			int op = (int)op1.getValue();
			if(op2.getType().equals("INTEGER"))
				return new Lexeme("INTEGER", op + (int)op2.getValue(), line);
			else if(op2.getType().equals("REAL"))
				return new Lexeme("REAL", op + Double.parseDouble(op2.getValue().toString()), line);
		}
		else if(op1.getType().equals("REAL")) {
			Double op = Double.parseDouble(op1.getValue().toString());
			if(op2.getType().equals("INTEGER"))
				return new Lexeme("REAL", op + (int)op2.getValue(), line);
			else if(op2.getType().equals("REAL"))
				return new Lexeme("REAL", op + Double.parseDouble(op2.getValue().toString()), line);
		}
		else if(op1.getType().equals("STRING")) {
			String op = op1.getValue().toString();
			if(op2.getType().equals("STRING")) 
				return new Lexeme("STRING", op + op2.getValue().toString(), line);
		}
		Fatal.FATAL("Cannot add with the given operands", line);
		return env.nullLexeme();
	}
	
	private static Lexeme subBuiltin(ArrayList<Lexeme> operands,  Environment env, int line) {
		if(operands.size() != 2){
			Fatal.FATAL("Invalid number of arguments to builtin sub", line);
		}
		Lexeme op1 = operands.get(0);
		Lexeme op2 = operands.get(1);
		
		if(op1.getType().equals("INTEGER")) {
			int op = (int)op1.getValue();
			if(op2.getType().equals("INTEGER"))
				return new Lexeme("INTEGER", op - (int)op2.getValue(), line);
			else if(op2.getType().equals("REAL"))
				return new Lexeme("REAL", op - Double.parseDouble(op2.getValue().toString()), line);
		}
		else if(op1.getType().equals("REAL")) {
			Double op = Double.parseDouble(op1.getValue().toString());
			if(op2.getType().equals("INTEGER"))
				return new Lexeme("REAL", op - (int)op2.getValue(), line);
			else if(op2.getType().equals("REAL"))
				return new Lexeme("REAL", op - Double.parseDouble(op2.getValue().toString()), line);
		}
		Fatal.FATAL("Cannot subtract with the given operands", line);
		return env.nullLexeme();
	}

	private static Lexeme multBuiltin(ArrayList<Lexeme> operands,  Environment env, int line) {
		if(operands.size() != 2){
			Fatal.FATAL("Invalid number of arguments to builtin mult", line);
		}
		Lexeme op1 = operands.get(0);
		Lexeme op2 = operands.get(1);
		
		if(op1.getType().equals("INTEGER")) {
			int op = (int)op1.getValue();
			if(op2.getType().equals("INTEGER"))
				return new Lexeme("INTEGER", op * (int)op2.getValue(), line);
			else if(op2.getType().equals("REAL"))
				return new Lexeme("REAL", op * Double.parseDouble(op2.getValue().toString()), line);
		}
		else if(op1.getType().equals("REAL")) {
			Double op = Double.parseDouble(op1.getValue().toString());
			if(op2.getType().equals("INTEGER"))
				return new Lexeme("REAL", op * (int)op2.getValue(), line);
			else if(op2.getType().equals("REAL"))
				return new Lexeme("REAL", op * Double.parseDouble(op2.getValue().toString()), line);
		}
		Fatal.FATAL("Cannot multiply with the given operands", line);
		return env.nullLexeme();
		}
	
	private static Lexeme divBuiltin(ArrayList<Lexeme> operands,  Environment env, int line) {
		if(operands.size() != 2){
			Fatal.FATAL("Invalid number of arguments to builtin div", line);
		}
		Lexeme op1 = operands.get(0);
		Lexeme op2 = operands.get(1);
		
		if(op2.check("INTEGER") && (int)op2.getValue() == 0)
			Fatal.FATAL("Divide by zero", line);
		
		if(op1.getType().equals("INTEGER")) {
			int op = (int)op1.getValue();
			if(op2.getType().equals("INTEGER"))
				return new Lexeme("INTEGER", op / (int)op2.getValue(), line);
			else if(op2.getType().equals("REAL"))
				return new Lexeme("REAL", op / Double.parseDouble(op2.getValue().toString()), line);
		}
		else if(op1.getType().equals("REAL")) {
			Double op = Double.parseDouble(op1.getValue().toString());
			if(op2.getType().equals("INTEGER"))
				return new Lexeme("REAL", op / (int)op2.getValue(), line);
			else if(op2.getType().equals("REAL"))
				return new Lexeme("REAL", op / Double.parseDouble(op2.getValue().toString()), line);
		}
		Fatal.FATAL("Cannot divide with the given operands", line);
		return env.nullLexeme();
		}
	
	private static Lexeme raiseBuiltin(ArrayList<Lexeme> operands,  Environment env, int line) {
		if(operands.size() != 2){
			Fatal.FATAL("Invalid number of arguments to builtin raise", line);
		}
		Lexeme op1 = operands.get(0);
		Lexeme op2 = operands.get(1);
		
		if(op1.getType().equals("INTEGER")) {
			int op = (int)op1.getValue();
			if(op2.getType().equals("INTEGER"))
				return new Lexeme("INTEGER", (int)Math.pow(op, (int)op2.getValue()), line);
			else if(op2.getType().equals("REAL"))
				return new Lexeme("REAL", Math.pow(op, Double.parseDouble(op2.getValue().toString())), line);
		}
		else if(op1.getType().equals("REAL")) {
			Double op = Double.parseDouble(op1.getValue().toString());
			if(op2.getType().equals("INTEGER"))
				return new Lexeme("REAL", Math.pow(op, (int)op2.getValue()), line);
			else if(op2.getType().equals("REAL"))
				return new Lexeme("REAL", Math.pow(op, Double.parseDouble(op2.getValue().toString())), line);
		}
		Fatal.FATAL("Cannot divide with the given operands", line);
		return env.nullLexeme();
		}
	
	private static Lexeme eqBuiltin(ArrayList<Lexeme> operands,  Environment env, int line) {
		if(operands.size() != 2){
			Fatal.FATAL("Invalid number of arguments to builtin eq", line);
		}
		Lexeme op1 = operands.get(0);
		Lexeme op2 = operands.get(1);
		
		if(op1.getType().equals("INTEGER")) {
			int op = (int)op1.getValue();
			if(op2.getType().equals("INTEGER"))
				if(op == (int)op2.getValue())
					return new Lexeme("BOOLEAN", true, line);
		}
		else if(op1.getType().equals("REAL")) {
			Double op = Double.parseDouble(op1.getValue().toString());
			if(op2.getType().equals("REAL"))
				if(op == Double.parseDouble(op2.getValue().toString()))
					return new Lexeme("BOOLEAN", true, line);
		}
		else if(op1.getType().equals("STRING")) {
			if(op2.getType().equals("STRING"))
				if(op1.getValue().toString().equals(op2.getValue().toString()))
					return new Lexeme("BOOLEAN", true, line);
		}
		else if(op1.getType().equals("NULL")) {
			if(op2.getType().equals("NULL"))
				return new Lexeme("BOOLEAN", true, line);
		}
		else if(op1.getType().equals("OBJECT")) {
			if(op2.getType().equals("OBJECT"))
				if(op1.getValue().equals(op2.getValue()))
					return new Lexeme("BOOLEAN", true, line);
		}
		return new Lexeme("BOOLEAN", false, line);
 	}
	
	private static Lexeme neqBuiltin(ArrayList<Lexeme> operands,  Environment env, int line) {
		if(operands.size() != 2){
			Fatal.FATAL("Invalid number of arguments to builtin neq", line);
		}
		Lexeme op1 = operands.get(0);
		Lexeme op2 = operands.get(1);
		
		if(op1.getType().equals("INTEGER")) {
			int op = (int)op1.getValue();
			if(op2.getType().equals("INTEGER"))
				if(op == (int)op2.getValue())
					return new Lexeme("BOOLEAN", false, line);
		}
		else if(op1.getType().equals("REAL")) {
			Double op = Double.parseDouble(op1.getValue().toString());
			if(op2.getType().equals("REAL"))
				if(op == Double.parseDouble(op2.getValue().toString()))
					return new Lexeme("BOOLEAN", false, line);
		}
		else if(op1.getType().equals("STRING")) {
			if(op2.getType().equals("STRING"))
				if(op1.getValue().toString().equals(op2.getValue().toString()))
					return new Lexeme("BOOLEAN", false, line);
		}
		else if(op1.getType().equals("NULL")) {
			if(op2.getType().equals("NULL"))
				return new Lexeme("BOOLEAN", false, line);
		}
		else if(op1.getType().equals("OBJECT")) {
			if(op2.getType().equals("OBJECT"))
				if(op1.getValue().equals(op2.getValue()))
					return new Lexeme("BOOLEAN", false, line);
		}
		return new Lexeme("BOOLEAN", true, line);
 	}
	
	private static Lexeme greaterBuiltin(ArrayList<Lexeme> operands,  Environment env, int line) {
		if(operands.size() != 2){
			Fatal.FATAL("Invalid number of arguments to builtin greater", line);
		}
		Lexeme op1 = operands.get(0);
		Lexeme op2 = operands.get(1);
		
		if(op1.getType().equals("INTEGER")) {
			int op = (int)op1.getValue();
			if(op2.getType().equals("INTEGER")) {
				if(op > (int)op2.getValue())
					return new Lexeme("BOOLEAN", true, line);
				else
					return new Lexeme("BOOLEAN", false, line);
			}
			else if(op2.getType().equals("REAL")) {
				if(op > Double.parseDouble(op2.getValue().toString()))
					return new Lexeme("BOOLEAN", true, line);
				else
					return new Lexeme("BOOLEAN", false, line);
			}
		}
		else if(op1.getType().equals("REAL")) {
			Double op = Double.parseDouble(op1.getValue().toString());
			if(op2.getType().equals("INTEGER")) {
				if(op > (int)op2.getValue())
				return new Lexeme("BOOLEAN", true, line);
				else
					return new Lexeme("BOOLEAN", false, line);
			}
			else if(op2.getType().equals("REAL")) {
				if(op > Double.parseDouble(op2.getValue().toString()))
					return new Lexeme("BOOLEAN", true, line);
				else
					return new Lexeme("BOOLEAN", false, line);
			}
		}
		else if(op1.getType().equals("STRING")) {
			String op = op1.getValue().toString();
			if(op2.getType().equals("STRING")) {
				if(op.compareTo(op2.getValue().toString()) > 0)
					return new Lexeme("BOOLEAN", true, line);
				else
					return new Lexeme("BOOLEAN", false, line);
			}
		}
		Fatal.FATAL("Cannot compare the given operands", line);
		return env.nullLexeme();
	}
	
	private static Lexeme lessBuiltin(ArrayList<Lexeme> operands,  Environment env, int line) {
		if(operands.size() != 2){
			Fatal.FATAL("Invalid number of arguments to builtin less", line);
		}
		Lexeme op1 = operands.get(0);
		Lexeme op2 = operands.get(1);
		
		if(op1.getType().equals("INTEGER")) {
			int op = (int)op1.getValue();
			if(op2.getType().equals("INTEGER")) {
				if(op < (int)op2.getValue())
					return new Lexeme("BOOLEAN", true, line);
				else
					return new Lexeme("BOOLEAN", false, line);
			}
			else if(op2.getType().equals("REAL")) {
				if(op < Double.parseDouble(op2.getValue().toString()))
					return new Lexeme("BOOLEAN", true, line);
				else
					return new Lexeme("BOOLEAN", false, line);
			}
		}
		else if(op1.getType().equals("REAL")) {
			Double op = Double.parseDouble(op1.getValue().toString());
			if(op2.getType().equals("INTEGER")) {
				if(op < (int)op2.getValue())
				return new Lexeme("BOOLEAN", true, line);
				else
					return new Lexeme("BOOLEAN", false, line);
			}
			else if(op2.getType().equals("REAL")) {
				if(op < Double.parseDouble(op2.getValue().toString()))
					return new Lexeme("BOOLEAN", true, line);
				else
					return new Lexeme("BOOLEAN", false, line);
			}
		}
		else if(op1.getType().equals("STRING")) {
			String op = op1.getValue().toString();
			if(op2.getType().equals("STRING")) {
				if(op.compareTo(op2.getValue().toString()) < 0)
					return new Lexeme("BOOLEAN", true, line);
				else
					return new Lexeme("BOOLEAN", false, line);
			}
		}
		Fatal.FATAL("Cannot compare the given operands", line);
		return env.nullLexeme();
	}
	
	private static Lexeme greaterEqBuiltin(ArrayList<Lexeme> operands,  Environment env, int line) {
		if(operands.size() != 2){
			Fatal.FATAL("Invalid number of arguments to builtin greaterEq", line);
		}
		Lexeme op1 = operands.get(0);
		Lexeme op2 = operands.get(1);
		
		if(op1.getType().equals("INTEGER")) {
			int op = (int)op1.getValue();
			if(op2.getType().equals("INTEGER")) {
				if(op >= (int)op2.getValue())
					return new Lexeme("BOOLEAN", true, line);
				else
					return new Lexeme("BOOLEAN", false, line);
			}
			else if(op2.getType().equals("REAL")) {
				if(op >= Double.parseDouble(op2.getValue().toString()))
					return new Lexeme("BOOLEAN", true, line);
				else
					return new Lexeme("BOOLEAN", false, line);
			}
		}
		else if(op1.getType().equals("REAL")) {
			Double op = Double.parseDouble(op1.getValue().toString());
			if(op2.getType().equals("INTEGER")) {
				if(op >= (int)op2.getValue())
				return new Lexeme("BOOLEAN", true, line);
				else
					return new Lexeme("BOOLEAN", false, line);
			}
			else if(op2.getType().equals("REAL")) {
				if(op >= Double.parseDouble(op2.getValue().toString()))
					return new Lexeme("BOOLEAN", true, line);
				else
					return new Lexeme("BOOLEAN", false, line);
			}
		}
		else if(op1.getType().equals("STRING")) {
			String op = op1.getValue().toString();
			if(op2.getType().equals("STRING")) {
				if(op.compareTo(op2.getValue().toString()) >= 0)
					return new Lexeme("BOOLEAN", true, line);
				else
					return new Lexeme("BOOLEAN", false, line);
			}
		}
		Fatal.FATAL("Cannot compare the given operands", line);
		return env.nullLexeme();
	}
	
	private static Lexeme lessEqBuiltin(ArrayList<Lexeme> operands,  Environment env, int line) {
		if(operands.size() != 2){
			Fatal.FATAL("Invalid number of arguments to builtin lessEq", line);
		}
		Lexeme op1 = operands.get(0);
		Lexeme op2 = operands.get(1);
		
		if(op1.getType().equals("INTEGER")) {
			int op = (int)op1.getValue();
			if(op2.getType().equals("INTEGER")) {
				if(op <= (int)op2.getValue())
					return new Lexeme("BOOLEAN", true, line);
				else
					return new Lexeme("BOOLEAN", false, line);
			}
			else if(op2.getType().equals("REAL")) {
				if(op <= Double.parseDouble(op2.getValue().toString()))
					return new Lexeme("BOOLEAN", true, line);
				else
					return new Lexeme("BOOLEAN", false, line);
			}
		}
		else if(op1.getType().equals("REAL")) {
			Double op = Double.parseDouble(op1.getValue().toString());
			if(op2.getType().equals("INTEGER")) {
				if(op <= (int)op2.getValue())
				return new Lexeme("BOOLEAN", true, line);
				else
					return new Lexeme("BOOLEAN", false, line);
			}
			else if(op2.check("REAL")) {
				if(op <= Double.parseDouble(op2.getValue().toString()))
					return new Lexeme("BOOLEAN", true, line);
				else
					return new Lexeme("BOOLEAN", false, line);
			}
		}
		else if(op1.check("STRING")) {
			String op = op1.getValue().toString();
			if(op2.check("STRING")) {
				if(op.compareTo(op2.getValue().toString()) <= 0)
					return new Lexeme("BOOLEAN", true, line);
				else
					return new Lexeme("BOOLEAN", false, line);
			}
		}
		Fatal.FATAL("Cannot compare the given operands", line);
		return env.nullLexeme();
	}
	
	private static Lexeme incBuiltin(ArrayList<Lexeme> operands,  Environment env, int line) {
		if(operands.size() != 1){
			Fatal.FATAL("Invalid number of arguments to builtin inc", line);
		}
		Lexeme op1 = operands.get(0);
		if(op1.check("INTEGER")) 
			return new Lexeme(op1.getType(), (int)op1.getValue() + 1, line);
		Fatal.FATAL("Cannot increment the given operand", line);
		return env.nullLexeme();
	}
	
	private static Lexeme decBuiltin(ArrayList<Lexeme> operands,  Environment env, int line) {
		if(operands.size() != 1){
			Fatal.FATAL("Invalid number of arguments to builtin dec", line);
		}
		Lexeme op1 = operands.get(0);
		if(op1.check("INTEGER")) 
			return new Lexeme(op1.getType(), (int)op1.getValue() - 1, line);
		Fatal.FATAL("Cannot increment the given operand", line);
		return env.nullLexeme();
	}
	
	private static Lexeme printBuiltin(ArrayList<Lexeme> operands,  Environment env, int line) {
		for(int i = 0; i < operands.size(); i++) {
			Lexeme l = operands.get(i);
			if(l.check("NULL"))
				System.out.print("null ");
			else
				System.out.print(l.getValue());
		}
		return env.nullLexeme();
	}
	
	private static Lexeme printLnBuiltin(ArrayList<Lexeme> operands,  Environment env, int line) {
		for(int i = 0; i < operands.size(); i++) {
			Lexeme l = operands.get(i);
			if(l.check("NULL"))
				System.out.print("null ");
			else
				System.out.print(l.getValue());
		}
		System.out.println();
		return env.nullLexeme();
	}
	
	@SuppressWarnings("unchecked")
	private static Lexeme displayArrayBuiltin(ArrayList<Lexeme> operands,  Environment env, int line) {
		if(operands.size() != 1){
			Fatal.FATAL("Invalid number of arguments to builtin display", line);
		}
		Lexeme op1 = operands.get(0);

		if(op1.getType() != "ARRAY") 
			Fatal.FATAL("Attempting to use display on something not of type array", line);
		ArrayList<Lexeme> vals = (ArrayList<Lexeme>) op1.getValue();
		for(int i = 0; i < vals.size(); i++) {
			System.out.print(vals.get(i).getValue() + " ");
		}
		System.out.println();
		return env.nullLexeme();
	}
	
	@SuppressWarnings("unchecked")
	private static Lexeme appendArrayBuiltin(ArrayList<Lexeme> operands,  Environment env, int line) {
		if(operands.size() != 2){
			Fatal.FATAL("Invalid number of arguments to builtin append", line);
		}
		Lexeme op1 = operands.get(0);
		Lexeme op2 = operands.get(1);
		
		if(op1.getType() != "ARRAY") 
			Fatal.FATAL("Attempting to use append on something not of type array", line);
		ArrayList<Lexeme> vals = (ArrayList<Lexeme>) op1.getValue();
		vals.add(op2);
		return new Lexeme("ARRAY", vals, line);
	}
	
	@SuppressWarnings("unchecked")
	private static Lexeme prependArrayBuiltin(ArrayList<Lexeme> operands,  Environment env, int line) {
		if(operands.size() != 2){
			Fatal.FATAL("Invalid number of arguments to builtin prepend", line);
		}
		Lexeme op1 = operands.get(0);
		Lexeme op2 = operands.get(1);
		
		if(op1.getType() != "ARRAY") 
			Fatal.FATAL("Attempting to use append on something not of type array", line);
		ArrayList<Lexeme> vals = (ArrayList<Lexeme>) op1.getValue();
		vals.add(0, op2);
		return new Lexeme("ARRAY", vals, line);
	}
	
	@SuppressWarnings("unchecked")
	private static Lexeme getArrayBuiltin(ArrayList<Lexeme> operands,  Environment env, int line) {
		if(operands.size() != 2){
			Fatal.FATAL("Invalid number of arguments to builtin get", line);
		}
		Lexeme op1 = operands.get(0);
		Lexeme op2 = operands.get(1);
		
		if(op1.getType() != "ARRAY") 
			Fatal.FATAL("Attempting to use get on something not of type array", line);
		ArrayList<Lexeme> vals = (ArrayList<Lexeme>) op1.getValue();
		if(!op2.check("INTEGER"))
			Fatal.FATAL("Argument 2 of get not of type integer", line);
		return vals.get((int)op2.getValue());
	}
	
	@SuppressWarnings("unchecked")
	private static Lexeme setArrayBuiltin(ArrayList<Lexeme> operands,  Environment env, int line) {
		if(operands.size() != 3){
			Fatal.FATAL("Invalid number of arguments to builtin prepend", line);
		}
		Lexeme op1 = operands.get(0);
		Lexeme op2 = operands.get(1);
		Lexeme op3 = operands.get(2);
		
		if(op1.getType() != "ARRAY") 
			Fatal.FATAL("Attempting to use append on something not of type array", line);
		ArrayList<Lexeme> vals = (ArrayList<Lexeme>) op1.getValue();
		if(!op2.check("INTEGER"))
			Fatal.FATAL("Argument 2 of get not of type integer", line);
		vals.set((int)op2.getValue(), op3);
		return new Lexeme("ARRAY", vals, line);
	}
	
	@SuppressWarnings("unchecked")
	private static Lexeme removeArrayBuiltin(ArrayList<Lexeme> operands,  Environment env, int line) {
		if(operands.size() != 2){
			Fatal.FATAL("Invalid number of arguments to builtin prepend", line);
		}
		Lexeme op1 = operands.get(0);
		Lexeme op2 = operands.get(1);
		
		if(op1.getType() != "ARRAY") 
			Fatal.FATAL("Attempting to use append on something not of type array", line);
		ArrayList<Lexeme> vals = (ArrayList<Lexeme>) op1.getValue();
		if(!op2.check("INTEGER"))
			Fatal.FATAL("Argument 2 of get not of type integer", line);
		vals.remove((int)op2.getValue());
		return new Lexeme("ARRAY", vals, line);
	}
	
	@SuppressWarnings("unchecked")
	private static Lexeme sizeArrayBuiltin(ArrayList<Lexeme> operands,  Environment env, int line) {
		if(operands.size() != 1){
			Fatal.FATAL("Invalid number of arguments to builtin prepend", line);
		}
		Lexeme op1 = operands.get(0);
		
		if(op1.getType() != "ARRAY") 
			Fatal.FATAL("Attempting to use append on something not of type array", line);
		ArrayList<Lexeme> vals = (ArrayList<Lexeme>) op1.getValue();
		return new Lexeme("INTEGER", vals.size(), line);
	}
}
