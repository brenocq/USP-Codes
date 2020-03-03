
import java.io.IOException;

public class Exercicio2 {
	public static void main (String arg []) throws IOException{
		EntradaTeclado entTec = new EntradaTeclado();
		System.out.println("Please enter a number");
		int n = entTec.leInt();	

			for(int j=0;j<n;j++){
		for(int i=n;n>0;n--){
				System.out.printf("*");
			}
			System.out.println("");
		}
	}
}
