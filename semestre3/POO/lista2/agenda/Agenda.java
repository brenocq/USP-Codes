import java.util.*;

public class Agenda
{
	private Contato contatos[] = new Contato[100];
	private int nContatos = 0;
	private int maxContatos = 100;

	public static void main(String[] args) throws Exception {
		int opcao = 0;
		Agenda agenda = new Agenda();
		
		while (opcao != 5) {
        	System.out.println("1) Adicionar Contato\n2) Remover Contato\n3) Pesquisar Contato\n4) Imprimir contatos\n5) Sair");
			opcao = agenda.leOpcao(5);
			switch (opcao)
			{
			case 1: 
				System.out.println("************ Criar contato **************");
				agenda.criarContato();
				break;
			case 2: 
				System.out.println("************ Remover contato **************");
				agenda.removerContato();
				break;
			case 3:
				System.out.println("************ Pesquisar contato **************");
				agenda.pesquisarContato();
				break;
			case 4:
				System.out.println("************ Imprimir contatos **************");
				agenda.imprimirContatos();
				break;
			case 5:
				System.out.println("Terminando o programa...");
				return;
			}
			System.out.println("Digite ENTER para continuar");
			EntradaTeclado.leString();
			System.out.println("\n\n");
		}
	}

	private void criarContato() {
		if(nContatos>=maxContatos) {
			System.out.println("A agenda está cheia, não é possível inserir novos contatos.");
			return;
		}

		int opcao = -1;
        System.out.println("1) Pessoa física\n2) Pessoa jurídica\n");
		opcao = leOpcao(5);
		String nome, email, endereco;

		switch(opcao) {
			case 1:
				String cpf, nascimento, estadoCivil;
        		System.out.println("************ Criar pessoa física ************");
				nome = leInput("Nome: ");
				email = leInput("Email: ");
				endereco = leInput("Endereco: ");
				cpf = leInput("CPF: ");
				nascimento = leInput("Nascimento: ");
				estadoCivil = leInput("Estado Civil: ");

				PessoaFisica pf = new PessoaFisica(nome, email, endereco, cpf, nascimento, estadoCivil);
				contatos[nContatos++] = pf;
				System.out.println("\n" + nome + " adicionado com sucesso!");
				break;
			case 2:
				String cnpj, inscricaoEstadual, razaoSocial;
        		System.out.println("************ Criar pessoa jurídica ************");
				nome = leInput("Nome: ");
				email = leInput("Email: ");
				endereco = leInput("Endereco: ");
				cnpj = leInput("CNPJ: ");
				inscricaoEstadual = leInput("Inscrição Estadual: ");
				razaoSocial = leInput("Razão Social: ");

				PessoaJuridica pj = new PessoaJuridica(nome, email, endereco, cnpj, inscricaoEstadual, razaoSocial);
				contatos[nContatos++] = pj;
				System.out.println("\n" + nome + " adicionado com sucesso!");
				break;
		}
	}
	
	private void removerContato() {
		int id = -1;
		// Receber id para deletar
        while (true)
        {
			System.out.print("Qual o id do contato que você deseja deletar? ");
        	try {
        		id = EntradaTeclado.leInt();
        		if (id >= 0 && id < nContatos)
        			break;
				if(id==-1)
					return;
				System.out.println("Id inválido, tente novamente ou digite -1 para cancelar.");
        	}
        	catch (Exception e) {
				System.out.println("Id inválido, tente novamente ou digite -1 para cancelar.");
        	}
        }
		// Mostra contato
		if(contatos[id] instanceof PessoaFisica) {
			System.out.println("\nId: " + id);
			System.out.println("Nome: " + ((PessoaFisica)contatos[id]).getNome());
			System.out.println("Nome: " + ((PessoaFisica)contatos[id]).getNome());
			System.out.println("Email: " + ((PessoaFisica)contatos[id]).getEmail());
			System.out.println("Endereço: " + ((PessoaFisica)contatos[id]).getEndereco());
			System.out.println("CPF: " + ((PessoaFisica)contatos[id]).getCPF());
			System.out.println("Nascimento: " + ((PessoaFisica)contatos[id]).getNascimento());
			System.out.println("Estado Civil: " + ((PessoaFisica)contatos[id]).getEstadoCivil());
		}else if(contatos[id] instanceof PessoaJuridica) {
			System.out.println("\nId: " + id);
			System.out.println("Nome: " + ((PessoaJuridica)contatos[id]).getNome());
			System.out.println("Email: " + ((PessoaJuridica)contatos[id]).getEmail());
			System.out.println("Endereço: " + ((PessoaJuridica)contatos[id]).getEndereco());
			System.out.println("CNPJ: " + ((PessoaJuridica)contatos[id]).getCNPJ());
			System.out.println("Inscrição Estadual: " + ((PessoaJuridica)contatos[id]).getInscricaoEstadual());
			System.out.println("Razão Social: " + ((PessoaJuridica)contatos[id]).getRazaoSocial());
		}
		// Confirmação para deletar
		String confirmacao;

		System.out.println("");
        while (true)
        {
			System.out.print("Tem certeza que deseja deletar o contato acima?(s/n) ");
        	try {
        		confirmacao = EntradaTeclado.leString();
				if(confirmacao.length()==1 && confirmacao.charAt(0)=='s')
					break;
				if(confirmacao.length()==1 && confirmacao.charAt(0)=='n')
					return;
				System.out.println("Entrada inválida.");
        	}
        	catch (Exception e) {
				System.out.println("Entrada inválida.");
        	}
        }
		// Deletar contato neste id (shift outros contatos)
		for(int i=id;i<nContatos && i+1<maxContatos;i++)
			contatos[i]=contatos[i+1];
		nContatos--;
		System.out.println("Contato removido com sucesso!");
	}

