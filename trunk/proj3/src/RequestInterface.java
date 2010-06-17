import java.rmi.Remote;
import java.rmi.RemoteException;
import java.sql.SQLException;
import java.util.List;

import bd.Filme;

public interface RequestInterface extends Remote {

	void sayHello() throws RemoteException;
	List<Filme> getFullList() throws RemoteException, SQLException;
	List<Filme> getFilmeById(Integer idProcurado) throws RemoteException, SQLException;
	Boolean avaliaFilme(Integer idFilme, Float novaNota) throws RemoteException, SQLException;
	
}
