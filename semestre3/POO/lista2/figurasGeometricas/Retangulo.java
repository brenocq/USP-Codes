import java.util.*;

public class Retangulo extends FiguraGeometrica
{
	private Double largura;
	private Double altura;

	public Retangulo(String cor, Boolean filled, Double largura, Double altura) {
		super(cor, filled);
		this.largura = largura;
		this.altura = altura;
	}

	public Double getLargura() {
		return largura;
	}

	public Double getAltura() {
		return altura;
	}

	@Override
	public String toString() {
		String result = "Retangulo da cor " + this.getCor();
		if(this.getFilled())
			result+=" preenchido ";
		else
			result+=" vazio ";

		result+="de largura " + this.getLargura();
		result+=" e altura " + this.getAltura();
		return result;
	}
}

