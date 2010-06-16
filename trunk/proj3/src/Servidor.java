import java.rmi.RemoteException;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.rmi.server.UnicastRemoteObject;
import java.sql.SQLException;

import bd.ConnectionFactory;


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
		System.out.println("Hello! :)");
	}

}