package bd;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;

// esta classe é responsável por fazer a interface com o banco de dados
// aqui se encontram os comandos SQL responsáveis pelas consultas ao e 
// alterações no banco
public class DataAccess {

	// Métodos usados pelo Servidor para acesso aos dados	
	
	// retorna a lista de todos os filmes no banco
	public static List<Filme> getFullList() throws SQLException {
		
		long t1,t2;
		
		// inicia a contagem do tempo de consulta
    	t1 = System.nanoTime();
    	
		// abre a conexão com o banco
		Connection con = ConnectionFactory.getConnection();

		// preparo do comando sql de consulta
		String sql = "SELECT * FROM filme;";
		PreparedStatement stmt = con.prepareStatement(sql);
		ResultSet rs = stmt.executeQuery();

		List<Filme> listaFilmes = new ArrayList<Filme>();

		// popula a lista com o resultado da consulta
		while(rs.next()) {
			// instancia e popula o objeto filme
			Filme f = new Filme();
			f.buildBeanByRs(rs);
			// e o adiciona na lista
			listaFilmes.add(f);
		}

		stmt.close();
		con.close(); // fecha a conexão
		
		//termina a contagem do tempo de consulta
		t2 = System.nanoTime();
		System.err.println( ( (t2-t1)/1000 ) );
		
		return listaFilmes;
	}

	// consulta a filme a partir do seu ID:
	// retorna uma lista ou vazia ou com um único elemento
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

		stmt.close();
		con.close(); // fecha a conexão com o banco
		return listaFilmes;
	}


	// realiza a atualização da nota, retornando true se a operação for
	// bem-sucedida (ie, se o filme solicitado existe)
	public static boolean avaliaFilme(Integer idProcurado, Float novaNota)
		throws SQLException {

		// abre a conexão com o banco
		Connection con = ConnectionFactory.getConnection();
		
		// preparo do comando sql de consulta
		String sql = "SELECT * FROM filme WHERE id=?;";
		PreparedStatement stmt = con.prepareStatement(sql);
		stmt.setInt(1, idProcurado);
		ResultSet rs = stmt.executeQuery();
		
		// se não houver nenhum elemento na consulta, termina
		if(!rs.next()) {
			stmt.close();
			con.close();
			return false;
		}

		// lê a nota e o n de aval atuais
		float nota = rs.getFloat("nota");
		int n_avaliacoes = rs.getInt("n_avaliacoes");
		
		// faz a média ponderada das notas que já foram dadas
		nota = ((nota * n_avaliacoes) + novaNota) / (n_avaliacoes + 1);
		n_avaliacoes++;
		
		// preparo do comando sql de atualização
		sql = "UPDATE filme SET nota=?, n_avaliacoes=? WHERE id=?";
		stmt = con.prepareStatement(sql);
		stmt.setFloat(1, nota);
		stmt.setInt(2, n_avaliacoes);
		stmt.setInt(3, idProcurado);
		stmt.execute(); // executa a operação
		
		stmt.close();
		con.close(); // fecha a conexão com o banco

		return true;
	}

}
