import java.io.IOException;
import java.rmi.RemoteException;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.sql.SQLException;


public class Cliente {

	private static final int serverPort = 3232;
	
    static public void main(String args[]) throws IOException, SQLException {

    	// o cliente tem acesso à interface para o objeto remoto
		RequestInterface servidor = null;
    	Registry registry;
    	
    	// endereço é passado como argumento
    	String serverAddress = args[0];

    	// estabelece comunicação com o objeto remoto
    	try {
        	// recebe o "registry" pelo endereço e porta
        	registry = LocateRegistry.getRegistry(serverAddress, serverPort);
        	// busca pelo objeto remoto
        	servidor = (RequestInterface) registry.lookup("servidor");
    	} 

    	// tratamento das possíveis exceções
    	catch(RemoteException e) {
    		System.err.println("Não foi possível localizar o objeto remoto.");
    		//e.printStackTrace();
    		System.out.println("Servidor não disponível.");
    		System.exit(1);
    	} catch(Exception e) {
    		e.printStackTrace();
    		System.exit(1);
    	}
    	
    	
    	// a partir daqui, se o cliente conseguiu encontrar o objeto remoto,
    	// então pode-se realizar as chamadas para os métodos remotos
    	servidor.sayHello();
    	
    	// loop principal do cliente
    	int option = ClientAux.readOption();
    	while(option != ClientAux.SAIR) {
    		try {
        		ClientAux.makeRequest(servidor, option);
    		} catch(RemoteException e) {
        		System.out.println("Servidor não disponível.");
        		System.exit(1);
    		}
    		option = ClientAux.readOption();
    	}

    	return; // main cliente

    }

    	
}
