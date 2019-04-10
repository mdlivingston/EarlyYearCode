package io;

import java.io.EOFException;

public class FileInputRunner {

	public static void main(String[] args) {
		FileInput f = new FileInput("thorough.txt");
		Character c = null;
		try {
			c = f.readNextRawCharacter();
		} catch (EOFException e) {
			return;
		}
		System.out.print(c);
	}
}
