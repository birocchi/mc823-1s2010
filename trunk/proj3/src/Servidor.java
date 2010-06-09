import java.sql.SQLException;
import java.util.List;


import bd.ConnectionFactory;
import bd.ConnectionTest;
import bd.Filme;


public class Servidor {

	public static void main(String[] args) throws SQLException {

		// o servidor é executado com o caminho do arquivo do 
		// BD como primeiro e único parâmetro
		ConnectionFactory.caminhoAbsolutoBd = args[0];
		
		ConnectionTest teste = new ConnectionTest();
		List<Filme> lf = teste.getListaFilmes();
		
		for (Filme f : lf) {
			f.printFullInfo();
			System.out.println("  ---------------------------  ");
		}

		return;
	}

}