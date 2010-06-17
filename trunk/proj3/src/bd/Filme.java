package bd;

import java.io.Serializable;
import java.sql.ResultSet;
import java.sql.SQLException;

@SuppressWarnings("serial")
public class Filme implements Serializable {

	// atributos do filme
	private int id;
	private int n_avaliacoes;
	private float nota;
	private String titulo;
	private String sinopse;
	private String salas;
	
	// método público para recurar id de um filme
	public int getId() {
		return id;
	}
	

	// método de população do objeto que representa um registro (bean)
	// a partir do ResultSet retornado da consulta SQL
	public void buildBeanByRs(ResultSet rs) throws SQLException {
		this.id = rs.getInt("id");
		this.n_avaliacoes = rs.getInt("n_avaliacoes");
		this.nota = rs.getFloat("nota");
		this.titulo = rs.getString("titulo");
		this.sinopse = rs.getString("sinopse");
		this.salas = rs.getString("salas");
		return;
	}
	
	// métodos de impressão das informações de um filme
	public void printFullInfo() {
		System.out.println("  Id: " + getId() + " | Título: " + titulo);
		System.out.println("  Sinopse: " + sinopse);
		System.out.println("  Salas: " + salas);
		if (n_avaliacoes != 0) {
			// aval recebe 'avaliação' (exatamente UMA) ou 'avaliações' (>1)
			String aval = (n_avaliacoes > 1) ? "avaliações" : "avaliação";
			System.out.println("  Nota: " + nota + " (a partir de " + 
					n_avaliacoes + " " + aval + ")");
		} else {
			System.out.println("  Ainda não há avaliações para este filme.");
		}
		System.out.println("___");
		return;
	}
	public void printIdNome() {
		System.out.println("  Id: " + getId() + " | Título: " + titulo + "\n___");
		return;
	}
	public void printSinopse() {
		System.out.println("  Sinopse: " + sinopse);
	}
	public void printNota() {
		if (n_avaliacoes != 0) {
			String aval = (n_avaliacoes > 1) ? "avaliações" : "avaliação";
			System.out.println("  Nota: " + nota + " (a partir de " + 
					n_avaliacoes + " " + aval + ")");
		} else {
			System.out.println("  Ainda não há avaliações para este filme.");
		}
		return;
	}


}
