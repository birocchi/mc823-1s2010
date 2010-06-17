import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.rmi.RemoteException;
import java.sql.SQLException;
import java.util.List;

import bd.Filme;


public class ClientAux {

	// --- Constantes ---
	static final int LISTAR_TODOS_COMPLETO = 1;
	static final int LISTAR_TODOS = 2;
	static final int REG_COMPLETO = 3;
	static final int REG_SINOPSE = 4;
	static final int REG_MEDIA = 5;
	static final int REG_AVALIAR = 6;
	static final int SAIR = 7;
	// --- Constantes ---
	
	
	// método auxiliar para interface e leitura da opção
	public static int readOption() throws IOException {
		
		// objeto para leitura
		BufferedReader in = new BufferedReader(new InputStreamReader(System.in));

		System.out.println("\n====================================================\n");
		System.out.println("Escolha uma entre as opções e tecle Enter:");
		System.out.println(" [1] Listar todas as informações de todos os filmes.");
		System.out.println(" [2] Listar id e título de todos os filmes.");
		System.out.println(" [3] Listar todas as informações de um filme.");
		System.out.println(" [4] Mostrar a sinopse de um filme.");
		System.out.println(" [5] Mostrar a avaliação de um filme.");
		System.out.println(" [6] Avaliar um filme!");
		System.out.println(" [7] Sair");
		
		// tenta fazer o parse da string digitada para inteiro. Se funcio-
		// nar, retorna o valor; caso contrário, chama novamente a função
		try {
			return Integer.parseInt(in.readLine());
		} catch (NumberFormatException e) {
			return readOption();
		}

	}

	// método para interface com o usuário e leitura de Id
	private static int readId() throws IOException {
		System.out.println("  Id procurado: ");
		BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
		try {
			return Integer.parseInt(in.readLine());
		} catch (NumberFormatException e) {
			return readOption();
		}
	}
	
	
	// método que seleciona a opção e realiza as chamadas ao servidor
	public static void makeRequest(RequestInterface servidor, int option) 
		throws SQLException, IOException, RemoteException {
		
		// variável para retorno das consultas
		List<Filme> listaFilmes;
		
		int idProcurado;
		
		// seleciona o que será executado a partir da opção de entrada
		switch (option) {
		case LISTAR_TODOS_COMPLETO:
			// faz a requisição de todos os filmes ao servidor
			listaFilmes = servidor.getFullList();
			// para cada filme na lista retornada, imprime as informações
			for(Filme f : listaFilmes) {
				f.printFullInfo();
			}
			break;
		case LISTAR_TODOS:
			listaFilmes = servidor.getFullList();
			for(Filme f : listaFilmes) {
				f.printIdNome();
			}
			break;
		case REG_COMPLETO:
			idProcurado = readId();
			// faz a requisição por um filme específico
			listaFilmes = servidor.getFilmeById(idProcurado);
			// o retorno da busca por um filme é uma lista, de modo
			// que é possível verificar se a mesma está vazia ou não
			if(listaFilmes.isEmpty()) System.out.println("  Filme não encontrado!");
			else listaFilmes.get(0).printFullInfo();
			break;
		case REG_SINOPSE:
			idProcurado = readId();
			listaFilmes = servidor.getFilmeById(idProcurado);
			if(listaFilmes.isEmpty()) System.out.println("  Filme não encontrado!");
			else listaFilmes.get(0).printSinopse();
			break;
		case REG_MEDIA:
			idProcurado = readId();
			listaFilmes = servidor.getFilmeById(idProcurado);
			if(listaFilmes.isEmpty()) System.out.println("  Filme não encontrado!");
			else listaFilmes.get(0).printNota();
			break;
		case REG_AVALIAR:
//			idProcurado = readId();
//			filme = servidor.getFilmeById(idProcurado);
//			filme.setNota();
			break;
		}
		
	}



}
