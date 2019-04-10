package lexer;

public class Lexeme {
	
	protected String type;
	protected Object value;
	protected Integer line;
	protected Lexeme left;
	protected Lexeme right;
	
	public Lexeme(String t, Integer l) {
		type = t;
		value = null;
		line = l;
	}
	
	public Lexeme(String t, Object v, Integer l) {
		type = t;
		value = v;
		line = l;
	}
	
	public String getType()
	{
		return type;
	}
	
	public void setType(String type) {
		this.type = type;
	}
	
	public Object getValue() {
		return value;
	}

	public void setValue(Object value) {
		this.value = value;
	}
	
		public Lexeme getLeft() {
		return left;
	}

	public void setLeft(Lexeme left) {
		this.left = left;
	}

	public Lexeme getRight() {
		return right;
	}

	public void setRight(Lexeme right) {
		this.right = right;
	}

	public void display(){
		System.out.print(type);
		if(value != null) {
			System.out.println(": " + value);
		}
		else
		{
			System.out.println();
		}
	}
	
	public boolean check(String type) {
		return this.type.equals(type);
	}

	public Integer getLine() {
		return line;
	}
}
	
