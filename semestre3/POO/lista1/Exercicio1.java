import java.io.IOException;

public class Exercicio1 {
	public static void main (String arg []) throws IOException{
		EntradaTeclado entTec = new EntradaTeclado();

		System.out.println("Please enter x");
		Double x = entTec.leDouble();	
		System.out.println("Please enter a guess");
		Double guess = entTec.leDouble();	

		// Calculate root
		double lastGuess = 0;
		do{
			lastGuess = guess;
			guess = (lastGuess+(x/lastGuess))/2;
			System.out.printf("%f %f %f\n",lastGuess, guess, lastGuess-guess);
		}while(Math.abs(guess-lastGuess)>=0.00000001);

		System.out.printf("Your result is: %f\n", guess);

	}
}
