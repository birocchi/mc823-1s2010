package bd;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;

public class DataAccess {

	// Métodos usados pelo Servidor para acesso aos dados 
	
	
	public static List<Filme> getFullList() throws SQLException {

		// abre a conexão com o banco
		Connection con = ConnectionFactory.getConnection();
		
		String sql = "SELECT * FROM filme;";
		PreparedStatement stmt = con.prepareStatement(sql);
		ResultSet rs = stmt.executeQuery();

		List<Filme> listaFilmes = new ArrayList<Filme>();

		// popula a lista com o resultado da consulta
		while(rs.next()) {
			Filme f = new Filme();
			f.buildBeanByRs(rs);
			listaFilmes.add(f);
		}

		con.close();
		return listaFilmes;
	}

	public static List<Filme> getIdTitle() throws SQLException {
		
		// abre a conexão com o banco
		Connection con = ConnectionFactory.getConnection();
		
		String sql = "SELECT id, titulo FROM filme;";
		PreparedStatement stmt = con.prepareStatement(sql);
		ResultSet rs = stmt.executeQuery();

		List<Filme> listaFilmes = new ArrayList<Filme>();

		// popula a lista com o resultado da consulta
		while(rs.next()) {
			Filme f = new Filme();
			f.buildBeanByRs(rs);
			listaFilmes.add(f);
		}

		con.close();
		return listaFilmes;
	}

}
