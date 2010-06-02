package bd;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;

public class ConnectionTest {

	private Connection con;
	
	// construtor: conecta com o banco
	public ConnectionTest() throws SQLException {
		this.con = ConnectionFactory.getConnection();
	}
	
	public void closeConnection() throws SQLException {
		this.con.close();
		return;
	}

	public List<Filme> getListaFilmes() throws SQLException {

		String sql = "SELECT * FROM filme;";
        PreparedStatement stmt = this.con.prepareStatement(sql);
        ResultSet rs = stmt.executeQuery();
        
        List<Filme> listaFilmes = new ArrayList<Filme>();
        
        // popula a lista com o resultado da consulta
        while(rs.next()) {
        	Filme f = new Filme();
        	f.buildBeanByRs(rs);
        	listaFilmes.add(f);
        }

        return listaFilmes;
	}
	
}
