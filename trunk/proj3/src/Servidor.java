import java.sql.SQLException;
import java.util.List;
import java.util.Scanner;


import bd.ConnectionFactory;
import bd.ConnectionTest;
import bd.Filme;


public class Servidor {

	public static void main(String[] args) throws SQLException {

		ConnectionFactory.caminhoAbsolutoBd = readDataBasePath();
		
		ConnectionTest teste = new ConnectionTest();
		List<Filme> lf = teste.getListaFilmes();
		
		for (Filme f : lf) {
			f.printFullInfo();
			System.out.println("  ---------------------------  ");
		}

		return;
	}

	private static String readDataBasePath() {
		System.out.println("Entre com o caminho absoluto para o arq do banco:");
		Scanner in = new Scanner(System.in);
		return in.nextLine();
	}

}