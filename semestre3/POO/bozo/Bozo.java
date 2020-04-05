import java.util.*;
import java.io.IOException;

/**
 * Essa é a classe inicial do programa Bozó. 
 * Possui apenas o método main, que cuida da execução do jogo.
 * @author Breno Cunha Queiroz
 */
public class Bozo {
	/**
	 * Método inicial do programa. 
	 * Ele cuida da execução do jogo e possui um laço, no qual cada iteração representa uma rodada do jogo. 
	 * Em cada rodada, o jogador joga os dados até 3 vezes e depois escolhe a posição do placar que deseja preencher. 
	 * No final das rodadas a pontuação total é exibida.
	 * @param args
	 * @throws IOException
	 */
	public static void main(String[] args) throws java.io.IOException {
		// Cria objetos
		Placar placar = new Placar();
		RolaDados rolaDados = new RolaDados(5);
		EntradaTeclado enTec = new EntradaTeclado();

		// Executa 10 rodadas
		for(int rodada=1;rodada<=10;rodada++)
		{
			// Imprime placar
			System.out.println(placar);

			// Imprime mensagem inicio rodada
			System.out.println("****** Rodada "+rodada);
			System.out.println("Pressione ENTER para lançar os dados");

			// Espera ENTER para rolar dados
			enTec.leString();
			int[] dados = rolaDados.rolar();
			// Imprime dados
			System.out.println(rolaDados);

			// Repete três vezes para receber quais dados o usuario quer rolar novamente
			for(int i=0;i<3;i++)
			{
				// Recebe quais dados serão rodados novamente
				System.out.println("Digite os números dos dados que quiser TROCAR. Separados por espaços.");
				String input = enTec.leString();

				// Preenche o vetor boolean com os dados selecionados
				String[] inputSplit = input.split(" ");
				boolean[] quais = {false, false, false, false, false};
				for(int j=0;j<inputSplit.length;j++)
				{
					try
					{
						quais[Integer.parseInt(inputSplit[j])-1] = true;
					}
					catch(NumberFormatException e)
					{
						continue;
					}
				}
				// Rola os dados
				dados = rolaDados.rolar(quais);
				System.out.println(rolaDados);
			}
			// Contabiliza ponto no placar
			System.out.println(placar);
			int posicao = -1;
			while(true)
			{
				// Recebe posição do usuário
				System.out.print("Escolha a posição que quer ocupar com essa jogada ===> ");
				while(true)
				{
					try
					{
						posicao = enTec.leInt();
						break;
					}
					catch(NumberFormatException e)
					{
						System.out.println("Por favor insira um valor");
						System.out.print("Escolha a posição que quer ocupar com essa jogada ===> ");
					}
				}
				// Contabiliza pontos no placar
				try
				{
					placar.add(posicao, dados);
					break;
				}
				catch(IllegalArgumentException e)
				{
					System.out.println(e.getMessage());	
				}
			}
		}
		System.out.println(placar);

		System.out.println("*************************************");
		System.out.println("*****");
		System.out.println("***** Seu escore final foi: "+placar.getScore());
		System.out.println("*****");
		System.out.println("*************************************");
	}
}

