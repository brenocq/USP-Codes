import java.io.IOException;
import java.lang.Math; 

public class Exercicio8 {
	public static void main (String arg []) throws IOException{
		EntradaTeclado entTec = new EntradaTeclado();
		System.out.println("Initial x:");
		double curr  = entTec.leDouble();
		double last = 0;
		double res1 = solveEq(curr);
		double res2 = solveEq(last);

		while(Math.abs(res2-res1)>0.0000001) {
			last = curr;
			curr = last-(solveEq(last)/calcTan(last));

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
