import java.rmi.RemoteException;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.rmi.server.UnicastRemoteObject;
import java.sql.SQLException;
import java.util.List;

import bd.ConnectionFactory;
import bd.DataAccess;
import bd.Filme;


@SuppressWarnings("serial")
public class Servidor extends UnicastRemoteObject 
	implements RequestInterface {

	private static int port = 3232;
	private Registry registry;

	// ========== Construtor ==========
	public Servidor() throws RemoteException {

		// cria o registry na porta especificada
		registry = LocateRegistry.createRegistry(port);
		// faz o bind para o nome do objeto
		registry.rebind("servidor", this);
		
		System.out.println("Aguardando requisições...");
		
		return;
	}
	
	// ========== Main ==========
	public static void main(String[] args) throws SQLException {

		// o servidor é executado com o caminho do arquivo do
		// BD como primeiro e único parâmetro
		ConnectionFactory.caminhoAbsolutoBd = args[0];

		try {
			@SuppressWarnings("unused")
			Servidor s = new Servidor();
		} catch (Exception e) {
			e.printStackTrace();
			System.exit(1);
		}
	
		return;
	}
	
	
	// ========== Métodos remotos que o servidor implementa ==========
//	public RMIResponse executeRequest(RMIRequest request) {
//		System.out.println("Oi, eu sou o servidor, com o método sendo chamado pelo cliente! :)");
//		return null;
//	}

	public void sayHello() {
		System.out.println("Algum cliente se conectou.");
	}

	public List<Filme> getFullList() throws RemoteException, SQLException {
		System.out.println(" getFullList()");
		return DataAccess.getFullList();
	}
	
	public List<Filme> getIdTitle() throws RemoteException, SQLException {
		System.out.println(" getIdTitle()");
		return DataAccess.getIdTitle();
	}

	@Override
	public Filme getFilmeById(int idProcurado) {
		// TODO Auto-generated method stub
		return null;
	}
	
//	public List<Filme> getFullList() throws RemoteException, SQLException {
//		System.out.println(" getInformation()");
//		return DataAccess.getInformation();
//	}
//	
//	public List<Filme> getFullList() throws RemoteException, SQLException {
//		System.out.println(" getSinopse()");
//		return DataAccess.getSinopse();
//	}
//	
//	public List<Filme> getFullList() throws RemoteException, SQLException {
//		System.out.println(" getEvaluation()");
//		return DataAccess.getEvaluation();
//	}
//	
//	public List<Filme> getFullList() throws RemoteException, SQLException {
//		System.out.println(" evaluate()");
//		return DataAccess.evaluate();
//	}

}