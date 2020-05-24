import java.util.*;

public class Produto
{
	protected Integer codigoDeBarras;
	protected String nome;
	protected String categoria;
	protected Float preco;

	public Produto(Integer codigoDeBarras, String nome, String categoria, Float preco) {
		this.codigoDeBarras = codigoDeBarras;
		this.nome = nome;
		this.categoria = categoria;
		this.preco = preco;
	}

	public Integer getCodigoDeBarras() {
		return codigoDeBarras;
	}

	public String getNome() {
		return nome;
	}

	public String getCategoria() {
		return categoria;
	}

	public Float getPreco() {
		return preco;
	}
}
