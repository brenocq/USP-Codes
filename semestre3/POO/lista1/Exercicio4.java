import java.io.IOException;
import java.lang.Math; 

public class Exercicio4 {
	public static void main (String arg []) throws IOException{
		EntradaTeclado entTec = new EntradaTeclado();
		System.out.println("Please enter a number");
		int n = entTec.leInt();	

		// Check is prime
		int minDiv = 0;
		for(int i=2;i<=Math.sqrt(n);i++){
			if(n%i==0){
				minDiv = i;
				break;
			}
		}

		if(minDiv == 0){
			System.out.println("Is a prime");
		}else{
			System.out.printf("Not a prime: %d\n", minDiv);
		}
	}
}
