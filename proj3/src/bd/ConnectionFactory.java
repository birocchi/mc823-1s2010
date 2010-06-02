package bd;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;

public class ConnectionFactory {
	
	public static Connection getConnection() throws SQLException {

		Connection con = null;

		try {
			Class.forName("org.sqlite.JDBC");
			con =  DriverManager.getConnection("jdbc:sqlite:./filmes.db");
		} catch (ClassNotFoundException e) {
			e.printStackTrace();
		}

		return con;
		
	}

}
