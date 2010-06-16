import java.rmi.*;
import java.rmi.registry.*;
import java.net.*;
import java.util.Calendar;

public class RmiClient {

    static public void main(String args[])
    {
       ReceiveMessageInterface rmiServer;
       Registry registry;
       String serverAddress=args[0];
       String serverPort=args[1];
       String text=args[2];
       long t1,t2;
       System.out.println("sending "+text+" to "+serverAddress+":"+serverPort);
       try{
           // get the “registry”
           registry=LocateRegistry.getRegistry(
               serverAddress,
               (new Integer(serverPort)).intValue()
           );
           // look up the remote object
           rmiServer=
              (ReceiveMessageInterface)(registry.lookup("rmiServer"));
           
           //get Calendar instance
           Calendar now = Calendar.getInstance();
           /*
            * To get time in milliseconds, use
            * long getTimeInMillis() method of Java Calendar class.
            *
            * It returns millseconds from Jan 1, 1970.
            */
           t1 = System.nanoTime();
           System.out.println("Inicio: " + t1);
           // call the remote method
           rmiServer.receiveMessage(text);
           t2 = System.nanoTime();
           System.out.println("Fim: " + t2);
           
           System.out.println("Tempo demorado: " + (t2-t1) + "ns ou " + ((t2-t1)/1000) + "us");
       }
       catch(RemoteException e){
           e.printStackTrace();
       }
       catch(NotBoundException e){
           e.printStackTrace();
       }
    }
}
