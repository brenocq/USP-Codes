import java.util.*;

public class Quadrado extends FiguraGeometrica
{
	private Double lado;

	public Quadrado(String cor, Boolean filled, Double lado) {
		super(cor, filled);
		this.lado = lado;
	}

	public Double getLado() {
		return lado;
	}

	@Override
	public String toString() {
		String result = "Quadrado da cor " + this.getCor();
		if(this.getFilled())
			result+=" preenchido ";
		else
			result+=" vazio ";

		result+="de lado " + this.getLado();
		return result;
	}
}

