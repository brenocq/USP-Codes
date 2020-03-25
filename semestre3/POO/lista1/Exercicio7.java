import java.io.IOException;
import java.lang.Math; 

public class Exercicio7 {
	public static void main (String arg []) {
		EntradaTeclado entTec = new EntradaTeclado();
		System.out.println("First x:");
		double x1 = 0;
		double x2 = 0;
		// Le a entrada do usuário até digitar um double
		while(true)
			try{	
				x1 =  entTec.leDouble();
				break;
			}catch(Exception e){
				System.out.println("Must enter a double. Please try again");
			}
		System.out.println("Second x:");
		// Le a entrada do usuário até digitar um double
		while(true)
			try{
				x2 = entTec.leDouble();
				if(x2<=x1){
					System.out.println("Must be greater than the first X. Please try again.");
					continue;
				}
				break;
			}catch(Exception e){
				System.out.println("Must enter a double. Please try again");
			}
		// Imprime os resultados nos pontos iniciais 
		System.out.printf("Init:\n\tf(%f)=%f\n\tf(%f)=%f\n\n", x1, solveEq(x1), x2, solveEq(x2));

		double res1 = solveEq(x1);
		double res2 = solveEq(x2);
		// Enquanto o erro for maior que 0.0000001...
		while(Math.abs(res2-res1)>0.0000001) {
			double mean = (x1+x2)/2;
			double resMean = solveEq(mean);

			// Atribuição para diminuir o intervalo
			if(resMean<=0) {
				x1 = mean;
			}else{
				x2 = mean;
			}

			// Para calcular o erro
			res1 = solveEq(x1);
			res2 = solveEq(x2);
		}
		System.out.printf("Result: f(%f)=%f\n", x1, solveEq(x1));
	}

	public static double solveEq(double x) {
		return x*x*x + x*x - 13*x + 8;
	}


}
