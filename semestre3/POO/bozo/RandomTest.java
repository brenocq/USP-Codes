import static org.junit.Assert.*;

import org.junit.After;
import org.junit.Before;
import org.junit.Test;
/**
 * Teste da classe Random.
 * @author Breno Cunha Queiroz
 */
public class RandomTest {

	private Random r;
	@Before
	public void setUp() throws Exception {
		// Cria objeto da classe Random para testes
		r = new Random();
	}

	@After
	public void tearDown() throws Exception {
		// Deleta objeto com o garbage collector
		r = null;
	}

	@Test
	public void testRandom() {
		// Testa random com semente randomica
		Random r1 = new Random();
		r1 = null;
	}

	@Test
	public void testRandomInt() {
		// Testa random com semente fixa
		Random r1 = new Random(42);
		r1 = null;
	}

	@Test
	public void testGetIntRand() {
		// Testa se 1000 numeros randomicos estão entre 0 e 10
		int result = 0;
		for(int i=0;i<1000;i++) {
			result = r.getIntRand(10);
			if(result<0 || result>10)
				fail("Resultado do random fora do range");
		}
	}

	@Test
	public void testGetRand() {
		// Testa se 1000 numeros randomicos estão entre 0 e 1
		double result = 0;
		for(int i=0;i<1000;i++) {
			result = r.getRand();
			if(result<0 || result>1)
				fail("Resultado do random fora do range");
		}
	}

	@Test
	public void testSetSemente() {
		r.setSemente(20);
	}

}
