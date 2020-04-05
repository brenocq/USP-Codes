import java.util.*;
/**
 * Simula um dado de número de lados variados. 
 * Ao criar o objeto é possível estabelecer o número de lados. 
 * A rolagem do dado é feita por meio de um gerador de números aleatórios (Random).
 * @author Breno Cunha Queiroz
 */
public class Dado {
	private int lado;
	private int numLados;
	private Random rand;

	/**
	 * Cria um dado com 6 lados (um cubo) 
	 */
	public Dado() {
		rand = new Random();

		numLados = 6;
		lado = rand.getIntRand(numLados)+1;
	}

	/**
	 * Cria objeto com um número qualquer de lados
	 * @param n número de lados do dado
	 */
	public Dado(int n) {
		rand = new Random();

		numLados = n;
		lado = rand.getIntRand(numLados)+1;
	}

	/**
	 * Recupera o último número selecionado.
	 * @return o número do último lado selecionado. 
	 */
	public int getLado() {
		return lado;
	}

	/**
	 * Simula a rolagem do dado por meio de um gerador aleatório. 
	 * O número selecionado pode posteriormente ser recuperado com a chamada a getLado()
	 * @return o número que foi sorteado
	 */
	public int rolar() {
		lado = rand.getIntRand(numLados)+1;
		return lado;
	}

	/**
	 * Transforma representação do dado em String. 
	 * É mostrada uma representação do dado que está para cima.
	 * Note que só funciona corretamente para dados de 6 lados. Exemplo:
		+-----+    
		|*   *|    
		|  *  |    
		|*   *|    
		+-----+    
	 */
	@Override
	public String toString() {
		switch(lado)
		{
			case 1:
				return "+-----+\n|     |\n|  *  |\n|     |\n+-----+\n";
			case 2:
				return "+-----+\n|*    |\n|     |\n|    *|\n+-----+\n";
			case 3:
				return "+-----+\n|*    |\n|  *  |\n|    *|\n+-----+\n";
			case 4:
				return "+-----+\n|*   *|\n|     |\n|*   *|\n+-----+\n";
			case 5:
				return "+-----+\n|*   *|\n|  *  |\n|*   *|\n+-----+\n";
			case 6:
				return "+-----+\n|* * *|\n|     |\n|* * *|\n+-----+\n";
		}
		return "";
	}
}

