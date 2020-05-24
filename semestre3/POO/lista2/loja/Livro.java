import java.util.*;

public class Livro extends Produto
{
	private String autor;
	private String dataPublicacao;

	public Livro(Integer codigoDeBarras, String nome, String categoria, Float preco, String autor, String dataPublicacao) {
		super(codigoDeBarras, nome, categoria, preco);
		this.autor = autor;
		this.dataPublicacao = dataPublicacao;
	}

	public String getAutor() {
		return autor;
	}

	public String getDataPublicacao() {
		return dataPublicacao;
	}

	@Override
	public String toString() {
		String result = "";
		result+="------ Livro -----\n";
		result+="Cod: " + getCodigoDeBarras() + "\n";
		result+="Nome: " + getNome() + "\n";
		result+="Autor: " + getAutor() + "\n";
		result+="Categoria: " + getCategoria() + "\n";
		result+="Data de publicação: " + getDataPublicacao() + "\n";
		result+="Preço: R$" + getPreco() + "\n";
		return result;
	}
}
