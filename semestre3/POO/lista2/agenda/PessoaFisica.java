import java.util.*;

public class PessoaFisica extends Contato
{
	private String CPF;
	private String nascimento;
	private String estadoCivil;

	public PessoaFisica(String nome, String email, String endereco, String CPF, String nascimento, String estadoCivil) {
		super(nome, email, endereco);
		this.CPF = CPF;
		this.nascimento = nascimento;
		this.estadoCivil = estadoCivil;
	}

	public String getCPF() {
		return CPF;
	}

	public String getNascimento() {
		return nascimento;
	}

	public String getEstadoCivil() {
		return estadoCivil;
	}

	@Override
	public String toString() {
		String result = "";
		result+="Nome: " + getNome() + "\n";
		result+="Email: " + getEmail() + "\n";
		result+="Endereço: " + getEndereco() + "\n";
		result+="CPF: " + getCPF() + "\n";
		result+="Nascimento: " + getNascimento() + "\n";
		result+="Estado Civil: " + getEstadoCivil() + "\n";
		return result;
	}
}

