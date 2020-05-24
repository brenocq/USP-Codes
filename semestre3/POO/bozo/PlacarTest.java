import static org.junit.Assert.*;

import org.junit.After;
import org.junit.Before;
import org.junit.Test;

/**
 * Esta classe testa a classe Placar.
 * @author Breno Cunha Queiroz
 */
public class PlacarTest {

	private Placar p1;
	@Before
	public void setUp() throws Exception {
		// Cria objeto da classe Placar para testes
		p1 = new Placar();
	}

	@After
	public void tearDown() throws Exception {
		// Deleta objeto com o garbage collector
		p1 = null;
	}
	
	@Test(expected=IllegalArgumentException.class)
	public void testAddArgInferior() {
		// Testa adicionar com posição menor do que o possível
		p1.add(0, new int[] {1,2,3,4,5});
	}
	
	@Test(expected=IllegalArgumentException.class)
	public void testAddArgSuperior() {
		// Testa adicionar com posição maior do que o possível
		p1.add(11, new int[] {1,1,1,1,1});
	}
	
	
	@Test(expected=IllegalArgumentException.class)
	public void testAddPosicaoRepetida() {
		// Testa adicionar na mesma posição pela segunda vez
		p1.add(1, new int[] {1,1,1,1,1});
		p1.add(1, new int[] {1,1,1,1,1});
	}

	@Test
	public void testAddRight() {
		// Pontos esperados
		int esp = 0;
		// Testa posições do placar com valores corretos
		p1.add(1, new int[] {1,1,1,1,1});
		esp+=5;
		p1.add(2, new int[] {1,2,3,4,5});
		esp+=2;
		p1.add(3, new int[] {1,2,3,4,5});
		esp+=3;
		p1.add(4, new int[] {1,2,3,4,5});
		esp+=4;
		p1.add(5, new int[] {1,2,3,4,5});
		esp+=5;
		p1.add(6, new int[] {1,2,3,4,6});
		esp+=6;
		p1.add(7, new int[] {1,1,2,2,2});
		esp+=15;
		p1.add(8, new int[] {1,2,3,4,5});
		esp+=20;
		p1.add(9, new int[] {1,1,1,1,2});
		esp+=30;
		p1.add(10, new int[] {1,1,1,1,1});
		esp+=40;
		
		// Testa o score esperado com o retornado pelo objeto
		int score = p1.getScore();
		assertEquals(esp, score);
	}
	
	@Test
	public void testAddWrong() {
		// Testa posições do placar com valores errados
		p1.add(1, new int[] {2,2,2,2,2});
		p1.add(2, new int[] {1,1,1,1,1});
		p1.add(3, new int[] {1,1,1,1,1});
		p1.add(4, new int[] {1,1,1,1,1});
		p1.add(5, new int[] {1,1,1,1,1});
		p1.add(6, new int[] {1,1,1,1,1});
		p1.add(7, new int[] {1,1,1,1,1});
		p1.add(8, new int[] {1,1,1,1,1});
		p1.add(9, new int[] {1,2,3,4,5});
		p1.add(10, new int[] {1,2,3,4,5});

		int score = p1.getScore();
		assertEquals(0, score);
		
		// Testa if(iguais2 && iguais3) caso 7
		reiniciaPlacar();// Reinicia classe placar para poder adicionar novamente
		p1.add(7, new int[] {1,1,3,3,3});
		reiniciaPlacar();
		p1.add(7, new int[] {1,2,3,3,3});
		reiniciaPlacar();
		p1.add(7, new int[] {1,1,3,4,5});
		reiniciaPlacar();
		p1.add(7, new int[] {1,2,3,4,5});
		reiniciaPlacar();
		
		// Testa if(dados1a5 || dados2a6) caso 8
		reiniciaPlacar();
		p1.add(8, new int[] {1,2,3,4,5});
		reiniciaPlacar();
		p1.add(8, new int[] {2,3,4,5,6});
	}

	@Test
	public void testGetScoreVazio() {
		// Testa placar vazio
		int k = p1.getScore();
		assertEquals(0, k);
	}
	

	@Test
	public void testToString() {
		// Testa placar vazio
		System.out.println(p1);
		
		// Testa placar preenchido no máximo
		p1.add(1, new int[] {1,1,1,1,1});
		p1.add(2, new int[] {2,2,2,2,2});
		p1.add(3, new int[] {3,3,3,3,3});
		p1.add(4, new int[] {4,4,4,4,4});
		p1.add(5, new int[] {5,5,5,5,5});
		p1.add(6, new int[] {6,6,6,6,6});
		p1.add(7, new int[] {1,1,1,2,2});
		p1.add(8, new int[] {1,2,3,4,5});
		p1.add(9, new int[] {1,1,1,1,2});
		p1.add(10, new int[] {1,1,1,1,1});
		System.out.println(p1);
	}
	
	private void reiniciaPlacar() {
		// Deleta objeto e cria novamente para testar mais adições no placar
		p1 = null;
		p1 = new Placar();
	}

}
