import java.util.*;

public class CD extends Produto
{
	public CD(Integer codigoDeBarras, String nome, String categoria, Float preco) {
		super(codigoDeBarras, nome, categoria, preco);
	}

	@Override
	public String toString() {
		String result = "";
		result+="------ CD -----\n";
		result+="Cod: " + getCodigoDeBarras() + "\n";
		result+="Nome: " + getNome() + "\n";
		result+="Categoria: " + getCategoria() + "\n";
		result+="Preço: R$" + getPreco() + "\n";
		return result;
	}
}
