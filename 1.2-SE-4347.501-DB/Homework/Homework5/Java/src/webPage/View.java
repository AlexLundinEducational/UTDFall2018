package webPage;

import java.awt.Container;
import java.awt.Dimension;
import java.awt.Insets;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JButton;
import javax.swing.JFrame;




import java.awt.Container;
import java.awt.Insets;
import java.awt.Dimension;

import javax.swing.JButton;
import javax.swing.JFrame;

/*MVC Notes:
https://www.tomdalling.com/blog/software-design/model-view-controller-explained/
	Summary:
	Model View and Controller work best when separated
	Model		- holds data
	View		- loads data independently of the Model
	Controller	- provides model data to view, also performs operations on the data
	
	
https://code.tutsplus.com/tutorials/mvc-for-noobs--net-10488
*/

public class View {

	// attributes
	static final long serialVersionUID = 0L;	
    private View currentView;
   
 // constructors
    /*	   View(){
    System.out.println("\nView constructor");

    }*/
    // getters

    private void getView(){
    }
    // setters
    protected static void setFactField(Fact f){
    	String tempString = f.getText();
    	MVCWrapper.factField.setText(tempString);
    	
    }

    private void setView(){
    }

   

}
