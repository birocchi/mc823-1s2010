package bd;

import java.io.Serializable;
import java.sql.ResultSet;
import java.sql.SQLException;

@SuppressWarnings("serial")
public class Filme implements Serializable {

	private int id;
	private int n_avaliacoes;
	private float nota;
	private String titulo;
	private String sinopse;
	
	public void setId(int id) {
		this.id = id;
	}
	public int getId() {
		return id;
	}
	public void setN_avaliacoes(int n_avaliacoes) {
		this.n_avaliacoes = n_avaliacoes;
	}
	public int getN_avaliacoes() {
		return n_avaliacoes;
	}
	public void setNota(float nota) {
		this.nota = nota;
	}
	public float getNota() {
		return nota;
	}
	public void setTitulo(String titulo) {
		this.titulo = titulo;
	}
	public String getTitulo() {
		return titulo;
	}
	public void setSinopse(String sinopse) {
		this.sinopse = sinopse;
	}
	public String getSinopse() {
		return sinopse;
	}


	public void buildBeanByRs(ResultSet rs) throws SQLException {
		this.id = rs.getInt("id");
		this.n_avaliacoes = rs.getInt("n_avaliacoes");
		this.nota = rs.getFloat("nota");
		this.titulo = rs.getString("titulo");
		this.sinopse = rs.getString("sinopse");
		return;
	}
	
	public void printFullInfo() {
		System.out.println("  Id: " + id + " | Título: " + titulo);
		System.out.println("  Sinopse: " + sinopse);
		String aval = (n_avaliacoes > 1) ? "avaliações" : "avaliação";
		if (n_avaliacoes != 0) {
			System.out.println("  Nota: " + nota + " (a partir de " + n_avaliacoes + aval + ")");
		}
		return;
	}
	
	public void printIdNome() {
		System.out.println("  Id: " + id + " | Título: " + titulo);
		return;
	}

	public void printSinopse() {
		System.out.println("  Sinopse: " + sinopse);
	}

	public void printNota() {
		String aval = (n_avaliacoes > 1) ? "avaliações" : "avaliação";
		if (n_avaliacoes != 0) {
			System.out.println("  Nota: " + nota + " (a partir de " + n_avaliacoes + aval + ")");
		}
		return;
	}
	
}
