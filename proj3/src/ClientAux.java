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
		
		return Integer.parseInt(in.readLine());

	}
	
	
	// método que seleciona a opção e realiza as chamadas ao servidor
	public static void makeRequest(RequestInterface servidor, int option) 
		throws RemoteException, SQLException {
		
		switch (option) {
		case LISTAR_TODOS_COMPLETO:
			List<Filme> filmes = servidor.getFullList();
			for(Filme f : filmes) {
				f.printFullInfo();
			}
			break;
		case LISTAR_TODOS:
			break;
		case REG_COMPLETO:
			break;
		case REG_SINOPSE:
			break;
		case REG_MEDIA:
			break;
		case REG_AVALIAR:
			break;
		}
		
	}


}
