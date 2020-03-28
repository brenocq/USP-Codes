/**
 * Gerador simples de números aleatórios.
 * @author Breno Cunha Queiroz
 */
public class Random {
	private long p = 3648L;
	private long m = 7094L;
	private long a = 35039L;
	public long semente = 1023;// Seed

	/**
	 * Construtor que usa uma semente aleatória, adquerida usando o método Calendar.getTimeInMillis().
	 */
	public Random() {

	}

	/**
	 * Construtor que permite criar o gerador, especificando o valor inicial da semente.
	 * @param k O valor inicial da semente.
	 */
	public Random(int k){
		semente = k;
	}

	/**
	 * Retorna um valor inteiro no intervalo (0,max[
	 * @param max O valor limite para a geração do número inteiro
	 * @return O número gerado
	 */
	public int getIntRand(int max) {
		double d = getRand()*max;
		return (int)d;
	}

	/**
	 * Retorna um número aleatório no intervalo (0,1[
	 * @return O número gerado
	 */
	public double getRand() {
		xi = (a+m*xi)%p;
		return (double)xi/p;
	}
	

	/**
	 * Permite alterar a semente de geração de números aleatórios.
	 * Supostamente deve ser chamada antes de iniciar a geração, mas se for chamado a qualquer instante, reseta o valor da semante
	 * @param semente O valor da nova semente de geração
	 */
	public void setSemente(int semente){
		this.semente = semente
	}
}
