import java.util.*;

public class FiguraGeometrica
{
	protected String cor;
	protected Boolean filled;

	public FiguraGeometrica(String cor, Boolean filled) {
		this.cor = cor;
		this.filled = filled;
	}

	public String getCor() {
		return cor;
	}

	public Boolean getFilled() {
		return filled;
	}
}
