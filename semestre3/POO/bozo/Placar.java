/**
 * Esta classe representa o placar de um jogo de Bozó. 
 * Permite que combinações de dados sejam alocadas às posições e mantém o escore de um jogador.
 * @author Breno Cunha Queiroz
 */
public class Placar {
	private int score;
	private int[] pontos = new int[10]{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
	/**
	 * Adiciona uma sequencia de dados em uma determinada posição do placar.
	 * @param posicao Posição a ser preenchida. 
	 * As posições 1 a 6 correspondem às quantidas de uns até seis, ou seja, as laterais do placar. 
	 * As outas posições são: 7 - full hand; 8 - sequencia; 9 - quadra; e 10 - quina
	 * @param dados um array de inteiros, de tamanho 5.
	 * Cada posição corresponde a um valor de um dado.
	 * Supões-se que cada dado pode ter valor entre 1 e 6.
	 * @throws IllegalArgumentException Se a posição estiver ocupada ou se for passado um valor de posição inválido, essa exceção é lançada. 
	 * Não é feita nenhuma verificação quanto ao tamanho do array nem quanto ao seu conteúdo.
	 */
	public void add(int posicao, int[] dados) throws java.lang.IllegalArgumentException {
		if(pontos[posicao-1]!=0)	
		{
			throw new IllegalArgumentException("A posição não pode já estar preenchida");
		}
		else
		{
			if(posicao<=10)
			{
				for(int i=0;i<dados.length;i++)
				{
					if(dados[i]==posicao)
					{
						pontos[posicao-1]+=posicao;
					}
				}
				if(pontos[posicao-1]==-1)
					pontos[posicao-1] = 0;
			}
			else
			{
				int[] somaDados= new int[5];
				for(int i=0;i<dados.length;i++)
				{
					somaDados[dados[i]-1]++;
				}
				switch(posicao)
				{
					case 11:
						boolean iguais2 = false;// Dois dados mesmo número
						boolean iguais3 = false;// Tres dados mesmo número
						for(int i=0;i<dados.length;i++)
						{
							if(somaDados[i]==2)
								iguais2=true;
							if(somaDados[i]==3)
								iguais3=true;
						}
						if(iguais2 && iguais3)
						{
							pontos[10]=15;
						}
						else
						{
							pontos[10]=0;
						}
						break;
					case 12:
						boolean dados1a5 = true;
						boolean dados2a6 = true;
						if(somaDados[0]!=0)
							dados1a5 = false;
						if(somaDados[5]!=0)
							dados2a6 = false;
						for(int i=0;i<dados.length;i++)
						{
							if(somaDados[i]>=2)
							{
								dados1a5=false;
								dados2a6=false;
							}
						}
						if(dados1a5 || dados2a6)
						{
							pontos[11]=20;
						}
						else
						{
							pontos[11]=0;
						}
						break;
					case 13:
						boolean iguais4 = false;// Quatro dados mesmo número
						for(int i=0;i<dados.length;i++)
						{
							if(somaDados[i]==4)
								iguais4=true;
						}
						if(iguais4)
						{
							pontos[12]=30;
						}
						else
						{
							pontos[12]=0;
						}
						break;
					case 14:
						boolean iguais5 = false;// Cinco dados mesmo número
						for(int i=0;i<dados.length;i++)
						{
							if(somaDados[i]==5)
								iguais5=true;
						}
						if(iguais5)
						{
							pontos[13]=40;
						}
						else
						{
							pontos[13]=0;
						}
						break;
				}
			}
		}
	}

	/**
	 * Computa a soma dos valores obtidos, considerando apenas as posições que já estão ocupadas.
	 * @return O valor da soma.
	 */
	public int getScore() {

	}

	/**
	 *A representação na forma de string, mostra o placar completo, 
	 indicando quais são as posições livres (com seus respectivos números) e o valor obtido nas posições já ocupadas. 
	 Por exemplo:
	 (1)    |   (7)    |   (4) 
	 --------------------------
	 (2)    |   20     |   (5) 
	 --------------------------
	 (3)    |   30     |   (6) 
	--------------------------
			|   (10)   |
			+----------+  
	mostra as posições 8 (sequencia) e 9 (quadra) ocupadas.
	 */
	@Override
	public String toString() {

	}
}

