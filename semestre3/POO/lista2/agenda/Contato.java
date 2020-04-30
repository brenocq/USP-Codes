import java.util.*;

public class Contato
{
	protected String nome;
	protected String email;
	protected String endereco;

	public Contato(String nome, String email, String endereco) {
		this.nome = nome;
		this.email = email;
		this.endereco = endereco;
	}

	public String getNome() {
		return nome;
	}

	public String getEmail() {
		return email;
	}

	public String getEndereco() {
		return endereco;
	}
}
