import java.rmi.Remote;
import java.rmi.RemoteException;
import java.sql.SQLException;
import java.util.List;

import bd.Filme;

public interface RequestInterface extends Remote {
	//RMIResponse executeRequest(RMIRequest request);
	void sayHello() throws RemoteException;
	List<Filme> getFullList() throws RemoteException, SQLException;;
}
