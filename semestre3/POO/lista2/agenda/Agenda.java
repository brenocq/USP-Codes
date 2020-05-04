import java.util.*;

public class Agenda
{
	private Contato contatos[] = new Contato[100];
	private int nContatos = 0;
	private int maxContatos = 100;

	public static void main(String[] args) throws Exception {
		int opcao = 0;
		Agenda agenda = new Agenda();
		
		while (opcao != 6) {
        	System.out.println("1) Adicionar Contato\n2) Remover Contato\n3) Pesquisar Contato\n4) Imprimir contatos\n5) Ordena\n6) Sair");
			opcao = agenda.leOpcao(6);
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
				System.out.println("************ Ordena contatos **************");
				agenda.ordena();
				break;
			case 6:
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
		opcao = leOpcao(2);
		String nome, email, endereco;

		switch(opcao) {
			case 1:
				String cpf, nascimento, estadoCivil;
        		System.out.println("************ Criar pessoa física ************");
				nome = leInput("Nome: ");
				email = leInput("Email: ");
				endereco = leInput("Endereco: ");
				cpf = leInput("CPF: ");
				cpf = cpf.replace("-","");
				cpf = cpf.replace(" ","");
				cpf = cpf.replace(".","");
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
				cnpj = cnpj.replace("-","");
				cnpj = cnpj.replace(" ","");
				cnpj = cnpj.replace(".","");
				cnpj = cnpj.replace("/","");
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
			System.out.println("Id: " + id);
			System.out.println(((PessoaFisica)contatos[id]));
		}else if(contatos[id] instanceof PessoaJuridica) {
			System.out.println("Id: " + id);
			System.out.println(((PessoaJuridica)contatos[id]));
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
						System.out.println(((PessoaFisica)contatos[i]));
						System.out.println("");
					}
			}else if(contatos[i] instanceof PessoaJuridica) {
				if(((PessoaJuridica)contatos[i]).getNome().contains(pesquisa) || 
					((PessoaJuridica)contatos[i]).getCNPJ().contains(pesquisa)) {
						System.out.println("Id: " + i);
						System.out.println(((PessoaJuridica)contatos[i]));
						System.out.println("");
					}
			}
		}
	}
	
	private void imprimirContatos() {
		for(int i=0;i<nContatos;i++) {
			if(contatos[i] instanceof PessoaFisica) {
				System.out.println("Id: " + i);
				System.out.println(((PessoaFisica)contatos[i]));
				System.out.println("");
			}else if(contatos[i] instanceof PessoaJuridica) {
				System.out.println("Id: " + i);
				System.out.println(((PessoaJuridica)contatos[i]));
				System.out.println("");
			}
		}
	}

	private void ordena() {
		for(int i=0;i<this.nContatos;i++) {
			for(int j=i+1;j<this.nContatos;j++) {
				if(contatos[j] instanceof PessoaFisica && contatos[i] instanceof PessoaJuridica){
					Contato temp = contatos[j];
					contatos[j] = contatos[i];
					contatos[i] = temp;
				}else if(contatos[j] instanceof PessoaFisica && contatos[i] instanceof PessoaFisica &&
					((PessoaFisica)contatos[j]).getCPF().compareTo(((PessoaFisica)contatos[i]).getCPF())<0){

					PessoaFisica temp = (PessoaFisica)contatos[j];
					contatos[j] = contatos[i];
					contatos[i] = temp;
				}else if(contatos[j] instanceof PessoaJuridica && contatos[i] instanceof PessoaJuridica &&
					((PessoaJuridica)contatos[j]).getCNPJ().compareTo(((PessoaJuridica)contatos[i]).getCNPJ())<0){

					PessoaJuridica temp = (PessoaJuridica)contatos[j];
					contatos[j] = contatos[i];
					contatos[i] = temp;
				}
			}
		}
		System.out.println("Os contatos foram ordenados!");
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
