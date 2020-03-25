import java.io.IOException;
import java.lang.Math; 

public class Exercicio8 {
	public static void main (String arg []) {
		EntradaTeclado entTec = new EntradaTeclado();
		System.out.println("Initial x:");

		double curr = 0;
		// Le a entrada do usuário até digitar um double
		while(true)
			try{	
				curr  = entTec.leDouble();
				break;
			}catch(Exception e){
				System.out.println("Must enter a double. Please try again");
			}
	
		double last = 0;
		double res1 = solveEq(curr);
		double res2 = solveEq(last);

		// Enquanto o erro for maior que 0.0000001...
		while(Math.abs(res2-res1)>0.0000001) {
			last = curr;
			curr = last-(solveEq(last)/calcTan(last));

			// Para calcular o erro
			res1 = solveEq(curr);
			res2 = solveEq(last);
			System.out.println(curr);
		}
		System.out.printf("Result: f(%f)=%f\n", curr, solveEq(curr));
	}

	public static double solveEq(double x) {
		return x*x*x + x*x - 13*x + 8;
	}
	
	public static double calcTan(double x) {
		return 3*x*x + 2*x - 13;
	}
}
