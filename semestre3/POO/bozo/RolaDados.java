import java.util.*;

/**
 * Essa é uma classe auxiliar que permite gerencia um conjunto de vários dados simultaneamente.
 * Operações como rolar alguns dos dados ou exibir o resultado de todos eles, são implementadas.
 * @author Breno Cunha Queiroz
 */
public class RolaDados {
	private Vector<Dado> dados = new Vector<Dado>();

	/**
	 * Construtor que cria e armazena vários objetos do tipo Dado.
	 * Usa para isso o construtor padrão daquela classe, ou seja, um dado de 6 lados e gerando sempre uma semente aleatória para o gerador de números aleatórios.
	 * Os dados criados podem ser referenciados por números, entre 1 e n.
	 * @param n Número de dados a serem criados.
	 */
	public RolaDados(int n) {
		for(int i=0;i<n;i++)
		{
			Dado dado = new Dado(6);
			dados.addElement(dado);
		}
	}

	/**
	 * Rola todos os dados.
	 * @return Retorna o valor de cada um dos dados, inclusive os que não foram rolados.
	 * Nesse caso, o valor retornado é o valor anterior que ele já possuia.
	 */
	public int[] rolar() {
		int[] results = new int[dados.size()];
		for(int i=0;i<dados.size();i++)
		{
			results[i] = dados.get(i).rolar();
		}
		return results;
	}

	/**
	 * Rola alguns dos dados.
	 * @param quais É um array de booleanos que indica quais dados devem ser rolados.
	 * Cada posição representa um dos dados.
	 * Ou seja, a posição 0 do array indica se o dado 1 deve ser rolado ou não, e assim por diante.
	 * @return Retorna o valor de cada um dos dados, inclusive os que não foram rolados.
	 * Nesse caso, o valor retornado é o valor anterior que ele já possuia.
	 */
	public int[] rolar(boolean[] quais) {
		int[] results = new int[dados.size()];
		for(int i=0;i<dados.size();i++)
		{
			if(quais[i])
			{
				results[i] = dados.get(i).rolar();
			}
			else
			{
				results[i] = dados.get(i).getLado();
			}
		}
		return results;
	}

	/**
	 * Rola alguns dos dados.
	 * @param s É um String que possui o número dos dados a serem rolados.
	 * Por exemplo "1 4 5" indica que os dados 1 4 e cinco devem ser rolados.
	 * Os números devem ser separados por espaços.
	 * Se o valor passado no string estiver fora do intervalo válido, ele é ignorado simplesmente. 
	 * @return Retorna o valor de cada um dos dados, inclusive os que não foram rolados.
	 * Nesse caso, o valor retornado é o valor anterior que ele já possuia.
	 */
	public int[] rolar(String s) {
		int[] results = new int[dados.size()];
		String[] split = s.split("\\s+");
		// Guarda o lado dos que foram rolados
		for(int i=0;i<split.length;i++)
		{
			int index = Integer.parseInt(split[i])-1;
			if(index>=0 && index<dados.size())
				results[index] = dados.get(index).rolar();
		}
		// Guarda o lado dos que não foram rolados
		for(int i=0;i<results.length;i++)
		{
			if(results[i]==0)
				results[i] = dados.get(i).getLado();
		}
		return results;
	}

	/**
	 * Usa a representação em string do dados, para mostrar o valor de todos os dados do conjunto.
	 * Exibe os dados horisontalmente, por exemplo:
	 *  1          2          3          4          5
		+-----+    +-----+    +-----+    +-----+    +-----+
		|*   *|    |     |    |*    |    |*    |    |*   *|
		|  *  |    |  *  |    |     |    |  *  |    |     |
		|*   *|    |     |    |    *|    |    *|    |*   *|
		+-----+    +-----+    +-----+    +-----+    +-----+

	 */
	@Override
	public String toString() {
		String result = "";
		String[] dadosStr = new String[dados.size()];
		// Recebe string de cada dado
		for(int i=0;i<dados.size();i++)
		{
			result += Integer.toString(i+1)+"          ";
			dadosStr[i] = dados.get(i).toString();
		}
		// Imprime header
		for(int dado=0;dado<dadosStr.length;dado++)
		{
			result+="\t\t";
		}
		result+="\n";

		// Imprime linha por linha
		for(int row=0;row<5;row++)
		{
			for(int dado=0;dado<dadosStr.length;dado++)
			{
				String[] split = dadosStr[dado].split("\n");
				result+=split[row]+"    ";
			}
			result+="\n";
		}
		return result;
	}
}
