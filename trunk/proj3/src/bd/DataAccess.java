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

		// preparo do comando sql de consulta
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
		
		// preparo do comando sql de consulta
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

		con.close(); // fecha a conexão com o banco
		return listaFilmes;
	}

	
	public static List<Filme> getFilmeById(Integer idProcurado) throws SQLException {

		// abre a conexão com o banco
		Connection con = ConnectionFactory.getConnection();
		
		// preparo do comando sql de consulta
		String sql = "SELECT * FROM filme WHERE id=?;";
		PreparedStatement stmt = con.prepareStatement(sql);
		stmt.setInt(1, idProcurado);
		ResultSet rs = stmt.executeQuery();

		List<Filme> listaFilmes = new ArrayList<Filme>();

		// se houver algum filme com o id procurado, insere-o na lista
		if(rs.next()) {
			Filme f = new Filme();
			f.buildBeanByRs(rs);
			listaFilmes.add(f);
		}

		con.close(); // fecha a conexão com o banco
		return listaFilmes;
	}

}
