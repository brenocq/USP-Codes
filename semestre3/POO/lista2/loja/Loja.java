import java.util.*;

public class Loja
{
	private Produto[] produtos = new Produto[100];
	private int nProdutos = 0;
	private int maxProdutos = 100;
	private String[] categorias = {"Ação", "Ficção Científica", "Heróis", "Suspense", "Terror", "Romance"};
	private int[] qtdPorCategoria;
	private int[] qtdPorProduto;

	public static void main(String[] args) throws Exception {
		int opcao = 0;
		Loja loja = new Loja();
		
		while (opcao != 6) {
        	System.out.println("1) Cadastrar Produto\n2) Vender Produto\n3) Remover Produto\n4) Pesquisar Produto\n5) Ver Estoque\n6) Sair");
			opcao = loja.leOpcao(6);
			switch (opcao)
			{
			case 1: 
				System.out.println("************ Cadatrar Produto **************");
				loja.cadastrarProduto();
				break;
			case 2: 
				System.out.println("************ Vender Produto **************");
				loja.venderProduto();
				break;
			case 3:
				System.out.println("************ Remover Produto **************");
				loja.removerProduto();
				break;
			case 4:
				System.out.println("************ Pesquisar Produto **************");
				loja.pesquisarProduto();
				break;
			case 5:
				System.out.println("************ Ver Estoque **************");
				loja.verEstoque();
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

	public Loja() {
		qtdPorCategoria = new int[categorias.length];
		qtdPorProduto = new int[3];
	}

	private void cadastrarProduto() {
		if(nProdutos>=maxProdutos) {
			System.out.println("A loja está lotada. Não é possível adicionar mais produtos.");
			return;
		}

		// Recebe qual o tipo de produto
		int opcao = -1;
        System.out.println("1) Livro\n2) CD\n3) DVD\n");
		opcao = leOpcao(3);
		Integer codigoDeBarras;
		int indexCategoria;
		String nome, categoria;
		Float preco;

		switch(opcao) {
			case 1:
        		System.out.println("************ Cadastrar Livro ************");
				// Lê campos do livro
				String autor, dataPublicacao;
				codigoDeBarras = leCodigoDeBarras();
				nome = leInput("Nome: ");
				indexCategoria = leCategoria();
				categoria = categorias[indexCategoria];
				preco = lePreco();
				autor = leInput("Autor: ");
				dataPublicacao = leInput("Data de publicacao: ");

				// Insere novo livro 
				qtdPorCategoria[indexCategoria]++;
				qtdPorProduto[0]++;
				Livro livro = new Livro(codigoDeBarras, nome, categoria, preco, autor, dataPublicacao);
				produtos[nProdutos++] = livro;
				System.out.println("\n" + nome + " adicionado com sucesso!");
				break;
			case 2:
        		System.out.println("************ Cadastrar CD ************");
				// Lê campos do CD
				codigoDeBarras = leCodigoDeBarras();
				nome = leInput("Nome: ");
				indexCategoria = leCategoria();
				categoria = categorias[indexCategoria];
				preco = lePreco();

				// Insere novo CD
				qtdPorCategoria[indexCategoria]++;
				qtdPorProduto[1]++;
				CD cd = new CD(codigoDeBarras, nome, categoria, preco);
				produtos[nProdutos++] = cd;
				break;
			case 3:
        		System.out.println("************ Cadastrar DVD ************");
				// Lê campos do DVD 
				codigoDeBarras = leCodigoDeBarras();
				nome = leInput("Nome: ");
				indexCategoria = leCategoria();
				categoria = categorias[indexCategoria];
				preco = lePreco();

				// Insere novo DVD
				qtdPorCategoria[indexCategoria]++;
				qtdPorProduto[2]++;
				DVD dvd = new DVD(codigoDeBarras, nome, categoria, preco);
				produtos[nProdutos++] = dvd;
				break;
		}
	}

	private void venderProduto() {
		int codigoDeBarras = -1;
		int indexProduto = -1;
		// Receber codigo de barras do produto para deletar
        while (true)
        {
			System.out.print("Qual o código de barras do produto que você deseja vender? ");
        	try {
        		codigoDeBarras = EntradaTeclado.leInt();
				if(codigoDeBarras==-1)
					return;

				indexProduto = buscaProduto(codigoDeBarras);
				if(indexProduto!=-1)
					break;

				System.out.println("Nenhum produto cadastrado com este código de barras, tente novamente ou digite -1 para cancelar.");
        	}
        	catch (Exception e) {
				System.out.println("Nenhum produto cadastrado com este código de barras, tente novamente ou digite -1 para cancelar.");
        	}
        }
		Produto produto = produtos[indexProduto];
		// Mostra produto que sera deletado
		System.out.println(produto);
		System.out.println("");

		// Subtrai da quantidade por produto de por categoria 
		if(produto instanceof Livro)
			qtdPorProduto[0]--;
		else if(produto instanceof CD)
			qtdPorProduto[1]--;
		else if(produto instanceof DVD)
			qtdPorProduto[2]--;

		for(int i=0;i<categorias.length;i++)
			if(categorias[i] == produto.getCategoria())
				qtdPorCategoria[i]--;

		// Vender produto (shift outros produtos)
		for(int i=indexProduto;i<nProdutos && i+1<maxProdutos;i++)
			produtos[i]=produtos[i+1];
		nProdutos--;

		System.out.println("Produto vendido com sucesso!");
	}
	
	private void removerProduto() {
		int codigoDeBarras = -1;
		int indexProduto = -1;
		// Receber codigo de barras do produto para deletar
        while (true)
        {
			System.out.print("Qual o código de barras do produto que você deseja deletar? ");
        	try {
        		codigoDeBarras = EntradaTeclado.leInt();
				if(codigoDeBarras==-1)
					return;

				indexProduto = buscaProduto(codigoDeBarras);
				if(indexProduto!=-1)
					break;

				System.out.println("Nenhum produto cadastrado com este código de barras, tente novamente ou digite -1 para cancelar.");
        	}
        	catch (Exception e) {
				System.out.println("Nenhum produto cadastrado com este código de barras, tente novamente ou digite -1 para cancelar.");
        	}
        }
		Produto produto = produtos[indexProduto];
		// Mostra produto que sera deletado
		System.out.println(produto);
		System.out.println("");
		// Confirmação para deletar
		String confirmacao;
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

		// Subtrai da quantidade por produto de por categoria 
		if(produto instanceof Livro)
			qtdPorProduto[0]--;
		else if(produto instanceof CD)
			qtdPorProduto[1]--;
		else if(produto instanceof DVD)
			qtdPorProduto[2]--;

		for(int i=0;i<categorias.length;i++)
			if(categorias[i] == produto.getCategoria())
				qtdPorCategoria[i]--;

		// Deletar produto (shift outros produtos)
		for(int i=indexProduto;i<nProdutos && i+1<maxProdutos;i++)
			produtos[i]=produtos[i+1];
		nProdutos--;
		System.out.println("Produto removido com sucesso!");
	}

	private void pesquisarProduto() {
		String pesquisa = leInput("Pesquisar produto por uma parte do nome ou código de barras: ");
		for(int i=0;i<nProdutos;i++) {
			// Checa se o input faz parte de algum nome ou código de barras
			if((produtos[i]).getNome().contains(pesquisa) || 
				(produtos[i]).getCodigoDeBarras().toString().contains(pesquisa)) {
					System.out.println(produtos[i]);
					System.out.println("");
				}
		}
	}
	
	private void imprimirProdutos() {
		for(int i=0;i<nProdutos;i++) {
			if(produtos[i] instanceof Livro) {
				System.out.println(((Livro)produtos[i]));
				System.out.println("");
			}else if(produtos[i] instanceof CD) {
				System.out.println(((CD)produtos[i]));
				System.out.println("");
			}else if(produtos[i] instanceof DVD) {
				System.out.println(((DVD)produtos[i]));
				System.out.println("");
			}
		}
	}

	private void verEstoque() {
		System.out.println("Qtd de produtos: "+nProdutos+"\n");

		System.out.println("Qtd de livros: "+qtdPorProduto[0]);
		System.out.println("Qtd de CDs: "+qtdPorProduto[1]);
		System.out.println("Qtd de DVDs: "+qtdPorProduto[2]+"\n");

		for(int i=0;i<categorias.length;i++)
			System.out.println("Qtd da categoria "+categorias[i]+": "+qtdPorCategoria[i]);
		System.out.println("");

		imprimirProdutos();
	}

	private int buscaProduto(int codigoDeBarras) {
		// Retorna id do produto com código de barras inserido
		for(int i=0;i<nProdutos;i++) {
			if(produtos[i].getCodigoDeBarras() == codigoDeBarras)
				return i;
		}
		return -1;
	}

	private Integer leCodigoDeBarras() {
		Integer codigoDeBarras;

		// Lê input até um código de barras válido ser inserido
		while(true) {
        	try {
				System.out.print("Código de barras: ");
				codigoDeBarras = EntradaTeclado.leInt();

				// Checa se código de barras é único
				boolean unico = true;
				for(int i=0;i<nProdutos;i++) {
					if(produtos[i].getCodigoDeBarras() == codigoDeBarras) {
						unico = false;
						break;
					}
				}
				if(!unico) {
					// Se o código de barras já tiver sido cadastrado
					System.out.println("O código de barras deve ser único. Por favor insira novamente.");
					continue;
				}
				return codigoDeBarras;
        	}
        	catch (Exception e) {
				System.out.println("Formato de entrada incorreto. Deve ser um inteiro. Ex: 19834923");
        	}
		}
	}

	private static String leInput(String text) {
		String result;

		// Imprime text e lê input string
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

	private int leCategoria() {
		// Imprime categorias
		int qtdCategorias = categorias.length;
		System.out.println("Categoria: ");
		for(int i=1;i<=qtdCategorias;i++) {
			System.out.println("\t"+i+") "+categorias[i-1]);
		}
		// Lê opção
		int opcao;
		opcao = leOpcao(qtdCategorias);
		return opcao-1;
	}

	private static int leOpcao(int numOpcoes) {
        int opcao = -1;

		// Lê entrada até inserir uma opção válida
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

	private static Float lePreco() {
		Float preco;

		// Lê entrada até inserir um preço válido
		while(true) {
        	try {
				System.out.print("Preço: ");
				preco = EntradaTeclado.leFloat();
				return preco;
        	}
        	catch (Exception e) {
				System.out.println("Formato de entrada incorreto. Deve ser um número. Ex: 1.99");
        	}
		}
	}
}
