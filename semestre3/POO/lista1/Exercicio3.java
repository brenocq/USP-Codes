
import java.io.IOException;

public class Exercicio3 {
	public static void main (String arg []) throws IOException{
		EntradaTeclado entTec = new EntradaTeclado();
		System.out.println("Please enter a number");
		int n = entTec.leInt();	

		for(int i=n;i>0;i--){
			for(int j=0;j<n-i;j++){
				System.out.printf(" ");
			}
			for(int j=0;j<i;j++){
				System.out.printf("*");
			}
			System.out.println("");
		}
	}
}
