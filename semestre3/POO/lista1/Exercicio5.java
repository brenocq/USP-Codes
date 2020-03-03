import java.io.IOException;
import java.lang.Math; 

public class Exercicio5 {
	public static void main (String arg []) throws IOException{
		EntradaTeclado entTec = new EntradaTeclado();
		System.out.println("Please enter a number");
		int n = entTec.leInt();	

		if(n==1 || n==2) {
			System.out.printf("No prev prime");
		}

		// Check is prime
		int prime = 0;
		for(int i=n-1;i>=0;i--){
			boolean isPrime=false;
			for(int j=2;j<=Math.sqrt(i);j++){
				if(i%j==0){
					isPrime = true;
					break;
				}
			}
			if(isPrime){
				prime = i;
				break;
			}
		}

		if(prime == 0){
			System.out.println("There is no prime");
		}else{
			System.out.printf("Prev prime: %d\n", prime);
		}
	}
}
