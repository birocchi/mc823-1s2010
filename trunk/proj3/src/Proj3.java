import java.sql.SQLException;
import java.util.List;

import bd.ConnectionTest;
import bd.Filme;


public class Proj3 {

	public static void main(String[] args) throws SQLException {

		ConnectionTest teste = new ConnectionTest();
		List<Filme> lf = teste.getListaFilmes();
		
		for (Filme f : lf) {
			f.printFullInfo();
			System.out.println("  ---------------------------  ");
		}
		
		return;
	}

}
