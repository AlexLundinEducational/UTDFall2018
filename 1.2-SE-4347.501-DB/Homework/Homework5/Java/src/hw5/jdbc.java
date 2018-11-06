package hw5;


import java.sql.DriverManager;
import java.sql.Connection;
import java.sql.SQLException;

// https://www.mkyong.com/jdbc/connect-to-oracle-db-via-jdbc-driver-java/

public class jdbc {

    public static void main(String[] argv) {

        System.out.println("-------- Oracle JDBC Connection Testing ------");

        try {

            Class.forName("oracle.jdbc.driver.OracleDriver");

        } catch (ClassNotFoundException e) {

            System.out.println("Where is your Oracle JDBC Driver?");
            e.printStackTrace();
            return;

        }

        System.out.println("Oracle JDBC Driver Registered!");

        Connection connection = null;
        
        // connection info
        String hostName = "localhost";
        String port = "1521";
        String sid = "orcl";
        String username = "CS4347F18";
        String password = "a1";
        try {

            connection = DriverManager.getConnection(
                    "jdbc:oracle:thin:@"+ hostName +":"+ port +":"+ sid, username, password);

        } catch (SQLException e) {

            System.out.println("Connection Failed! Check output console");
            e.printStackTrace();
            return;

        }

        if (connection != null) {
            System.out.println("You made it, take control your database now!");
        } else {
            System.out.println("Failed to make connection!");
        }
    }

}

