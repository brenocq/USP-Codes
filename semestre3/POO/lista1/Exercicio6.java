
import java.io.IOException;
import java.lang.Math; 

public class Exercicio6 {
	public static void main (String arg []) throws IOException{
		EntradaTeclado entTec = new EntradaTeclado();
		System.out.println("Please enter float numbers (0 to see the result)");
		float number = entTec.leFloat();	
		float min = number;
		float max = number;

		while(number!=0) {
			min = Math.min(min, number);
			max = Math.max(max, number);
			number = entTec.leFloat();	
		}
		System.out.printf("Result:\n\tMin: %f\n\tMax: %f\n",min,max);
	}
}
