import java.util.*;

public class Circulo extends FiguraGeometrica
{
	private Double raio;

	public Circulo(String cor, Boolean filled, Double raio) {
		super(cor, filled);
		this.raio = raio;
	}

	public Double getRaio() {
		return raio;
	}

	@Override
	public String toString() {
		String result = "Circulo da cor " + this.getCor();
		if(this.getFilled())
			result+=" preenchido ";
		else
			result+=" vazio ";

		result+="de raio " + this.getRaio();
		return result;
	}
}

