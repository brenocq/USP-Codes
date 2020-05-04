import java.util.*;

public class MinhasFiguras
{
	public static void main(String[] args){
		Circulo circulo = new Circulo("azul", false, 0.5);
		Quadrado quadrado = new Quadrado("vermelha", true, 0.2);
		Retangulo retangulo = new Retangulo("amarela", false, 0.2, 0.5);

		System.out.println(circulo);
		System.out.println(quadrado);
		System.out.println(retangulo);
	}
}
