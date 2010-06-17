import java.rmi.Remote;
import java.rmi.RemoteException;
import java.sql.SQLException;
import java.util.List;

import bd.Filme;

// esta é a interface que define os métodos remotos 
// implementados pelo servidor 
public interface RequestInterface extends Remote {
	
	// Notificar que alguem se conectou no servidor
	// Método "leve", isto é, sem parâmetros nem retorno. É usado para encontrar 
	// o tempo de comunicação base do RMI, isto é, o tempo para chamada de método
	void sayHello() throws RemoteException;
	
	//Retornar a lista completa de todos os filmes
	List<Filme> getFullList() throws RemoteException, SQLException;
	
	//Retornar uma lista, que pode ser vazia se não encontrou o elemento, ou ter 
	// 1 elemento caso contrario
	List<Filme> getFilmeById(Integer idProcurado) throws 
		RemoteException, SQLException;
	
	//Receber uma avaliação e atualizar a nota do filme
	Boolean avaliaFilme(Integer idFilme, Float novaNota) throws 
		RemoteException, SQLException;
	
}
