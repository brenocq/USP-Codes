import static org.junit.Assert.*;

import org.junit.After;
import org.junit.Before;
import org.junit.Test;
/**
 * Teste da classe RolaDados.
 * @author Breno Cunha Queiroz
 */
public class RolaDadosTest {
	private RolaDados rolaDados;
	@Before
	public void setUp() throws Exception {
		// Cria objeto para rolar 5 dados
		rolaDados = new RolaDados(5);
	}

	@After
	public void tearDown() throws Exception {
		// Deleta objeto com o garbage collector
		rolaDados = null;
	}

	@Test
	public void testRolar() {
		// Testa rolar todos os dados
		rolaDados.rolar();
	}

	@Test
	public void testRolarBooleanArray() {
		// Testa rolar com array booleana
		rolaDados.rolar(new boolean[]{true, true, false, false, true});
		rolaDados.rolar(new boolean[]{false, true, false, false, true});
		rolaDados.rolar(new boolean[]{false, false, false, false, false});
		rolaDados.rolar(new boolean[]{true, true, true, true, true});
	}

	@Test
	public void testRolarString() {
		// Testa rola dados com diferentes combinações
		rolaDados.rolar(new String("1 2 3 4 5"));
		rolaDados.rolar(new String("1 2 3"));
		rolaDados.rolar(new String("5"));
		// Nenhum dado deve ser rolado neste caso
		rolaDados.rolar(new String("-1 7 100"));
	}

	@Test
	public void testToString() {
		System.out.println(rolaDados);
	}

}
