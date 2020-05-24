import static org.junit.Assert.*;

import org.junit.After;
import org.junit.Before;
import org.junit.Test;
/**
 * Teste da classe Dado.
 * @author Breno Cunha Queiroz
 */
public class DadoTest {
	private Dado dado = new Dado();
	
	@Before
	public void setUp() throws Exception {
		// Cria objeto da classe Dado para testes
		dado = new Dado();
	}

	@After
	public void tearDown() throws Exception {
		// Deleta objeto com o garbage collector
		dado = null;
	}

	@Test
	public void testDado() {
		// Testa dado com criação padão
		Dado test = new Dado();
		test = null;	
	}

	@Test
	public void testDadoInt() {
		// Testa dado com numero de faces diferente de 6
		Dado test = new Dado(12);
		test = null;
	}

	@Test
	public void testGetLado() {
		// Recebe lado
		int l = dado.getLado();
	}

	@Test
	public void testRolar() {
		// Rola o dado
		dado.rolar();
	}

	@Test
	public void testToString() {
		// Testa imprimir varios dados diferentes
		for(int i=0;i<30;i++)
		{
			dado.rolar();
			System.out.println(dado);
		}
		// Testa imprimir dado de 12 lados (se lado maior que 6, não imprime)
		Dado dado12 = new Dado(12);
		for(int i=0;i<30;i++)
		{
			dado12.rolar();
			System.out.println(dado12);
		}
		dado12 = null;
	}
}
