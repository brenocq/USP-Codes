import java.util.*;

public class DVD extends Produto
{
	public DVD(Integer codigoDeBarras, String nome, String categoria, Float preco) {
		super(codigoDeBarras, nome, categoria, preco);
	}

	@Override
	public String toString() {
		String result = "";
		result+="------ DVD -----\n";
		result+="Cod: " + getCodigoDeBarras() + "\n";
		result+="Nome: " + getNome() + "\n";
		result+="Categoria: " + getCategoria() + "\n";
		result+="Preço: R$" + getPreco() + "\n";
		return result;
	}
}
