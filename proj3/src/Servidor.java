import java.net.InetAddress;
import java.rmi.RemoteException;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.sql.SQLException;

import bd.ConnectionFactory;


public class Servidor implements RequestInterface {

	@SuppressWarnings("unused")
	private String address;
	private int port;
	private Registry registry;  // registry para procura do objeto remoto

	public Servidor() throws RemoteException {

		// instancia o endereço
		try {
			address = InetAddress.getLocalHost().toString();
		} catch (Exception e) {
			throw new RemoteException("Não conseguiu pegar o próprio endereço.");
		}
		
		// instancia a porta
		port = 3232;
		
		// cria o registry, fazendo o "bind" para o nome do objeto
		registry = LocateRegistry.createRegistry(port);
		registry.rebind("servidor", this);

	}
	
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

	public RMIResponse executeRequest(RMIRequest request) {
		System.out.println("Oi, eu sou o servidor, com o método sendo chamado pelo cliente! :)");
		return null;
	}

}