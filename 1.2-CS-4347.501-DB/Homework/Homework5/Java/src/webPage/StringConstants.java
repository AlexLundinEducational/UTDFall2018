package webPage;

// this design pattern allows all necessary classes to implement the string constants interface
// any class that implements StringConstants has access to the constant strings
// this ensures modularity

// Edit this file to allow project to build correctly with your workspace path

public interface StringConstants {
	
	// Java windows paths for Alex's machine #1
	public static final String jsFile = "C:\\Programs\\JavaEEWorkspace\\Homework5\\src\\webPage\\facts.js";
	public static final String xmlFile = "C:\\Programs\\JavaEEWorkspace\\Homework5\\WebContent\\WEB-INF\\facts.xml";
	
	// Java windows path for Webpage
	public static final String thisServlet = "http://localhost:8080/Homework5";
}
