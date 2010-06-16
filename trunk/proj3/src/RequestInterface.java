import java.rmi.Remote;

public interface RequestInterface extends Remote {
	RMIResponse executeRequest(RMIRequest request);
}
