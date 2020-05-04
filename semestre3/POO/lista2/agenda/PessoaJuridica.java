import java.util.*;

public class PessoaJuridica extends Contato
{
	private String CNPJ;
	private String inscricaoEstadual;
	private String razaoSocial;

	public PessoaJuridica(String nome, String email, String endereco, String CNPJ, String inscricaoEstadual, String razaoSocial) {
		super(nome, email, endereco);
		this.CNPJ = CNPJ;
		this.inscricaoEstadual = inscricaoEstadual;
		this.razaoSocial = razaoSocial;
	}

	public String getCNPJ() {
		return CNPJ;
	}

	public String getInscricaoEstadual() {
		return inscricaoEstadual;
	}

	public String getRazaoSocial() {
		return razaoSocial;
	}

	@Override
	public String toString() {
		String result = "";
		result+="Nome: " + getNome() + "\n";
		result+="Email: " + getEmail() + "\n";
		result+="Endereço: " + getEndereco() + "\n";
		result+="CNPJ: " + getCNPJ() + "\n";
		result+="Inscricao estadual: " + getInscricaoEstadual() + "\n";
		result+="Razao social: " + getRazaoSocial() + "\n";
		return result;
	}
}
