
public class ClientAux {

	// --- Constantes ---
	static final int LISTAR_TODOS_COMPLETO = 1;
	static final int LISTAR_TODOS = 2;
	static final int REG_COMPLETO = 3;
	static final int REG_SINOPSE = 4;
	static final int REG_MEDIA = 5;
	static final int REG_AVALIAR = 6;
	static final int SAIR = 7;
	// --- Constantes ---
	
	
	// método auxiliar para interface e leitura da opção
	public static int readOption() {
		// TODO Auto-generated method stub
		return 1;
	}
	
	
	// método que seleciona a opção e realiza as chamadas ao servidor
	public static void makeRequest(RequestInterface servidor, int option) {
		
		switch (option) {
		case LISTAR_TODOS_COMPLETO:
			break;
		case LISTAR_TODOS:
			break;
		case REG_COMPLETO:
			break;
		case REG_SINOPSE:
			break;
		case REG_MEDIA:
			break;
		case REG_AVALIAR:
			break;

		}
		
	}


}
