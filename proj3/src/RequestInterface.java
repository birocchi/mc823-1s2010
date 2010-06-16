import java.rmi.Remote;
import java.rmi.RemoteException;
import java.sql.SQLException;
import java.util.List;

import bd.Filme;

public interface RequestInterface extends Remote {

	void sayHello() throws RemoteException;
	List<Filme> getFullList() throws RemoteException, SQLException;
	Filme getFilmeById(int idProcurado);
	//List<Filme> setNota(int id, int nota) throws RemoteException, SQLException;
	
}