	private void pesquisarContato() {
		String pesquisa = leInput("Pesquisar por uma parte do nome ou CPF/CNPJ: ");
		for(int i=0;i<nContatos;i++) {
			if(contatos[i] instanceof PessoaFisica) {
				if(((PessoaFisica)contatos[i]).getNome().contains(pesquisa) || 
					((PessoaFisica)contatos[i]).getCPF().contains(pesquisa)) {
						System.out.println("Id: " + i);
						System.out.println("Nome: " + ((PessoaFisica)contatos[i]).getNome());
						System.out.println("Nome: " + ((PessoaFisica)contatos[i]).getNome());
						System.out.println("Email: " + ((PessoaFisica)contatos[i]).getEmail());
						System.out.println("Endereço: " + ((PessoaFisica)contatos[i]).getEndereco());
						System.out.println("CPF: " + ((PessoaFisica)contatos[i]).getCPF());
						System.out.println("Nascimento: " + ((PessoaFisica)contatos[i]).getNascimento());
						System.out.println("Estado Civil: " + ((PessoaFisica)contatos[i]).getEstadoCivil());
						System.out.println("");
					}
			}else if(contatos[i] instanceof PessoaJuridica) {
				if(((PessoaJuridica)contatos[i]).getNome().contains(pesquisa) || 
					((PessoaJuridica)contatos[i]).getCNPJ().contains(pesquisa)) {
						System.out.println("Id: " + i);
						System.out.println("Nome: " + ((PessoaJuridica)contatos[i]).getNome());
						System.out.println("Email: " + ((PessoaJuridica)contatos[i]).getEmail());
						System.out.println("Endereço: " + ((PessoaJuridica)contatos[i]).getEndereco());
						System.out.println("CNPJ: " + ((PessoaJuridica)contatos[i]).getCNPJ());
						System.out.println("Inscrição Estadual: " + ((PessoaJuridica)contatos[i]).getInscricaoEstadual());
						System.out.println("Razão Social: " + ((PessoaJuridica)contatos[i]).getRazaoSocial());
						System.out.println("");
					}
			}
		}
	}
	
	private void imprimirContatos() {
		for(int i=0;i<nContatos;i++) {
			if(contatos[i] instanceof PessoaFisica) {
				System.out.println("Id: " + i);
				System.out.println("Nome: " + ((PessoaFisica)contatos[i]).getNome());
				System.out.println("Email: " + ((PessoaFisica)contatos[i]).getEmail());
				System.out.println("Endereço: " + ((PessoaFisica)contatos[i]).getEndereco());
				System.out.println("CPF: " + ((PessoaFisica)contatos[i]).getCPF());
				System.out.println("Nascimento: " + ((PessoaFisica)contatos[i]).getNascimento());
				System.out.println("Estado Civil: " + ((PessoaFisica)contatos[i]).getEstadoCivil());
				System.out.println("");
			}else if(contatos[i] instanceof PessoaJuridica) {
				System.out.println("Id: " + i);
				System.out.println("Nome: " + ((PessoaJuridica)contatos[i]).getNome());
				System.out.println("Email: " + ((PessoaJuridica)contatos[i]).getEmail());
				System.out.println("Endereço: " + ((PessoaJuridica)contatos[i]).getEndereco());
				System.out.println("CNPJ: " + ((PessoaJuridica)contatos[i]).getCNPJ());
				System.out.println("Inscrição Estadual: " + ((PessoaJuridica)contatos[i]).getInscricaoEstadual());
				System.out.println("Razão Social: " + ((PessoaJuridica)contatos[i]).getRazaoSocial());
				System.out.println("");
			}
		}
	}

	private static String leInput(String text) {
		String result;

		while(true) {
        	try {
				System.out.print(text);
				result = EntradaTeclado.leString();
				if(result.length() == 0){
					System.out.println("A entrada não deve ser vazia.");
					continue;
				}
				return result;
        	}
        	catch (Exception e) {
				System.out.println("Formato de entrada incorreto.");
        	}
		}
	}

	private static int leOpcao(int numOpcoes) {
        int opcao = -1;
        while (true)
        {
        	System.out.print("Digite a opção desejada ===> ");
        	try {
        		opcao = EntradaTeclado.leInt();
        		if ( opcao > 0 && opcao <= numOpcoes )
        			return opcao;
        	}
        	catch (Exception e) {
        		;
        	}
        }
	}

}
