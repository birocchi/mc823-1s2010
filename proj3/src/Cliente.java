import java.io.IOException;
import java.rmi.RemoteException;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.sql.SQLException;


public class Cliente {

	// número da porta que o servidor usará
	private static final int serverPort = 50000;
	
	// constantes para a seção de teste
	private static final boolean TEST = false;
	private static final int DEFAULT_OPT = ClientAux.LISTAR_TODOS_COMPLETO;
	private static final int TEST_ITERATIONS = 100;
	
	
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
    	long t1,t2;
    	
    	// faz a contagem do tempo de RTT
    	t1 = System.nanoTime();
    	// notifica o servidor da conexão
    	servidor.sayHello();  
		t2 = System.nanoTime();
		System.err.println( ( (t2-t1)/1000 ) );
    	
    	int option;
    	
    	// loop principal do cliente
		if(!TEST) {
	    	option = ClientAux.readOption();
		}
    	// [início] Seção de teste
    	// tivemos dificuldade em gerar um script para a automação do teste 
    	// de sucessivas consultas. Desconsiderar esta seção
		else {
    		option = DEFAULT_OPT;
    		for(int i = 0; i < TEST_ITERATIONS; i++) {
        		ClientAux.makeRequest(servidor, option);
    		}
    		option = ClientAux.SAIR;
    	}
    	// [fim] Seção de teste
    	
    	while(option != ClientAux.SAIR) {
    		try {
        		ClientAux.makeRequest(servidor, option);
    		} catch(RemoteException e) {
        		System.out.println("Servidor não disponível.");
        		System.exit(1);
    		} catch(Exception e) {
    			System.out.println("Algum erro ocorreu no servidor.");
        		System.exit(1);
    		}
    		
    		option = ClientAux.readOption();
    	}

    	return; // main cliente

    }

    	
}
