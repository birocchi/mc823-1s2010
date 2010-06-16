import java.rmi.Remote;
import java.rmi.RemoteException;

public interface RequestInterface extends Remote {
	//RMIResponse executeRequest(RMIRequest request);
	void sayHello() throws RemoteException;
}
