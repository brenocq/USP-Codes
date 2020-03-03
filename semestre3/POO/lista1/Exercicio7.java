import java.io.IOException;
import java.lang.Math; 

public class Exercicio7 {
	public static void main (String arg []) throws IOException{
		EntradaTeclado entTec = new EntradaTeclado();
		System.out.println("First x");
		double x1 =  entTec.leDouble();
		System.out.println("Second x");
		double x2 = entTec.leDouble();
		System.out.printf("Init:\n\tf(%f)=%f\n\tf(%f)=%f\n", x1, solveEq(x1), x2, solveEq(x2));

		double res1 = solveEq(x1);
		double res2 = solveEq(x2);
		while(Math.abs(res2-res1)>0.0000001) {
			double mean = (x1+x2)/2;
			double resMean = solveEq(mean);
			if(resMean<=0) {
				x1 = mean;
			}else{
				x2 = mean;
			}

			res1 = solveEq(x1);
			res2 = solveEq(x2);
		}
		System.out.printf("Result: f(%f)=%f\n", x1, solveEq(x1));
	}

	public static double solveEq(double x) {
		return x*x*x + x*x - 13*x + 8;
	}
}
